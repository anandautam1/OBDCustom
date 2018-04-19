/**
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_REGS_H__
#define __CAN_REGS_H__

#include "stm32f10x.h"

#define CAN1_BASE_ADDR											0x40006400		
#define CAN2_BASE_ADDR											0x40006800		
#define CAN_RAM															0x40006000


#define	CAN_OFFSET													0x400
#define CAN_FILTER													28
#define CAN_FILTER_OFFSET										0x08

// Define the register offsets.
#define RCAN_MCR														0x00
#define RCAN_MSR														0x04
#define RCAN_TSR														0x08
#define RCAN_RF0R														0x0C
#define RCAN_RF1R														0x10
#define RCAN_IER														0x14
#define RCAN_ESR														0x18
#define RCAN_BTR														0x1C
#define RCAN_TI0R														0x180
#define RCAN_TDT0R													0x184
#define RCAN_TDL0R													0x188
#define RCAN_TDH0R													0x18C
#define RCAN_TI1R												 		0x190
#define RCAN_TDT1R													0x194
#define RCAN_TDL1R													0x198
#define RCAN_TDH1R													0x19C
#define RCAN_TI2R														0x1A0
#define RCAN_TDT2R													0x1A4
#define RCAN_TDL2R											 		0x1A8
#define RCAN_TDH2R													0x1AC
#define RCAN_RI0R														0x1B0
#define RCAN_RDT0R													0x1B4
#define RCAN_RDL0R													0x1B8
#define RCAN_RHD0R													0x1BC
#define RCAN_RI1R														0x1C0
#define RCAN_RDT1R													0x1C4
#define RCAN_RDL1R													0x1C8
#define RCAN_RHD1R													0x1CC

// Registers below an offset of 0x200 only exist for CAN1
#define RCAN_FMR														0x200
#define RCAN_FM1R														0x204
#define RCAN_FS1R														0x20C
#define RCAN_FFA1R													0x214
#define RCAN_FA1R														0x21C
#define RCAN_F0R1														0x240
#define RCAN_F0R2														0x244
#define RCAN_F1R1														0x248
#define RCAN_F1R2														0x24C
#define RCAN_F2R1														0x250
#define RCAN_F2R2														0x254
#define RCAN_F3R1														0x258
#define RCAN_F3R2														0x25C
#define RCAN_F4R1														0x260
#define RCAN_F4R2														0x264
#define RCAN_F5R1														0x268
#define RCAN_F5R2														0x26C
#define RCAN_F6R1														0x270
#define RCAN_F6R2														0x274
#define RCAN_F7R1														0x278
#define RCAN_F7R2														0x27C
#define RCAN_F8R1														0x280
#define RCAN_F8R2														0x284
#define RCAN_F9R1														0x288
#define RCAN_F9R2														0x28C
#define RCAN_F10R1													0x290
#define RCAN_F10R2													0x294
#define RCAN_F11R1													0x298
#define RCAN_F11R2													0x29C
#define RCAN_F12R1													0x2A0
#define RCAN_F12R2													0x2A4
#define RCAN_F13R1													0x2A8
#define RCAN_F13R2													0x2AC
#define RCAN_F14R1													0x2B0
#define RCAN_F14R2													0x2B4
#define RCAN_F15R1													0x2B8
#define RCAN_F15R2													0x2BC
#define RCAN_1F16R1													0x2C0
#define RCAN_F16R2													0x2C4
#define RCAN_F17R1													0x2C8
#define RCAN_F17R2													0x2CC
#define RCAN_F18R1													0x2D0
#define RCAN_F18R2													0x2D4
#define RCAN_F19R1													0x2D8
#define RCAN_F19R2													0x2DC
#define RCAN_F20R1													0x2E0
#define RCAN_F20R2													0x2E4
#define RCAN_F21R1													0x2E8
#define RCAN_F21R2													0x2EC
#define RCAN_F22R1													0x2F0
#define RCAN_F22R2													0x2F4
#define RCAN_F23R1													0x2F8
#define RCAN_F23R2													0x2FC
#define RCAN_F24R1													0x300
#define RCAN_F24R2													0x304
#define RCAN_F25R1													0x308
#define RCAN_F25R2													0x30C
#define RCAN_F26R1													0x310
#define RCAN_F26R2													0x314
#define RCAN_F27R1													0x318
#define RCAN_F27R2													0x31C

#define RCAN1_MCR    (volatile unsigned int *) (CAN1_BASE_ADDR +  0x00  )
#define RCAN1_MSR    (volatile unsigned int *) (CAN1_BASE_ADDR +  0x04  )  
#define RCAN1_TSR    (volatile unsigned int *) (CAN1_BASE_ADDR +  0x08  )  
#define RCAN1_RF0R	 (volatile unsigned int *) (CAN1_BASE_ADDR +  0x0C  )  
#define RCAN1_RF1R	 (volatile unsigned int *) (CAN1_BASE_ADDR +  0x10  )  
#define RCAN1_IER    (volatile unsigned int *) (CAN1_BASE_ADDR +  0x14  )  
#define RCAN1_ESR    (volatile unsigned int *) (CAN1_BASE_ADDR +  0x18  )   
#define RCAN1_BTR    (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1C  )  
#define RCAN1_TI0R	 (volatile unsigned int *) (CAN1_BASE_ADDR +  0x180 )  
#define RCAN1_TDT0R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x184 )  
#define RCAN1_TDL0R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x188 )  
#define RCAN1_TDH0R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x18C )
#define RCAN1_TI1R	 (volatile unsigned int *) (CAN1_BASE_ADDR +  0x190 )
#define RCAN1_TDT1R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x194 )
#define RCAN1_TDL1R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x198 )
#define RCAN1_TDH1R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x19C )
#define RCAN1_TI2R	 (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1A0 )
#define RCAN1_TDT2R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1A4 )
#define RCAN1_TDL2R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1A8 )
#define RCAN1_TDH2R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1AC )
#define RCAN1_RI0R	 (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1B0 )
#define RCAN1_RDT0R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1B4 )
#define RCAN1_RDL0R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1B8 )
#define RCAN1_RHD0R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1BC )
#define RCAN1_RI1R	 (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1C0 )
#define RCAN1_RDT1R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1C4 )
#define RCAN1_RDL1R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1C8 )
#define RCAN1_RHD1R  (volatile unsigned int *) (CAN1_BASE_ADDR +  0x1CC )

#define RCAN1_FMR		    (volatile unsigned int *) (CAN1_BASE_ADDR + 0x200 )
#define RCAN1_FM1R		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x204 )
#define RCAN1_FS1R		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x20C )
#define RCAN1_FFA1R	        (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x214 )
#define RCAN1_FA1R		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x21C )
#define RCAN1_F0R1		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x240 )
#define RCAN1_F0R2		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x244 )
#define RCAN1_F1R1		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x248 )
#define RCAN1_F1R2		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x24C )
#define RCAN1_F2R1		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x250 )
#define RCAN1_F2R2		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x254 )
#define RCAN1_F3R1		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x258 )
#define RCAN1_F3R2		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x25C )
#define RCAN1_F4R1		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x260 )
#define RCAN1_F4R2		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x264 )
#define RCAN1_F5R1		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x268 )
#define RCAN1_F5R2		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x26C )
#define RCAN1_F6R1		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x270 )
#define RCAN1_F6R2		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x274 )
#define RCAN1_F7R1		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x278 )
#define RCAN1_F7R2		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x27C )
#define RCAN1_F8R1		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x280 )
#define RCAN1_F8R2		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x284 )
#define RCAN1_F9R1		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x288 )
#define RCAN1_F9R2		    (volatile unsigned int *) (CAN1_BASE_ADDR +	 0x28C )
#define RCAN1_F10R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x290 )
#define RCAN1_F10R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x294 )
#define RCAN1_F11R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x298 )
#define RCAN1_F11R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x29C )
#define RCAN1_F12R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2A0 )
#define RCAN1_F12R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2A4 )
#define RCAN1_F13R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2A8 )
#define RCAN1_F13R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2AC )
#define RCAN1_F14R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2B0 )
#define RCAN1_F14R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2B4 )
#define RCAN1_F15R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2B8 )
#define RCAN1_F15R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2BC )
#define RCAN1_1F16R1    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2C0 )
#define RCAN1_F16R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2C4 )
#define RCAN1_F17R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2C8 )
#define RCAN1_F17R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2CC )
#define RCAN1_F18R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2D0 )
#define RCAN1_F18R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2D4 )
#define RCAN1_F19R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2D8 )
#define RCAN1_F19R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2DC )
#define RCAN1_F20R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2E0 )
#define RCAN1_F20R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2E4 )
#define RCAN1_F21R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2E8 )
#define RCAN1_F21R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2EC )
#define RCAN1_F22R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2F0 )
#define RCAN1_F22R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2F4 )
#define RCAN1_F23R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2F8 )
#define RCAN1_F23R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x2FC )
#define RCAN1_F24R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x300 )
#define RCAN1_F24R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x304 )
#define RCAN1_F25R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x308 )
#define RCAN1_F25R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x30C )
#define RCAN1_F26R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x310 )
#define RCAN1_F26R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x314 )
#define RCAN1_F27R1	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x318 )
#define RCAN1_F27R2	    (volatile unsigned int *) (CAN1_BASE_ADDR +		 0x31C )


// Typdef for the various registers (this will allow for single-bit manipulation)
typedef union _CAN_MCR 						/* Address offset: 0x00 */
{
  uint32_t d32;
  struct
  {		
		unsigned int binrq : 1;	
		unsigned int bsleep : 1;
		unsigned int btxfp : 1;
		unsigned int brflm : 1;
		unsigned int bnart : 1;		
		unsigned int bawum : 1;
		unsigned int babom : 1;
		unsigned int bttcm : 1;
		unsigned int bReserver8_14 : 7;
		unsigned int breset : 1;
		unsigned int bdbf : 1;
		unsigned int bReserved17_31 : 15;
  }  b;
} CAN_MCR ;

