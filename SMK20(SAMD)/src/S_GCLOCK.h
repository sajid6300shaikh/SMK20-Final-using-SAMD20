#include "compiler.h"

#ifndef _S_GCLOCK_h
#define _S_GCLOCK_h

/************************************************************************/
/*		 These are GCLK_generator macros used in GCLKGen_Peripheral		*/
/************************************************************************/

#define		GCLKGEN0	0
#define		GCLKGEN1	1
#define		GCLKGEN2	2
#define		GCLKGEN3	3
#define		GCLKGEN4	4
#define		GCLKGEN5	5
#define		GCLKGEN6	6
#define		GCLKGEN7	7
#define		GCLKGEN8	8


/*****************************************************************************/
/* These are the Peripheral names macros used in GCLKGen_Peripheral function */
/*****************************************************************************/
#define		GCLK_DFLL48M_REF	  	   0x00
#define		GCLK_DPLL  				   0x01
#define		GCLK_DPLL_32K  			   0x02
#define		GCLK_WDT  				   0x03
#define		GCLK_RTC  				   0x04
#define		GCLK_EIC  				   0x05
#define		GCLK_USB  				   0x06
#define		GCLK_EVSYS_CHANNEL_0  	   0x07
#define		GCLK_EVSYS_CHANNEL_1  	   0x08
#define		GCLK_EVSYS_CHANNEL_2  	   0x09
#define		GCLK_EVSYS_CHANNEL_3  	   0x0A
#define		GCLK_EVSYS_CHANNEL_4  	   0x0B
#define		GCLK_EVSYS_CHANNEL_5  	   0x0C
#define		GCLK_EVSYS_CHANNEL_6  	   0x0D
#define		GCLK_EVSYS_CHANNEL_7  	   0x0E
#define		GCLK_EVSYS_CHANNEL_8  	   0x0F
#define		GCLK_EVSYS_CHANNEL_9  	   0x10
#define		GCLK_EVSYS_CHANNEL_10	   0x11
#define		GCLK_EVSYS_CHANNEL_11	   0x12
#define		GCLK_SERCOMx_SLOW		   0x13
#define		GCLK_SERCOM0_CORE		   0x14
#define		GCLK_SERCOM1_CORE		   0x15
#define		GCLK_SERCOM2_CORE		   0x16
#define		GCLK_SERCOM3_CORE		   0x17
#define		GCLK_SERCOM4_CORE		   0x18
#define		GCLK_SERCOM5_CORE		   0x19
#define		GCLK_TCC0_GCLK_TCC1		   0x1A
#define		GCLK_TCC2_GCLK_TC3		   0x1B
#define		GCLK_TC4_GCLK_TC5		   0x1C
#define		GCLK_TC6_GCLK_TC7		   0x1D
#define		GCLK_ADC				   0x1E
#define		GCLK_AC_DIG				   0x1F
#define		GCLK_AC_ANA				   0x20
#define		GCLK_DAC				   0x21
#define 	GCLK_PTC				   0x22
#define 	GCLK_I2S_0				   0x23
#define		GCLK_I2S_1				   0x24
//reserved				   0x25-0x3F



/************************************************************************/
/* CloCK Source used in GENCTRL Register                                */
/************************************************************************/

#define		XOSC		0x00	
#define	   	GCLKIN		0x01
#define	   	GCLOCKGEN1	0x02
#define	   	OSCULP32K	0x03
#define	   	OSC32K		0x04
#define	   	XOSC32K		0x05
#define	   	OSC8M		0x06
#define	   	DFLL48M		0x07
#define	   	FDPLL96M	0x08
			//Reserved	0x09-0x1F

/************************************************************************/
/* These are GCLCK Peripheral Register                                  */
/************************************************************************/

#define		GCLK_CTRL		(*(RwReg8 *)0x40000C00U) /**< \brief (GCLK) Control */
#define		GCLK_STATUS     (*(RoReg8 *)0x40000C01U) /**< \brief (GCLK) Status */
#define		CLKCTRL         (*(RwReg16*)0x40000C02U) /**< \brief (GCLK) Generic Clock Control */
#define		GENCTRL         (*(RwReg  *)0x40000C04U) /**< \brief (GCLK) Generic Clock Generator Control */
#define		GENCTRLID		(*(RwReg8 *)0x40000C07U)
#define		GENDIV          (*(RwReg  *)0x40000C08U) /**< \brief (GCLK) Generic Clock Generator Division */

/************************************************************************/
/*  GENCLK generator division factor                                    */
/************************************************************************/
//these are allowed Division Factor for each Gclock Generator
//	GclockGen0	:	0-127
//	GclockGen1	:	0-65535
//	GclockGen2	:	0-31
//	GclockGen3-8:	0-127
#define	CLKRDY	(REG_SYSCTRL_DPLLSTATUS & (1<<1))


void GCLKGen_Peripheral(uint8_t GclockGen, uint8_t Peripheral);
void GCLKGen_Source(uint8_t GclockGen, uint8_t ClockSource);
void GCLKGen_Divide(uint8_t GclockGen, uint16_t Divisor);
void ConfigureGCLKGen(uint8_t GclockGen, uint8_t ClkSrc, bool outputGclk, uint16_t Divisor, bool DivType);

//FDPLL not supported on SAMD20
//void StopFDPLL();
//void RunFDPLL(uint32_t Frequency);

#endif