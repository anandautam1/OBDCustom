/********************************************
*			STM32F105/7 Connectivity Line 				*
*			RCC Register Descriptions						  *
*			Author: Dr. Glenn Matthews						*
*			Header File														*
********************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RCC_REGS_H__
#define __RCC_REGS_H__

#include "stm32f10x.h"

// RCC Base Address (Connected to APB2)
#define RCC_BASE_ADDR												0x40021000		
	
// Define the RCC register offsets.
#define RRCC_CR									(unsigned int *) (RCC_BASE_ADDR + 0x000)
#define RRCC_CFGR								(unsigned int *) (RCC_BASE_ADDR + 0x004)
#define RRCC_CIR								(unsigned int *) (RCC_BASE_ADDR + 0x008)
#define RRCC_APB2RSTR						(unsigned int *) (RCC_BASE_ADDR + 0x00C)
#define RRCC_APB1RSTR 					(unsigned int *) (RCC_BASE_ADDR + 0x010)
#define RRCC_AHBENR							(unsigned int *) (RCC_BASE_ADDR + 0x014)
#define RRCC_APB2ENR						(unsigned int *) (RCC_BASE_ADDR + 0x018)
#define RRCC_APB1ENR						(unsigned int *) (RCC_BASE_ADDR + 0x01C)
#define RRCC_BDCR								(unsigned int *) (RCC_BASE_ADDR + 0x020)
#define RRCC_CSR								(unsigned int *) (RCC_BASE_ADDR + 0x024)
#define RRCC_AHBSTR							(unsigned int *) (RCC_BASE_ADDR + 0x028)
#define RRCC_CFGR2							(unsigned int *) (RCC_BASE_ADDR + 0x02C)

// Typdef for the various registers (this will allow for single-bit manipulation)
typedef union _RCC_CR 						/* Address offset: 0x000 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bhsion: 1;	
		unsigned int bhsirdy: 1;
		unsigned int bReserved: 1;
		unsigned int bhsitrim: 5;
		unsigned int bhsical: 8;		
		unsigned int bhseon: 1;
		unsigned int bhserdy: 1;
		unsigned int bhsebyp: 1;
		unsigned int bcsson: 1;
		unsigned int bReserved20_23: 4;
		unsigned int bpllon: 1;
		unsigned int bpllrdy:1;
		unsigned int bpll2on: 1;
		unsigned int bpll2rdy: 1;
		unsigned int bpll3on: 1;
		unsigned int bpll3rdy: 1;
		unsigned int bReserved30_31: 2;
  }  b;
} RCC_CR ;

typedef union _RCC_CFGR 						/* Address offset: 0x004 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bsw: 2;
		unsigned int bsws: 2;
		unsigned int bhpre: 4;
		unsigned int bppre1: 3;
		unsigned int bppre2: 3;
		unsigned int badcpre: 21;
		unsigned int bpllsrc: 1;
		unsigned int bpllxtpre: 1;
		unsigned int bpllmul: 4;
		unsigned int botgfspre: 1;
		unsigned int bResered: 1;
		unsigned int bMCO: 4;
		unsigned int bReserved28_31: 4;
  }  b;
} RCC_CFGR ;

typedef union _RCC_CIR 							/* Address offset: 0x008 */
{
  uint32_t d32;
  struct
	{	
		unsigned int blsirdyf: 1;
		unsigned int blserdyf: 1;
		unsigned int bhsirdyf: 1;
		unsigned int bhserdyf: 1;
		unsigned int bpllrdyf: 1;
		unsigned int bpll2rdyf: 1;
		unsigned int bpll3rdyf: 1;
		unsigned int bcssf: 1;
		unsigned int blsirdyie: 1;
		unsigned int blserdyie: 1;
		unsigned int bhsirdyie: 1;
		unsigned int bhserdyie: 1;
		unsigned int bpllrdyie: 1;
		unsigned int bpll2rdyie: 1;
		unsigned int bpll3rdyie: 1;
		unsigned int bReserved15: 1;
		unsigned int blsirdyc: 1;
		unsigned int blserdyc: 1;
		unsigned int bhsirdyc: 1;
		unsigned int bhserdyc: 1;
		unsigned int bpllrdyc: 1;
		unsigned int bpll2rdyc: 1;
		unsigned int bpll3rdyc: 1;
		unsigned int bcscc: 1;
		unsigned int bReserved24_31: 7; 
  }  b;
} RCC_CIR ;

typedef union _RCC_APB2RSTR 				/* Address offset: 0x00C */
{
  uint32_t d32;
  struct
  {		
		unsigned int bafiorst: 1;
		unsigned int bReserved1: 1;
		unsigned int bioparst: 1;
		unsigned int biopbrst: 1;
		unsigned int biopcrst: 1;
		unsigned int biopdrst: 1;
		unsigned int bioperst: 1;
		unsigned int bReserved7_8: 2;
		unsigned int badc1rst: 1;
		unsigned int badc2rst: 1;
		unsigned int btim1rst: 1;
		unsigned int bspi1rst: 1;
		unsigned int bReserved13: 1;
		unsigned int busart1rst: 1;
		unsigned int bReserved15_31: 16;
  }  b;
} RCC_APB2RSTR ;