typedef union _CAN_MSR 						/* Address offset: 0x04 */
{
  uint32_t d32;
  struct
  {
		unsigned int binak : 1;	
		unsigned int bslak : 1;
		unsigned int berri : 1;
		unsigned int bwkui : 1;
		unsigned int bslaki : 1;		
		unsigned int bReserved5_7: 3;
		unsigned int btxm : 1;
		unsigned int brxm : 1;
		unsigned int bsamp : 1;
		unsigned int brx : 1;
		unsigned int bReserved12_31 : 20;
  }   b;
} CAN_MSR;


typedef union _CAN_TSR 					/* Address offset: 0x08 */
{
  uint32_t d32;
  struct
  {		
		unsigned int brqcp0 : 1;
		unsigned int btxok0 : 1;
		unsigned int balst0 : 1;
		unsigned int bterr0 : 1;		
		unsigned int bReserved4_6: 3;
		unsigned int babrq0 : 1;
		unsigned int brqcp1 : 1;
		unsigned int btxok1 : 1;
		unsigned int balst1 : 1;
		unsigned int bterr1 : 1;
		unsigned int bReserved12_14 : 3;
		unsigned int babrq1 : 1;
		unsigned int brqcp2 : 1;
		unsigned int btxok2 : 1;
		unsigned int balst2 : 1;
		unsigned int bterr2 : 1;		
		unsigned int bReserved20_22: 3;
		unsigned int babrq2 : 1;
		unsigned int bcode : 2;
		unsigned int btme0 : 1;
		unsigned int btme1 : 1;
		unsigned int btme2 : 1;		
		unsigned int blow0: 1;
		unsigned int blow1: 1;
		unsigned int blow2: 1;
  } b;
} CAN_TSR ;


