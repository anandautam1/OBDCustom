/********************************************
*			STM32F107 GPIO Controller							*
*			Developed for the STM32								*
*			Author: Dr. Glenn Matthews						*
*			Source File														*
********************************************/

#include "stm32f10x.h"
#include "utility.h"
#include "RCCController.h"
#include "GPIOController.h"
#include "gpioRegisters.h"

// The GPIO Controller is designed to take care of the peripheral mapping
// for the various devices on the STM32F107. 

// The GPIO sub-system will enable all of the IO Clocks and Remap / Alternate functions.
// The enabling of the peripheral will still be the task of the other controllers.

//******************************************************************************//
// Function: GPIOController()
// Input:
// Output: 
// Description: Default constructor for GPIO Controller
// *****************************************************************************//
GPIOController::GPIOController(RCCController * inputRCCControl)
{
	// Configure the base address of the GPIO Ports.
	for(unsigned char i = 0; i < MAX_GPIO; i++)
	{
		GPIO[i].baseAddress = (unsigned int *) (GPIOA_BASE_ADDR + (i * GPIO_OFFSET));											// The base address of the GPIO Port
		GPIO[i].configLowAddress = (unsigned int *) (GPIOA_BASE_ADDR + RGPIO_CRL + (i * GPIO_OFFSET));		// GPIO Low Configuration (bits 0 - 7)
		GPIO[i].configHighAddress = (unsigned int *) (GPIOA_BASE_ADDR + RGPIO_CRH + (i * GPIO_OFFSET));		// GPIO High Configuration (bits 8 - 16)
		GPIO[i].inputDataAddress = (unsigned int *) (GPIOA_BASE_ADDR + RGPIO_IDR + (i * GPIO_OFFSET));		// GPIO Input Data Register
		GPIO[i].outputDataAddress = (unsigned int *) (GPIOA_BASE_ADDR + RGPIO_ODR + (i * GPIO_OFFSET));		// GPIO Output Data Register
		GPIO[i].bitSetAddress = (unsigned int *) (GPIOA_BASE_ADDR + RGPIO_BSRR + (i * GPIO_OFFSET));			// GPIO Bit Set Register
		GPIO[i].bitResetAddress = (unsigned int *) (GPIOA_BASE_ADDR + RGPIO_BRR + (i * GPIO_OFFSET));			// GPIO Bit Clear Register
		GPIO[i].bitLockAddress = (unsigned int *) (GPIOA_BASE_ADDR + RGPIO_LCKR + (i * GPIO_OFFSET));			// GPIO Lock Bit Register
		
		GPIO[i].clockEnabled = 0;    // By default the GPIO clock has not been enabled.
	}
	
	// Assign the RCC Controller
	RCCControl = inputRCCControl;
	
	// Given the wide number of periperhals, enable (and reset) the AFIO Clock
	RCCControl->enablePeripheral(RCC_AFIO);
	
}

//******************************************************************************//
// Function: ~GPIOController()
// Input:
// Output: 
// Description: Default destructor for GPIO Controller
// *****************************************************************************//
GPIOController::~GPIOController()
{
	
	
	
}

//******************************************************************************//
// Function: readRegister()
// Input : Register to read from.
// Return : Data from the register of interest
// Description : Read from a 32-bit ARM register
// *****************************************************************************//
unsigned int GPIOController::readRegister(volatile unsigned int * iregisterAddress)	
{
	// It may be necessary to modify this routine to inline to improve performance.
	return (*iregisterAddress);
	
}
	
//******************************************************************************//
// Function: writeRegister()
// Input : Register to write to and payload.
// Return : None
// Description : Write to a 32-bit ARM register
// *****************************************************************************//
void GPIOController::writeRegister(volatile unsigned int * iregisterAddress , unsigned int idataPacket)
{
	// The register address passed in is already a pointer so 
	// it is just a matter of changing the contents.
	*iregisterAddress = idataPacket;

}

