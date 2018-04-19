/********************************************
*			STM32F105/7 Connectivity Line 				*
*			GPIO and AFIO Register Descriptions		*
*			Author: Dr. Glenn Matthews						*
*			Header File														*
********************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_REGS_H__
#define __GPIO_REGS_H__

// GPIO Base Address (Connected to APB2)
#define GPIOA_BASE_ADDR											0x40010800		
#define GPIOB_BASE_ADDR											0x40010C00		
#define GPIOC_BASE_ADDR											0x40011000		
#define GPIOD_BASE_ADDR											0x40011400		
#define GPIOE_BASE_ADDR											0x40011800		
#define GPIOF_BASE_ADDR											0x40011C00		
#define GPIOG_BASE_ADDR											0x40012000	

// Alternate Function Base Address (Connected to APB2)
#define AFIO_BASE_ADDR											0x40010000

// Define the GPIO register offsets.
#define RGPIO_CRL								0x00
#define RGPIO_CRH								0x04
#define RGPIO_IDR								0x08
#define RGPIO_ODR								0x0C
#define RGPIO_BSRR							0x10
#define RGPIO_BRR								0x14
#define RGPIO_LCKR							0x18

// Define the AFIO register offsets
#define RAFIO_EVCR							(unsigned int *) (AFIO_BASE_ADDR + 0x00)
#define RAFIO_MAPR							(unsigned int *) (AFIO_BASE_ADDR + 0x04)
#define RAFIO_EXTICR1						(unsigned int *) (AFIO_BASE_ADDR + 0x08)
#define RAFIO_EXTICR2						(unsigned int *) (AFIO_BASE_ADDR + 0x0C)
#define RAFIO_EXTICR3						(unsigned int *) (AFIO_BASE_ADDR + 0x10)
#define RAFIO_EXTICR4						(unsigned int *) (AFIO_BASE_ADDR + 0x14)
#define RAFIO_MAPR2							(unsigned int *) (AFIO_BASE_ADDR + 0x1C0
	
// Offset of each GPIO Port
#define GPIO_OFFSET							0x400	

// As the GPIO registers are repeated through memory (just with an offset),
// there is no need to define all of the individual register addresses.
// Instead, when writing to the GPIO register, the base address is passed
// in and then the respective offset.

// Typdef for the various registers (this will allow for single-bit manipulation)
typedef union _GPIO_CRL 						/* Address offset: 0x00 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bmode0 : 2;	
		unsigned int bcnf0 : 2;
		unsigned int bmode1 : 2;
		unsigned int bcnf1 : 2;
		unsigned int bmode2: 2;		
		unsigned int bcnf2 : 2;
		unsigned int bmode3 : 2;
		unsigned int bcnf3 : 2;
		unsigned int bmode4 : 2;
		unsigned int bcnf4 : 2;
		unsigned int bmode5 : 2;
		unsigned int bcnf5: 2;
		unsigned int bmode6 : 2;
		unsigned int bcnf6 : 2;
		unsigned int bmode7 : 2;
		unsigned int bcnf7 : 2;
  }  b;
} GPIO_CRL ;

typedef union _GPIO_CRH 						/* Address offset: 0x04 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bmode8 : 2;	
		unsigned int bcnf8 : 2;
		unsigned int bmode9 : 2;
		unsigned int bcnf9 : 2;
		unsigned int bmode10: 2;		
		unsigned int bcnf10 : 2;
		unsigned int bmode11 : 2;
		unsigned int bcnf11 : 2;
		unsigned int bmode12 : 2;
		unsigned int bcnf12 : 2;
		unsigned int bmode13 : 2;
		unsigned int bcnf13: 2;
		unsigned int bmode14 : 2;
		unsigned int bcnf14 : 2;
		unsigned int bmode15 : 2;
		unsigned int bcnf15 : 2;
  }  b;
} GPIO_CRH ;


typedef union _GPIO_IDR 						/* Address offset: 0x08 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bidry : 16;	
		unsigned int bReserved16_31 : 16;
	
  }  b;
} GPIO_IDR ;

typedef union _GPIO_ODR 						/* Address offset: 0x0C */
{
  unsigned int d32;
  struct
  {		
		unsigned int bodry : 16;	
		unsigned int bReserved16_31 : 16;
	
  }  b;
} GPIO_ODR ;

