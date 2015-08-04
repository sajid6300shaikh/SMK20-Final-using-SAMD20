/*
20X4 LCD library routines created for Atmel SAMD Series controllers.

Author:Sajid Shaikh

Contains all low level and high level routines for Full four line display, Single line display,
Many cursor options, Custom Character Building, etc


*/
#include "CharLCD.h"
#include "Delay.h"

void LCD_Init(void)
{
//First Setup All port pins properly
//Setup port as output and pin LCD_D7 as output with input read enable.
pinMode(LCD_D4, OUT);		//D4
pinMode(LCD_D5, OUT);		//D5
pinMode(LCD_D6, OUT);		//D6
pinMode(LCD_D7, OUT);	//D7, INOUT since we need to read back busy flag

pinMode(LCD_RS, OUT);
pinMode(LCD_RWb, OUT);
pinMode(LCD_EN, OUT);
//------------------------------------------------------------------------
//LCD commands start here

	delay_ms(100);
	LCD_CmdWrite(0x30);
	delay_ms(20);
	LCD_CmdWrite(0x30);
	
	delay_ms(20);
	LCD_CmdWrite(0x30);
	
	delay_ms(40);
	LCD_CmdWrite(0x02);  //Initialize the LCD in 4bit Mode
	delay_ms(40);
	LCD_CmdWrite(0x28);
	checkbusy();

	
	LCD_CmdWrite(0x06);
	checkbusy();
	
	LCD_CmdWrite(0x0E);
	checkbusy();  // Display ON cursor ON
	
	LCD_CmdWrite(0x01);
	checkbusy();  // Clear the LCD
	
	LCD_CmdWrite(0x80);
	checkbusy();  // Move the Cursor to First line First Position
	
}

void LCD_Setcursor(char R, char C)	
//pass row and column no to this function
//for eg. LCD_Setcursor(1,15), for row 2nd and column 16 on LCD, since numbering here starts from 0.
{
	switch(R)		
	{
			case 0:
			LCD_CmdWrite(0x80+C);
			break;
			
			case 1:
			LCD_CmdWrite(0xC0+C);
			break;
			
			case 2:
			LCD_CmdWrite(0x94+C);
			break;
			
			case 3:
			LCD_CmdWrite(0xD4+C);
			break;
			
	}

	
}

void LCD_CmdWrite(unsigned char cmd)
{
	uint32_t lcddata =0;	//temp var
// GET the Higher Nibble of the command in lcddata buffer
	lcddata = ( 0xF << LCD_Shift) & (cmd << (LCD_Shift-4));     
// Select the Command Register by pulling RS pin LOW
	PinClr(LCD_RS);		
	
// Select the Write Operation  by pulling RW pin LOW
	PinClr(LCD_RWb);
	
//this instruction puts the nibble on o/p pins			
	LCD_BUS =LCD_BUS & ~LCD_BUS_Mask;		//put lcddata buffer's data on output port.
	LCD_BUS =LCD_BUS | lcddata;
		
// Send a enable pulse to lcd
	PinSet(LCD_EN);
		delay_1us();
	PinClr(LCD_EN);
		delay_ms(1);                 
	
	
	lcddata =0;
// GET the Lower Nibble of the command in lcddata buffer
	lcddata = ( 0xF << LCD_Shift) & (cmd << LCD_Shift);
 
// Select the Command Register by pulling RS LOW
	PinClr(LCD_RS);
	
// Select the Write Operation  by pulling RW LOW
	PinClr(LCD_RWb);

		LCD_BUS =LCD_BUS & ~LCD_BUS_Mask;
		LCD_BUS =LCD_BUS | lcddata;  
		
// Send a enable pulse to lcd
	PinSet(LCD_EN);
	delay_1us();
	PinClr(LCD_EN);
		checkbusy();
}


