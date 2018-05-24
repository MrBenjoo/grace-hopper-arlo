/*
 * debuggingLEDS.c
 *
 * Created: 2018-05-22 17:03:01
 *  Author: Sebastian
 */ 

#include <asf.h>
#include <stdio.h>
#include "../initializations/pins_init.h"


void binaryLEDS(int number){
	switch(number){
	
	case(0):
	ioport_set_pin_level(pin48, HIGH);
	ioport_set_pin_level(pin49, HIGH);
	ioport_set_pin_level(pin50, HIGH);
	ioport_set_pin_level(pin51, HIGH);
	break;
	
	case(1):
	ioport_set_pin_level(pin48, HIGH);
	ioport_set_pin_level(pin49, LOW);
	ioport_set_pin_level(pin50, LOW);
	ioport_set_pin_level(pin51, LOW);
	break;
	
	case(2):
	ioport_set_pin_level(pin48, LOW);
	ioport_set_pin_level(pin49, HIGH);
	ioport_set_pin_level(pin50, LOW);
	ioport_set_pin_level(pin51, LOW);
	break;
	
	case(3):
	ioport_set_pin_level(pin48, HIGH);
	ioport_set_pin_level(pin49, HIGH);
	ioport_set_pin_level(pin50, LOW);
	ioport_set_pin_level(pin51, LOW);
	break;
	
	case(4):
	ioport_set_pin_level(pin48, LOW);
	ioport_set_pin_level(pin49, LOW);
	ioport_set_pin_level(pin50, HIGH);
	ioport_set_pin_level(pin51, LOW);
	break;
	
	case(5):
	ioport_set_pin_level(pin48, HIGH);
	ioport_set_pin_level(pin49, LOW);
	ioport_set_pin_level(pin50, HIGH);
	ioport_set_pin_level(pin51, LOW);
	break;
	
	case(6):
	ioport_set_pin_level(pin48, LOW);
	ioport_set_pin_level(pin49, HIGH);
	ioport_set_pin_level(pin50, HIGH);
	ioport_set_pin_level(pin51, LOW);
	break;
	
	case(7):
	ioport_set_pin_level(pin48, HIGH);
	ioport_set_pin_level(pin49, HIGH);
	ioport_set_pin_level(pin50, HIGH);
	ioport_set_pin_level(pin51, LOW);
	break;
	
	case(8):
	ioport_set_pin_level(pin48, LOW);
	ioport_set_pin_level(pin49, LOW);
	ioport_set_pin_level(pin50, LOW);
	ioport_set_pin_level(pin51, HIGH);
	break;
	
	case(9):
	ioport_set_pin_level(pin48, HIGH);
	ioport_set_pin_level(pin49, LOW);
	ioport_set_pin_level(pin50, LOW);
	ioport_set_pin_level(pin51, HIGH);
	break;
	
		case(10):
	ioport_set_pin_level(pin48, LOW);
	ioport_set_pin_level(pin49, HIGH);
	ioport_set_pin_level(pin50, LOW);
	ioport_set_pin_level(pin51, HIGH);
	break;
	
	case(99):
	ioport_set_pin_level(pin48, LOW);
	ioport_set_pin_level(pin49, LOW);
	ioport_set_pin_level(pin50, LOW);
	ioport_set_pin_level(pin51, LOW);
	break;
	}
}



