/*
 * spi.h
 *
 * Created: 1/28/2012 8:44:37 PM
 *  Author: Nikola
 */ 


#ifndef SPI_H_
#define SPI_H_



void startSPI(void);
unsigned char SPI_transmit(unsigned char);
unsigned char SPI_receive(void);



#endif /* SPI_H_ */