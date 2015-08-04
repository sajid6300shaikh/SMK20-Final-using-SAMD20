#include "compiler.h"

#ifndef _S_PORT_H
#define _S_PORT_H


#define RWSFR	*(volatile uint32_t *)	//THIS SFRs CAN BE READ AND WRITTEN TO
#define ROSFR	*(volatile uint32_t *)	//THIS SFRs ARE READ ONLY
#define WOSFR	*(volatile uint32_t *)	//THESE SFRs CAN'T BE READ(READ ATTEMPT WILL RETURN 0)
#define RWSFR_8	*(volatile uint8_t *)	//THIS SFRs CAN BE READ AND WRITTEN TO

#define	OUTPUT		0		//output with Totem pole configuration(Strong push pull)
#define	WEAKOUT		1		//Output with pull up and down resistor(Weak push pull)
#define INPUT		2		//std input without any pull settings
#define INPUP		3		//input with pull up resistor
#define INPDN		4		//input with pull down resistor
#define INOUT		5		//Output with Input Enable
#define OUT			OUTPUT
#define IN			INPUT




/************************************************************************/
/*				PINMUX peripheral Macros			                    */
/************************************************************************/
//these are the peripheral options for "void pinMux(uint8_t Pin, uint8_t peripheral)" function in S_PORT.C

//		Mux Perip | Peripheral No.
#define		EICMUX			0

#define		ADCmux			0X1
#define		REFmux			ADCmux
#define		ACmux			ADCmux
#define		PTCmux			ADCmux
#define		DACmux			ADCmux

#define		CSERCOMmux		0X2
#define		DSERCOMmux		0X3

#define		ETCmux			0x4
#define		FTCmux			0x5

#define		GCLKmux			0x7
#define		ACoutmux		GCLKmux
#define		Disablemux		0x0A


/************************************************************************/
/* PIN NOs                                                              */
/************************************************************************/

