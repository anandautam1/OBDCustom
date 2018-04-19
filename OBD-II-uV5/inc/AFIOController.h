/********************************************
*			STM32F407 SPI Controller							*
*			Developed for the STM32								*
*			Author: Dr. Glenn Matthews						*
*			Header File														*
********************************************/

class AFIOController
{	
	private:
		
	public:
		AFIOController();							// Default constructor
		~AFIOController();												// Default destructor
			
	bool enablePeripheral(unsigned char);				// Enable the clock for a given peripheral.
};
