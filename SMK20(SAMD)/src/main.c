/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

#include "Delay.h"
#include "S_PORT.h"
#include "S_GCLOCK.h"
#include "CharLCD.h"
#include "EEProm.h"
#include "MatrixKeypad.h"



int main (void)
{
	system_init();
	
	pinMode(PA06,OUTPUT);

	//LCD_Init();
	//LCD_disp("SUCCESS");
	//
	//ClearKeys();
	volatile double a= 32978.768/978468.254561;
	
while (1)
{
	PinSet(PA06);
	delay_sec(1);
	PinClr(PA06);
	delay_sec(1);
	
}
	// Insert application code here, after the board has been initialized.
}
