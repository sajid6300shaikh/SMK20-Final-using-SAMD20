
#include "compiler.h"

#include "Delay.h"


 inline void delay_1us() {			//gives 1 us delay
	 for (int iter=0; iter<1;iter++)
	 {
	 }
 }

void delay_us(uint32_t iter_us){	//gives (2+iter_us)us delay
	while(iter_us!=0){
		delay_1us();
		iter_us--;
	}
}

void delay_1ms() {
	for(int iter=0;iter<3700;iter++)	//value adjusted to give 1 ms delay
	{
		asm("NOP");
	}
}

void delay_ms(uint32_t iter_ms){
	for (int i=iter_ms;i>0;i--)
	{
		delay_1ms();
	}
}


void delay_sec(uint16_t iter_s){
	while(iter_s!=0){
		delay_ms(1000);
		iter_s--;
	}
	
}