typedef union _CAN_RFxR 			/* Address offset: 0x0C & 0x10 */
{
  uint32_t d32;
  struct
  {
		unsigned int bfmp : 2;		
		unsigned int bReserved2 : 1;
		unsigned int bfull : 1;
		unsigned int bfovr : 1;
		unsigned int brfom : 1;
		unsigned int bReserverd6_31 : 26;
  } b;
} CAN_RFxR ;

typedef union _CAN_IER 			/* Address offset: 0x14 */
{
  uint32_t d32;
  struct
  {
		unsigned int btmeie : 1;		
		unsigned int bfmpie0 : 1;
		unsigned int bffie0 : 1;
		unsigned int bfovie0 : 1;
		unsigned int bfmpie1 : 1;
		unsigned int bffie1 : 1;
		unsigned int bfovie1 : 1;
		unsigned int bReserved7 : 1;
		unsigned int bewgie : 1;
		unsigned int bepvie : 1;
		unsigned int bbofie : 1;
		unsigned int blecie : 1;
		unsigned int bReserved12_14 : 3;		
		unsigned int berrie : 1;
		unsigned int bwkuie : 1;
		unsigned int bslkie : 1;
		unsigned int bReserved18_31 : 14;
  } b;
} CAN_IER ;


typedef union _CAN_ESR 			/* Address offset: 0x18 */
{
  uint32_t d32;
  struct
  {
		unsigned int bewgf : 1;		
		unsigned int bepvf : 1;
		unsigned int bboff : 1;
		unsigned int bReserved3 : 1;
		unsigned int blec : 3;
		unsigned int bReserved7_15 : 9;
		unsigned int btec : 8;
		unsigned int brec: 8;
  } b;
} CAN_ESR ;


