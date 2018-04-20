/******************************************************************************/
/* GLCD_SPI_STM32.c: STM32 low level Graphic LCD (320x240 pixels) driven with */
/* SPI functions */
/******************************************************************************/
#pragma diag_suppress=550
#include "stm32f10x_cl.h"
#include "DispCode.h"
#include "Font_24x16.h"
/*********************** Hardware specific configuration **********************/
/* SPI Interface: SPI3
PINS:
- CS = PB10 (GPIO pin)
- RS = GND
- WR/SCK = PC10 (SPI3_SCK)
- RD = GND
- SDO = PC11 (SPI3_MISO)
- SDI = PC12 (SPI3_MOSI) */
#define PIN_CS (1 << 10)
/* SPI_SR - bit definitions */
#define RXNE 0x01
#define TXE 0x02
#define BSY 0x80
/*------------------------- Speed dependant settings -------------------------*/
/* If processor works on high frequency delay has to be increased, it can be
increased by factor 2^N by this constant */
#define DELAY_2N 18
/*---------------------- Graphic LCD size definitions ------------------------*/
#define WIDTH 320 /* Screen Width (in pixels) */
#define HEIGHT 240 /* Screen Hight (in pixels) */
#define BPP 16 /* Bits per pixel */
#define BYPP ((BPP+7)/8) /* Bytes per pixel */
/*--------------- Graphic LCD interface hardware definitions -----------------*/
/* Pin CS setting to 0 or 1 */
#define LCD_CS(x) ((x) ? (GPIOB->BSRR = PIN_CS) : (GPIOB->BRR = PIN_CS));
#define SPI_START (0x70) /* Start byte for SPI transfer */
#define SPI_RD (0x01) /* WR bit 1 within start */
#define SPI_WR (0x00) /* WR bit 0 within start */
#define SPI_DATA (0x02) /* RS bit 1 within start byte */
#define SPI_INDEX (0x00) /* RS bit 0 within start byte */
/*---------------------------- Global variables ------------------------------*/
/******************************************************************************/
static volatile unsigned short TextColor = Black, BackColor = White;
/************************ Local auxiliary functions ***************************/
/*******************************************************************************
* Delay in while loop cycles *
* Parameter: cnt: number of while cycles to delay *
* Return: *
*******************************************************************************/
static void delay (int cnt) {
cnt <<= DELAY_2N;
while (cnt--);
}
/*******************************************************************************
* Send 1 byte over serial communication *
* Parameter: byte: byte to be sent *
* Return: byte read while sending *
*******************************************************************************/
static __inline unsigned char spi_send (unsigned char byte) {
SPI3->DR = byte;
while (!(SPI3->SR & RXNE)); /* Wait for send to finish */
return (SPI3->DR);
}
/*******************************************************************************
* Write command to LCD controller *
* Parameter: c: command to be written *
* Return: *
*******************************************************************************/
static __inline void wr_cmd (unsigned char c) {
LCD_CS(0)
spi_send(SPI_START | SPI_WR | SPI_INDEX); /* Write : RS = 0, RW = 0 */
spi_send(0);
spi_send(c);
LCD_CS(1)
}
/*******************************************************************************
* Write data to LCD controller *
* Parameter: c: data to be written *
* Return: *
*******************************************************************************/
static __inline void wr_dat (unsigned short c) {
LCD_CS(0)
spi_send(SPI_START | SPI_WR | SPI_DATA); /* Write : RS = 1, RW = 0 */
spi_send((c >> 8)); /* Write D8..D15 */
spi_send((c & 0xFF)); /* Write D0..D7 */
LCD_CS(1)
}
/*******************************************************************************
* Start of data writing to LCD controller *
* Parameter: *
* Return: *
*******************************************************************************/
static __inline void wr_dat_start (void) {
LCD_CS(0)
spi_send(SPI_START | SPI_WR | SPI_DATA); /* Write : RS = 1, RW = 0 */
}
/*******************************************************************************
* Stop of data writing to LCD controller *
* Parameter:
* Return: *
*******************************************************************************/
static __inline void wr_dat_stop (void) {
LCD_CS(1)
}
/*******************************************************************************
* Data writing to LCD controller *
* Parameter: c: data to be written *
* Return: *
*******************************************************************************/
static __inline void wr_dat_only (unsigned short c) {
spi_send((c >> 8)); /* Write D8..D15 */
spi_send((c & 0xFF)); /* Write D0..D7 */
}
/*******************************************************************************
* Read data from LCD controller *
* Parameter: *
* Return: read data *
*******************************************************************************/
static __inline unsigned short rd_dat (void) {
unsigned short val = 0;
LCD_CS(0)
spi_send(SPI_START | SPI_RD | SPI_DATA); /* Read: RS = 1, RW = 1 */
spi_send(0); /* Dummy read */
val = spi_send(0); /* Read D8..D15 */
val <<= 8;
val |= spi_send(0); /* Read D0..D7 */
LCD_CS(1)
return (val);
}
/*******************************************************************************
* Write to LCD register *
* Parameter: reg: register to be read *
* val: value to write to register *
*******************************************************************************/
static __inline void wr_reg (unsigned char reg, unsigned short val) {
wr_cmd(reg);
wr_dat(val);
}
/*******************************************************************************
* Read from LCD register *
* Parameter: reg: register to be read *
* Return: value read from register *
*******************************************************************************/

