/*
The code in this file was used to test FreeRTOS.
Change the code for your purpose.
Created: 2018-05-18 11:47:21
*  Author: Yohan
*/

#include <asf.h>
#include <stdio.h>

#include "../initializations/pins_init.h"
#include "../navigation.h"
#include "../ultraSoundSensor.h"
#include "../motorController.h"

//#define xTimeT1 50

/*
* Function: task1
* -------------------
* Performs an action every xTimeT1 milliseconds

*/




void Navigate() {
	uint8_t bestAngle;
	counter=0;
	check=0;
	while(counter <60){
		uint8_t dis;
		uint32_t valuesArray[30] = {};
		for(int i = 0; i < 30; i++) {
			usTrig();
			dis=distansUs();
			//printf("dis: %i \n", dis);
			valuesArray[i] = dis;
		}
		
		saveValues(counter, valuesArray);
		dis=get_values(counter);
		printf("values: %i \n",dis);
		
		
		
		if (!check) {
			rotate(1);			// ändra här om fel
			counter++;
			if (counter==29) {
				rotate(-30);
				//counter=0;
				check=1;
			}
			} else if (check==1) {
			rotate(-1);
			counter++;
			if (counter==59)
			{
				rotate(30);
				check=0;		//lägg den till 2 sen om det inte går
			}
		}
		
	}
	bestAngle=INT_MAX;
	uint8_t i;
	uint8_t index;
	// riktar sig där objektet befinner sig
	for ( i=0;i<60;i++)
	{
		if (bestAngle>get_values(i) && get_values(i) != 0)
		{
			bestAngle=get_values(i);
			index=i;
		}
	}
	if (index >= 0 && index < 30)
	{
		rotate(index);
	}
	else
	{
		rotate(index - 29);
	}
	driveCm(bestAngle-18,5);
	check=3;
	
	
}


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
		//printf("saveValues: %d\n",valuesArray[i]);
		
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
	uint8_t get_values(uint8_t _index){
		// 	static uint8_t check1=0;
		// 	static uint8_t check2=0;
		// 	static uint8_t value=0;
		uint32_t *valuesArray = values[_index];
		uint32_t countArray[30] = {0};
		
		int i, max, index;
		for(i = 0; i < 30; i++)
		{
			++countArray[valuesArray[i]];
			//printf("%i \n", countArray[valuesArray[i]]);
		}
		//printf("hej");
		
		// Find the letter that was used the most
		max = countArray[0];
		index = 0;
		for(i = 0; i < 30; i++)
		{
			if( countArray[valuesArray[i]] > max)
			{
				max = countArray[valuesArray[i]];
				index = i;
			}
		}

		//printf("Most common: %i \n", valuesArray[index]);
		
		/*for (int i = 0; i < 30; i++) {
		countArray[valuesArray[i]]++;
		printf("%i \n", countArray[valuesArray[i]]);
		}

		int mostTimes= -1;
		for (int i = 0; i < 10; i ++) {
		if(countArray[i] > mostTimes) {
		mostTimes = countArray[i];
		//printf("%i \n", countArray[i]);
		}
		}
		
		//printf("%i \n", mostTimes);*/

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
		return valuesArray[index];
		
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
