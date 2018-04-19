/********************************************
*			STM32F105 Utility Functions						*
*			Developed for the STM32								*
*			Author: Dr. Glenn Matthews						*
*			Source File														*
********************************************/


//******************************************************************************//
// Function: delay_software_us()
// Input: Delay time (in microseconds)
// Output: None
// Description: Software driven delay loop.
// *****************************************************************************//
void delay_software_us(unsigned int idelayTime)
{
	// In this function a basic software delay is utilised.
	for(int i = 0; i < (idelayTime * 8); i++);
}


//******************************************************************************//
// Function: delay_software_ms()
// Input: Delay time (in milliseconds)
// Output: None
// Description: Software driven delay loop.
// *****************************************************************************//
void delay_software_ms(unsigned int idelayTime)
{
	// In this function a basic software delay is utilised.
	for(int i = 0; i < (idelayTime * 7250); i++);
}
