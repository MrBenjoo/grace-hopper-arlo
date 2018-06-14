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
# define scan 1;
# define orientate  2;

//#define xTimeT1 50

/*
* Function: task1
* -------------------
* Performs an action every xTimeT1 milliseconds

*/
//4 interrupt läsa av
//6 trig 
void echoUsM(){
	if (pio_get(PIOC, PIO_TYPE_PIO_INPUT, pin4i)) {
		tc_start(TC1,2);
		//i=1;
		} else {
		echoTimeStopM=tc_read_cv(TC1,2)/42;
		//printf("time:\n %i",echoTimeStop);
		//i=0;
		tc_stop(TC1, 2);
	}
	
}
// enable us sensorM 
void usTrigM(){
	ioport_enable_pin(pin6);
	ioport_set_pin_dir(pin6, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(pin6,LOW);
	delay_us(5);
	ioport_set_pin_level(pin6,HIGH);
	delay_us(10);
	ioport_set_pin_level(pin6,LOW);
	delay_ms(5);
}

// get distans for sensor M
long distansUsM(){
		long dis = (long)(echoTimeM()/58);
		if(dis < 100 && dis > 0) {
			return dis;
		}
		return 0;
}
// get echo time
	long echoTimeM(){
		long data=echoTimeStopM;
		return data;
	}


// scanning and orientation
void Navigate() {
	uint8_t bestAngle;
	counter=0;
	check=0;
	
	while(counter <60){
		uint8_t dis;
		uint32_t valuesArray[30] = {};
		for(int i = 0; i < 30; i++) { // start sampling  
			usTrig();
			dis=distansUs();
			//printf("dis: %i \n", dis);
			valuesArray[i] = dis;
		}
		
		saveValues(counter, valuesArray); // save samplearray
		dis=get_values(counter);
		printf("values: %i \n",dis);
		
		
		
		if (!check) {			// scan left side
			rotate(1);			// 
			counter++;
			if (counter==29) {
				rotate(-31);
				//counter=0;
				check=1;
			}
			} else if (check==1) { // scan right side
			rotate(-1);
			counter++;
			if (counter==59)
			{
				rotate(30);
				check=0;		
			}
		}
		
	}
	
	//find right angle
	bestAngle=INT_MAX;
	uint8_t i;
	uint8_t index;
	for ( i=0;i<60;i++)
	{
		if (bestAngle>get_values(i) && get_values(i) != 0) //compare angles
		{
			bestAngle=get_values(i);
			index=i;
		}
	}
	//rotate against right direction
	if (index >= 0 && index < 30)
	{
		rotate(index);
	}
	else
	{
		rotate(index - 29);
	}
	
	//move the robot to right distans
	driveCm(bestAngle-18,5);
	
	
}

// init function to enable tc timers and interrupts
void us_init() {
	//klocktimer sensor 1 
	sysclk_enable_peripheral_clock(ID_TC2);
	tc_init(TC0,2,0);
	tc_set_block_mode(TC0,0);
	//klocktimer sensor m
	sysclk_enable_peripheral_clock(ID_TC5);
	tc_init(TC1,2,0);
	tc_set_block_mode(TC1,0);

	/*  Initializes interrupt pin for the UltraSound sensor echo, trigger on level change, pin9*/
	pio_set_input(PIOC,pin9,NULL);
	pio_handler_set(PIOC,ID_PIOC,pin9,PIO_IT_EDGE,echoUs);
	pio_enable_interrupt(PIOC,pin9);

	//interrupts sensorM
		pio_set_input(PIOC,pin4i,NULL);
		pio_handler_set(PIOC,ID_PIOC,pin4i,PIO_IT_EDGE,echoUsM);
		pio_enable_interrupt(PIOC,pin4i);

	NVIC_EnableIRQ(PIOC_IRQn);
}
// enable sensor 1
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
// save samples 
void saveValues(uint32_t i, uint32_t valuesArray[]) {
	values[i] = valuesArray;
	for(int i = 0; i < 30; i++) {
		//printf("saveValues: %d\n",valuesArray[i]);
		
	}
	
}

// get distans for the wanted angle
	uint8_t get_values(uint8_t angle){
		// 	static uint8_t check1=0;
		// 	static uint8_t check2=0;
		// 	static uint8_t value=0;
		uint32_t *valuesArray = values[angle];
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

//get distans sensor1
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
