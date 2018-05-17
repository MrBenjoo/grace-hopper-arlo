/*
 * ultraSoundSensor.c
 *
 * Created: 2018-05-17 22:07:43
 *  Author: filip
 */ 

#include "initializations/pins_init.h"

void us_init() {
	echoTimeStop=0;

	sysclk_enable_peripheral_clock(ID_TC2);
	tc_init(TC0,2,0);
	tc_set_block_mode(TC0,0);

	pmc_enable_periph_clk(ID_PIOC);

	pio_set_input(PIOC,pin9,NULL);
	pio_handler_set(PIOC,ID_PIOC,pin9,PIO_IT_EDGE,echoUs);
	pio_enable_interrupt(PIOC,pin9);

	NVIC_EnableIRQ(PIOC_IRQn);
}

void echoUs(){
	if(pio_get(PIOC, PIO_TYPE_PIO_INPUT, pin9)){
		tc_start(TC0,2);
	} else {
		echoTimeStop=tc_read_cv(TC0,2)/42;
		tc_stop(TC0, 2);
	}
}

void usTrig(){
	ioport_enable_pin(pin8);
	ioport_set_pin_dir(pin8, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(pin8,LOW);
	delay_us(5);
	ioport_set_pin_level(pin8,HIGH);
	delay_us(10);
	ioport_set_pin_level(pin8,LOW);
	delay_ms(5);
	
}

long distansUs(){
	long dis = (long)(echoTime()/58);
	return dis;
}

long getEchoTime(){
	return echoTimeStop;
}