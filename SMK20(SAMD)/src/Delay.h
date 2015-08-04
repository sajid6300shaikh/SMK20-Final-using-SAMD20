

#ifndef _DELAY_H_
#define _DELAY_H_
/************************************************************************/
/* Timing checked on DSO, delay routines created for 48000MHZ DFLL CPU CLOCK  */
/************************************************************************/

void delay_us(uint32_t iter_us);
void delay_1us(void);
void delay_1ms(void);
void delay_ms(uint32_t);
void delay_sec(uint16_t);
#endif