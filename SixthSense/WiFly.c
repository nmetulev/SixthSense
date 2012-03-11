/*
 * WiFly.c
 *
 * Created: 3/3/2012 1:00:07 PM
 *  Author: Laptop
 */ 

#include "WiFly.h"
#include "main.h"

void WiFlyInit()
{
	
	enterCommandMode();
	//transmitCommand((unsigned char*)"set wlan ssid SixthSenseServer");
	//transmitData((unsigned char*)"set wlan passphrase sixthsense");
	//transmitCommand((unsigned char*)"set ftp address 192.168.1.1");
	//transmitCommand((unsigned char*)"set ftp user root");
	//transmitCommand((unsigned char*)"set ftp password admin");
	
	//transmitCommand((unsigned char*)"save");
	//transmitCommand((unsigned char*)"reboot");
	printCmd((unsigned char*)"set comm remote 0");
	printCmd((unsigned char*)"set comm open -");
	printCmd((unsigned char*)"set comm close *CLOS*");
	printCmd((unsigned char*)"set ftp timer 480");
	exitCommandMode();
	
	
}

int findInResponse(unsigned char *toMatch)
{
	// implement timeout
	
	unsigned int i = 0;
	unsigned int size = strlen((char*)toMatch);
	
	while (i < size)
	{
		unsigned char byte = USART_Receive();
		if (byte == toMatch[i]) i++;
		else i = 0;
	}
	
	
	return 1;
}

void enterCommandMode()
{
	
	// TO DO: check if already in command mode
	endLine();
	endLine();
	print((unsigned char*)"$$$");
	findInResponse((unsigned char*)"CMD");
}

void exitCommandMode()
{
	endLine();
	println((unsigned char*)"exit");
	findInResponse((unsigned char*)"EXIT");
	
}

void endLine()
{
	print((unsigned char*)"\r\n");
	//wait_avr(DELAY);
}

void println(unsigned char str[])
{
	print(str);
	endLine();
	
}

void print(unsigned char str[])
{
	int i;
	for (i = 0; i < strlen((char*)str); i++)
	{
		USART_Transmit(str[i]);
	}
}

void printCmd(unsigned char str[])
{
	USART_flush();
	println(str);
	findInResponse((unsigned char*)"AOK");
}

void openFTP(unsigned char *filename)
{
	USART_flush();
	//enterCommandMode();
	print((unsigned char*) "ftp put ");
	println(filename);
	
	unsigned char temp = USART_Receive();
	while (temp != (unsigned char)'-') temp = USART_Receive();
}

void closeFTP()
{
	// TO DO: Avoid using the wait_avr
	wait_avr(1000);
	print((unsigned char*)"*CLOS*");
	wait_avr(1000);
	//exitCommandMode();
}

int connect( unsigned char *script, unsigned char *args, unsigned char *filename)
{
	USART_flush();
	//enterCommandMode();
	// open server port
	println((unsigned char*) "open 192.168.1.1 8081");
	
	// wait till connection open
	unsigned char temp = USART_Receive();
	while (temp != (unsigned char)'-') temp = USART_Receive();
	
	print((unsigned char*)"POST ");
	print(script);
	println((unsigned char*) " HTTP/1.1");
	
	unsigned int size = strlen((char*) args);
	char buf[5];
	itoa(size, buf, 10);
	
	println((unsigned char*)"Host: www.camera.com");
	println((unsigned char*)"Content-Type: application/x-www-form-urlencoded");
	println((unsigned char*)"Connection: close");
	print((unsigned char*)"Content-Length: ");
	println((unsigned char*) buf);
	endLine();
	println(args);
	findInResponse((unsigned char*)"HTTP");
	findInResponse((unsigned char*) "filename: ");
	int i;
	for (i = 0; i < 26; ++i) filename[i] = USART_Receive();
	//endLine();
	enterCommandMode();
	println((unsigned char*)"close");
	
	return -1;
}