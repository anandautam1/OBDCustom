/* ===============================================================================
// Includes
================================================================================*/

#include "stm32f10x_it.h"
#include "RCCController.h"
#include "GPIOController.h"
#include "utility.h"
#include "canRegisters.h"
#include "canController.h"
#include "DispCode.h"

//#include <iostream>
#include <string>

#define IDRX0 0x0BADCAFE
//#define IDRX0 0x01A4F2B
#define IDRX1 0x0024FCE

#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

CAN_msg  CAN_TxMsg, CAN_RxMsg;

/* ===============================================================================
// Definitions
================================================================================*/
//#define LAB_HARDWARE 	// Defined in utility.h

/* ===============================================================================
// Function Prototypes
================================================================================*/

unsigned int readRegister(volatile unsigned int * iregisterAddress);
void writeRegister(volatile unsigned int * iregisterAddress, unsigned int idataPacket);

void configureAdc();
int readAdc();

void CAN_wrFilter (unsigned int id, unsigned char format, unsigned char mess_type);

void initializeLabSpecs();
void initFilter();

void txCAN(CAN_msg *finalMessage);
void canTransmissionUniversal(CAN_msg *finalmessage, int mailboxNo);
int checkTxMailbox();

void rxCAN(CAN_msg *msg);
void fifoHandler(void);


typedef union{
	int integer;
	unsigned char bytes[4];
}RESULT;

void toggle_led(int LED);