//******************************************************************************//
// Function: configureGPIOPin()
// Input : The GPIO Port
// Return : None
// Description : Configure an individual GPIO Pin
// *****************************************************************************//
bool GPIOController::configureGPIO(GPIO_Config * inputGPIO)
{
	// The struct GPIO contains all of the necessary information to set the GPIO Pin
	GPIO_CRL rGPIO_CR;
	unsigned char inputPin = 0;
		
	// Check to see whether the clock for the GPIO is enabled.
	if(GPIO[inputGPIO->Port].clockEnabled == 0)
	{
		enableGPIOClock(inputGPIO->Port);
		
		// Set the flag to indicate that the IO port has been enabled.
		GPIO[inputGPIO->Port].clockEnabled = 1;
	}
	
	// Decide on whether to access the high byte of low byte of the configuration register.
	if(inputGPIO->Pin <= 7)
	{
		// Low byte configuration register access
		// Read the low byte configuration register
		rGPIO_CR.d32 = readRegister(GPIO[inputGPIO->Port].configLowAddress);
		
		inputPin = inputGPIO->Pin;
	}
	else if(inputGPIO->Pin <= 15)
	{
		// Read the low byte configuration register
		rGPIO_CR.d32 = readRegister(GPIO[inputGPIO->Port].configHighAddress);		
		inputPin = (inputGPIO->Pin) - 8;
	}
				
		// Clear out the mode and configuration bits.
		rGPIO_CR.d32 &= ~(0xF << (inputPin * 4));
		
		switch(inputGPIO->Type)
		{
			case GPIO_Output_PushPull:
			{
				rGPIO_CR.d32 |= ((GPIO_OUT_PP << 2) | inputGPIO->Speed) << (inputPin * 4);
				break;
			}

			case GPIO_Output_OpenDrain:
			{
				rGPIO_CR.d32 |= ((GPIO_OUT_OD << 2) | inputGPIO->Speed) << (inputPin * 4);	
				break;
			}
						
			case GPIO_AF_PushPull:
			{
				rGPIO_CR.d32 |= ((GPIO_AF_PP << 2) | inputGPIO->Speed) << (inputPin * 4);
				break;
			}
			
			case GPIO_AF_OpenDrain:
			{
				rGPIO_CR.d32 |= ((GPIO_AF_OD << 2) | inputGPIO->Speed) << (inputPin * 4);
				break;
			}
			
			case GPIO_Input_Analog:
			{
				rGPIO_CR.d32 |= ((GPIO_IN_AN << 2) & 0xC) << (inputPin * 4);
				break;
			}
			
			case GPIO_Input_Floating:
			{
				rGPIO_CR.d32 |= ((GPIO_IN_FL << 2) & 0xC) << (inputPin * 4);			
				break;
			}
						
			case GPIO_Input_PullUpDown:	
			{
				rGPIO_CR.d32 |= ((GPIO_IN_PUPD << 2) & 0xC) << (inputPin * 4);	
				break;
			}

		}
			// Decide on whether to access the high byte of low byte of the configuration register.
	if(inputGPIO->Pin <= 7)
	{
		// Low byte configuration register access
		writeRegister(GPIO[inputGPIO->Port].configLowAddress, rGPIO_CR.d32);
	}
	else
	{
		// High byte configuration register access
		writeRegister(GPIO[inputGPIO->Port].configHighAddress, rGPIO_CR.d32);		
	}

	return 0;
}





//******************************************************************************//
// Function: enableGPIOClock()
// Input : The GPIO Port
// Return : None
// Description : Enable the GPIO Clock for a given port.
// *****************************************************************************//
void GPIOController::enableGPIOClock(GPIOPort inputPort)
{
		switch(inputPort)
		{
			case GPIO_A:
			{	
				RCCControl->enablePeripheral(RCC_GPIOA);
				break;
			}
			
			case GPIO_B:
			{
				RCCControl->enablePeripheral(RCC_GPIOB);	
				break;
			}
			
			case GPIO_C:
			{
				RCCControl->enablePeripheral(RCC_GPIOC);	
				break;
			}
			
			case GPIO_D:
			{
				RCCControl->enablePeripheral(RCC_GPIOD);	
				break;
			}
			
			case GPIO_E:
			{
				RCCControl->enablePeripheral(RCC_GPIOE);	
				break;
			}
			
			case GPIO_F:
			{
				RCCControl->enablePeripheral(RCC_GPIOF);	
			}
			
			case GPIO_G:
			{
				RCCControl->enablePeripheral(RCC_GPIOG);	
			}
			
		}
	
	
}

//******************************************************************************//
// Function: enablePeriperhal()
// Input : The peripheral to enable and the configuration
// Return : None
// Description : Enable the Alternate function (AFIO) and GPIO for the required periperhal
// *****************************************************************************//
void GPIOController::enablePeripheral(GPIOPeripheral inputDevice, GPIORemap inputConfig)
{
	// This function configures the basic GPIO requirements for a given set of 
	// peripherals. The alternate function registers are configured (and AF / GPIO clocks)
	// enabled. The actual peripheral clocks are NOT enaled.
	
	switch(inputDevice)
	{
		case PER_SPI1:
		{
		
			break;
		}		

		case PER_SPI2:
		{
			
			break;
		}
		
		case PER_SPI3:
		{
			//enableSPI(inputDevice, inputConfig);
			break;
		}
		
		case PER_ADC1:
		{
			break;
		}
		case PER_ADC2:
		{
			break;
		}
		case PER_ADC3:
		{
			break;
		}
		case PER_CAN1:
		{
			enableCAN(inputDevice, inputConfig);
			RCCControl->enablePeripheral(RCC_CAN1);
			break;
		}
		case PER_CAN2:
		{
			enableCAN(inputDevice, inputConfig);
			RCCControl->enablePeripheral(RCC_CAN2); 
			break;
		}
	}
		
}