void LCD_DataWrite(unsigned char dat)	//same as cmd functn, only RS pin is high in this case.
{
	uint32_t lcddata =0;
// GET the Higher Nibble of the command in lcddata buffer
	lcddata = ( 0xF << LCD_Shift) & (dat << (LCD_Shift-4)); 
	    
// Select the Data Register by pulling RS High
	PinSet(LCD_RS);
// Select the Write Operation  by pulling RW LOW
	PinClr(LCD_RWb);
	
//put lcddata buffer's data on output port.	
	LCD_BUS =LCD_BUS & ~LCD_BUS_Mask;
	LCD_BUS =LCD_BUS | lcddata;

// Send a enable pulse to lcd
	PinSet(LCD_EN);
	delay_1us();
	PinClr(LCD_EN);

	delay_ms(1);                   // wait for some time
	
//Now you know the Drill	
	lcddata =0;
	lcddata = ( 0xF << LCD_Shift) & (dat << LCD_Shift);

	PinSet(LCD_RS);
	PinClr(LCD_RWb);	
		
	LCD_BUS =LCD_BUS & ~LCD_BUS_Mask;
	LCD_BUS =LCD_BUS | lcddata;

	PinSet(LCD_EN);
	delay_1us();
	PinClr(LCD_EN);
	checkbusy();
}

void LCD_disp(char *str)
{
	while(*str) 			//till string ends
	LCD_DataWrite(*str++); 	//send characters one by one
}
void LCD_DispAscii(char a){
	LCD_DataWrite(a+48);
}

void LCD_fulldisp(char *str0, char *str1, char *str2, char *str3 )	//pass a string for each row	
{																		//string should not be more than 20 character long excluding string end character
//Fills all four lines of LCD with the passed strings msg.
	LCD_Setcursor(0,0);
	LCD_disp(str0);

	LCD_Setcursor(1,0);
	LCD_disp(str1);

	LCD_Setcursor(2,0);
	LCD_disp(str2);

	LCD_Setcursor(3,0);
	LCD_disp(str3);
}


void checkbusy()		//waits until LCD is busy
{

//delay_ms(2);
	volatile bool p27=1;			// temporary boolean bit var.

//	WritePin(LCD_D7,1);
	pinMode(LCD_D7, INPUT);		//configure lcd_d7 as input
	PinClr(LCD_RS);
	PinSet(LCD_RWb);	//RWb=1 indicates read operation.
	
	while(p27) 
	{
	PinClr(LCD_EN);
	delay_1us();
	PinSet(LCD_EN);

		p27=PinRead(LCD_D7);
		
	PinClr(LCD_EN);
	delay_1us();
	PinSet(LCD_EN);
	}
	PinClr(LCD_EN);
	PinClr(LCD_RWb);
	pinMode(LCD_D7,OUT);	//reconfigure LCD_D7 as output

}

void LCD_build(char location, char *ptr){		//character should be built before writing anything to lcd.
	unsigned char i;
	if(location<8){
		LCD_CmdWrite(0x40+(location*8));
		for(i=0;i<8;i++)
		LCD_DataWrite(ptr[ i ]);
	}
	
}


void LCD_build2(){			//polltech Symbol
	LCD_CmdWrite(0x48); //Load the location where we want to store
	LCD_DataWrite(0x10); //Load row 1 data
	LCD_DataWrite(0x00); //Load row 2 data
	LCD_DataWrite(0x1e); //Load row 3 data
	LCD_DataWrite(0x11); //Load row 4 data
	LCD_DataWrite(0x1e); //Load row 5 data
	LCD_DataWrite(0x10); //Load row 6 data
	LCD_DataWrite(0x10); //Load row 7 data
	LCD_DataWrite(0x00); //Load row 8 data
}


void LCD_CursorOn(){
	LCD_CmdWrite(0x0E);
}

void LCD_CursorOff(){
	LCD_CmdWrite(0x0C);
}

void LCD_CursorBlink(){
	LCD_CmdWrite(0x0F);
}

void LCD_Clrscr(){
	LCD_CmdWrite(0x01);
}
