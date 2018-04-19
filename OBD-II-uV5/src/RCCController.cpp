/********************************************
*			STM32F107 GPIO Controller							*
*			Developed for the STM32								*
*			Author: Dr. Glenn Matthews						*
*			Source File														*
********************************************/

#include "stm32f10x.h"
#include "utility.h"
#include "rccRegisters.h"
#include "RCCController.h"

// The RCC Controller is designed to take care of the clock control
// for the various devices on the STM32F107. 

// The main crystal on the board is 25MHz


// The maximum speed on the APB1 domain is 36MHz.
// The maximum speed on the APB2 domain is 72MHz

// Each additional peripheral will contain a pointer to the RCC Controller.

//******************************************************************************//
// Function: RCCController()
// Input:
// Output: 
// Description: Default constructor for RCC Controller
// *****************************************************************************//
RCCController::RCCController()
{
	// Set the APB1 (low speed) clock to 36MHz.
	setAPB1Clock();
	
}

//******************************************************************************//
// Function: ~RCCController()
// Input:
// Output: 
// Description: Default destructor for RCC Controller
// *****************************************************************************//
RCCController::~RCCController()
{
	
	
	
}

//******************************************************************************//
// Function: readRegister()
// Input : Register to read from.
// Return : Data from the register of interest
// Description : Read from a 32-bit ARM register
// *****************************************************************************//
unsigned int RCCController::readRegister(volatile unsigned int * iregisterAddress)	
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
void RCCController::writeRegister(volatile unsigned int * iregisterAddress , unsigned int idataPacket)
{
	// The register address passed in is already a pointer so 
	// it is just a matter of changing the contents.
	*iregisterAddress = idataPacket;

}
//******************************************************************************//
// Function: setAPB1Clock()
// Input : The peripheral to enable and the configuration
// Return : None
// Description : Enable the Alternate function (AFIO) and GPIO for the required periperhal
// *****************************************************************************//

// this code was uncommented as it needs to set he clock of the 
void RCCController::setAPB1Clock(void)
{
	RCC_CFGR rRCC_CFGR;
	
	rRCC_CFGR.d32 = readRegister(RRCC_CFGR);
	
	// Set the ABP1 Domain Clock to 36MHz.
	rRCC_CFGR.b.bppre1 |= 0x08;
	
	writeRegister(RRCC_CFGR, rRCC_CFGR.d32);
	
}
//******************************************************************************//
// Function: enablePeriperhal()
// Input : The peripheral to enable and the configuration
// Return : None
// Description : Enable the Alternate function (AFIO) and GPIO for the required periperhal
// *****************************************************************************//
void RCCController::enablePeripheral(RCCPeripheral inputDevice)
{
	// This function configures the basic GPIO requirements for a given set of 
	// peripherals. The alternate function registers are configured (and AF / GPIO clocks)
	// enabled. The actual peripheral clocks are NOT enaled.
	
	switch(inputDevice)
	{
		case RCC_AFIO:
		case RCC_GPIOA:
		case RCC_GPIOB:
		case RCC_GPIOC:
		case RCC_GPIOD:
		case RCC_GPIOE:
		case RCC_GPIOF:
		case RCC_GPIOG:
		{
			// A GPIO clock domain has been requested.
			enableGPIO(inputDevice);
			break;
		}

		case RCC_SPI1:
		case RCC_SPI2:
		case RCC_SPI3:
		{
			enableSPI(inputDevice);
			break;
		}		
		case RCC_CAN1:
		case RCC_CAN2:
		{
			enableCAN(inputDevice);
			break;
		}
		
		case RCC_ADC1:
		case RCC_ADC2:
		case RCC_ADC3:
		{
			enableADC(inputDevice);
			break;
		}
	}
		
}

