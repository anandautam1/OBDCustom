/* ===============================================================================
// Includes
================================================================================*/

#include "canController.h"
#include "canRegisters.h"
#include "rccRegisters.h"
#include "utility.h"

/* ===============================================================================
// Function Definitions
================================================================================*/

// Functions
void canInit()
{
	RCC_APB1ENR rAPB1ENR;
	RCC APB1RSTR rAPB1RSTR;

	RCC_APB2ENR rAPB2ENR;
	RCC APB2RSTR rAPB2RSTR;

	// Setup the gpio and afio
#ifdef LECTURE_CODE
	// This is enabled in the class implementation
	// Only used for the lecture exammple

	rAPB2ENR.d32 = canreadRegister(RRCC_APB2ENR);
	rAPB2ENR.b.bafioen = 1;
	rAPB2ENR.b.biopden = 1;
	canwriteRegister(RRCC_APB2ENR, rAPB2ENR.d32);

	rAPB2RSTR.d32 = canreadRegister(RRCC_APB2ENR);
	rAPB2RSTR.b.bafiorst = 1;
	rAPB2RSTR.b.biopden = 1;
	canwriteRegister(rAPB2RSTR, rAPB2RSTR.d32);
	delay_software_ms(10);

	rAPB2RSTR.b.bafiorst = 1;
	rAPB2RSTR.b.biopden = 1;
	canwriteRegister(rAPB1RSTR, rAPB1RSTR.d32);
#endif

	// Enable the CAN clocks
	rAPB1ENR = canreadRegister(RRCC_APB1ENR);
	rAPB1ENR.b.bcan1en = 1;
	canwriteRegister(RRCC_APB1ENR, rAPB1ENR.d32);

	// Enable the interface
	rAPB1ENR.d32 = canreadRegister(rAPB1RSTR);
	rAPB1ENR.b.bcan1rst = 1;
	canwriteRegister(rAPB1RSTR, rAPB1RSTR.d32);
	delay_software_ms(10);

	rAPB1ENR.b.bcan1rst = 0;
	canwriteRegister(rAPB1RSTR, rAPB1RSTR.d32);

	// TODO missing lines from lecture

	// Setup Bit timing register
	rCANBTR.d32 = canreadRegister(RCAN_STR);
	rCANBTR.b.bsjw = 0x02;	// 
	rCANBTR.b.bts2 = 0x02;	// Time segment 2	
	rCANBTR.b.bts1 = 0x08;	// Time segment 1
	rCANBTR.b.bbrp = 0x08;	// Baud rate
	rCANBTR.b.blbkn = 0;	// Disable loopback
	canwriteRegister(rCANBTR, rCANBTR.d32);

	// Setup CAN options


}


unsigned int canreadRegister(volatile unsigned int * iregisterAddress)
{
	return (*iregisterAddress);
}

void canwriteRegister(volatile unsigned int * iregisterAddress, unsigned int idataPacket)
{
	*iregisterAddress = idataPacket;
}