#define PA00                           0  /**< \brief Pin Number for PA00 */
#define P_PA00                 (1ul <<  0) /**< \brief PORT Mask  for PA00 */
#define PA01                           1  /**< \brief Pin Number for PA01 */
#define P_PA01                 (1ul <<  1) /**< \brief PORT Mask  for PA01 */
#define PA02                           2  /**< \brief Pin Number for PA02 */
#define P_PA02                 (1ul <<  2) /**< \brief PORT Mask  for PA02 */
#define PA03                           3  /**< \brief Pin Number for PA03 */
#define P_PA03                 (1ul <<  3) /**< \brief PORT Mask  for PA03 */
#define PA04                           4  /**< \brief Pin Number for PA04 */
#define P_PA04                 (1ul <<  4) /**< \brief PORT Mask  for PA04 */
#define PA05                           5  /**< \brief Pin Number for PA05 */
#define P_PA05                 (1ul <<  5) /**< \brief PORT Mask  for PA05 */
#define PA06                           6  /**< \brief Pin Number for PA06 */
#define P_PA06                 (1ul <<  6) /**< \brief PORT Mask  for PA06 */
#define PA07                           7  /**< \brief Pin Number for PA07 */
#define P_PA07                 (1ul <<  7) /**< \brief PORT Mask  for PA07 */
#define PA08                           8  /**< \brief Pin Number for PA08 */
#define P_PA08                 (1ul <<  8) /**< \brief PORT Mask  for PA08 */
#define PA09                           9  /**< \brief Pin Number for PA09 */
#define P_PA09                 (1ul <<  9) /**< \brief PORT Mask  for PA09 */
#define PA10                          10  /**< \brief Pin Number for PA10 */
#define P_PA10                 (1ul << 10) /**< \brief PORT Mask  for PA10 */
#define PA11                          11  /**< \brief Pin Number for PA11 */
#define P_PA11                 (1ul << 11) /**< \brief PORT Mask  for PA11 */
#define PA12                          12  /**< \brief Pin Number for PA12 */
#define P_PA12                 (1ul << 12) /**< \brief PORT Mask  for PA12 */
#define PA13                          13  /**< \brief Pin Number for PA13 */
#define P_PA13                 (1ul << 13) /**< \brief PORT Mask  for PA13 */
#define PA14                          14  /**< \brief Pin Number for PA14 */
#define P_PA14                 (1ul << 14) /**< \brief PORT Mask  for PA14 */
#define PA15                          15  /**< \brief Pin Number for PA15 */
#define P_PA15                 (1ul << 15) /**< \brief PORT Mask  for PA15 */
#define PA16                          16  /**< \brief Pin Number for PA16 */
#define P_PA16                 (1ul << 16) /**< \brief PORT Mask  for PA16 */
#define PA17                          17  /**< \brief Pin Number for PA17 */
#define P_PA17                 (1ul << 17) /**< \brief PORT Mask  for PA17 */
#define PA18                          18  /**< \brief Pin Number for PA18 */
#define P_PA18                 (1ul << 18) /**< \brief PORT Mask  for PA18 */
#define PA19                          19  /**< \brief Pin Number for PA19 */
#define P_PA19                 (1ul << 19) /**< \brief PORT Mask  for PA19 */
#define PA20                          20  /**< \brief Pin Number for PA20 */
#define P_PA20                 (1ul << 20) /**< \brief PORT Mask  for PA20 */
#define PA21                          21  /**< \brief Pin Number for PA21 */
#define P_PA21                 (1ul << 21) /**< \brief PORT Mask  for PA21 */
#define PA22                          22  /**< \brief Pin Number for PA22 */
#define P_PA22                 (1ul << 22) /**< \brief PORT Mask  for PA22 */
#define PA23                          23  /**< \brief Pin Number for PA23 */
#define P_PA23                 (1ul << 23) /**< \brief PORT Mask  for PA23 */
#define PA24                          24  /**< \brief Pin Number for PA24 */
#define P_PA24                 (1ul << 24) /**< \brief PORT Mask  for PA24 */
#define PA25                          25  /**< \brief Pin Number for PA25 */
#define P_PA25                 (1ul << 25) /**< \brief PORT Mask  for PA25 */
#define PA27                          27  /**< \brief Pin Number for PA27 */
#define P_PA27                 (1ul << 27) /**< \brief PORT Mask  for PA27 */
#define PA28                          28  /**< \brief Pin Number for PA28 */
#define P_PA28                 (1ul << 28) /**< \brief PORT Mask  for PA28 */
#define PA30                          30  /**< \brief Pin Number for PA30 */
#define P_PA30                 (1ul << 30) /**< \brief PORT Mask  for PA30 */
#define PA31                          31  /**< \brief Pin Number for PA31 */
#define P_PA31                 (1ul << 31) /**< \brief PORT Mask  for PA31 */
#define PB00                          32  /**< \brief Pin Number for PB00 */
#define P_PB00                 (1ul <<  0) /**< \brief PORT Mask  for PB00 */
#define PB01                          33  /**< \brief Pin Number for PB01 */
#define P_PB01                 (1ul <<  1) /**< \brief PORT Mask  for PB01 */
#define PB02                          34  /**< \brief Pin Number for PB02 */
#define P_PB02                 (1ul <<  2) /**< \brief PORT Mask  for PB02 */
#define PB03                          35  /**< \brief Pin Number for PB03 */
#define P_PB03                 (1ul <<  3) /**< \brief PORT Mask  for PB03 */
#define PB04                          36  /**< \brief Pin Number for PB04 */
#define P_PB04                 (1ul <<  4) /**< \brief PORT Mask  for PB04 */
#define PB05                          37  /**< \brief Pin Number for PB05 */
#define P_PB05                 (1ul <<  5) /**< \brief PORT Mask  for PB05 */
#define PB06                          38  /**< \brief Pin Number for PB06 */
#define P_PB06                 (1ul <<  6) /**< \brief PORT Mask  for PB06 */
#define PB07                          39  /**< \brief Pin Number for PB07 */
#define P_PB07                 (1ul <<  7) /**< \brief PORT Mask  for PB07 */
#define PB08                          40  /**< \brief Pin Number for PB08 */
#define P_PB08                 (1ul <<  8) /**< \brief PORT Mask  for PB08 */
#define PB09                          41  /**< \brief Pin Number for PB09 */
#define P_PB09                 (1ul <<  9) /**< \brief PORT Mask  for PB09 */
#define PB10                          42  /**< \brief Pin Number for PB10 */
#define P_PB10                 (1ul << 10) /**< \brief PORT Mask  for PB10 */
#define PB11                          43  /**< \brief Pin Number for PB11 */
#define P_PB11                 (1ul << 11) /**< \brief PORT Mask  for PB11 */
#define PB12                          44  /**< \brief Pin Number for PB12 */
#define P_PB12                 (1ul << 12) /**< \brief PORT Mask  for PB12 */
#define PB13                          45  /**< \brief Pin Number for PB13 */
#define P_PB13                 (1ul << 13) /**< \brief PORT Mask  for PB13 */
#define PB14                          46  /**< \brief Pin Number for PB14 */
#define P_PB14                 (1ul << 14) /**< \brief PORT Mask  for PB14 */
#define PB15                          47  /**< \brief Pin Number for PB15 */
#define P_PB15                 (1ul << 15) /**< \brief PORT Mask  for PB15 */
#define PB16                          48  /**< \brief Pin Number for PB16 */
#define P_PB16                 (1ul << 16) /**< \brief PORT Mask  for PB16 */
#define PB17                          49  /**< \brief Pin Number for PB17 */
#define P_PB17                 (1ul << 17) /**< \brief PORT Mask  for PB17 */
#define PB22                          54  /**< \brief Pin Number for PB22 */
#define P_PB22                 (1ul << 22) /**< \brief PORT Mask  for PB22 */
#define PB23                          55  /**< \brief Pin Number for PB23 */
#define P_PB23                 (1ul << 23) /**< \brief PORT Mask  for PB23 */
#define PB30                          62  /**< \brief Pin Number for PB30 */
#define P_PB30                 (1ul << 30) /**< \brief PORT Mask  for PB30 */
#define PB31                          63  /**< \brief Pin Number for PB31 */
#define P_PB31                 (1ul << 31) /**< \brief PORT Mask  for PB31 */