typedef union _RCC_APB1RSTR 				/* Address offset: 0x010 */
{
  uint32_t d32;
  struct
  {		
		unsigned int btim2rst: 1;
		unsigned int btim3rst: 1;
		unsigned int btim4rst: 1;
		unsigned int btim5rst: 1;
		unsigned int btim6rst: 1;
		unsigned int btim7rst: 1;
		unsigned int bReserved6_10: 5;
		unsigned int bwwdgrst: 1;
		unsigned int bReserved12_13: 2;
		unsigned int bspi2rst: 1;
		unsigned int bspi3rst: 1;
		unsigned int bReserved16: 1;
		unsigned int busart2rst: 1;
		unsigned int busart3rst: 1;
		unsigned int buart4rst: 1;
		unsigned int buart5rst: 1;
		unsigned int bi2c1rst: 1;
		unsigned int bi2c2rst: 1;
		unsigned int bReserved23_24: 2;
		unsigned int bcan1rst: 1;
		unsigned int bcan2rst: 1;
		unsigned int bkprst: 1;
		unsigned int bpwrrst: 1;
		unsigned int bdacrst:1;
		unsigned int bReservered30_31: 2;
  }  b;
} RCC_APB1RSTR ;

typedef union _RCC_AHBENR							/* Address offset: 0x014 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bdm1aen: 1;
		unsigned int bdm2aen: 1;
		unsigned int bsramen: 1;
		unsigned int bReserved3: 1;
		unsigned int bflitfen: 1;
		unsigned int bReserved5: 1;
		unsigned int bcrcen: 1;
		unsigned int bReserved7_11: 5;
		unsigned int botgfsen: 1;
		unsigned int bReserved13: 1;
		unsigned int bethmacen: 1;
		unsigned int bethmactxen: 1;
		unsigned int bethmacrxen: 1;
		unsigned int bReserved17_31: 14;
  }  b;
} RCC_AHBENR ;

typedef union _RCC_APB2ENR 						/* Address offset: 0x018 */
{
  uint32_t d32;
  struct
  {		
			unsigned int bafioen: 1;
			unsigned int bReserved1: 1;
			unsigned int biopaen: 1;
			unsigned int biopben: 1;
			unsigned int biopcen: 1;
			unsigned int biopden: 1;
			unsigned int biopeen: 1;
			unsigned int bReserved7_8: 2;
			unsigned int badc1en: 1;
			unsigned int badc2en: 1;
			unsigned int btim1en: 1;
			unsigned int bspi1en: 1;
			unsigned int bReserved13: 1;
			unsigned int busart1en: 1;
			unsigned int bReserved15_31: 17;
  }  b;
} RCC_APB2ENR ;

typedef union _RCC_APB1ENR 						/* Address offset: 0x01C */
{
  uint32_t d32;
  struct
  {		
		unsigned int btim2en: 1;
		unsigned int btim3en: 1;
		unsigned int btim4en: 1;
		unsigned int btim5en: 1;
		unsigned int btim6en: 1;
		unsigned int btim7en: 1;
		unsigned int bReserved6_10: 5;
		unsigned int bwwdgen: 1;
		unsigned int bReserved12_13: 2;
		unsigned int bspi2en: 1;
		unsigned int bspi3en: 1;
		unsigned int bReserved16: 1;
		unsigned int busart2en: 1;
		unsigned int busart3en: 1;
		unsigned int buart4en: 1;
		unsigned int buart5en: 1;
		unsigned int bi2c1en: 1;
		unsigned int bi2c2en: 1;
		unsigned int bReserved23_24: 2;
		unsigned int bcan1en: 1;
		unsigned int bcan2en: 1;
		unsigned int bbkpen: 1;
		unsigned int bpwren: 1;
		unsigned int bdacen: 1;
		unsigned int bReserved30_31: 2;
  }  b;
} RCC_APB1ENR ;

typedef union _RCC_BDCR 						/* Address offset: 0x020 */
{
  uint32_t d32;
  struct
  {		
		unsigned int blseon: 1;
		unsigned int blserdy: 1;
		unsigned int blsebyp: 1;
		unsigned int bReserved3_7: 5;
		unsigned int brtcsel: 2;
		unsigned int bReserved10_14: 5;
		unsigned int brtcen: 1;
		unsigned int bbdrst: 1;
		unsigned int bReserved17_31: 14;
  }  b;
} rRCC_BDCR ;

typedef union _RCC_CSR 							/* Address offset: 0x024 */
{
  uint32_t d32;
  struct
  {		
		unsigned int blsion: 1;
		unsigned int blsirdy: 1;
		unsigned int bReserved2_21: 19;
		unsigned int brmvf: 1;
		unsigned int bReserved25: 1;
		unsigned int bpinrstf: 1;
		unsigned int bporrstf: 1;
		unsigned int bsftrstf: 1;
		unsigned int biwdgrstf: 1;
		unsigned int bwwwdgrstf: 1;
		unsigned int blpwrstf: 1;
  }  b;
} RCC_CSR ;

typedef union _RCC_AHBSTR 					/* Address offset: 0x028 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bReserved0_11: 12;
		unsigned int botgfsrst: 1;
		unsigned int bReserved13: 1;
		unsigned int bethmacrst: 1;
		unsigned int bReserved15_31: 16;
  }  b;
} RCC_AHBSTR ;

typedef union _RCC_CFGR2 						/* Address offset: 0x02C */
{
  uint32_t d32;
  struct
  {		
		unsigned int bprediv1: 4;
		unsigned int bprediv2: 4;
		unsigned int bpll2mul: 4;
		unsigned int bpll3mul: 4;
		unsigned int bprediv1src: 1;
		unsigned int bi2s2src: 1;
		unsigned int bi2s3src: 1;
		unsigned int bReserved19_31: 12;
  }  b;
} RCC_CFGR2 ;

#endif 

