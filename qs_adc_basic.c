

#include <asf.h>


#include "Delay.h"
#include "S_PORT.c"
#include "S_GCLOCK.c"
#include "S_TIMER.c"
#include "S_Keypad.c"
#include "I2CEEPROM.C"

#include "LCD_Lib.c"

void configure_adc(void);

volatile char BCD0, BCD1, BCD2, BCD3, BCD4;
//! [module_inst]
struct adc_module adc_instance;
//! [module_inst]
void bintobcd(uint16_t);
//! [setup]
void configure_adc(void)
{
//! [setup_config]
	struct adc_config config_adc;
//! [setup_config]
//! [setup_config_defaults]
	adc_get_config_defaults(&config_adc);
//! [setup_config_defaults]
	
	config_adc.clock_prescaler=	ADC_CLOCK_PRESCALER_DIV512;
	config_adc.clock_source=GCLK_GENERATOR_0;
	
	config_adc.correction.correction_enable=false;
	config_adc.differential_mode=true;
	config_adc.event_action=ADC_EVENT_ACTION_DISABLED;
	config_adc.freerunning=false;
	
	//config_adc.accumulate_samples=ADC_ACCUMULATE_SAMPLES_16;
	//config_adc.divide_result=ADC_DIVIDE_RESULT_64;
	config_adc.resolution=ADC_RESOLUTION_16BIT;
	config_adc.gain_factor=ADC_GAIN_FACTOR_1X;
	
	config_adc.left_adjust=false;
	config_adc.negative_input=ADC_NEGATIVE_INPUT_PIN6;
	config_adc.positive_input=ADC_POSITIVE_INPUT_PIN7;
	
	config_adc.pin_scan.inputs_to_scan=0;
	
	config_adc.reference=ADC_REFERENCE_INT1V;
	config_adc.reference_compensation_enable=true;
	
	config_adc.run_in_standby=false;
	config_adc.sample_length= 63;
	config_adc.window.window_mode=ADC_WINDOW_MODE_DISABLE;
		

//! [setup_set_config]
	adc_init(&adc_instance, ADC, &config_adc);
//! [setup_set_config]
	
//! [setup_enable]
	adc_enable(&adc_instance);
//! [setup_enable]-
}
//! [setup]


void config_timer(){
	
	REG_PM_APBCMASK|= (1<<13);
	GCLKGen_Peripheral(GCLKGEN0 , GCLK_TC4_GCLK_TC5);

	REG_TC5_CTRLA=(1<<0);	//reset
	REG_TC5_CTRLBSET=(1<<6);
	REG_TC5_COUNT8_CC1= 127;
	pinMux(PB15,ETCmux);
	//presync |prescale|wave mode|TC Mode| Enable
	REG_TC5_CTRLA = (0<<12) | (5<<8) | (2<<5) | (1<<2) | (1<<1);
}


int main(void)
{
	int16_t x;
	int32_t z;
	system_init();
	bool sign;
//! [setup_init]
	configure_i2c_master();
	
	config_timer();
	configure_adc();
	write_byte(10,0x67);
	uint8_t eep=read_byte(10);
//	*((uint8_t *)0x41004447U)=0x1; //pincfg for pin PA07;
//	*((uint8_t *)0x41004433U)=0x11; //pinmux for pa6 and 7
//	*((uint8_t *)0x41004431U)=0x10; //pinmux for pa03
//! [setup_init]
	//float x,y,z;
	//z=x/y;
//! [main]
//! [start_conv]
	pinMode(PA12, OUTPUT);
	PinSet(PA12);
	delay_us(5);
	PinClr(PA12);
//! [start_conv]
REG_PORT_DIR0= 0x003F1400;

LCD_Init();
LCD_Init();
LCD_disp("ADC TEST");
LCD_CursorOff();
//! [get_res]
	

//! [get_res]

//! [inf_loop]
	while (1) {
		//simple averaging
		z=0;
	
			REG_ADC_SWTRIG=0B10;	//start adc
			//port_pin_set_output_level(PIN_PA12,1);
			bool resready=false;
			
			while(resready!=true){
			
				resready=(REG_ADC_INTFLAG&0b1);
			}
		//	port_pin_set_output_level(PIN_PA12,0);
				
				x=(4095) & REG_ADC_RESULT;
			
			LCD_Setcursor(1,5);
			LCD_DataWrite(' ');
			sign=0x8000&x;
			if (sign==1)
			{	LCD_Setcursor(1,5);
				LCD_DataWrite('-');
				x=65536-x;
			}
			
//				float y=(float)x*((1000.0/2048.0)*100.0); 
	//			y=y-1367.0;
		//		x=(int16_t)y;
				
				
				
				
			LCD_Setcursor(1,7);
			bintobcd(x);
			
			
			LCD_DispAscii(BCD0);
			LCD_DispAscii(BCD1);
			LCD_DispAscii(BCD2);
			LCD_DispAscii(BCD3);
			LCD_DispAscii(BCD4);
			
			//delay_ms(50);
	}
}


void bintobcd(uint16_t x)
{
	float t;					//Converts 16-bit binary no. to BCD to be displayed on screen.
	t=x/100000;
	BCD0 = x/10000;						
	BCD1 = x/1000 - BCD0*10;			
	BCD2 = x/100 - (x/1000)*10;			
	BCD3 = x/10 - ((x/100)*10);			
	BCD4 = x -(x/10)*10;				
}