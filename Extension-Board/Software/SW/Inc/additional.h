#ifndef _ADDITIONAL_h_
#define _ADDITIONAL_h_

#include "main.h"

char Relay(char set, char state, char pos);
char Led(char set, char state, char pos);
char RGB(char set, char colors);

void init_seg(void);
void seg_reset(void);

void UseSeg(char set, char t, char h, char z, char e, char pointPos, char doppelpunkt, char apostroph);
void seg(volatile char t, volatile char h, volatile char z, volatile char e, volatile char pointPos, volatile char doppelpunkt, volatile char apostroph);

void button(void);

void localtemp(uint32_t *temp, char set/*, char showtoseg*/);
void SendTemp(char set, volatile int iTemp);
#endif
