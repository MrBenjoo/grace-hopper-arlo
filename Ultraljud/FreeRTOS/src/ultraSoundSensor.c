/*
 * ultraSoundSensor.c
 *
 * Created: 2018-05-18 11:44:29
 *  Author: filip
 */

#include <asf.h>
#include "ultraSoundSensor.h"
#include "motorController.h"
#include "../initializations/pins_init.h"

void us_init() {
	sysclk_enable_peripheral_clock(ID_TC2);
	tc_init(TC0,2,0);
	tc_set_block_mode(TC0,0);

	/*  Initializes interrupt pin for the UltraSound sensor echo, trigger on level change, pin9*/
	pio_set_input(PIOC,pin9,NULL);
	pio_handler_set(PIOC,ID_PIOC,pin9,PIO_IT_EDGE,echoUs);
	pio_enable_interrupt(PIOC,pin9);



	NVIC_EnableIRQ(PIOC_IRQn);
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

/*ultraljud sensor echo pinnet trigger interrupts*/
void echoUs(){
	if (pio_get(PIOC, PIO_TYPE_PIO_INPUT, pin9)) {
		tc_start(TC0,2);
		//i=1;
	} else {
		echoTimeStop=tc_read_cv(TC0,2)/42;
		//printf("time:\n %i",echoTimeStop);
		//i=0;
		tc_stop(TC0, 2);
	}
	 
}

void saveValues(uint32_t i, uint32_t valuesArray[]) {
	values[i] = valuesArray;
	for(int i = 0; i < 30; i++) {
		printf("%d\n",valuesArray[i]);
		
	}
	
}

void ultraSound() {
	uint8_t dis;
	uint32_t valuesArray[30] = {};
	for(int i = 0; i < 30; i++) {
		usTrig();
		dis=distansUs();
		valuesArray[i] = dis;
		printf("avstånd: %li \n",distansUs());
	}
	saveValues(counter, valuesArray);
	if (check == 0) {
		rotate(1);
		delay_ms(1);
		counter++;
		if (counter==30) {
			rotate(-30);
			counter=0;
			check=1;
		}
	} else if (check == 1) {
		rotate(-1);
		delay_ms(1);
		counter++;
		if (counter==30) {
			rotate(30);
			counter = 0;
			check = 2;
		}
			
		
	} /*else if (dis ) {
			
	}*/
		
	//int dis= distansUs();
	
	//vTaskDelayUntil(xLastWakeTime,100);
}

uint8_t get_values(uint8_t index){
	static uint8_t check1=0;
	static uint8_t check2=0;
	static uint8_t value=0;
	static uint8_t i;
	static uint8_t j;
	uint32_t *valuesArray = values[index];
	uint32_t countArray[30] = {0};
	for (int i = 0; i < 30; i++) {
		countArray[valuesArray[i]]++;
	}

	int mostTimes= -1;
	for (int i = 0; i < 10; i ++) {
		if(countArray[i] > mostTimes) {
			mostTimes = countArray[i];
		}
	}

	/*for ( i=0; i< sizeof(valuesArray);i++) {
		


		for ( j=0; j<sizeof(values[index]); j++) {
			
			if (values[index][i] == values[index][j]) {
				check1++;
			}
		}
		
		if (check1>check2) {
			check2=check1;
			value==values[index][i];
		}
	}*/
	return mostTimes;
	
}

long distansUs(){
	long dis = (long)(echoTime()/58);
	if(dis < 100 && dis > 0) {
		return dis;
	}
	return 0;
}

//metoden returnerar längden av positiva flanken från echo-pinnet
long echoTime(){
	long data=echoTimeStop;
	return data;
}