/*
 * interruptz.c
 *Triggar en interrupt när pinne A0 på ett Arduino UNO ger HÖG- och LÅG-flank.
 *Inuti interrupt rutinen sätts pinne D13 HÖG på Arduino Due.
 *På varannan interrupt så inverteras värdet som skrivs ut på D13 så att en återskapning 
 av den digital signalen som kommer in på A0 skapas. 
 * Created: 2018-04-17 13:19:04
 *  Author: Grace Hopper
 */ 
#include <asf.h>
#include "pio.h"
#include "pio_handler.h"
#include "interruptz.h"
#include <stdio.h>
int pVal = -1;

void myISR(void){  
	ioport_set_pin_level(PIO_PB27_IDX,pVal); 
	pVal = ~pVal;
}