/* ===============================================================================
// Main
================================================================================*/
int main(void)
{
	// Wakeup switch on portA pin 0
	GPIO_Config Pin_A[1];
	Pin_A->Port = GPIO_A;
	Pin_A->Pin = Pin0;
	Pin_A->Type = GPIO_Input_Floating;
	Pin_A->Speed = GPIO_50MHz;
	
	// User switch on portB pin 7 
	GPIO_Config Pin_B[1];
	Pin_B->Port = GPIO_B;
	Pin_B->Pin = Pin7;
	Pin_B->Type = GPIO_Input_PullUpDown;
	Pin_B->Speed = GPIO_50MHz;
	
	// ADC reading on Port C pin 4 
	GPIO_Config Pin_C4[1];
	Pin_C4->Port = GPIO_C;
	Pin_C4->Pin = Pin4;
	Pin_C4->Type = GPIO_Output_PushPull;
	Pin_C4->Speed = GPIO_Reserved;
	
	// LED Output mode on portE pin 8 and 9 
	GPIO_Config Pin_E8[1];
	Pin_E8->Port = GPIO_E;
	Pin_E8->Pin = Pin8;
	Pin_E8->Type = GPIO_Output_PushPull;
	Pin_E8->Speed = GPIO_50MHz;

	GPIO_Config Pin_E9[1];
	Pin_E9->Port = GPIO_E;
	Pin_E9->Pin = Pin9;
	Pin_E9->Type = GPIO_Output_PushPull;
	Pin_E9->Speed = GPIO_50MHz;
	
	// Create an instance of the RCC Controller.
	RCCController RCCControl[1];
		
	// Create an instance of the GPIO Controller and link the RCC Controller to it.
	GPIOController GPIOControl[1] = {RCCControl};

	GPIOControl->configureGPIO(Pin_A);
	GPIOControl->setGPIO(Pin_A->Port, Pin_A->Pin);
	
	GPIOControl->configureGPIO(Pin_B);
	GPIOControl->setGPIO(Pin_B->Port, Pin_B->Pin);	

	GPIOControl->configureGPIO(Pin_C4);
	GPIOControl->setGPIO(Pin_C4->Port, Pin_C4->Pin);
	
	GPIOControl->configureGPIO(Pin_E8);
	GPIOControl->setGPIO(Pin_E8->Port, Pin_E8->Pin);	
	GPIOControl->configureGPIO(Pin_E9);
	GPIOControl->setGPIO(Pin_E9->Port, Pin_E9->Pin);
	
	// enable can bus and also the clock 
	// checked the enable clock for CAN1 
	// checked the enable clock for AF
	// checked the enable clock for GPIO D 
	// checked the can1_REMAP to be on 0x03 for PD0 & PD1
	GPIOControl->enablePeripheral(PER_CAN1,REMAP0);
	initializeLabSpecs();
	initFilter();
	
	configureAdc();

	unsigned char led8Data[4] = {0x01};
	CAN_msg led8Message[1];
	led8Message->id = 0x01AEFCA;
	for (int i = 0; i < 1; i++) 
	{led8Message->data[i] = led8Data[i];}
	led8Message->len = 1;
	led8Message->format = EXTENDED_IDENTIFIER;
	led8Message->type = DATA_FRAME;
	
	unsigned char led9Data[4] = {0x01};
	CAN_msg led9Message[1];
	led9Message->id = 0x002BEF;
	for (int i = 0; i < 1; i++) 
	{led9Message->data[i] = led9Data[i];}
	led9Message->len = 1;
	led9Message->format = EXTENDED_IDENTIFIER;
	led9Message->type = DATA_FRAME;
	
	// CAN Setup
	//canInit(); // OLD implementation 
	
	// LCD Code
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_DisplayString(1, 1, (unsigned char*)"Lab 3: CAN BUS");
	GLCD_DisplayString(2, 1, (unsigned char*)"ADC Value:");
	
	// enable interrupt 
	//initializeCanFilters();
	//NVIC->ISER[0] |= (1 << 20);       // enable CAN1_Rx interrupt
	
  // Main loop
  while (1)
  {
		int result = readAdc();
		//char AdcLabel[10] = "ADC value = "
		char resultChars[20]; 
		std::sprintf(resultChars,"%i  ", result);
		GLCD_DisplayString(3, 1, (unsigned char*)resultChars);
		
		// Read User Button
		if (!(GPIOControl->getPinValue(Pin_B->Port, Pin_B->Pin)))
		{
			 txCAN(led8Message);
			// DEBUG
			 GPIOControl->setGPIO(Pin_E8->Port,Pin_E8->Pin);
		}
		else
		{
			// DEBUG 
			 GPIOControl->resetGPIO(Pin_E8->Port,Pin_E8->Pin);
		}
		
		// Read Wakeup Button
		if ((GPIOControl->getPinValue(Pin_A->Port, Pin_A->Pin)))
		{
			 txCAN(led9Message);
			// DEBUG
			 GPIOControl->setGPIO(Pin_E9->Port,Pin_E9->Pin);
		}
		else
		{
			// DEBUG 
			 GPIOControl->resetGPIO(Pin_E9->Port,Pin_E9->Pin);
		}
		// deafult is to send the adc value of the trimpot regardless 
		
		RESULT adcData;
		adcData.integer = result;
		
		// if data 0E34
		// on graph its 340E but read 0E34
		
		CAN_msg adcMessage[4];
		adcMessage->id = 0x0BADCAFE;
		for (int i = 0; i < 4; i++) 
		{adcMessage->data[i] = adcData.bytes[i];}
		adcMessage->len = 4;
		adcMessage->format = EXTENDED_IDENTIFIER;
		adcMessage->type = DATA_FRAME;
		
		txCAN(adcMessage);
		
		delay_software_ms(10);	// TODO - This might not be needed
		
		// Read CAN Message
		// Check if FIFO has a message
		CAN_RFxR rCAN1_RF0R;
		rCAN1_RF0R.d32 = readRegister(RCAN1_RF0R);
		
		if (rCAN1_RF0R.b.bfmp > 0)
		{
			CAN_msg rx_msg;
			
			rxCAN(&rx_msg);
			fifoHandler();
		}
		
		// needed for the 5Hz update rate 
		// default was 180
		delay_software_ms(60);
  }
} 