//******************************************************************************//
// Function: enableCAN()
// Input : The peripheral to enable and the configuration
// Return : None
// Description : Enable the CAN controller(s) peripherals
// *****************************************************************************//
void GPIOController::enableCAN(GPIOPeripheral inputDevice, GPIORemap inputConfig)
{
	// There are several different configurations that can be set on the STM32F107
	// in regards to the mapping for the CAN controllers.
	
	// In Alternate function (default mapping):
	// AF0 - CAN1_TX = PA12 , CAN1_RX = PA11
	// AF0 - CAN2_TX = PB13, CAN2_RX = PB12
	
	// REMAP0 - CAN1_TX = PD1 , CAN1_RX = PD0 (100 pin QFP only)
	// REMAP0 - CAN2_TX = PB6, CAN2_RX = PB5
	
	// REMAP1 - CAN1_TX = PB9 , CAN1_RX = PB8
	
	// For CAN, the TX line should be set to AF Push Pull and the RX to input
	// floating or input pull-up
	
	GPIO_CRH rGPIO_CRH;
	GPIO_CRL rGPIO_CRL;
	AFIO_MAPR rAFIO_MAPR;
	
	if(inputDevice == PER_CAN1)
	{
		// Configure CAN_1, decide on IO configuration.
		switch(inputConfig)
		{
			case AF0:
			{
				// Check to see whether the clock for the GPIO is enabled.
				if(GPIO[GPIO_A].clockEnabled == 0)
				{
					enableGPIOClock(GPIO_A);
		
					// Set the flag to indicate that the IO port has been enabled.
					GPIO[GPIO_A].clockEnabled = 1;
				}
				
				// Set the GPIO registers.
				rGPIO_CRH.d32 = readRegister(GPIO[GPIO_A].configHighAddress);
				
				// Set the bits relating to AF (PA12 - CAN TX).
				rGPIO_CRH.b.bcnf12 = GPIO_AF_PP;
				rGPIO_CRH.b.bmode12 = GPIO_50MHz;
				
				// Set the input pin (PA11)
				rGPIO_CRH.b.bcnf11 = GPIO_IN_PUPD;
				rGPIO_CRH.b.bmode11 = GPIO_Reserved;
			
				// Write the register back
				writeRegister(GPIO[GPIO_A].configHighAddress, rGPIO_CRH.d32);

				// Read the AFIO register for CAN1.
				rAFIO_MAPR.d32 = readRegister(RAFIO_MAPR);
				
				// Clear the bits relating to AF0
				rAFIO_MAPR.b.bcan1_remap = 0;
				
				writeRegister(RAFIO_MAPR, rAFIO_MAPR.d32);
				
				break;
			}
			
			case REMAP0:
			{
				// Check to see whether the clock for the GPIO is enabled.
				if(GPIO[GPIO_D].clockEnabled == 0)
				{
					enableGPIOClock(GPIO_D);
		
					// Set the flag to indicate that the IO port has been enabled.
					GPIO[GPIO_D].clockEnabled = 1;
				}
				
				// Set the GPIO registers.
				rGPIO_CRL.d32 = readRegister(GPIO[GPIO_D].configLowAddress);
				
				// Set the bits relating to AF (PD1 - CAN TX).
				rGPIO_CRL.b.bcnf1 = GPIO_AF_PP;
				rGPIO_CRL.b.bmode1 = GPIO_50MHz;
				
				// Set the input pin (PD0)
				rGPIO_CRL.b.bcnf0 = GPIO_IN_PUPD;
				rGPIO_CRL.b.bmode0 = GPIO_Reserved;
			
				// Write the register back
				writeRegister(GPIO[GPIO_D].configLowAddress, rGPIO_CRL.d32);

				// Read the AFIO register for CAN1.
				rAFIO_MAPR.d32 = readRegister(RAFIO_MAPR);
				
				// Clear the bits relating to AF0
				rAFIO_MAPR.b.bcan1_remap = 0x03;
				
				writeRegister(RAFIO_MAPR, rAFIO_MAPR.d32);			
				break;
			}
					
			case REMAP1:
			{
				// Check to see whether the clock for the GPIO is enabled.
				if(GPIO[GPIO_B].clockEnabled == 0)
				{
					enableGPIOClock(GPIO_B);
		
					// Set the flag to indicate that the IO port has been enabled.
					GPIO[GPIO_B].clockEnabled = 1;
				}
				
				// Set the GPIO registers.
				rGPIO_CRH.d32 = readRegister(GPIO[GPIO_B].configHighAddress);
				
				// Set the bits relating to AF (PB9 - CAN TX).
				rGPIO_CRH.b.bcnf9 = GPIO_AF_PP;
				rGPIO_CRH.b.bmode9 = GPIO_50MHz;
				
				// Set the input pin (PB8)
				rGPIO_CRH.b.bcnf8 = GPIO_IN_PUPD;
				rGPIO_CRH.b.bmode8 = GPIO_Reserved;
			
				// Write the register back
				writeRegister(GPIO[GPIO_B].configHighAddress, rGPIO_CRH.d32);

				// Read the AFIO register for CAN1.
				rAFIO_MAPR.d32 = readRegister(RAFIO_MAPR);
				
				// Clear the bits relating to AF0
				rAFIO_MAPR.b.bcan1_remap = 0x02;
				
				writeRegister(RAFIO_MAPR, rAFIO_MAPR.d32);			
				
				break;
			}
			default:
			{
				break;
			}
		}
	}
	else if(inputDevice == PER_CAN2)
	{
		// Configure CAN_2, decide on IO configuration.
		// Check to see whether the clock for the GPIO is enabled.
		if(GPIO[GPIO_B].clockEnabled == 0)
		{
			enableGPIOClock(GPIO_B);
		
			// Set the flag to indicate that the IO port has been enabled.
			GPIO[GPIO_B].clockEnabled = 1;
		}
		
		switch(inputConfig)
		{
			case AF0:
			{
				// Set the GPIO registers.
				rGPIO_CRH.d32 = readRegister(GPIO[GPIO_B].configHighAddress);
				
				// Set the bits relating to AF (PB13 - CAN TX).
				rGPIO_CRH.b.bcnf13 = GPIO_AF_PP;
				rGPIO_CRH.b.bmode13 = GPIO_50MHz;
				
				// Set the input pin (PB12)
				rGPIO_CRH.b.bcnf12 = GPIO_IN_PUPD;
				rGPIO_CRH.b.bmode12 = GPIO_Reserved;
			
				// Write the register back
				writeRegister(GPIO[GPIO_B].configHighAddress, rGPIO_CRH.d32);

				// Read the AFIO register for CAN1.
				rAFIO_MAPR.d32 = readRegister(RAFIO_MAPR);
				
				// Clear the bits relating to AF0
				rAFIO_MAPR.b.bcan2_remap = 0;
				
				writeRegister(RAFIO_MAPR, rAFIO_MAPR.d32);
				
				break;
			}
			
			case REMAP0:
			{
				// Set the GPIO registers.
				rGPIO_CRL.d32 = readRegister(GPIO[GPIO_B].configLowAddress);
				
				// Set the bits relating to AF (PB6 - CAN TX).
				rGPIO_CRL.b.bcnf6 = GPIO_AF_PP;
				rGPIO_CRL.b.bmode6 = GPIO_50MHz;
				
				// Set the input pin (PB5)
				rGPIO_CRL.b.bcnf5 = GPIO_IN_PUPD;
				rGPIO_CRL.b.bmode5 = GPIO_Reserved;
			
				// Write the register back
				writeRegister(GPIO[GPIO_B].configLowAddress, rGPIO_CRL.d32);

				// Read the AFIO register for CAN1.
				rAFIO_MAPR.d32 = readRegister(RAFIO_MAPR);
				
				// Clear the bits relating to AF0
				rAFIO_MAPR.b.bcan2_remap = 0x01;
				
				writeRegister(RAFIO_MAPR, rAFIO_MAPR.d32);			
				break;
			}
			default:
			{
				break;
			}
		}	
	}
}

