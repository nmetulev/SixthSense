/*
 * USART.c
 *
 * Created: 2/28/2012 7:16:04 PM
 *  Author: Laptop
 */ 
#include "USART.h"

void USART_Init( unsigned int baud )
{
	/* Set baud rate */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
	//UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

unsigned char USART_Receive()
{

   while(!(UCSRA & (1<<RXC)));//{flashLED(RED);}
   
   return UDR;
}

void USART_flush()
{
	unsigned char dummy;
	while (UCSRA & (1<<RXC))
		dummy = UDR;
}
