/*
Triggar en interrupt när pinne A0 på ett Arduino UNO ger HÖG- och LÅG-flank.
Inuti interrupt rutinen sätts pinne D13 HÖG på Arduino Due.
På varannan interrupt så inverteras värdet som skrivs ut på D11 så att en återskapning
av den digital signalen som kommer in på A0 skapas. 
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