//******************************************************************************//
// Function: enableGPIO()
// Input : The GPIO port to enable (and reset)
// Return : None
// Description : Enable the GPIO port and perform a reset.
// *****************************************************************************//
void RCCController::enableGPIO(RCCPeripheral inputDevice)
{
	// All GPIO device clocks are on the APB2 enable bus
	RCC_APB2ENR rAPB2ENR;
	RCC_APB2RSTR rAPB2RST;
	
	// Read the current value of the enable and reset registers
	rAPB2ENR.d32 = readRegister(RRCC_APB2ENR);
	rAPB2RST.d32 = readRegister(RRCC_APB2RSTR);
	
	switch(inputDevice)
	{
		case RCC_AFIO:
		{
			
			// Check to see whether the AFIO has previously been initialised.
			if(rAPB2ENR.b.bafioen == 0)
			{
				// Set the enable for the AFIO
				rAPB2ENR.b.bafioen = 1;
				
				// Write the register back
				writeRegister(RRCC_APB2ENR, rAPB2ENR.d32);
				
				// Enable the reset register.
				rAPB2RST.b.bafiorst = 1;
				writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
				
				delay_software_us(10);
				rAPB2RST.b.bafiorst = 0;
				writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			}
			break;
		}
		case RCC_GPIOA:
		{
			// Set the enable for GPIO Port A
			rAPB2ENR.b.biopaen = 1;
			
			// Write the register back
			writeRegister(RRCC_APB2ENR, rAPB2ENR.d32);
			
			// Enable the reset register.
			rAPB2RST.b.bioparst = 1;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			delay_software_us(10);
			rAPB2RST.b.bioparst = 0;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			break;
		}
		case RCC_GPIOB:
		{
			// Set the enable for GPIO Port B
			rAPB2ENR.b.biopben = 1;
			
			// Write the register back
			writeRegister(RRCC_APB2ENR, rAPB2ENR.d32);
			
			// Enable the reset register.
			rAPB2RST.b.biopbrst = 1;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			delay_software_us(10);
			rAPB2RST.b.biopbrst = 0;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			break;
		}
		case RCC_GPIOC:
		{
			// Set the enable for GPIO Port C
			rAPB2ENR.b.biopcen = 1;
			
			// Write the register back
			writeRegister(RRCC_APB2ENR, rAPB2ENR.d32);
			
			// Enable the reset register.
			rAPB2RST.b.biopcrst = 1;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			delay_software_us(10);
			rAPB2RST.b.biopcrst = 0;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			break;
		}	
		case RCC_GPIOD:
		{
			// Set the enable for GPIO Port D
			rAPB2ENR.b.biopden = 1;
			
			// Write the register back
			writeRegister(RRCC_APB2ENR, rAPB2ENR.d32);
			
			// Enable the reset register.
			rAPB2RST.b.biopdrst = 1;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			delay_software_us(10);
			rAPB2RST.b.biopdrst = 0;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			break;
		}
		case RCC_GPIOE:
		{
			// Set the enable for GPIO Port E
			rAPB2ENR.b.biopeen = 1;
			
			// Write the register back
			writeRegister(RRCC_APB2ENR, rAPB2ENR.d32);
			
			// Enable the reset register.
			rAPB2RST.b.bioperst = 1;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			delay_software_us(10);
			rAPB2RST.b.bioperst = 0;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			break;
		}
		case RCC_GPIOF:
		case RCC_GPIOG:
		{
			// GPIO ports F and G do not exist on the connectivity line of devices (but may on others)
		}
		default:
		{
			break;
		}
			
	}
}

