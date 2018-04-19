/********************************************
*			STM32F105/7 Connectivity Line 				*
*			ADC Register Descriptions						  *
*			Author: Dr. Glenn Matthews						*
*			Header File														*
********************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_REGS_H__
#define __ADC_REGS_H__

#include "stm32f10x.h"

// ADC Base Address (Connected to APB2)
#define ADC1_BASE_ADDR												0x40012400		
#define ADC2_BASE_ADDR												0x40012800		
#define ADC3_BASE_ADDR												0x40013C00
	
// Define the RCC register offsets.
#define RADC_SR																0x00				// Status Register
#define RADC_CR1															0x04				// Control Register 1
#define RADC_CR2															0x08				// Control Register 2
#define RADC_SMPR1														0x0C				// Sample Time Register 1
#define RADC_SMPR2														0x10				// Sample Time Register 2
#define RADC_JOFR1														0x14				// Injected Channel Data Offset Register 1
#define RADC_JOFR2														0x18				// Injected Channel Data Offset Register 2
#define RADC_JOFR3														0x1C				// Injected Channel Data Offset Register 3
#define RADC_JOFR4														0x20				// Injected Channel Data Offset Register 4
#define RADC_HTR															0x24				// Watchdog High Threshold Register
#define RADC_LTR															0x28				// Watchdog Low Threshold Register
#define RADC_SQR1															0x2C				// Regular Sequence 1 Register
#define RADC_SQR2															0x30				// Regular Sequence 2 Register
#define RADC_SQR3															0x34				// Regular Sequence 3 Register 
#define RADC_JSQR															0x38				// Injected Channel Sequence Register
#define RADC_JDR1															0x3C				// Inject Channel Data Register 1
#define RADC_JDR2															0x40				// Inject Channel Data Register 2
#define RADC_JDR3															0x44				// Inject Channel Data Register 3
#define RADC_JDR4															0x48				// Inject Channel Data Register 4
#define RADC_DR																0x4C				// Regular Channel Data Register

// Typdef for the various registers (this will allow for single-bit manipulation)
typedef union _ADC_SR 						/* Address offset: 0x000 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bawd: 1;	
		unsigned int beoc: 1;
		unsigned int bjeoc: 1;
		unsigned int bjstrt: 1;
		unsigned int bstrt: 1;		
		unsigned int bReserved5_32: 27;
  }  b;
} ADC_SR;

typedef union _ADC_CR1 						/* Address offset: 0x04 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bawdch4: 5;	
		unsigned int beocie: 1;
		unsigned int bawdie: 1;
		unsigned int bjeocie: 1;
		unsigned int bscan: 1;		
		unsigned int bawdsgl: 1;
		unsigned int bjauto: 1;
		unsigned int bdiscen: 1;
		unsigned int bjdiscen: 1;
		unsigned int bdiscnum: 3;
		unsigned int bdualmod: 4;
		unsigned int bReserved20_21: 2;
		unsigned int bjawden: 1;
		unsigned int bawden: 1;
		unsigned int bReserved24_31: 8;
  }  b;
} ADC_CR1 ;

typedef union _ADC_CR2 						/* Address offset: 0x08 */
{
  uint32_t d32;
  struct
  {		
		unsigned int badon: 1;	
		unsigned int bcont: 1;
		unsigned int bcal: 1;
		unsigned int brstcal: 1;
		unsigned int bReserved4_7: 4;		
		unsigned int bdma: 1;
		unsigned int bReserved9_10: 2;
		unsigned int balign: 1;
		unsigned int bjextsel: 3;
		unsigned int bjexttrig: 1;
		unsigned int bReserved16: 1;
		unsigned int bextsel: 3;
		unsigned int bexttrig: 1;
		unsigned int bjswstart: 1;
		unsigned int bswstart: 1;
		unsigned int btsvrefe: 1;
		unsigned int bReserver24_31: 8;
  }  b;
} ADC_CR2 ;

typedef union _ADC_SMPR1 						/* Address offset: 0x0C */
{
  uint32_t d32;
  struct
  {		
		unsigned int bsmp10: 3;	
		unsigned int bsmp11: 3;
		unsigned int bsmp12: 3;
		unsigned int bsmp13: 3;
		unsigned int bsmp14: 3;		
		unsigned int bsmp15: 3;
		unsigned int bsmp16: 3;
		unsigned int bsmp17: 3;
		unsigned int bReserved24_31: 8;
  }  b;
} ADC_SMPR1 ;

typedef union _ADC_SMPR2						/* Address offset: 0x010 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bsmp0: 3;	
		unsigned int bsmp1: 3;
		unsigned int bsmp2: 3;
		unsigned int bsmp3: 3;
		unsigned int bsmp4: 3;		
		unsigned int bsmp5: 3;
		unsigned int bsmp6: 3;
		unsigned int bsmp7: 3;
		unsigned int bsmp8: 3;
		unsigned int bsmp9: 3;
		unsigned int bReserved30_31: 2;
  }  b;
} ADC_SMPR2;

typedef union _ADC_JOFRx 						/* Address offset: 0x14 - 0x20 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bjoffset: 12;	
		unsigned int bReserved12_31: 20;
  }  b;
} ADC_JOFRx ;

typedef union _ADC_HTR 						/* Address offset: 0x24 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bht: 12;	
		unsigned int bReserved12_31: 20;
  }  b;
} ADC_HTR;

typedef union _ADC_LTR						/* Address offset: 0x28 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bltr: 12;	
		unsigned int bReserved12_31: 20;
  }  b;
} ADC_LTR ;

typedef union _ADC_SQR1						/* Address offset: 0x2C */
{
  uint32_t d32;
  struct
  {		
		unsigned int bsq13: 5;	
		unsigned int bsq14: 5;
		unsigned int bsq15: 5;
		unsigned int bsq16: 5;
		unsigned int bl: 4;		
		unsigned int bReserved24_31: 8;
  }  b;
} ADC_SQR1 ;

typedef union _ADC_SQR2 						/* Address offset: 0x30 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bsq7: 5;	
		unsigned int bsq8: 5;
		unsigned int bsq9: 5;
		unsigned int bsq10: 5;
		unsigned int bsq11: 5;		
		unsigned int bsq12: 5;
		unsigned int bReserved30_31: 2;
  }  b;
} ADC_SQR2 ;

typedef union _ADC_SQR3 						/* Address offset: 0x34 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bsq1: 5;	
		unsigned int bsq2: 5;
		unsigned int bsq3: 5;
		unsigned int bsq4: 5;
		unsigned int bsq5: 5;		
		unsigned int bsq6: 5;
		unsigned int bReserved30_31: 2;
  }  b;
} ADC_SQR3 ;

typedef union _ADC_JSQR 						/* Address offset: 0x38 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bjsq1: 5;	
		unsigned int bjsq2: 5;
		unsigned int bjsq3: 5;
		unsigned int bjsq4: 5;
		unsigned int bjl: 2;		
		unsigned int bReserved22_31: 10;
  }  b;
} ADC_JSQR ;

typedef union _ADC_JDRx 						/* Address offset: 0x3C - 0x48 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bjdata: 16;	
		unsigned int bReserved16_31: 16;
  }  b;
} ADC_JDRx ;

typedef union _ADC_DR 						/* Address offset: 0x04C */
{
  uint32_t d32;
  struct
  {		
		unsigned int bdata: 16;	
		unsigned int badc2data: 16;
  }  b;
} ADC_DR ;


#endif 

