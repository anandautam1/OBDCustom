#include "stm32f10x_it.h"
#include "RCCController.h"
#include "GPIOController.h"
#include "utility.h"
#include "canRegisters.h"

// Function Prototypes

unsigned int readRegister(volatile unsigned int * iregisterAddress);
void writeRegister(volatile unsigned int * iregisterAddress, unsigned int idataPacket);

void txCAN(int ADDR, int DATA);
// TODO - prototype for RX DATA data
// int rxCAN();

void toggle_led(int LED);

//******************************************************************************//
// Function: main()
// Input : None
// Return : None
// Description : Entry point into the application.
// *****************************************************************************//
int main(void)
{
	// maybe instances can be created as an array .... 
	// but whats the point its just initialization i guess ... 
	
	// Wakeup swtich on portA pin 0
	
	//rCAN_TSR.d32 = readRegister((unsigned int *)CAN1_BASE_ADDR + RCAN_TSR);
	
	GPIO_Config Pin_A[1];
	Pin_A->Port = GPIO_A;
	Pin_A->Pin = Pin0;
	Pin_A->Type = GPIO_Input_PullUpDown;
	Pin_A->Speed = GPIO_50MHz;
	
	// User switch on portB pin 7 
	GPIO_Config Pin_B[1];
	Pin_B->Port = GPIO_B;
	Pin_B->Pin = Pin7;
	Pin_B->Type = GPIO_Input_PullUpDown;
	Pin_B->Speed = GPIO_50MHz;
	
	// ADC reading on Port C pin 4 
	GPIO_Config Pin_C[1];
	Pin_C->Port = GPIO_C;
	Pin_C->Pin = Pin4;
	Pin_C->Type = GPIO_Output_PushPull;
	Pin_C->Speed = GPIO_Reserved;
	
	
	// CAN bus mode RX and TX on PortD pin 0 and 1
	GPIO_Config Pin_D0[1];
	Pin_D0->Port = GPIO_D;
	Pin_D0->Pin = Pin0;
	Pin_D0->Type = GPIO_AF_PushPull;
	Pin_D0->Speed = GPIO_50MHz;

	GPIO_Config Pin_D1[1];
	Pin_D1->Port = GPIO_D;
	Pin_D1->Pin = Pin1;
	Pin_D1->Type = GPIO_AF_PushPull;
	Pin_D1->Speed = GPIO_50MHz;
	
	
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

	GPIOControl->configureGPIO(Pin_C);
	GPIOControl->setGPIO(Pin_C->Port, Pin_C->Pin);
	
	//GPIOControl->configureGPIO(Pin_D0);
	//GPIOControl->setGPIO(Pin_D0->Port, Pin_D0->Pin);
	//GPIOControl->configureGPIO(Pin_D1);
	//GPIOControl->setGPIO(Pin_D1->Port, Pin_D1->Pin);
	
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
	
	// GPIOControl->enableLabSpecsMode(PER_CAN1,REMAP0);
	
	// configure the switch 
	
	// configure the adc 
	// RCCControl->enablePeriperhal(RCC_CAN1);
	
	// Configure can bus clock and all the specs 
	
  // Main loop
	
	unsigned char adcData[4] = "hai";
	CAN_msg adcMessage[1];
	adcMessage->id = 0xBADCAFE;
	for (int i = 0; i < 4; i++) 
	{adcMessage->data[i] = adcData[i];}
	adcMessage->len = 4;
	adcMessage->format = STANDARD;
	adcMessage->type = DATA_FRAME;
	
	unsigned char led8Data[4] = "wor";
	CAN_msg led8Message[1];
	led8Message->id = 0x01A4F2B;
	for (int i = 0; i < 4; i++) 
	{led8Message->data[i] = led8Data[i];}
	led8Message->len = 4;
	led8Message->format = STANDARD;
	led8Message->type = DATA_FRAME;
	
	unsigned char led9Data[4] = "wor";
	CAN_msg led9Message[1];
	led9Message->id = 0x0024FCE;
	for (int i = 0; i < 4; i++) 
	{led9Message->data[i] = led8Data[i];}
	led9Message->len = 4;
	led9Message->format = STANDARD;
	led9Message->type = DATA_FRAME;
	
  while (1)
  {
// Read User Button
		if (!(GPIOControl->getPinValue(Pin_B->Port, Pin_B->Pin)))
		{
			// TODO - TX CAN
			// Send 0x01 to CAN Address 0x01AEFCA
			
			
			// TODO - Check mailbox
			
			
			// DEBUG
			//GPIOControl->setGPIO(Pin_E9->Port,Pin_E9->Pin);
		}
		else
		{
			// Do nothing if button isn't pressed
			
			// DEBUG 
			//GPIOControl->resetGPIO(Pin_E9->Port,Pin_E9->Pin);
		}
		
		// TODO
		// if another button pressed
		// transmitCAN( address, data, labspecsmode)
		
		// default will be to transmit the ADC code in bytes 
		// transmitCAN( address, data, labspecsmode) 
		
		// receiveCAN( address, result, labspecsmode) 
		
		//GPIOControl->writeRegister(
		
		delay_software_ms(10);

		
		//toggle_led(1 << 9);
  }
} 


