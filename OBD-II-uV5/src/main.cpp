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
	
	CAN_TIxR rCAN_TI1R;
	CAN_TDTxR rCAN_TDT1R;
	
	CAN_TDLxR rCAN_TDL1R;
	CAN_TDHxR rCAN_TDH1R;
	
	rCAN1_MCR.d32 = readRegister(RCAN_MCR);
	rCAN1_MCR.b.binrq = 1;
	rCAN1_MCR.b.bsleep = 0;
	writeRegister(RCAN_MCR , rCAN1_MCR.d32);
}

void txCAN(int ADDR, int DATA)
{
	// Send payload, DATA to the address, ADDR


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