typedef union _CAN_BTR 					/* Address offset: 0x1C */
{
  uint32_t d32;
  struct
  {		
		unsigned int bbrp : 10;		
		unsigned int bReserved10_15 : 6;
		unsigned int bts1 : 4;
		unsigned int bts2 : 3;
		unsigned int bReserved23 : 1;
		unsigned int bsjw : 2;
		unsigned int bReserved26_29 : 4;
		unsigned int blbkm : 1;
		unsigned int bsilm : 1;
  } b;
} CAN_BTR ;

typedef union _CAN_TIxR 					/* Address offset: 0x180, 0x190, 0x1A0 */
{
  uint32_t d32;
  struct
  {		
		unsigned int btxrq : 1;	
		unsigned int brtr : 1;
		unsigned int bide : 1;
		unsigned int bexid12_0 : 13;
		unsigned int bexid16_20 : 5;
		unsigned int bstidexid28_18 : 11;
  } b;
} CAN_TIxR ;

typedef union _CAN_TDTxR 					/* Address offset: 0x184, 0x194, 0x1A4 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bdlc : 4;	
		unsigned int bReserved4_7 : 4;
		unsigned int btgt : 1;
		unsigned int bReserved9_15 : 7;
		unsigned int btime : 16;
  } b;
} CAN_TDTxR ;

typedef union _CAN_TDLxR 					/* Address offset: 0x188, 0x198, 0x1A8 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bdata0 : 8;	
		unsigned int bdata1 : 8;
		unsigned int bdata2 : 8;
		unsigned int bdata3 : 8;
  } b;
} CAN_TDLxR ;

typedef union _CAN_TDHxR 					/* Address offset: 0x18C, 0x19C, 0x1AC */
{
  uint32_t d32;
  struct
  {		
		unsigned int bdata4 : 8;	
		unsigned int bdata5 : 8;
		unsigned int bdata6 : 8;
		unsigned int bdata7 : 8;
  } b;
} CAN_TDHxR ;


