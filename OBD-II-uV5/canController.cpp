#include "canController.h"
#include "canRegisters.h"
#include "rccRegisters.h"
#include "utility.h"

/*
void canInit()
{
	// setup the GPIO and AFIO 
	RCC_APB1ENR rAPB1ENR;
	//RCC_APB1RSTR rAPB1RSTR;
	
	// enable the can clocks 
	rAPB1ENR.d32 = canreadRegister(RRCC_APB1ENR);
	rAPB1ENR.b.bcan1en = 1;
	canwriteRegister(RRCC_APB1ENR, rAPB1ENR.d32);
	
	// reset the can interface
	//rAPB2_RSTR.d32;
	
	// enable the CAN clocks 
}

unsigned int canreadRegister(volatile unsigned int * iregisterAddress){
	return (*iregisterAddress);
}
void canwriteRegister(volatile unsigned int * iregisterAddress, unsigned int idataPacket){
	*iregisterAddress = idataPacket;
}
*/