/* ===============================================================================
// Function Definitions
================================================================================*/

unsigned int readRegister(volatile unsigned int * iregisterAddress){
	return (*iregisterAddress);
}
void writeRegister(volatile unsigned int * iregisterAddress, unsigned int idataPacket){
	*iregisterAddress = idataPacket;
}

//void CAN_wrFilter (unsigned int id, unsigned char format, unsigned char mess_type)  
//{
//	
//	static unsigned short CAN_filterIdx = 0;
//         unsigned int   CAN_msgId     = 0;
//	
//	if (CAN_filterIdx > 13) {                       // check if Filter Memory is full
//    return;
//  }
//	
//  // Setup identifier information
//  if (format == STANDARD_FORMAT)  {               // Standard ID
//      CAN_msgId  |= (unsigned int)(id << 21) | 0; //CAN_ID_STD;
//  }  else  {                                      // Extended ID
//      CAN_msgId  |= (unsigned int)(id <<  3) | 4; //CAN_ID_EXT;
//  }
//  if (mess_type == 1)	CAN_msgId  |= 2;

//	CAN_FA1R rCAN1_FA1R;
//	rCAN1_FA1R.d32 = readRegister(RCAN1_FA1R);
//	rCAN1_FA1R.d32 &= ~(unsigned int) (1 << CAN_filterIdx);
//	writeRegister(RCAN1_FA1R, rCAN1_FA1R.d32);
//	
//  // initialize filter
//	// set 32-bit scale configuration
//	CAN_FS1R rCAN1_FS1R;
//	rCAN1_FS1R.d32 = readRegister(RCAN1_FS1R);
//	rCAN1_FS1R.d32 |= (unsigned int) (1 << CAN_filterIdx);
//	writeRegister(RCAN1_FS1R, rCAN1_FS1R.d32);
//	
//	// set 2 32-bit identifier list mode
//	CAN_FM1R rCAN1_FM1R;
//	rCAN1_FM1R.d32 = readRegister(RCAN1_FM1R);
//	rCAN1_FM1R.d32 |= (unsigned int)(1 << CAN_filterIdx);
//  writeRegister(RCAN1_FM1R, rCAN1_FM1R.d32);

//	// not sure on how to use the classes for the array register access on the register better best to leave it 
//  CAN1->sFilterRegister[CAN_filterIdx].FR1 = CAN_msgId; //  32-bit identifier
//  CAN1->sFilterRegister[CAN_filterIdx].FR2 = CAN_msgId; //  32-bit identifier
//    													   
//	// assign filter to FIFO 0
//	CAN_FFA1R rCAN1_FFA1R;
//	rCAN1_FFA1R.d32 = readRegister(RCAN1_FFA1R);
//	rCAN1_FFA1R.d32 &= ~(unsigned int)(1 << CAN_filterIdx); 
//	writeRegister(RCAN1_FFA1R, rCAN1_FFA1R.d32);
//	
//	// activate filter
//	rCAN1_FA1R.d32 = readRegister(RCAN1_FA1R);
//	rCAN1_FA1R.d32 |=  (unsigned int)(1 << CAN_filterIdx);
//	writeRegister(RCAN1_FA1R, rCAN1_FA1R.d32);
//  
//	// increment the static variable for any instanceof a new filter 
//  CAN_filterIdx += 1; 
//}