/************************************************************************/
/*                  PORT REGISTERS DEFINITIONS                          */
/************************************************************************/

//PORTA

#define DIR0		(RWSFR 0x41004400U)				//PORTA DATA DIRECTION
#define DIRCLR0		(RWSFR 0x41004404U)				//PORTA Data Direction Clear 0
#define DIRSET0		(RWSFR 0x41004408U)				//PORTA Data Direction Set 0
#define DIRTGL0		(RWSFR 0x4100440CU)				//PORTA Data Direction Toggle 0
#define OUT0		(RWSFR 0x41004410U)				//PORTA Data Output Value 0
#define OUTCLR0		(RWSFR 0x41004414U)				//PORTA Data Output Value Clear 0
#define OUTSET0		(RWSFR 0x41004418U)				//PORTA Data Output Value Set 0
#define OUTTGL0		(RWSFR 0x4100441CU)				//PORTA Data Output Value Toggle 0
#define IN0			(ROSFR 0x41004420U)				//PORTA Data Input Value 0
#define CTRL0		(RWSFR 0x41004424U)				//PORTA Control 0
#define WRCONFIG0	(WOSFR 0x41004428U)				//PORTB Write Configuration 1
#define PMUX0(i)	(RWSFR_8 (0x41004430U+i))		//PORTA Peripheral Multiplexing 0
#define PINCFG0(i)	(RWSFR_8(0x41004440U+i))		//PORTA Pin Configuration 0

//PORTB

#define DIR1		(RWSFR 0x41004480U)			//PORTB Data Direction 1
#define DIRCLR1		(RWSFR 0x41004484U)			//PORTB Data Direction Clear 1
#define DIRSET1		(RWSFR 0x41004488U)			//PORTB Data Direction Set 1
#define DIRTGL1		(RWSFR 0x4100448CU)			//PORTB Data Direction Toggle 1
#define OUT1		(RWSFR 0x41004490U)			//PORTB Data Output Value 1
#define OUTCLR1		(RWSFR 0x41004494U)			//PORTB Data Output Value Clear 1
#define OUTSET1		(RWSFR 0x41004498U)			//PORTB Data Output Value Set 1
#define OUTTGL1		(RWSFR 0x4100449CU)			//PORTB Data Output Value Toggle 1
#define IN1			(ROSFR 0x410044A0U)			//PORTB Data Input Value 1
#define CTRL1		(RWSFR 0x410044A4U)			//PORTB Control 1
#define WRCONFIG1	(WOSFR 0x410044A8U)			//PORTB Write Configuration 1
#define PMUX1(i)	(RWSFR_8 (0x410044B0U+i))	//PORTB Peripheral Multiplexing 1
#define PINCFG1(i)	(RWSFR_8 (0x410044C0U+i))	//PORTB Pin Configuration 1

