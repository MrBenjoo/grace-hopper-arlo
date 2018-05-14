#include "initializations/main_init.h"
#include "initializations/pins_init.h"
#include "Reglering/Reglering.h"
#include "encoderISR.h"
#include "motorController.h"
#include <asf.h>
/*
This version Experiment 1.1 of our FreeRTOS program is ment to test the encoders, if we can count them and save the counter value 
with appropiate values in two separate variables, one for each wheel. Clear?[]
And does it count positive for positive direction and negative for negative direction? Clear?[]

Next version (1.2) will test if we can add in P-regulation to make the wheels go at the same speed. Clear?[]

Next version (1.3) will test if we can add in the distance the robot has travelled. Clear?[]

Next version (1.4) will test if we can implement PWM to control the signal to the motorcontrollers. Clear?[] 

*/
int main (void)
{

	misc_init(); //pin 2 out, pin5&7 in
	console_init();
	//interrupt_init();	//	pin 7 and 8 as interrupt pins	
	encoder_init(); //also initialises pin 5 (left encoder) & 7 (right encoder) as interrupt pins
	//rtos_init(); //Starts RTOS scheduler
	//delay_us(3000000);
	//controlCenter(50);
	//delay_init();
	
	//rotate(180);
	driveCm(3);
	
}