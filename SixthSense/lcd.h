// Copyright 2010, Tony Givargis.

#ifndef __lcd__
#define __lcd__

void ini_lcd(void);
void clr_lcd(void);
void pos_lcd(unsigned char r, unsigned char c);
void put_lcd(char c);
void puts_lcd(const char *s);

#endif