typedef union _GPIO_BSRR 						/* Address offset: 0x10 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bbsr : 16;	
		unsigned int bbr : 16;
	
  }  b;
} GPIO_BSRR ;

typedef union _GPIO_BRR							/* Address offset: 0x14 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bbr : 16;	
		unsigned int bReserved16_31 : 16;
	
  }  b;
} GPIO_BRR ;

typedef union _GPIO_LCKR 						/* Address offset: 0x18 */
{
  unsigned int d32;
  struct
  {		
		unsigned int blck : 16;	
		unsigned int blckk: 1;
		unsigned int bReserved17_31 : 15;	
  }  b;
} GPIO_LCKR ;

// ************************************* Alternate Function Definitions **********************************
typedef union _AFIO_EVCR 						/* Address offset: 0x00 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bpin : 4;	
		unsigned int bport: 3;
		unsigned int bevoe: 1;
		unsigned int bReserved7_31 : 24;	
  }  b;
} AFIO_EVCR ;

typedef union _AFIO_MAPR 						/* Address offset: 0x04 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bspi1_remap: 1;	
		unsigned int bi2c1_remap: 1;
		unsigned int busart1_remap: 1;
		unsigned int busart2_remap: 1;
		unsigned int busart3_remap: 2;		
		unsigned int btim1_remap : 2;
		unsigned int btim2_remap : 2;
		unsigned int btim3_remap : 2;
		unsigned int btim4_remap : 1;
		unsigned int bcan1_remap : 2;
		unsigned int bpd01_remap : 1;
		unsigned int btim5ch4_iremap: 1;
		unsigned int bReserved17_20 : 4;
		unsigned int beth_remap : 1;
		unsigned int bcan2_remap : 1;
		unsigned int bmii_rmii_sel:1;
		unsigned int bswj_cfg : 3;
		unsigned int bReserved27 : 1;
		unsigned int bspi3_remap : 1;
		unsigned int btim2itr1_iremap : 1;
		unsigned int bptp_pps_remap : 1;
		unsigned int bReserved31 : 1;
  }  b;
} AFIO_MAPR ;

typedef union _AFIO_EXTICR1 						/* Address offset: 0x08 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bexti0: 4;	
		unsigned int bexti1: 4;
		unsigned int bexti2: 4;
		unsigned int bexti3: 4;
		unsigned int bReserved16_31: 16;		
  }  b;
} AFIO_EXTICR1 ;

typedef union _AFIO_EXTICR2 						/* Address offset: 0x08 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bexti4: 4;	
		unsigned int bexti5: 4;
		unsigned int bexti6: 4;
		unsigned int bexti7: 4;
		unsigned int bReserved16_31: 16;		
  }  b;
} AFIO_EXTICR2 ;

typedef union _AFIO_EXTICR3 						/* Address offset: 0x08 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bexti8: 4;	
		unsigned int bexti9: 4;
		unsigned int bexti10:4;
		unsigned int bexti11: 4;
		unsigned int bReserved16_31: 16;		
  }  b;
} AFIO_EXTICR3 ;

typedef union _AFIO_EXTICR4 						/* Address offset: 0x08 */
{
  unsigned int d32;
  struct
  {		
		unsigned int bexti12: 4;	
		unsigned int bexti13: 4;
		unsigned int bexti14: 4;
		unsigned int bexti15: 4;
		unsigned int bReserved16_31: 16;		
  }  b;
} AFIO_EXTICR4 ;

typedef union _AFIO_MAPR2 						/* Address offset: 0x1C */
{
  unsigned int d32;
  struct
  {		
		unsigned int btim15_remap: 1;	
		unsigned int btim16_remap: 1;
		unsigned int btim17_remap: 1;
		unsigned int bcec_remap: 1;
		unsigned int btim1_dma_remap: 1;		
		unsigned int btim9_remap: 1;	
		unsigned int btim10_remap: 1;
		unsigned int btim11_remap: 1;
		unsigned int btim13_remap: 1;	
		unsigned int btim14_remap: 1;
		unsigned int bfsmc_nadv: 1;
		unsigned int btim67_dac_dma_remap: 1;
		unsigned int btim12_remap: 1;
		unsigned int bmisc_remap: 1;
		unsigned int bReserved14_31: 17;  
  }  b;
} AFIO_MAPR2 ;

#endif 

