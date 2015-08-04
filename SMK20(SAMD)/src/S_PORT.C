/************************************************************************/
/* CUSTOM PORT MACROS                                                    
Author: Sajid Shaikh													*/
/************************************************************************/

#include "S_PORT.h"

/************************************************************************/
/* Usage Eg: pinMode(PA,15, OUTPUT);                                    */

/************************************************************************/
/*void pinMode(bool port_grp, uint8_t pin_no, uint8_t mode)
{
	if (port_grp==PA)
	{
		if (mode==OUTPUT) {
			DIRSET0=(1<<pin_no);			//make pin as ouput
		} 
		else if(mode==INPUT) {
			DIRCLR0=(1<<pin_no);			//make pin input			
		}
		else {							//pin configured as input and output
			DIRSET0=(1<<pin_no);		//enable pin as output
			PINCFG0(pin_no)|=0b10;	//enable input pin sampling			
		}								
	} 
	
	else
	{
		if (mode==OUTPUT)
		{
			DIRSET1=(1<<pin_no);		//make pin output
		}
		else if(mode==INPUT) {
			DIRCLR0=(1<<pin_no);		//make pin input			
		}
		else
		{
			DIRCLR1=(0<<pin_no);
			PINCFG1(pin_no)|=0b10;		//enable input pin sampling			
		}
	}
	
}
OLD approach */
/*
void pinMode(bool port_grp, uint8_t pin_no, uint8_t mode)
{
		if (mode==OUTPUT) {
			DIRSET(port_grp)=(1<<pin_no);	//make pin as output
		}
		else if(mode==INPUT) {
			DIRCLR(port_grp)=(1<<pin_no);	//make pin input
			PINCFG(port_grp,pin_no)|=0b10;	//enable input pin sampling
		}
		else {								//pin configured as input and output
			DIRSET(port_grp)=(1<<pin_no);	//enable pin as output
			PINCFG(port_grp,pin_no)|=0b10;	//enable input pin sampling
		}
}

 OLD approach*/

//usage pinMode(PA15, OUTPUT)
void pinMode(uint8_t Pin, uint8_t mode)
{
	if (mode==OUTPUT) {			//strong Totem Pole output
		DIRSET(Pin);			//enable pin as output
		PINCFG(Pin)=0;			//disable pull up, input, low drive strength
	}
		
	else if (mode==WEAKOUT){	//pin configured as output with weak pull
		DIRCLR(Pin);			//enable pin as output
		PINCFG(Pin)|=0b100;		//enable pull RESISTOR
	//Pull value will be decided by OUT register value
	//when OUT bit is 1 for a particular pin it will be pulled high and for out bit =0 pin will be pulled low
	}
	
	else if(mode==INPUT) {		//high impedance input
		DIRCLR(Pin);			//make pin input
		PINCFG(Pin)|=0b10;		//enable input pin sampling, pull disabled		
	}
	
	else if (mode==INOUT){		//pin configured as input and output
		DIRSET(Pin);			//enable pin as output
		PINCFG(Pin)|=0b10;		//enable input pin sampling
	}
	
	else if (mode==INPUP){		//pin configured as input with pull up resistor
		DIRCLR(Pin);			//enable pin as input
		PINCFG(Pin)|=0b110;		//enable pull and input pin sampling
	//pull value(1 or 0) depends on OUT register value, since we want pull up so we will set 'OUT' register bit
		PinSet(Pin);											
	}
	
	else if (mode==INPDN){		//pin configured as input with pull down resistor
		DIRCLR(Pin);			//enable pin as input
		PINCFG(Pin)|=0b110;		//enable pull and input pin sampling
	//pull value(1 or 0) depends on OUT register value, since we want pull dwn so we will clear 'OUT' register bit
		PinClr(Pin);
	}
		
}

//usage digitalWrite(PA20, HIGH); to set pin PA20
//Alternatively you can use PinSet(PA20) and PinClr(pin_no) macros
void digitalWrite(uint8_t pin_no, bool val){
	if (val==1)
	{
		PinSet(pin_no);
	}
	else
	{
		
		PinClr(pin_no);
	}
}

//usage bool a= digitalRead(PB20); a will contain status of pin PB20
//Alternatively You can use macro function eg:PinRead(PA04), since this function also does the same.
bool digitalRead(uint8_t Pin){
	return(PinRead(Pin));
}


	/*		Usage: pinMux(PA2, ADC);		*/
//REFER S_PORT.h To get list of PINMUX peripheral names
	 
void pinMux(uint8_t Pin, uint8_t peripheral){ //refer S_PORT.h for available options for peripheral.
//Enable PINMUX for the pin
if (peripheral==0x0A)
{
	PINCFG(Pin)&=0xFE;	//clr bit 0
}
else
{
	PINCFG(Pin) = 0b1;
	//peripheral &= 0x0F;						//makes sure peripheral is 4 bit value
	if ((Pin%32) %2==0)						//even pin no. corresponds to lower nibble in Pmux reg
	{
		PMUX(Pin)&=0xF0;		//clr all lower bits
		PMUX(Pin)|= peripheral;	// place data in lower nibble
	} 
	else  {								//odd pin no. corresponds to higher nibble in Pmux register
		PMUX(Pin)&=0x0F;		//set all higher bits
		PMUX(Pin)|=(peripheral<<4);	// place data in higher nibble
	}
}
}