/* ============================================================================*/

/*	Alternate definitions
#define DIR(i)		(RWSFR (0x41004400U+i*0x80))		//PORTA DATA DIRECTION
#define DIRCLR(i)	(RWSFR (0x41004404U+i*0x80))		//PORTA Data Direction Clear 0
#define DIRSET(i)	(RWSFR (0x41004408U+i*0x80))		//PORTA Data Direction Set 0
#define DIRTGL(i)	(RWSFR (0x4100440CU+i*0x80))		//PORTA Data Direction Toggle 0
#define OUTREG(i)	(RWSFR (0x41004410U+i*0x80))		//PORTA Data Output Value 0
#define OUTCLR(i)	(RWSFR (0x41004414U+i*0x80))		//PORTA Data Output Value Clear 0
#define OUTSET(i)	(RWSFR (0x41004418U+i*0x80))		//PORTA Data Output Value Set 0
#define OUTTGL(i)	(RWSFR (0x4100441CU+i*0x80))		//PORTA Data Output Value Toggle 0
#define INREG(i)	(ROSFR (0x41004420U+i*0x80))		//PORTA Data Input Value 0
#define CTRL		(RWSFR 0x41004424U)					//PORTA Control 0
#define WRCONFIG	(WOSFR 0x41004428U)					//PORTB Write Configuration 1
#define PMUX(j,i)	(RWSFR_8 (0x41004430U+i/2+j*0x80))	//PORTA Peripheral Multiplexing 0. 8 bit register
#define PINCFG(j,i) (RWSFR_8 (0x41004440U+i+j*0x80))	//PORTA Pin Configuration 0
*/

/************************************************************************/
/* Another Macros for pin functions                                     */
/*Usage: PinClr(PA15); to clear pin 15 of port A 						*/
/************************************************************************/
//i= Pin Name name i.e. PA15 or PB20
#define DIRCLR(i)	((RWSFR (0x41004404U+((i/32)*0x80)))=(1<<(i%32)))		//PORTA Data Direction Clear 0
#define DIRSET(i)	((RWSFR (0x41004408U+((i/32)*0x80)))=(1<<(i%32)))		//PORTA Data Direction Set 0
#define DIRTGL(i)	((RWSFR (0x4100440CU+((i/32)*0x80)))=(1<<(i%32)))		//PORTA Data Direction Toggle 0

#define PinClr(i)	((RWSFR (0x41004414U+((i/32)*0x80)))=(1<<(i%32)))		//PORT Data Direction Clear 0
#define PinSet(i)	((RWSFR (0x41004418U+((i/32)*0x80)))=(1<<(i%32)))		//PORT Data Direction Set 0
#define PinTgl(i)	((RWSFR (0x4100441CU+((i/32)*0x80)))=(1<<(i%32)))		//PORT Data Direction Toggle 0

#define PinRead(i)	((ROSFR (0x41004420U+((i/32)*0x80))) & (1ul<<((i%32))))	//PORTA Data Input Value 0

#define PINCFG(i)	(RWSFR_8 (0x41004440U+((i/32)*0x80)+(i%32)))			//PORTA Pin Configuration
#define PMUX(i)		(RWSFR_8 (0x41004430U+((i%32)/2)+((i/32)*0x80)))	//PORTA Peripheral Multiplexing 0. 8 bit register


//Function Prototypes for functions defined in S_PORT.C
void portMode(bool port_grp, uint32_t mask, uint8_t mode); //not complete
void pinMode(uint8_t Pin, uint8_t mode);
void digitalWrite(uint8_t pin_no, bool val);
bool digitalRead(uint8_t pin_no);
void pinMux(uint8_t pin_no, uint8_t peripheral);
/*
Apart from above Function these are Macro functions which can be used instead of digitalWrite and digitalRead.
To Set a pin	: PinSet(Pin);
To Clear a pin	: PinClr(Pin);
To Read a pin	: PinRead(Pin);
Pin: PA00,PB20, etc
*/

#endif