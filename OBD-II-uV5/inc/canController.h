/* ===============================================================================
// Includes
================================================================================*/


/* ===============================================================================
// Definitions
================================================================================*/
#ifndef __CAN_CONTROLLER_H__
#define __CAN_CONTROLLER_H__
#endif

/* ===============================================================================
// Function Prototypes
================================================================================*/

void canInit();	// Itialize the CAN peripheral

unsigned int canreadRegister(volatile unsigned int * iregisterAddress);
void canwriteRegister(volatile unsigned int * iregisterAddress, unsigned int idataPacket);
 
// EOF