// Function Definitions
unsigned int readRegister(volatile unsigned int * iregisterAddress){
	return (*iregisterAddress);
}
void writeRegister(volatile unsigned int * iregisterAddress, unsigned int idataPacket){
	*iregisterAddress = idataPacket;
}

void initializeLabSpecs()
{
	// delacre the variable register with the offset 
	CAN_MCR rCAN1_MCR;
	CAN_MSR rCAN1_MSR;
	
	CAN_BTR rCAN1_BTR;
	CAN_TSR rCAN1_TSR;
	// end of definition 
	
	rCAN1_MCR.d32 = readRegister(RCAN_MCR);
	// initialize the bit 
	rCAN1_MCR.b.binrq = 1;
	// set to 1 even if packet error occurs 
	rCAN1_MCR.b.bnart = 1;
	// set reset to 1 to check if the periperhals has been resetted 
	rCAN1_MCR.b.breset = 1;
	// exit the sleep mode 
	rCAN1_MCR.b.bsleep = 0;
	writeRegister(RCAN_MCR , rCAN1_MCR.d32);
	
	rCAN1_MCR.d32 = readRegister(RCAN_MCR);
	while(rCAN1_MCR.b.breset)
	{
		rCAN1_MCR.d32 = readRegister(RCAN_MCR);
	}
	 
	// the apbr1 default clock is 36MHz 
	// bit field 8 brp set to 8 ... 
	rCAN1_BTR.b.bbrp = 8;
	writeRegister(RCAN1_BTR, rCAN1_BTR.d32);
}

void txCAN(CAN_msg *finalMessage)
{
	// need to be enabled first 
	CAN_TDTxR rCAN_TDT1R;
	
	// mailbox registers
	// low bit 
	CAN_TDLxR rCAN_TDL1R;
	// high bit
	CAN_TDHxR rCAN_TDH1R;
	
	// need to be enabled when performing sending 
	CAN_TIxR rCAN_TI1R;
	
	//rCAN_TI1R.
	
	CAN1->sTxMailBox[0].TIR  = (unsigned int)(finalMessage->id << 3) | 4; 
	int temp = DATA_FRAME;
	if (finalMessage->type == temp){								// DATA FRAME
		CAN1->sTxMailBox[0].TIR &= ~(1<<1);
	}
	// REMOTE FRAME
	else{
		CAN1->sTxMailBox[0].TIR |= 1<<1;
	}
  CAN1->sTxMailBox[0].TDLR = (((unsigned int)finalMessage->data[3] << 24) | 
                             ((unsigned int)finalMessage->data[2] << 16) |
                             ((unsigned int)finalMessage->data[1] <<  8) | 
                             ((unsigned int)finalMessage->data[0])        );
  CAN1->sTxMailBox[0].TDHR = (((unsigned int)finalMessage->data[7] << 24) | 
                             ((unsigned int)finalMessage->data[6] << 16) |
                             ((unsigned int)finalMessage->data[5] <<  8) |
                             ((unsigned int)finalMessage->data[4])        );
  CAN1->sTxMailBox[0].TDTR &= ~0xf; // Setup length
  CAN1->sTxMailBox[0].TDTR |=  (finalMessage->len & 0xf);
  CAN1->sTxMailBox[0].TIR |=  1;                     // transmit message
	
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

// EOF