void rxCAN ( CAN_msg *msg)  
{
	CAN_RIxR rCAN1_RI0R;
	rCAN1_RI0R.d32 = readRegister(RCAN1_RI0R);

	msg->format = rCAN1_RI0R.b.bide;
	msg->type 	= rCAN1_RI0R.b.brtr;
	
	// Check identifier
	if (msg->format == 1)
	{
		// Extended Identifier
		msg->id 		= (unsigned int) 0x1FFFFFFF & (rCAN1_RI0R.d32 >> 3);	
	}
	else
	{
		// Standard Identifier
		msg->id 		= (unsigned int) 0x000007FF & (rCAN1_RI0R.d32 >> 21);
	}
	
	// Check length identifier 
	CAN_RDTxR rCAN1_RDT0R;
	rCAN1_RDT0R.d32 = readRegister(RCAN1_RDT0R);
	msg->len = rCAN1_RDT0R.b.bdlc; 
	
	// Read data low register
	CAN_TDLxR rCAN1_RDLR;
	rCAN1_RDLR.d32 = readRegister(RCAN1_TDL0R);
	
	// Read data high register
	CAN_TDHxR rCAN1_RDHR;
	rCAN1_RDHR.d32 = readRegister(RCAN1_TDH0R);

	// Read in data
	msg->data[0] = (unsigned int) 0x000000FF & (rCAN1_RDLR.d32);
	msg->data[1] = (unsigned int) 0x000000FF & (rCAN1_RDLR.d32 >> 8);
	msg->data[2] = (unsigned int) 0x000000FF & (rCAN1_RDLR.d32 >> 16);
	msg->data[3] = (unsigned int) 0x000000FF & (rCAN1_RDLR.d32 >> 24);

	msg->data[4] = (unsigned int) 0x000000FF & (rCAN1_RDHR.d32);
	msg->data[5] = (unsigned int) 0x000000FF & (rCAN1_RDHR.d32 >> 8);
	msg->data[6] = (unsigned int) 0x000000FF & (rCAN1_RDHR.d32 >> 16);
	msg->data[7] = (unsigned int) 0x000000FF & (rCAN1_RDHR.d32 >> 24);
}

void fifoHandler(void)
{
	// Release FIFO 
	CAN_RFxR rCAN1_RF0R;
	rCAN1_RF0R.d32 = readRegister(RCAN1_RF0R);
	rCAN1_RF0R.b.bfull = 0;		// Clear FIFO FULL flag
	rCAN1_RF0R.b.brfom = 1;		// Release Mailbox
	rCAN1_RF0R.b.bfovr = 0;  	// Clear overflow 
	writeRegister(RCAN1_RF0R, rCAN1_RF0R.d32);
}

//CAN1 receiver interrupt
void CAN1_RX0_IRQHandler(void) {
 GPIOE->BSRR = 1<<10;   //LED ON for observation on MSO  
 if (CAN1->RF0R & 3) {			      // message pending ?
   rxCAN (&CAN_RxMsg);                       // read the message
	 CAN1->RF0R |= 0x20;                    // Release FIFO 0 output mailbox 
   //   CAN_RxRdy = 1;                                // set receive flag
	 
	 GLCD_DisplayString(5, 1, (unsigned char*)"CAN message address: ");
	 GLCD_DisplayString(6, 1, (unsigned char*)CAN_RxMsg.id);
	 GLCD_DisplayString(7, 1, (unsigned char*)"CAN message data: ");
	 GLCD_DisplayString(8, 1, (unsigned char*)CAN_RxMsg.data);
	 
	 GPIOE->BSRR = 1<<(10+16);  // LED OFF
 }
}