//******************************************************************************//
// Function: enableSPI()
// Input : The peripheral to enable and the configuration
// Return : None
// Description : Enable the CAN controller(s) peripherals
// *****************************************************************************//
void GPIOController::enableSPI(GPIOPeripheral inputDevice, GPIORemap inputConfig, bool externalChipSelect)
{
	// There are several different configurations that can be set on the STM32F107
	// in regards to the mapping for the SPI controllers.
	
	// In Alternate function (default mapping):
	// AF0 - SPI1 - MISO = PA6 , MOSI = PA7, SCLK = PA5, SS = PA4
	// AF0 - SPI2 - MISO = PB14 , MOSI = PB15 , SCLK = PB13, SS = PB12
	// AF0 - SPI3 - MISO = PB4, MOSI = PB5, SCLK = PB3 , SS = PA15
	
	// REMAP0 - SPI1 - MISO = PB4 , MOSI = PB5 , SCLK = PB3, SS = PA15
	// REMAP0 - SPI3 - MISO = PC11, MOSI = PC12, SCLK = PC10, SS = PA4

	
	// The IO state for the chip select is given by the boolean value
	// externalChipSelect.
	
	// The SPI Port is configured for full-duplex communication.
	
	GPIO_CRH rGPIO_CRH;
	GPIO_CRL rGPIO_CRL;
	AFIO_MAPR rAFIO_MAPR;
	
	if(inputDevice == PER_SPI1)
	{
		// Configure SPI_1, decide on IO configuration.
		switch(inputConfig)
		{
			case AF0:
			{
				// AF0 - SPI1 - MISO = PA6 , MOSI = PA7, SCLK = PA5, SS = PA4
				// Enable the clock for Port A
				if(GPIO[GPIO_A].clockEnabled == 0)
				{
					enableGPIOClock(GPIO_A);
					GPIO[GPIO_A].clockEnabled = 1;
				}
		
				// Set the Port A GPIO registers.
				rGPIO_CRL.d32 = readRegister(GPIO[GPIO_A].configLowAddress);
				
				// Set the bits relating to AF (PA6 - MISO).
				rGPIO_CRL.b.bcnf6 = GPIO_IN_PUPD;
				rGPIO_CRL.b.bmode6 = GPIO_Reserved;
				
				// PA7 - MOSI
				rGPIO_CRL.b.bcnf7 = GPIO_AF_PP;
				rGPIO_CRL.b.bmode7 = GPIO_50MHz;
				
				// PA5 - SCLK
				rGPIO_CRL.b.bcnf5 = GPIO_AF_PP;
				rGPIO_CRL.b.bmode5 = GPIO_50MHz;			
			
				// Write the register back
				writeRegister(GPIO[GPIO_A].configLowAddress, rGPIO_CRL.d32);
				
				// Decide on the external chip select
				if(externalChipSelect == 0)
				{
						// Using the hardware version - set up accordingly.
						rGPIO_CRL.d32 = readRegister(GPIO[GPIO_A].configLowAddress);
						
						rGPIO_CRL.b.bcnf4 = GPIO_AF_PP;
						rGPIO_CRL.b.bmode4 = GPIO_50MHz;
						
						writeRegister(GPIO[GPIO_A].configLowAddress, rGPIO_CRL.d32);
				}

				// Read the AFIO register for SP3.
				rAFIO_MAPR.d32 = readRegister(RAFIO_MAPR);
				
				// Clear the bits relating to AF0
				rAFIO_MAPR.b.bspi1_remap = 0;
				
				writeRegister(RAFIO_MAPR, rAFIO_MAPR.d32);
				
				break;
			}
			
			case REMAP0:
			{
				// REMAP0 - SPI1 - MISO = PB4 , MOSI = PB5 , SCLK = PB3, SS = PA15
				// Enable the clock for Port B
				if(GPIO[GPIO_B].clockEnabled == 0)
				{
					enableGPIOClock(GPIO_B);
					GPIO[GPIO_B].clockEnabled = 1;
				}
		
				// Set the Port B GPIO registers.
				rGPIO_CRL.d32 = readRegister(GPIO[GPIO_B].configLowAddress);
				
				// Set the bits relating to AF (PB4 - MISO).
				rGPIO_CRL.b.bcnf4 = GPIO_IN_PUPD;
				rGPIO_CRL.b.bmode4 = GPIO_Reserved;
				
				// PB5 - MOSI
				rGPIO_CRL.b.bcnf5 = GPIO_AF_PP;
				rGPIO_CRL.b.bmode5 = GPIO_50MHz;
				
				// PB3 - SCLK
				rGPIO_CRL.b.bcnf3 = GPIO_AF_PP;
				rGPIO_CRL.b.bmode3 = GPIO_50MHz;			
			
				// Write the register back
				writeRegister(GPIO[GPIO_B].configLowAddress, rGPIO_CRL.d32);
				
				// Decide on the external chip select
				if(externalChipSelect == 0)
				{
						// Using the hardware version - set up accordingly.
						if(GPIO[GPIO_A].clockEnabled == 0)
						{
							enableGPIOClock(GPIO_A);
							GPIO[GPIO_A].clockEnabled = 1;
						}
				
						rGPIO_CRH.d32 = readRegister(GPIO[GPIO_A].configHighAddress);
						
						rGPIO_CRH.b.bcnf15 = GPIO_AF_PP;
						rGPIO_CRH.b.bmode15 = GPIO_50MHz;
						
						writeRegister(GPIO[GPIO_A].configHighAddress, rGPIO_CRH.d32);
				}

				// Read the AFIO register for SP1.
				rAFIO_MAPR.d32 = readRegister(RAFIO_MAPR);
				
				// Clear the bits relating to AF0
				rAFIO_MAPR.b.bspi1_remap = 1;
				
				writeRegister(RAFIO_MAPR, rAFIO_MAPR.d32);
				
				break;
			}
			
			default:
			{
				break;
			}
		}
	}	
	else if(inputDevice == PER_SPI2)
	{
		// AF0 - SPI2 - MISO = PB14 , MOSI = PB15 , SCLK = PB13, SS = PB12
		
		// Enable the clock for Port B
		if(GPIO[GPIO_B].clockEnabled == 0)
		{
			enableGPIOClock(GPIO_B);
			GPIO[GPIO_B].clockEnabled = 1;
		}
		
		// Set the Port B GPIO registers.
		rGPIO_CRH.d32 = readRegister(GPIO[GPIO_B].configHighAddress);
				
		// Set the bits relating to AF (PB14 - MISO).
		rGPIO_CRH.b.bcnf14 = GPIO_IN_PUPD;
		rGPIO_CRH.b.bmode14 = GPIO_Reserved;
				
		// PB15 - MOSI
		rGPIO_CRH.b.bcnf15 = GPIO_AF_PP;
		rGPIO_CRH.b.bmode15 = GPIO_50MHz;
				
		// PB13 - SCLK
		rGPIO_CRH.b.bcnf13 = GPIO_AF_PP;
		rGPIO_CRH.b.bmode13 = GPIO_50MHz;			
			
		// Write the register back
		writeRegister(GPIO[GPIO_B].configHighAddress, rGPIO_CRH.d32);
				
		// Decide on the external chip select
		if(externalChipSelect == 0)
		{
			// Grab the config high register.
			rGPIO_CRH.d32 = readRegister(GPIO[GPIO_A].configHighAddress);
				
			rGPIO_CRH.b.bcnf12 = GPIO_AF_PP;
			rGPIO_CRH.b.bmode12 = GPIO_50MHz;
			
			writeRegister(GPIO[GPIO_B].configHighAddress, rGPIO_CRH.d32);
		}	
	}
	else if(inputDevice == PER_SPI3)
	{
		// Configure SPI 3, decide on IO configuration.
		switch(inputConfig)
		{
			case AF0:
			{
				// AF0 - SPI3 - MISO = PB4, MOSI = PB5, SCLK = PB3 , SS = PA15
				// Enable the clock for Port B
				if(GPIO[GPIO_B].clockEnabled == 0)
				{
					enableGPIOClock(GPIO_B);
					GPIO[GPIO_B].clockEnabled = 1;
				}
		
				// Set the Port B GPIO registers.
				rGPIO_CRL.d32 = readRegister(GPIO[GPIO_B].configLowAddress);
				
				// Set the bits relating to AF (PB4 - MISO).
				rGPIO_CRL.b.bcnf4 = GPIO_IN_PUPD;
				rGPIO_CRL.b.bmode4 = GPIO_Reserved;
				
				// PB5 - MOSI
				rGPIO_CRL.b.bcnf5 = GPIO_AF_PP;
				rGPIO_CRL.b.bmode5 = GPIO_50MHz;
				
				// PB3 - SCLK
				rGPIO_CRL.b.bcnf5 = GPIO_AF_PP;
				rGPIO_CRL.b.bmode5 = GPIO_50MHz;			
			
				// Write the register back
				writeRegister(GPIO[GPIO_B].configLowAddress, rGPIO_CRL.d32);
				
				// Decide on the external chip select
				if(externalChipSelect == 0)
				{
						// Using the hardware version - set up accordingly.
						// Enable the clock for Port A
						if(GPIO[GPIO_A].clockEnabled == 0)
						{
							enableGPIOClock(GPIO_A);
							GPIO[GPIO_A].clockEnabled = 1;
						}
						
						// Grab the config high register.
						rGPIO_CRH.d32 = readRegister(GPIO[GPIO_A].configHighAddress);
						
						rGPIO_CRH.b.bcnf15 = GPIO_AF_PP;
						rGPIO_CRH.b.bmode15 = GPIO_50MHz;
						
						writeRegister(GPIO[GPIO_A].configHighAddress, rGPIO_CRH.d32);
				}

				// Read the AFIO register for SP3.
				rAFIO_MAPR.d32 = readRegister(RAFIO_MAPR);
				
				// Clear the bits relating to AF0
				rAFIO_MAPR.b.bspi3_remap = 0;
				
				writeRegister(RAFIO_MAPR, rAFIO_MAPR.d32);
				
				break;
			}
			
			case REMAP0:
			{
				// REMAP1 - SPI3 - MISO = PC11, MOSI = PC12, SCLK = PC10, SS = PA4
				// Enable the clock for Port B
				if(GPIO[GPIO_C].clockEnabled == 0)
				{
					enableGPIOClock(GPIO_C);
					GPIO[GPIO_C].clockEnabled = 1;
				}
		
				// Set the Port C GPIO registers.
				rGPIO_CRH.d32 = readRegister(GPIO[GPIO_C].configHighAddress);
				
				// Set the bits relating to REMAP (PC11 - MISO).
				rGPIO_CRH.b.bcnf11 = GPIO_IN_PUPD;
				rGPIO_CRH.b.bmode11 = GPIO_Reserved;
				
				// PC12 - MOSI
				rGPIO_CRH.b.bcnf12 = GPIO_AF_PP;
				rGPIO_CRH.b.bmode12 = GPIO_50MHz;
				
				// PC10 - SCLK
				rGPIO_CRH.b.bcnf10 = GPIO_AF_PP;
				rGPIO_CRH.b.bmode10 = GPIO_50MHz;			
			
				// Write the register back
				writeRegister(GPIO[GPIO_C].configHighAddress, rGPIO_CRH.d32);
				
				// Decide on the external chip select
				if(externalChipSelect == 0)
				{
						// Using the hardware version - set up accordingly.
						// Enable the clock for Port A
						if(GPIO[GPIO_A].clockEnabled == 0)
						{
							enableGPIOClock(GPIO_A);
							GPIO[GPIO_A].clockEnabled = 1;
						}
						
						// Grab the config high register.
						rGPIO_CRL.d32 = readRegister(GPIO[GPIO_A].configLowAddress);
						
						rGPIO_CRL.b.bcnf4 = GPIO_AF_PP;
						rGPIO_CRL.b.bmode4 = GPIO_50MHz;
						
						writeRegister(GPIO[GPIO_A].configLowAddress, rGPIO_CRL.d32);
				}

				// Read the AFIO register for SP3.
				rAFIO_MAPR.d32 = readRegister(RAFIO_MAPR);
				
				// Clear the bits relating to AF0
				rAFIO_MAPR.b.bspi3_remap = 1;
				
				writeRegister(RAFIO_MAPR, rAFIO_MAPR.d32);
				
				break;
				
			}
			
			default:
			{
				break;
			}
		}	
		
		
	}
}

