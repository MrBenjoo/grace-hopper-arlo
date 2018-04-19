/*
Triggar en interrupt när pinne A0 på ett Arduino UNO ger HÖG- och LÅG-flank.
Inuti interrupt rutinen sätts pinne D13 HÖG på Arduino Due.
På varannan interrupt så inverteras värdet som skrivs ut på D11 så att en återskapning
av den digital signalen som kommer in på A0 skapas. 
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
