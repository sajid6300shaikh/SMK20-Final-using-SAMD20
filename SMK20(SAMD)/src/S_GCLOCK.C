
#include "compiler.h"
#include "S_GCLOCK.h"
/************************************************************************/
/* Usage EG: To assign Gclock4 to ADC, call
		GCLKGen_Peripheral(GclockGen4, GCLK_ADC);
					or
		GCLKGen_Peripheral(4,GCLK_ADC);								    */
/************************************************************************/
#define	CLKRDY	(REG_SYSCTRL_DPLLSTATUS & (1<<1))

void GCLKGen_Peripheral(uint8_t GclockGen, uint8_t Peripheral){
//this function writes to 16 bit CLKCTRL register
// [WRTLOCK|CLKEN|GEN()]
	uint16_t Data=0;
  //Data=(CLKEN) |    (GEN[0:3])   | (Peripheral ID[5:0])
	Data=(1<<14) |  (GclockGen<<8) | (Peripheral<<0) ;
	CLKCTRL=Data;
}


void GCLKGen_Source(uint8_t GclockGen, uint8_t ClockSource){
//this function writes to 32 bit GENCTRL register	

	uint32_t Data=0;
	Data=(0b001011<<16) | (5<<8) | (4<<0);
	REG_GCLK_GENCTRL=Data;
}


void GCLKGen_Divide(uint8_t GclockGen, uint16_t Divisor){
//this function modifies the GENDIV register
	GENDIV=(Divisor<<8) | (GclockGen<<0);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void ConfigureGCLKGen(uint8_t GclockGen, uint8_t ClkSrc, bool outputGclk, uint16_t Divisor, bool DivType){
//this function modifies 32 bit GENCTRL register
	
  //           (ID[0:3])    | (SRC[8:12]) |  GENEN  |   IDC   |   OOV   |  Output Enable  |    DivSel     | runstdby
 	GENCTRL= (GclockGen<<0) | (ClkSrc<<8) | (1<<16) | (1<<17) | (0<<18) | (outputGclk<<19)| (DivType<<20) | (0<<21);	
	
	GENDIV = (GclockGen<<0) | (Divisor<<8);
}


/*
void RunFDPLL(uint32_t Frequency){
//As per Datasheet using fractional value to multiply i.e. having non-zero value in LDRFRAC has negative impact on jitter
//So we'll avoid using LDRFRAC since we don't need very accurate frequency from FDPLL.
//Minimum Frequency from FDPLL=29Mhz and Max Freq=114 Mhz. hence 885 < LDRval < 3476

		uint16_t LDRval=Frequency/32768-1;		
				//DPLLRatio	 =      LDR    |LDRFRAC
		REG_SYSCTRL_DPLLRATIO=	(LDRval<<0)| (0<<16);	//FDPLL frequency=(LDRval+1+LDRFRAC/16) * REfclk
		
				//DPLLCTRLB  = Filter|Lowpwr| WUF  |Refclk|timout|LckByp |XOSC DIV
		REG_SYSCTRL_DPLLCTRLB=(0<<0) |(0<<2)|(0<<3)|(0<<4)|(0<<8)|(1<<12)|(0<<16);
				//DPLLCTRLA =   Enable
		REG_SYSCTRL_DPLLCTRLA=	(1<<1);
		
		//while (CLKRDY==0)
		//{
		//}
}

void StopFDPLL(){
				//DPLLCTRLA		 =	Enable
			REG_SYSCTRL_DPLLCTRLA=	(0<<1);
}

*/