//******************************************************************************//
// Function: enableSPIChipSelect()
// Input : The GPIO port and pin for the external chip select
// Return : None
// Description : Enable the external chip select for the SPI Controller.
// *****************************************************************************//
void GPIOController::enableSPIChipSelect(GPIOPort externalChipSelectPort, GPIOPin externalChipSelectPin)
{
	GPIO_CRH rGPIO_CRH;
	GPIO_CRL rGPIO_CRL;
	
	// Check to see whether the clock for the given pin is enabled.
	if(GPIO[externalChipSelectPort].clockEnabled == 0)
	{
			enableGPIOClock(externalChipSelectPort);
			GPIO[externalChipSelectPort].clockEnabled = 1;
	}
	
	// Check to see whether the pin is a 'high' or 'low' byte.
	if(externalChipSelectPin <= 7)
	{
		rGPIO_CRL.d32 = readRegister(GPIO[externalChipSelectPort].configLowAddress);
				
		// Clear out the mode and configuration bits.
		rGPIO_CRL.d32 &= ~(0xF << (externalChipSelectPin * 4));
		
		rGPIO_CRL.d32 |= ((GPIO_OUT_PP << 2) | GPIO_50MHz) << (externalChipSelectPin * 4);
		writeRegister(GPIO[externalChipSelectPort].configLowAddress, rGPIO_CRL.d32);
		
	}
	else if (externalChipSelectPin <= 15)
	{
		// Due to the offset, subtract 8 from the GPIO Pin
		rGPIO_CRH.d32 = readRegister(GPIO[externalChipSelectPort].configHighAddress);

		// Clear out the mode and configuration bits.
		rGPIO_CRH.d32 &= ~(0xF << ((externalChipSelectPin - 8)* 4));

		rGPIO_CRH.d32 |= ((GPIO_OUT_PP << 2) | GPIO_50MHz) << ((externalChipSelectPin - 8) * 4);
		writeRegister(GPIO[externalChipSelectPort].configHighAddress, rGPIO_CRH.d32);
	}
	
}