void initializeLabSpecs()
{
	// delacre the variable register with the offset 
	volatile CAN_MCR rCAN1_MCR;
	volatile CAN_MSR rCAN1_MSR;
	
	CAN_BTR rCAN1_BTR;
	
	//CAN_TSR rCAN1_TSR;
	// end of definition 
	
	rCAN1_MCR.d32 = readRegister(RCAN1_MCR);
	rCAN1_MCR.b.breset = 1;
	writeRegister(RCAN1_MCR , rCAN1_MCR.d32);
	
	// what till the MCR has been free
	rCAN1_MCR.d32 = readRegister(RCAN1_MCR);
	while(rCAN1_MCR.b.breset == 1)
	{
		rCAN1_MCR.d32 = readRegister(RCAN1_MCR);
		// timeout is less than x 
	}
	
	rCAN1_MCR.d32 = readRegister(RCAN1_MCR);
	// initialize the bit 
	rCAN1_MCR.b.binrq = 1;
	writeRegister(RCAN1_MCR , rCAN1_MCR.d32);
	
	// reat the init
	rCAN1_MSR.d32 = readRegister(RCAN1_MSR);
	while(rCAN1_MSR.b.binak == 0)
	{
		rCAN1_MSR.d32 = readRegister(RCAN1_MSR);
		// timeout is less than x 
	}
	
	// set the timing register 
	rCAN1_BTR.d32 = readRegister(RCAN1_BTR); 
	
	// BTR bit timing register
	// loopback mode 
	// the apbr1 default clock is 36MHz 
	// bit field 8 brp set to 8 ... 
	// resynchronization 
	rCAN1_BTR.b.bsjw = 0x02;
	// time segment 2
	rCAN1_BTR.b.bts2 = 0x02;
	// time segment 1 
	rCAN1_BTR.b.bts1 = 0x0B;
	// set the baud rate 250kHz 
	rCAN1_BTR.b.bbrp = 0x08;
	// enable loopback 
	rCAN1_BTR.b.blbkm = 1;
	writeRegister(RCAN1_BTR, rCAN1_BTR.d32);
	
	rCAN1_MCR.d32 = readRegister(RCAN1_MCR);
	// set to 1 even if packet error occurs 
	rCAN1_MCR.b.bnart = 1;
	writeRegister(RCAN1_MCR, rCAN1_MCR.d32);
	// set reset to 1 to check if the periperhals has been resetted 
	// exit the sleep mode 
	
	rCAN1_MCR.d32 = readRegister(RCAN1_MCR);
	// set to 1 even if packet error occurs 
	rCAN1_MCR.b.binrq = 0;
	rCAN1_MCR.b.bsleep = 0;
	writeRegister(RCAN1_MCR, rCAN1_MCR.d32);
	
	// read the init
	rCAN1_MSR.d32 = readRegister(RCAN1_MSR);
	while(rCAN1_MSR.b.binak == 1)
	{
		rCAN1_MSR.d32 = readRegister(RCAN1_MSR);
		// timeout is less than x 
	}
}