//******************************************************************************//
// Function: enableSPI()
// Input : The SPI port to enable (and reset)
// Return : None
// Description : Enable the GPIO port and perform a reset.
// *****************************************************************************//
void RCCController::enableSPI(RCCPeripheral inputDevice)
{
	// Register definitions for APB1 (low speed bus - 36MHz)
	RCC_APB1ENR rAPB1ENR;
	RCC_APB1RSTR rAPB1RST;
	
	// Register definitions for APB2 (high speed bus - 72MHz)
	RCC_APB2ENR rAPB2ENR;
	RCC_APB2RSTR rAPB2RST;
	
	switch(inputDevice)
	{
		case RCC_SPI1:
		{
			// SP1 is on the high speed ABP2 bus.
			// Read the current value of the enable and reset registers
			rAPB2ENR.d32 = readRegister(RRCC_APB2ENR);
			rAPB2RST.d32 = readRegister(RRCC_APB2RSTR);
			
			// Set the enable for SPI1
			rAPB2ENR.b.bspi1en = 1;
			
			// Write the register back
			writeRegister(RRCC_APB2ENR, rAPB2ENR.d32);
			
			// Enable the reset register.
			rAPB2RST.b.bspi1rst = 1;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			delay_software_us(10);
			rAPB2RST.b.bspi1rst = 0;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			break;
		}
		case RCC_SPI2:
		{
			// SPI 2 is on the low speed ABP1 bus.
			rAPB1ENR.d32 = readRegister(RRCC_APB1ENR);
			rAPB1RST.d32 = readRegister(RRCC_APB1RSTR);
			
			// Set the enable for SPI2
			rAPB1ENR.b.bspi2en = 1;
			
			// Write the register back
			writeRegister(RRCC_APB1ENR, rAPB1ENR.d32);
			
			// Enable the reset register.
			rAPB1RST.b.bspi2rst = 1;
			writeRegister(RRCC_APB1RSTR, rAPB1RST.d32);
			
			delay_software_us(10);
			rAPB1RST.b.bspi2rst = 0;
			writeRegister(RRCC_APB1RSTR, rAPB1RST.d32);
			
			break;
		}
		case RCC_SPI3:
		{
			// SPI 3 is on the low speed ABP1 bus.
			rAPB1ENR.d32 = readRegister(RRCC_APB1ENR);
			rAPB1RST.d32 = readRegister(RRCC_APB1RSTR);
			
			// Set the enable for SPI2
			rAPB1ENR.b.bspi3en = 1;
			
			// Write the register back
			writeRegister(RRCC_APB1ENR, rAPB1ENR.d32);
			
			// Enable the reset register.
			rAPB1RST.b.bspi3rst = 1;
			writeRegister(RRCC_APB1RSTR, rAPB1RST.d32);
			
			delay_software_us(10);
			rAPB1RST.b.bspi3rst = 0;
			writeRegister(RRCC_APB1RSTR, rAPB1RST.d32);
				
			break;
		}	
		default:
		{
			break;
		}
			
	}
}
//******************************************************************************//
// Function: enableCAN()
// Input : The CAN port to enable (and reset)
// Return : None
// Description : Enable the CAN port and perform a reset.
// *****************************************************************************//
void RCCController::enableCAN(RCCPeripheral inputDevice)
{
	// All GPIO device clocks are on the APB2 enable bus
	RCC_APB1ENR rAPB1ENR;
	RCC_APB1RSTR rAPB1RST;
	
	// Read the current value of the enable and reset registers
	rAPB1ENR.d32 = readRegister(RRCC_APB1ENR);
	rAPB1RST.d32 = readRegister(RRCC_APB1RSTR);
	
	switch(inputDevice)
	{
		case RCC_CAN1:
		{
			// Set the enable for CAN Controller 1
			rAPB1ENR.b.bcan1en = 1;
			
			// Write the register back
			writeRegister(RRCC_APB1ENR, rAPB1ENR.d32);
			
			// Enable the reset register.
			rAPB1RST.b.bcan1rst = 1;
			writeRegister(RRCC_APB1RSTR, rAPB1RST.d32);
			
			delay_software_us(10);
			rAPB1RST.b.bcan1rst = 0;
			writeRegister(RRCC_APB1RSTR, rAPB1RST.d32);
			
			break;
		}
		case RCC_CAN2:
		{
			// Set the enable for CAN Controller 2
			rAPB1ENR.b.bcan2en = 1;
			
			// Write the register back
			writeRegister(RRCC_APB1ENR, rAPB1ENR.d32);
			
			// Enable the reset register.
			rAPB1RST.b.bcan2rst = 1;
			writeRegister(RRCC_APB1RSTR, rAPB1RST.d32);
			
			delay_software_us(10);
			rAPB1RST.b.bcan2rst = 0;
			writeRegister(RRCC_APB1RSTR, rAPB1RST.d32);

			break;
		}
		default:
		{
			break;
		}
			
	}
}

//******************************************************************************//
// Function: enableADC()
// Input : The CAN port to enable (and reset)
// Return : None
// Description : Enable the CAN port and perform a reset.
// *****************************************************************************//
void RCCController::enableADC(RCCPeripheral inputDevice)
{
	// All GPIO device clocks are on the APB2 enable bus
	RCC_CFGR rCFGR;
	RCC_APB2ENR rAPB2ENR;
	RCC_APB2RSTR rAPB2RST;
	

	// The ADC has a maximum clock frequency of 14MHz. Given that the APB2 bus
	// is running at 72MHz, the ADC must be dvided down by 6 (12MHz), which is done
	// via the RCC_CFGR
	
	rCFGR.d32 = readRegister(RRCC_CFGR);
	rCFGR.b.badcpre = 0x02;
	writeRegister(RRCC_CFGR, rCFGR.d32);
	
	// Read the current value of the enable and reset registers
	rAPB2ENR.d32 = readRegister(RRCC_APB2ENR);
	rAPB2RST.d32 = readRegister(RRCC_APB2RSTR);
	
	switch(inputDevice)
	{
		case RCC_ADC1:
		{
			// Set the enable for ADC Converter 1
			rAPB2ENR.b.badc1en = 1;
			
			// Write the register back
			writeRegister(RRCC_APB2ENR, rAPB2ENR.d32);
			
			// Enable the reset register.
			rAPB2RST.b.badc1rst = 1;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			delay_software_us(10);
			rAPB2RST.b.badc1rst = 0;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			break;
		}
		case RCC_ADC2:
		{
			// Set the enable for ADC Converter 2
			rAPB2ENR.b.badc2en = 1;
			
			// Write the register back
			writeRegister(RRCC_APB2ENR, rAPB2ENR.d32);
			
			// Enable the reset register.
			rAPB2RST.b.badc2rst = 1;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);
			
			delay_software_us(10);
			rAPB2RST.b.badc2rst = 0;
			writeRegister(RRCC_APB2RSTR, rAPB2RST.d32);

			break;
		}
		case RCC_ADC3:
		{
			// This doesn't appear to be implemented in the clock domain?
			
		}
		default:
		{
			break;
		}
			
	}
}
