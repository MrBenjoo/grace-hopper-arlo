/*
 * CFile1.c
 *
 * Created: 2018-05-11 10:25:35
 *  Author: yohan
 */ 

#include "initializations/pins_init.h"
#include "encoderISR.h"
void us_init(){
	 sysclk_enable_peripheral_clock(ID_TC2);
	 tc_init(TC0,2,0);
	 tc_set_block_mode(TC0,0);
}
void usTrig(){
	ioport_enable_pin(pin8);
	ioport_set_pin_dir(pin8, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(pin8,HIGH);
	delay_us(11);
	ioport_set_pin_level(pin8,LOW);	
	
}
uint16_t distansUs(){
	uint32_t dis = echoTime()/58;
	printf("distansus: %i \n",dis);
	return dis;
}
