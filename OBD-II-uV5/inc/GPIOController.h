/********************************************
*			STM32F107 GPIO Controller							*
*			Developed for the STM32								*
*			Author: Dr. Glenn Matthews						*
*			Header File														*
********************************************/

// Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_CONTROLLER_H__
#define __GPIO_CONTROLLER_H__

#include "RCCController.h"

//const char GPIO_Speed_2MHz				(unsigned char)	0x02;			
//const char GPIO_Speed_10MHz				(unsigned char) 0x01;
//const char GPIO_Speed_50MHz				(unsigned char) 0x03;

#define MAX_GPIO						(unsigned char) 7						// A maximum of 7 GPIO Ports are available.
	
// Create a struct representing the GPIO Port
typedef struct _GPIO
{
	// Declare all the variables relating to a particular GPIO
	volatile unsigned int * baseAddress;						// The base address of the GPIO Port
	volatile unsigned int * configLowAddress;			// GPIO Low Configuration (bits 0 - 7)
	volatile unsigned int * configHighAddress;			// GPIO High Configuration (bits 8 - 16)
	volatile unsigned int * inputDataAddress;			// GPIO Input Data Register
	volatile unsigned int * outputDataAddress;			// GPIO Output Data Register
	volatile unsigned int * bitSetAddress;					// GPIO Bit Set Register
	volatile unsigned int * bitResetAddress;				// GPIO Bit Clear Register
	volatile unsigned int * bitLockAddress;				// GPIO Lock Bit Register

	bool clockEnabled;										// Has the clock been enabled.
	
	
} GPIO_Port;

// Friendly name for the GPIO Prts (external use only)
typedef enum {GPIO_A = 0, GPIO_B, GPIO_C,	GPIO_D,	GPIO_E,	GPIO_F,	GPIO_G} GPIOPort;
typedef enum {Pin0 = 0, Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7, Pin8, Pin9, Pin10, Pin11, Pin12, Pin13, Pin14, Pin15}GPIOPin;
typedef enum {GPIO_Reserved = 0, GPIO_10MHz, GPIO_2MHz, GPIO_50MHz }GPIOSpeed;
typedef enum {GPIO_Output_PushPull = 0, GPIO_Output_OpenDrain, GPIO_AF_PushPull, GPIO_AF_OpenDrain, GPIO_Input_Analog, GPIO_Input_Floating, GPIO_Input_PullUpDown}GPIOType;

typedef enum {PER_SPI1, PER_SPI2, PER_SPI3, PER_CAN1, PER_CAN2, PER_ADC1, PER_ADC2, PER_ADC3}GPIOPeripheral;			// Peripheral to enable GPIO configuration (not all are used yet)
typedef enum {AF0, AF1, AF2, REMAP0, REMAP1, REMAP2} GPIORemap;											// Peripheral configuration (Alternate function or remap)

// Port configuration bits.
#define GPIO_OUT_PP			(unsigned char)	0
#define GPIO_OUT_OD			(unsigned char) 1
#define GPIO_AF_PP			(unsigned char) 2
#define GPIO_AF_OD			(unsigned char) 3

#define GPIO_IN_AN			(unsigned char) 0
#define GPIO_IN_FL			(unsigned char) 1
#define GPIO_IN_PUPD		(unsigned char) 2
		



typedef struct
{
		GPIOPort Port;			// GPIO Port on which the pin resides.
		GPIOPin  Pin;				// The actual pin to modify (0 through to 15).
		GPIOSpeed Speed;		// The maximum speed of the pin (2, 10 or 50MHz)
		GPIOType Type;			// The GPIO Type (input, output, open drain, etc);
		
} GPIO_Config;


class GPIOController
{	
	private:
		unsigned int readRegister(volatile unsigned int *);							// Read a value from the 32-bit ARM register
		void writeRegister(volatile unsigned int * , unsigned int);			// Write to a 32-bit ARM register
	
		void enableGPIOClock(GPIOPort);											// Enable the clock for a given GPIO
	
		void enableCAN(GPIOPeripheral, GPIORemap);							// Perform CAN specific AFIO / GPIO configuration.
	
		RCCController * RCCControl;															// Provides acccess to the Reset and Clock Control System
	
	public:
		GPIOController(RCCController *);				// Default constructor
		~GPIOController();													// Default destructor

		// Define variables
		GPIO_Port GPIO[MAX_GPIO];													// Create an array of GPIO Ports (Maximum of 7 GPIO Ports).
	
		bool configureGPIO(GPIO_Config *);								// Configure the GPIO Pin of interest
	
		void enablePeripheral(GPIOPeripheral, GPIORemap);
		void enableSPI(GPIOPeripheral, GPIORemap, bool);															// Configure the SPI Controller (the bool is used to select an external slave select)			
		void enableSPIChipSelect(GPIOPort, GPIOPin);																	// Enable the external SPI chip select pin
		void enableADC(GPIOPeripheral, GPIOPort * , GPIOPin *, unsigned char);				// Enable the ADC 
		
		bool getPinValue(GPIOPort, GPIOPin);												// Obtain the current value of an I/O pin (IDR)
		void setGPIO(GPIOPort, GPIOPin);														// Set an individual I/O Pin
		void resetGPIO(GPIOPort, GPIOPin);													// Clear an individual I/O Pin
};


#endif