static unsigned short rd_reg (unsigned char reg) {
wr_cmd(reg);
return (rd_dat());
}
/************************ Exported functions **********************************/
/*******************************************************************************
* Initialize the Graphic LCD controller *
* Parameter: *
* Return: *
*******************************************************************************/
void GLCD_Init (void) {
static unsigned short driverCode;
/* Enable clock for GPIOB,C AFIO and SPI3 */
RCC->APB2ENR |= 0x00000019;
RCC->APB1ENR |= 0x00008000;
/* Set SPI3 remap (use PC10..PC12) */
AFIO->MAPR |= 0x10000000;
/* NCS is PB10, GPIO output set to high */
GPIOB->CRH &= 0xFFFFF0FF;
GPIOB->CRH |= 0x00000300;
GPIOB->CRL &= 0xFFFFFFF0;
GPIOB->CRL |= 0x00000003;
GPIOB->BSRR = 0x00000401;
/* SPI3_SCK, SPI3_MISO, SPI3_MOSI are SPI pins */
GPIOC->CRH &= 0xFFF000FF;
GPIOC->CRH |= 0x000B8B00;
/* Enable SPI in Master Mode, CPOL=1, CPHA=1 */
/* Max. 18 MBit used for Data Transfer @ 72MHz */
SPI3->CR1 = 0x0347;
SPI3->CR2 = 0x0000;
delay(5); /* Delay 50 ms */
driverCode = rd_reg(0x00);
/* Start Initial Sequence --------------------------------------------------*/
wr_reg(0x01, 0x0100); /* Set SS bit */
wr_reg(0x02, 0x0700); /* Set 1 line inversion */
wr_reg(0x04, 0x0000); /* Resize register */
wr_reg(0x08, 0x0207); /* 2 lines front, 7 back porch */
wr_reg(0x09, 0x0000); /* Set non-disp area refresh cyc ISC */
wr_reg(0x0A, 0x0000); /* FMARK function */
wr_reg(0x0C, 0x0000); /* RGB interface setting */
wr_reg(0x0D, 0x0000); /* Frame marker Position */
wr_reg(0x0F, 0x0000); /* RGB interface polarity */
/* Power On sequence -------------------------------------------------------*/
wr_reg(0x10, 0x0000); /* Reset Power Control 1 */
wr_reg(0x11, 0x0000); /* Reset Power Control 2 */
wr_reg(0x12, 0x0000); /* Reset Power Control 3 */
wr_reg(0x13, 0x0000); /* Reset Power Control 4 */

delay(20); /* Discharge cap power voltage (200ms)*/
wr_reg(0x10, 0x12B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
wr_reg(0x11, 0x0007); /* DC1[2:0], DC0[2:0], VC[2:0] */
delay(5); /* Delay 50 ms */
wr_reg(0x12, 0x01BD); /* VREG1OUT voltage */
delay(5); /* Delay 50 ms */
wr_reg(0x13, 0x1400); /* VDV[4:0] for VCOM amplitude */
wr_reg(0x29, 0x000E); /* VCM[4:0] for VCOMH */
delay(5); /* Delay 50 ms */
wr_reg(0x20, 0x0000); /* GRAM horizontal Address */
wr_reg(0x21, 0x0000); /* GRAM Vertical Address */
/* Adjust the Gamma Curve ---omitted----------------------------------------*/
/* Set GRAM area -----------------------------------------------------------*/
wr_reg(0x50, 0x0000); /* Horizontal GRAM Start Address */
wr_reg(0x51, (HEIGHT-1)); /* Horizontal GRAM End Address */
wr_reg(0x52, 0x0000); /* Vertical GRAM Start Address */
wr_reg(0x53, (WIDTH-1)); /* Vertical GRAM End Address */
wr_reg(0x60, 0xA700); /* Gate Scan Line */
if (driverCode == 0x5408) /* LCD with SPFD5408 LCD Controller */
wr_reg(0x60, 0xA700); /* Gate Scan Line */
else /* LCD with other LCD Controller */
wr_reg(0x60, 0x2700); /* Gate Scan Line */
wr_reg(0x61, 0x0001); /* NDL,VLE, REV */
wr_reg(0x6A, 0x0000); /* Set scrolling line */
/* Partial Display Control -------------------------------------------------*/
wr_reg(0x80, 0x0000);
wr_reg(0x81, 0x0000);
wr_reg(0x82, 0x0000);
wr_reg(0x83, 0x0000);
wr_reg(0x84, 0x0000);
wr_reg(0x85, 0x0000);
/* Panel Control -----------------------------------------------------------*/
wr_reg(0x90, 0x0010);
wr_reg(0x92, 0x0000);
wr_reg(0x93, 0x0003);
wr_reg(0x95, 0x0110);
wr_reg(0x97, 0x0000);
wr_reg(0x98, 0x0000);
/* Set GRAM write direction
I/D=10 (Horizontal : increment, Vertical : increment)
AM=1 (address is updated in vertical writing direction) */
wr_reg(0x03, 0x1038);
wr_reg(0x07, 0x0137); /* 262K color and display ON */
}
/*******************************************************************************
* Set draw window region to whole screen *
* Parameter: *
* Return: *
*******************************************************************************/
void GLCD_WindowMax (void) {
wr_reg(0x50, 0); /* Horizontal GRAM Start Address */
wr_reg(0x51, HEIGHT-1); /* Horizontal GRAM End Address (-1) */
wr_reg(0x52, 0); /* Vertical GRAM Start Address */
wr_reg(0x53, WIDTH-1); /* Vertical GRAM End Address (-1) */
}
/*******************************************************************************
* Set foreground color *
* Parameter: color: foreground color *
* Return: *
*******************************************************************************/
void GLCD_SetTextColor (unsigned short color) {
TextColor = color;
}
/*******************************************************************************
* Set background color *
* Parameter: color: background color *
* Return: *
*******************************************************************************/
void GLCD_SetBackColor (unsigned short color) {
BackColor = color;
}
/*******************************************************************************
* Clear display *
* Parameter: color: display clearing color *
* Return: *
*******************************************************************************/
void GLCD_Clear (unsigned short color) {
unsigned int i;
GLCD_WindowMax();
wr_reg(0x20, 0);
wr_reg(0x21, 0);
wr_cmd(0x22);
wr_dat_start();
for(i = 0; i < (WIDTH*HEIGHT); i++)
wr_dat_only(color);
wr_dat_stop();
}
/*******************************************************************************
* Draw character on given position *
* Parameter: x: horizontal position *
* y: vertical position *
* c: pointer to character bitmap *
* Return: *
*******************************************************************************/
void GLCD_DrawChar (unsigned int x, unsigned int y, unsigned short *c) {
int idx = 0, i, j;
x = WIDTH-x-CHAR_W;
wr_reg(0x50, y); /* Horizontal GRAM Start Address */
wr_reg(0x51, y+CHAR_H-1); /* Horizontal GRAM End Address (-1) */
wr_reg(0x52, x); /* Vertical GRAM Start Address */
wr_reg(0x53, x+CHAR_W-1); /* Vertical GRAM End Address (-1) */
wr_reg(0x20, y);
wr_reg(0x21, x);
wr_cmd(0x22);
wr_dat_start();
for (j = 0; j < CHAR_H; j++) {
for (i = CHAR_W-1; i >= 0; i--) {
if((c[idx] & (1 << i)) == 0x00) {
wr_dat_only(BackColor);
} else {
wr_dat_only(TextColor);
}
}
c++;
}
wr_dat_stop();
}
/*******************************************************************************
* Disply character on given line *
* Parameter: ln: line number *
* col: column number *
* c: ascii character *
* Return: *
*******************************************************************************/
void GLCD_DisplayChar (unsigned int ln, unsigned int col, unsigned char c) {
c -= 32;
GLCD_DrawChar(col * CHAR_W, ln * CHAR_H, &Font_24x16[c * CHAR_H]);
}
/*******************************************************************************
* Disply string on given line *
* Parameter: ln: line number *
* col: column number *
* s: pointer to string *
* Return: *
*******************************************************************************/
void GLCD_DisplayString (unsigned int ln, unsigned int col, unsigned char *s) {
GLCD_WindowMax();
while (*s) {
GLCD_DisplayChar(ln, col++, *s++);
}
}

