#include "compiler.h"
#include "S_GCLOCK.h"
#include "S_SPI.h"
#include "S_PORT.h"



void ConfigureSpi(uint8_t SERCOMxN, uint32_t SCKFreq){	
//SPI SETTING is Master Mode, CPha=0, CPol=0.
//MISO= PAD[0], MOSI= PAD[2], SCK= PAD[3], SS= PAD[1].
//Here We will not waste any other GCLK and use the main clock used by CPU i.e. GCLK0=48MHz (driven from DFLL)	
	uint8_t Baud=0;
	Baud = (48005400/(2*SCKFreq))-1; //DFLL freq is around 48MHz
	switch(SERCOMxN) {
	case 0:
		GCLKGen_Peripheral(GCLKGEN0, GCLK_SERCOM0_CORE);	//Assign GCLK0 to sercom
		REG_PM_APBCMASK= (1<<2);							//enable SERCOM module
		
		REG_SERCOM0_SPI_CTRLA=(1<<0);						//Reset SERCOM
						//	Char Size[2:0]	|		 |	SSDE  | MSSEN	| AMODE	  |  RXEN  |
		REG_SERCOM0_SPI_CTRLB = (0<<0)		| (0<<6) | (1<<9) | (1<<13) | (0<<14) | (1<<17);
		//baud rate is GCLK_SERCOMx_CORE/2(Baud+1)		
		
		REG_SERCOM0_SPI_BAUD =	Baud;
						//		RESET	| Enable |  MODE  |Runstdby|OF notif| DOPO	 | DIPO	   |  FORM   | CPhase |  CPOL |	 DORD
		REG_SERCOM0_SPI_CTRLA= (0<<0)	| (1<<1) | (3<<2) | (0<<7) | (0<<8) | (1<<16)| (0<<20) | (0<<24) | (0<<28)|(0<<29)| (0<<30);
		//CTRLA should be written in the end because other SPI registers are enable protected i.e they can't be modified after CTRLA.Enable bit is set 1
		pinMux(PA08, CSERCOMmux);
		pinMux(PA09, CSERCOMmux);
		pinMux(PA10, CSERCOMmux);
		pinMux(PA11, CSERCOMmux);
	break;
	
	case 1:
		GCLKGen_Peripheral(GCLKGEN0, GCLK_SERCOM1_CORE);	//Assign GCLK0 to sercom
		REG_PM_APBCMASK= (1<<3);							//enable SERCOM module
		
		REG_SERCOM1_SPI_CTRLA=(1<<0);						//Reset SERCOM
						//	Char Size[2:0]	|		 |	SSDE  | MSSEN	| AMODE	  |  RXEN  |
		REG_SERCOM1_SPI_CTRLB = (0<<0)		| (0<<6) | (1<<9) | (1<<13) | (0<<14) | (1<<17);
		//baud rate is GCLK_SERCOMx_CORE/2(Baud+1)
		
		REG_SERCOM1_SPI_BAUD =	Baud;
						//		RESET	| Enable |  MODE  |Runstdby|OF notif| DOPO	 | DIPO	   |  FORM   | CPhase |  CPOL |	 DORD
		REG_SERCOM1_SPI_CTRLA= (0<<0)	| (1<<1) | (3<<2) | (0<<7) | (0<<8) | (1<<16)| (0<<20) | (0<<24) | (0<<28)|(0<<29)| (0<<30);
		//CTRLA should be written in the end because other SPI registers are enable protected i.e they can't be modified after CTRLA.Enable bit is set 1
		
		pinMux(PA16, CSERCOMmux);
		pinMux(PA17, CSERCOMmux);
		pinMux(PA18, CSERCOMmux);
		pinMux(PA19, CSERCOMmux);
		
	break;
		
	case 2:
		GCLKGen_Peripheral(GCLKGEN0, GCLK_SERCOM2_CORE);	//Assign GCLK0 to sercom
		REG_PM_APBCMASK= (1<<4);							//enable SERCOM module
		
		REG_SERCOM2_SPI_CTRLA=(1<<0);						//Reset SERCOM
						//	Char Size[2:0]	|		|	SSDE | MSSEN   | AMODE	 |  RXEN  
		REG_SERCOM2_SPI_CTRLB = (0<<0)		| (0<<6) | (1<<9) | (1<<13) | (0<<14) | (1<<17);
		//baud rate is GCLK_SERCOMx_CORE/2(Baud+1)
		
		REG_SERCOM2_SPI_BAUD =	Baud;
						//		RESET	| Enable |  MODE  |Runstdby|OF notif| DOPO	 | DIPO	   |  FORM   | CPhase |  CPOL |	 DORD
		REG_SERCOM2_SPI_CTRLA= (0<<0)	| (1<<1) | (3<<2) | (0<<7) | (0<<8) | (1<<16)| (0<<20) | (0<<24) | (0<<28)|(0<<29)| (0<<30);
		//CTRLA should be written in the end because other SPI registers are enable protected i.e they can't be modified after CTRLA.Enable bit is set 1
		pinMux(PA12, CSERCOMmux);
		pinMux(PA13, CSERCOMmux);
		//pinMux(PA14, CSERCOMmux);
		pinMux(PA15, CSERCOMmux);

	break;
	
	case 3:
		GCLKGen_Peripheral(GCLKGEN0, GCLK_SERCOM3_CORE);	//Assign GCLK0 to sercom
		REG_PM_APBCMASK= (1<<5);							//enable SERCOM module
		
		REG_SERCOM3_SPI_CTRLA=(1<<0);						//Reset SERCOM
						//	Char Size[2:0]	|		 |	SSDE  | MSSEN	| AMODE	  |  RXEN  |
		REG_SERCOM3_SPI_CTRLB = (0<<0)		| (0<<6) | (1<<9) | (1<<13) | (0<<14) | (1<<17);
		//baud rate is GCLK_SERCOMx_CORE/2(Baud+1)
		
		REG_SERCOM3_SPI_BAUD =	Baud;
		//		RESET	| Enable |  MODE  |Runstdby|OF notif| DOPO	 | DIPO	   |  FORM   | CPhase |  CPOL |	 DORD
		REG_SERCOM3_SPI_CTRLA= (0<<0)	| (1<<1) | (3<<2) | (0<<7) | (0<<8) | (1<<16)| (0<<20) | (0<<24) | (0<<28)|(0<<29)| (0<<30);
		//CTRLA should be written in the end because other SPI registers are enable protected i.e they can't be modified after CTRLA.Enable bit is set 1
		pinMux(PA22, CSERCOMmux);
		pinMux(PA23, CSERCOMmux);
		pinMux(PA24, CSERCOMmux);
		pinMux(PA25, CSERCOMmux);
			
	break;
	
	case 4:
		GCLKGen_Peripheral(GCLKGEN0, GCLK_SERCOM4_CORE);	//Assign GCLK0 to sercom
		REG_PM_APBCMASK= (1<<6);							//enable SERCOM module
		
		REG_SERCOM4_SPI_CTRLA=(1<<0);						//Reset SERCOM
						//	Char Size[2:0]	|		 |	SSDE  | MSSEN	| AMODE	  |  RXEN  |
		REG_SERCOM4_SPI_CTRLB = (0<<0)		| (0<<6) | (1<<9) | (1<<13) | (0<<14) | (1<<17);
		//baud rate is GCLK_SERCOMx_CORE/2(Baud+1)
		
		REG_SERCOM4_SPI_BAUD =	Baud;
						//		RESET	| Enable |  MODE  |Runstdby|OF notif| DOPO	 | DIPO	   |  FORM   | CPhase |  CPOL |	 DORD
		REG_SERCOM4_SPI_CTRLA= (0<<0)	| (1<<1) | (3<<2) | (0<<7) | (0<<8) | (1<<16)| (0<<20) | (0<<24) | (0<<28)|(0<<29)| (0<<30);
		//CTRLA should be written in the end because other SPI registers are enable protected i.e they can't be modified after CTRLA.Enable bit is set 1
		pinMux(PB12, CSERCOMmux);
		pinMux(PB13, CSERCOMmux);
		pinMux(PB14, CSERCOMmux);
		pinMux(PB15, CSERCOMmux);
		
	break;
	
	case 5:
		GCLKGen_Peripheral(GCLKGEN0, GCLK_SERCOM5_CORE);	//Assign GCLK0 to sercom
		REG_PM_APBCMASK= (1<<7);							//enable SERCOM module
		
		REG_SERCOM5_SPI_CTRLA=(1<<0);						//Reset SERCOM
						//	Char Size[2:0]	|		 |	SSDE  | MSSEN	| AMODE	  |  RXEN  |
		REG_SERCOM5_SPI_CTRLB = (0<<0)		| (0<<6) | (1<<9) | (1<<13) | (0<<14) | (1<<17);
		//baud rate is GCLK_SERCOMx_CORE/2(Baud+1)
		
		REG_SERCOM5_SPI_BAUD =	Baud;
						//		RESET	| Enable |  MODE  |Runstdby|OF notif| DOPO	 | DIPO	   |  FORM   | CPhase |  CPOL |	 DORD
		REG_SERCOM5_SPI_CTRLA= (0<<0)	| (1<<1) | (3<<2) | (0<<7) | (0<<8) | (1<<16)| (0<<20) | (0<<24) | (0<<28)|(0<<29)| (0<<30);
		//CTRLA should be written in the end because other SPI registers are enable protected i.e they can't be modified after CTRLA.Enable bit is set 1
		
		pinMux(PB16, CSERCOMmux);
		pinMux(PB17, CSERCOMmux);
		pinMux(PA20, CSERCOMmux);
		pinMux(PA21, CSERCOMmux);
		
	break;
	
	default:
	while (1)
	{
		//do nothing
	}
	break;
	}
	
}