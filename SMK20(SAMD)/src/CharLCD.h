#ifndef _CHAR_LCD_H
#define _CHAR_LCD_H

#include "S_PORT.h"


//Hardware definitions
#define LCD_D7			PA19		//to read back busy flag
#define LCD_D6			PA18		//connected to port A
#define LCD_D5			PA17
#define LCD_D4			PA16

#define LCD_RS			PA10
#define LCD_EN			PA20
#define LCD_RWb			PA21

#define LCD_BUS			REG_PORT_OUT0	//write to lcd_bus means write to PORTA (change it to reg_port_out1 for port B)

//Software Definitions
#define LCD_BUS_Mask	0x000f0000		//In binary it is 1111 at position 16,17,18,19(i.e. pins connected to LCD D4...D7).
#define LCD_Shift		16				//since bus starts at pin 16 connected to D4 of LCD, we will shift the nibble to be sent to LCD by this many positions


void LCD_DataWrite(unsigned char );
void LCD_Init(void);
void LCD_CmdWrite(unsigned char );
void checkbusy(void);
void LCD_Setcursor(char, char);
void LCD_disp(char *);
void LCD_DispAscii(char a);
void LCD_CursorOn(void);
void LCD_CursorOff(void);
void LCD_CursorBlink(void);
void LCD_fulldisp(	char *, char *, char *, char *);
void LCD_build(char, char *);
void LCD_build2(void);
void LCD_Clrscr(void);
#endif