void initFilter(void)
{
	// =======================================================
	// CAN Filter Initialization
	// =======================================================
	
	// Disable CAN reception to set CAN filters
	CAN_FMR rCAN1_FMR;
	rCAN1_FMR.d32 = readRegister(RCAN1_FMR);
	rCAN1_FMR.b.bfinit = 1;		// Disable CAN reception
	writeRegister(RCAN1_FMR, rCAN1_FMR.d32);
	
	// Activate CAN filters	
	CAN_FA1R rCAN1_FA1R;
	rCAN1_FA1R.d32 = readRegister(RCAN1_FA1R);
	rCAN1_FA1R.b.bfact0 = 1;		//TODO Set filter0 to active
	rCAN1_FA1R.b.bfact1 = 1;		//TODO Set filter1 to active	
	writeRegister(RCAN1_FA1R, rCAN1_FA1R.d32);
	
	// Set Filter identifier list or identifier mask
	CAN_FM1R rCAN1_FM1R;
	rCAN1_FM1R.d32 = readRegister(RCAN1_FM1R);
	rCAN1_FM1R.b.bfmb0 = 0;	 		// Set filter0 to use identifier mask mode
	rCAN1_FM1R.b.bfmb1 = 0;			// Set filter1 to use identifier mask mode
	writeRegister(RCAN1_FM1R, rCAN1_FM1R.d32);
	
	// Set Filter scale
	CAN_FS1R rCAN1_FS1R;
	rCAN1_FS1R.d32 = readRegister(RCAN1_FS1R);
	rCAN1_FS1R.b.bfsc0 = 1;			// Set filter scale to 32-bit
	rCAN1_FS1R.b.bfsc1 = 1;			// Set filter scale to 32-bit
	writeRegister(RCAN1_FS1R, rCAN1_FS1R.d32);

	// Setup Filter Mask
	// shift address left by 3
	// OR with 0x04
	unsigned int mask0 = (IDRX0 << 3) | 0x04;
	CAN_FiRx rCAN1_F0R1;
	rCAN1_F0R1.d32 = readRegister(RCAN1_F0R1);
	rCAN1_F0R1.d32 = mask0;
	writeRegister(RCAN1_F0R1, rCAN1_F0R1.d32);
	
	unsigned int mask1 = (IDRX1 << 3) | 0x04;
	CAN_FiRx rCAN1_F1R1;
	rCAN1_F1R1.d32 = readRegister(RCAN1_F1R1);
	rCAN1_F1R1.d32 = mask1;
	writeRegister(RCAN1_F1R1, rCAN1_F1R1.d32);	

	// Set FIFO destination for each filter
	CAN_FFA1R rCAN1_FFA1R;
	rCAN1_FFA1R.d32 = readRegister(RCAN1_FFA1R);
	rCAN1_FFA1R.b.bffa0 = 0;		// Set filter0 to send message to FIFO0
	rCAN1_FFA1R.b.bffa1 = 0;		// Set filter1 to send message to FIFO0
	writeRegister(RCAN1_FFA1R, rCAN1_FFA1R.d32);

	// Enable CAN reception now that filters are setup
	rCAN1_FMR.d32 = readRegister(RCAN1_FMR);
	rCAN1_FMR.b.bfinit = 0;			// Enable CAN reception
	writeRegister(RCAN1_FMR, rCAN1_FMR.d32);
}

void txCAN(CAN_msg *finalMessage)
{
	// need to be enabled when performing sending 
	// CAN_TIxR rCAN_TI1R;
	// need to be enabled first 
	// CAN_TDTxR rCAN_TDT1R;
	// mailbox registers
	// low bit 
	// CAN_TDLxR rCAN_TDL1R;
	// high bit
	// CAN_TDHxR rCAN_TDH1R;
	
	int mailbox_no = checkTxMailbox(); 
	if(mailbox_no == 0 || mailbox_no == 1 || mailbox_no == 2)
	{
		GLCD_DisplayString(4, 1, (unsigned char*)"MAILBOX GOOD");
		canTransmissionUniversal(finalMessage,mailbox_no);
		return;
	}
	if(mailbox_no == -1)
	{
		// there are no free mailbox just
		GLCD_DisplayString(4, 1, (unsigned char*)"MAILBOX FULL");
		return;
	}
}


int checkTxMailbox()
{
	// determine free mailbox put mailbox_no as argument 
	CAN_TSR rCAN1_TSR;
	rCAN1_TSR.d32 = readRegister(RCAN1_TSR);
	// on the CAN_TSR do the following 
	// check tsr on TME2 , TME1 , TME0 on set (high) when there are not transmission 
	if(rCAN1_TSR.b.btme0 == 1)
	{
		return 0;
	}
	if(rCAN1_TSR.b.btme1 == 1)
	{
		return 1;
	}
	if(rCAN1_TSR.b.btme2 == 1)
	{
		return 2;
	}
	else
	{
		return -1;
	}
}

int checkMailbox()
{
	// determine free mailbox put mailbox_no as argument 
	CAN_TSR rCAN1_TSR;
	rCAN1_TSR.d32 = readRegister(RCAN1_TSR);
	// on the CAN_TSR do the following 
	// check tsr on TME2 , TME1 , TME0 on set (high) when there are not transmission 
	if(rCAN1_TSR.b.btme0 == 1)
	{
		return 0;
	}
	if(rCAN1_TSR.b.btme1 == 1)
	{
		return 1;
	}
	if(rCAN1_TSR.b.btme2 == 1)
	{
		return 2;
	}
	else
	{
		return -1;
	}
}

