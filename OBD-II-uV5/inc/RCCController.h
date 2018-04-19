/********************************************
*			STM32F107 RCC Controller							*
*			Developed for the STM32								*
*			Author: Dr. Glenn Matthews						*
*			Header File														*
********************************************/

// Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RCC_CONTROLLER_H__
#define __RCC_CONTROLLER_H__

// Friendly name for the RCC Peripherals Devices (external use only)
typedef enum {RCC_AFIO, RCC_GPIOA, RCC_GPIOB, RCC_GPIOC, RCC_GPIOD, RCC_GPIOE, RCC_GPIOF, RCC_GPIOG, RCC_SPI1, RCC_SPI2, RCC_SPI3, RCC_CAN1, RCC_CAN2, RCC_ADC1, RCC_ADC2, RCC_ADC3} RCCPeripheral;			// Peripheral to enable clock configuration (not all are used yet)

class RCCController
{	
	private:
		unsigned int readRegister(volatile unsigned int *);							// Read a value from the 32-bit ARM register
		void writeRegister(volatile unsigned int * , unsigned int);			// Write to a 32-bit ARM register
	
		void setAPB1Clock();
		void enableGPIO(RCCPeripheral);													// Enable (and reset) any GPIO Port
		void enableCAN(RCCPeripheral);													// Enable (and reset) any CAN Port
		void enableSPI(RCCPeripheral);													// Enable (and reset) any SPI Port
		void enableADC(RCCPeripheral);													// Enable (and reset) and ADC Port
	
	public:
		RCCController();																				// Default constructor
		~RCCController();																				// Default destructor
	
		void enablePeripheral(RCCPeripheral inputDevice);

};


#endif
