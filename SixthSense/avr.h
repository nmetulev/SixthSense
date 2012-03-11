// Copyright 2010, Tony Givargis.

#ifndef __avr__
#define __avr__

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#define XTAL_FRQ                                7372800lu

#define SET_BIT(p,i)                            ((p) |=  (1 << (i)))
#define CLR_BIT(p,i)                            ((p) &= ~(1 << (i)))
#define GET_BIT(p,i)                            ((p) &   (1 << (i)))

#define WDR()                                   asm volatile("wdr"::)
#define NOP()                                   asm volatile("nop"::)
#define CLI() asm volatile("cli"::);
#define SEI() asm volatile("sei"::);
#define RST()                                   for(;;);

void ini_avr(void);
void wait_avr(unsigned short msec);

#endif