//******************************************************************************//
// Function: enableADC()
// Input : The ADC and GPIO Pin (and port)
// Return : None
// Description : Bit set the GPIO Pin passed in..
// *****************************************************************************//
void GPIOController::enableADC(GPIOPeripheral inputDevice, GPIOPort inputPort, GPIOPin inputPin, unsigned char channelCount)
{
	RCCControl->enablePeripheral(RCC_ADC1);
	// The ADC peripheral is not used in alternate function.
	GPIO_CRH rGPIO_CRH;
	GPIO_CRL rGPIO_CRL;
	
	// Iterate through the channel list and place each channel in analog mode.
	for(unsigned char i = 0; i < channelCount; i++)
	{
		// Check to see whether the clock for the given pin is enabled.
		if(GPIO[inputPort].clockEnabled == 0)
		{
				enableGPIOClock(inputPort);
				GPIO[inputPort].clockEnabled = 1;
		}
		
		// Check to see whether the pin is a 'high' or 'low' byte.
		if(inputPin <= 7)
		{
			rGPIO_CRL.d32 = readRegister(GPIO[inputPort].configLowAddress);
				
			// Clear out the mode and configuration bits.
			rGPIO_CRL.d32 &= ~(0xF << (inputPin * 4));
		
			rGPIO_CRL.d32 |= ((GPIO_IN_AN << 2) | GPIO_Reserved) << (inputPin * 4);
			writeRegister(GPIO[inputPort].configLowAddress, rGPIO_CRL.d32);
		
		}
		else if (inputPin <= 15)
		{
			// Due to the offset, subtract 8 from the GPIO Pin
			rGPIO_CRH.d32 = readRegister(GPIO[inputPort].configHighAddress);

			// Clear out the mode and configuration bits.
			rGPIO_CRH.d32 &= ~(0xF << ((inputPin - 8)* 4));

			rGPIO_CRH.d32 |= ((GPIO_IN_AN << 2) | GPIO_Reserved) << ((inputPin - 8) * 4);
			writeRegister(GPIO[inputPort].configHighAddress, rGPIO_CRH.d32);
		}
		
	}
}

