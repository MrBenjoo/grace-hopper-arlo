#include "initializations/main_init.h"
#include "initializations/pins_init.h"
#include "Reglering/Reglering.h"
#include "encoderISR.h"
#include "motorController.h"
#include "I2C/I2CFunctions.h"
#include "taskPOS.h"
#include <math.h>
#include <asf.h>



/*
This version Experiment 1.1 of our FreeRTOS program is meant to test the encoders, if we can count them and save the counter value
with appropriate values in two separate variables, one for each wheel. Clear?[]
And does it count positive for positive direction and negative for negative direction? Clear?[]

Next version (1.2) will test if we can add in P-regulation to make the wheels go at the same speed. Clear?[]

Next version (1.3) will test if we can add in the distance the robot has traveled. Clear?[]

Next version (1.4) will test if we can implement PWM to control the signal to the motorcontrollers. Clear?[]

*/
int main (void)
{

	misc_init(); //initiate
		
}