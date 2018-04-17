/*
 * interruptz.c
 *
 * Created: 2018-04-17 13:19:04
 *  Author: gustav
 */ 
#include <asf.h>
#include "pio.h"
#include "pio_handler.h"
#include "interruptz.h"
#include <stdio.h>

void myISR(void){
	ioport_set_pin_level(PIO_PB27_IDX,HIGH);
}