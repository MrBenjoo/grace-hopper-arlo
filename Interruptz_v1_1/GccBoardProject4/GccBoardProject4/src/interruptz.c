/*
 * interruptz.c
 *Triggar en interrupt n�r pinne A0 p� ett Arduino UNO ger H�G- och L�G-flank.
 *Inuti interrupt rutinen s�tts pinne D13 H�G p� Arduino Due.
 *P� varannan interrupt s� inverteras v�rdet som skrivs ut p� D13 s� att en �terskapning 
 av den digital signalen som kommer in p� A0 skapas. 
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
