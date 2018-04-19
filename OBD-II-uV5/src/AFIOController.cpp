/********************************************
*			STM32F105 AFIO Controller							*
*			Developed for the STM32								*
*			Author: Dr. Glenn Matthews						*
*			Source File														*
********************************************/

#include "stm32f10x.h"
#include "utility.h"
#include "afioController.h"

//******************************************************************************//
// Function: afioController()
// Input:
// Output: 
// Description: Default constructor for AFIO Controller
// *****************************************************************************//
AFIOController::AFIOController()
{
	// As the clock control is required everywhere, I have allowed
	// access directly to it.
		
	// Enable AFIO clock and associated registers.
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// Reset the AFIO and wait for 25 microseconds 
	RCC->APB2RSTR |= RCC_APB2RSTR_AFIORST;
	
	delay_software_us(25);
	
	// Clear the AFIO Reset
	
	
	
}

//******************************************************************************//
// Function: ~AFIOController()
// Input:
// Output: 
// Description: Default destructor for SPI Controller
// *****************************************************************************//
AFIOController::~AFIOController()
{
	// Reset the AFIO Controller
	RCC->APB2RSTR |= RCC_APB2RSTR_AFIORST;
	
	// Clear the reset
	
	// Disable the AFIO Controller
	
	
}

//******************************************************************************//
// Function: enablePeripheral()
// Input:
// Output: 
// Description: Enable the clock for a given peripheral.
// *****************************************************************************//
bool AFIOController::enablePeripheral(unsigned char cperipheralID)
{
	
	
	return false;
}

