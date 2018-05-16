/*
Triggar en interrupt n�r pinne A0 p� ett Arduino UNO ger H�G- och L�G-flank.
Inuti interrupt rutinen s�tts pinne D13 H�G p� Arduino Due.
P� varannan interrupt s� inverteras v�rdet som skrivs ut p� D11 s� att en �terskapning
av den digital signalen som kommer in p� A0 skapas. 
*/

#include <asf.h>
#include "ISR.h"
#include "../initializations/pins_init.h"

int8_t pVal1 = -1;
int8_t pVal2 = -1;

void ISR1(void)
{

	//ioport_toggle_pin_level(pin11)
	//ioport_get_pin_level()
	ioport_set_pin_level(pin11,pVal1);
	pVal1 = ~pVal1;
}

void ISR2(void)
{
	ioport_set_pin_level(pin10,pVal2);
	pVal2 = ~pVal2;
}
