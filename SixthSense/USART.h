/*
 * USART.h
 *
 * Created: 2/28/2012 7:16:19 PM
 *  Author: Laptop
 */ 
#include "main.h"
#include <avr/io.h>

#ifndef USART_H_
#define USART_H_

void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive();
void USART_flush(void);

#endif /* USART_H_ */