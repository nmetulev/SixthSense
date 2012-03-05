/*
 * WiFly.h
 *
 * Created: 3/3/2012 1:01:03 PM
 *  Author: Laptop
 */ 
#include "SPItoUART.h"
#include <avr/io.h>
#include "avr.h"
#include <string.h>
#include "USART.h"
#define DELAY 1000

#ifndef WIFLY_H_
#define WIFLY_H_

void enterCommandMode();
void exitCommandMode();
void print(unsigned char str[]);
void println(unsigned char str[]);
void printNoWait(unsigned char str[]);
void endLine();
void openFTP(unsigned char*);
void closeFTP();

void WiFlyInit();






#endif /* WIFLY_H_ */