typedef union _CAN_RIxR 					/* Address offset: 0x1B0, 0x1C0 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bReserved0 : 1;	
		unsigned int brtr : 1;
		unsigned int bide : 1;
		unsigned int bexid12_0 : 13;
		unsigned int bexid16_20 : 5;
		unsigned int bstidexid28_18 : 11;
  } b;
} CAN_RIxR ;

typedef union _CAN_RDTxR 					/* Address offset: 0x1B4, 0x1C4 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bdlc : 4;	
		unsigned int bReserved4_7 : 4;
		unsigned int bfmi : 8;
		unsigned int btime : 16;
  } b;
} CAN_RDTxR ;

typedef union _CAN_RDLxR 					/* Address offset: 0x1B8, 0x1C8 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bdata0 : 8;	
		unsigned int bdata1 : 8;
		unsigned int bdata2 : 8;
		unsigned int bdata3 : 8;
  } b;
} CAN_RDLxR ;

typedef union _CAN_RDHxR 					/* Address offset: 0x1BC, 0x1CC */
{
  uint32_t d32;
  struct
  {		
		unsigned int bdata4 : 8;	
		unsigned int bdata5 : 8;
		unsigned int bdata6 : 8;
		unsigned int bdata7 : 8;
  } b;
} CAN_RDHxR ;

typedef union _CAN_FMR 					/* Address offset: 0x200 */
{
  uint32_t d32;
  struct
  {		
		unsigned int bfinit : 1;	
		unsigned int bReserved1_31 : 31;
  } b;
} CAN_FMR ;

typedef union _CAN_FM1R 			/* Address offset: 0x204 */
{
  uint32_t d32;
  struct
  {
		unsigned int bfmb0 : 1;		
		unsigned int bfmb1 : 1;
		unsigned int bfmb2 : 1;
		unsigned int bfmb3 : 1;
		unsigned int bfmb4 : 1;		
		unsigned int bfmb5 : 1;
		unsigned int bfmb6 : 1;
		unsigned int bfmb7 : 1;
		unsigned int bfmb8 : 1;		
		unsigned int bfmb9 : 1;
		unsigned int bfmb10 : 1;
		unsigned int bfmb11 : 1;
		unsigned int bfmb12 : 1;		
		unsigned int bfmb13 : 1;
		unsigned int bfmb14 : 1;
		unsigned int bfmb15 : 1;
		unsigned int bfmb16 : 1;		
		unsigned int bfmb17 : 1;
		unsigned int bfmb18 : 1;
		unsigned int bfmb19 : 1;
		unsigned int bfmb20 : 1;		
		unsigned int bfmb21 : 1;
		unsigned int bfmb22 : 1;
		unsigned int bfmb23 : 1;
		unsigned int bfmb24 : 1;		
		unsigned int bfmb25 : 1;
		unsigned int bfmb26 : 1;
		unsigned int bfmb27 : 1;
		unsigned int bReserved28_31 : 4;
  } b;
} CAN_FM1R ;

typedef union _CAN_FS1R 			/* Address offset: 0x20C */
{
  uint32_t d32;
  struct
  {
		unsigned int bfsc0 : 1;		
		unsigned int bfsc1 : 1;
		unsigned int bfsc2 : 1;
		unsigned int bfsc3 : 1;
		unsigned int bfsc4 : 1;		
		unsigned int bfsc5 : 1;
		unsigned int bfsc6 : 1;
		unsigned int bfsc7 : 1;
		unsigned int bfsc8 : 1;		
		unsigned int bfsc9 : 1;
		unsigned int bfsc10 : 1;
		unsigned int bfsc11 : 1;
		unsigned int bfsc12 : 1;		
		unsigned int bfsc13 : 1;
		unsigned int bfsc14 : 1;
		unsigned int bfsc15 : 1;
		unsigned int bfsc16 : 1;		
		unsigned int bfsc17 : 1;
		unsigned int bfsc18 : 1;
		unsigned int bfsc19 : 1;
		unsigned int bfsc20 : 1;		
		unsigned int bfsc21 : 1;
		unsigned int bfsc22 : 1;
		unsigned int bfsc23 : 1;
		unsigned int bfsc24 : 1;		
		unsigned int bfsc25 : 1;
		unsigned int bfsc26 : 1;
		unsigned int bfsc27 : 1;
		unsigned int bReserved28_31 : 4;
  } b;
} CAN_FS1R ;