void canTransmissionUniversal(CAN_msg *finalMessage, int mailboxNo)
{
		if(mailboxNo > 2 || mailboxNo < 0)
		{
			return;
		}
		CAN1->sTxMailBox[mailboxNo].TIR  = (unsigned int)(finalMessage->id << 3) | 4; 
		int temp = DATA_FRAME;
		// DATA FRAME
		if (finalMessage->type == temp){								
			CAN1->sTxMailBox[mailboxNo].TIR &= ~(1<<1);
		}
		// REMOTE FRAME
		else{
			CAN1->sTxMailBox[mailboxNo].TIR |= 1<<1;
		}
		CAN1->sTxMailBox[mailboxNo].TDLR = (((unsigned int)finalMessage->data[3] << 24) | 
															 ((unsigned int)finalMessage->data[2] << 16) |
															 ((unsigned int)finalMessage->data[1] <<  8) | 
															 ((unsigned int)finalMessage->data[0])        );
		CAN1->sTxMailBox[mailboxNo].TDHR = (((unsigned int)finalMessage->data[7] << 24) | 
															 ((unsigned int)finalMessage->data[6] << 16) |
															 ((unsigned int)finalMessage->data[5] <<  8) |
															 ((unsigned int)finalMessage->data[4])        );
															 
		CAN1->sTxMailBox[mailboxNo].TDTR &= ~0xf; // Setup length
		CAN1->sTxMailBox[mailboxNo].TDTR |=  (finalMessage->len & 0xf);
		CAN1->sTxMailBox[mailboxNo].TIR |=  1;                     // transmit message
}

void toggle_led(int LED)
{
	int LED_BANK;
	
	LED_BANK = GPIOE->IDR;
	
	// If LED is on
	if (LED_BANK & LED)
	{
		// Turn LED off
		GPIOE->ODR &= ~(LED); 
	}
	else if (LED_BANK & ~(LED))
	{
		// Turn LED on
		GPIOE->ODR |= LED;
	}
	else
	{
		// What is happening - Bad Case
		LED = 256;
	}	
}

void configureAdc()
{
	// Non urgent (to have the register config based on the class created)
	RCC->APB2ENR |= 1 << 9; //Enable ADC clock
	RCC->APB2ENR |= 1 << 4;	//Enable GPIOC clock
	
	GPIOC->CRL &= ~0x000F0000; 	//PC4 as ADC 14 input
		
	ADC1->SQR1 = 0x00000000;		//Regular Channel 1 Conversion
	ADC1->SQR2 = 0x00000000;		//Clear Register
	ADC1->SQR3 = (14<<0);				//SQ1 = Channel 14
	ADC1->SMPR1 = (5<<12);			//SAmple TIme Channel 14, 55, 5 cycles
	
	//Power on the ADC, Select SWARER as external ecent, enable external trigger mode
	ADC1->CR2 = ((1<<0)|(7<<17)|(1<<20));	
	ADC1->CR2 |= (1<<3);				//Reset Calibration
	while (ADC1->CR2 & (1<<3));	//Wait until Reset finished
	
	ADC1->CR2 |= (1<<2);				//Start Calibration
	while (ADC1->CR2 & (1<<2));	//Wait until Calibration Finished

	ADC1->CR2 |= (1<<3);				//reset calibration
	while (ADC1->CR2 & (1<<3));	//wait until reset finished
	ADC1->CR2 |= (1<<2);				//start calibration 
	while (ADC1->CR2 & (1<<2));	// wait until calibration finished.
}

int readAdc()
{
	int result = 0; 
	ADC1->CR2 |= (1<<22); 			//retrigger
	while (!(ADC1->SR & (1<<1))); //wait until EOC
	//read value and clear (read and clear)
	result = ADC1->DR;
	return result;
}

// EOF
