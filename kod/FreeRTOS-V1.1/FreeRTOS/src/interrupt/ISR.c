/*
Triggar en interrupt n�r pinne A0 p� ett Arduino UNO ger H�G- och L�G-flank.
Inuti interrupt rutinen s�tts pinne D13 H�G p� Arduino Due.
P� varannan interrupt s� inverteras v�rdet som skrivs ut p� D11 s� att en �terskapning
av den digital signalen som kommer in p� A0 skapas. 
*/

#include <asf.h>
#include "ISR.h"
#include "../initializations/pins_init.h"

int pVal = -1;

void my_ISR(void)
{
	ioport_set_pin_level(pin11,pVal);
	pVal = ~pVal;
}