typedef union _CAN_FFA1R 			/* Address offset: 0x214 */
{
  uint32_t d32;
  struct
  {
		unsigned int bffa0 : 1;		
		unsigned int bffa1 : 1;
		unsigned int bffa2 : 1;
		unsigned int bffa3 : 1;
		unsigned int bffa4 : 1;		
		unsigned int bffa5 : 1;
		unsigned int bffa6 : 1;
		unsigned int bffa7 : 1;
		unsigned int bffa8 : 1;		
		unsigned int bffa9 : 1;
		unsigned int bffa10 : 1;
		unsigned int bffa11 : 1;
		unsigned int bffa12 : 1;		
		unsigned int bffa13 : 1;
		unsigned int bffa14 : 1;
		unsigned int bffa15 : 1;
		unsigned int bffa16 : 1;		
		unsigned int bffa17 : 1;
		unsigned int bffa18 : 1;
		unsigned int bffa19 : 1;
		unsigned int bffa20 : 1;		
		unsigned int bffa21 : 1;
		unsigned int bffa22 : 1;
		unsigned int bffa23 : 1;
		unsigned int bffa24 : 1;		
		unsigned int bffa25 : 1;
		unsigned int bffa26 : 1;
		unsigned int bffa27 : 1;
		unsigned int bReserved28_31 : 4;
  } b;
} CAN_FFA1R ;

typedef union _CAN_FA1R 			/* Address offset: 0x21C */
{
  uint32_t d32;
  struct
  {
		unsigned int bfact0 : 1;		
		unsigned int bfact1 : 1;		
		unsigned int bfact2 : 1;		
		unsigned int bfact3 : 1;		
		unsigned int bfact4 : 1;		
		unsigned int bfact5 : 1;		
		unsigned int bfact6 : 1;		
		unsigned int bfact7 : 1;		
		unsigned int bfact8 : 1;		
		unsigned int bfact9 : 1;		
		unsigned int bfact10 : 1;		
		unsigned int bfact11 : 1;		
		unsigned int bfact12 : 1;		
		unsigned int bfact13 : 1;		
		unsigned int bfact14 : 1;		
		unsigned int bfact15 : 1;		
		unsigned int bfact16 : 1;		
		unsigned int bfact17 : 1;		
		unsigned int bfact18 : 1;		
		unsigned int bfact19 : 1;		
		unsigned int bfact20 : 1;		
		unsigned int bfact21 : 1;		
		unsigned int bfact22 : 1;		
		unsigned int bfact23 : 1;		
		unsigned int bfact24 : 1;		
		unsigned int bfact25 : 1;		
		unsigned int bfact26 : 1;		
		unsigned int bfact27 : 1;		
		unsigned int bReserved28_31 : 4;
  } b;
} CAN_FA1R ;

typedef union _CAN_FiRx 			/* Address offset: 0x240...0x31C */
{
  uint32_t d32;
  struct
  {
		unsigned int bfb : 32;		
  } b;
} CAN_FiRx ;

// additional code for the can message format 
#define STANDARD 0x00;
#define EXTENDED_IDENTIFIER 0x01;
#define DATA_FRAME 0x00;
#define REMOTE_FRAME 0x01;

typedef struct _CAN_msg
{
	unsigned int   id;                 // 29 bit identifier
  unsigned char  data[4];            // Data field
  unsigned char  len;                // Length of data field in bytes
  unsigned char  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  unsigned char  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
} CAN_msg;

#endif 