//******************************************************************************//
// Function: setGPIO()
// Input : The GPIO port and pin to be set to logic 1
// Return : None
// Description : Bit set the GPIO Pin passed in..
// *****************************************************************************//
void GPIOController::setGPIO(GPIOPort inputPort, GPIOPin inputPin)
{
	GPIO_BSRR rGPIO_BSRR;
	
	// Read in the current bit set register.
	rGPIO_BSRR.d32 = readRegister(GPIO[inputPort].bitSetAddress);
	
	// To 'set' a bit, the lower 16-bits can be utilised.
	rGPIO_BSRR.d32 |= 0x01 << inputPin;
	
	writeRegister(GPIO[inputPort].bitSetAddress, rGPIO_BSRR.d32);
}

//******************************************************************************//
// Function: resetGPIO()
// Input : The GPIO port and pin to be set to logic 0
// Return : None
// Description : Bit clear the GPIO Pin passed in..
// *****************************************************************************//
void GPIOController::resetGPIO(GPIOPort inputPort, GPIOPin inputPin)
{
	GPIO_BSRR rGPIO_BSRR;
	
	// Read in the current bit set register.
	rGPIO_BSRR.d32 = readRegister(GPIO[inputPort].bitSetAddress);
	
	// To 'set' a bit, the lower 16-bits can be utilised.
	rGPIO_BSRR.d32 |= 0x01 << (inputPin + 16);
	
	writeRegister(GPIO[inputPort].bitSetAddress, rGPIO_BSRR.d32);
}


//******************************************************************************//
// Function: getPinValue()
// Input : The GPIO port and pin to read
// Return : None
// Description : Obtain the value of an I/O Pin
// *****************************************************************************//
bool GPIOController::getPinValue(GPIOPort inputPort, GPIOPin inputPin)
{
	GPIO_IDR rGPIO_IDR;
	bool bitValue = 0;
	
	// Read in the current GPIO input data register
	rGPIO_IDR.d32 = readRegister(GPIO[inputPort].inputDataAddress);
	
	// AND off the bits and shift accordingly
	bitValue = (rGPIO_IDR.d32 >> inputPin) & 0x00000001;
	
	return bitValue;

}



