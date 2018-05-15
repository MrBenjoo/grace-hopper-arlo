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

	misc_init(); //pin 2 out, pin5&7 
	//interrupt_init();	//	pin 7 and 8 as interrupt pins	
	//encoder_init(); //also initialises pin 5 (left encoder) & 7 (right encoder) as interrupt pins
	//rtos_init(); //Starts RTOS scheduler
	//delay_us(3000000);
	//controlCenter(50);
	//delay_init();
	//init_twi();
	
	
	
	int current_case = 0;
	int next_case = 0;
	int Old_OurPositionX = 0;		// Stores old position in X (State 0)
	int Old_OurPositionY = 0;		// Stores old position in Y (State 0)
	int New_OurPositionX = 0;		// Stores new position in X (State 1)
	int New_OurPositionY = 0;		// Stores new position in Y (State 1)		
	int objectPositionX = 0;		// Object position X
	int objectPositionY = 0;		// Object position Y
	int dropOffPositionX = 0;		// Drop off X
	int dropOffPositionY = 0;		// Drop off Y
	int distanceToObjekt = 0;		// Distance to object
	int distanceToDropOff = 0;		// (Kommer eventuellt användas för att beräkna dropoff-positionen)
	int ourDirection = 0;
	int angle = 0;					// Angle to object
	
	while(1){
		switch(current_case){
			case(0):								//Get ARLO position, object position and dropoff position
			Old_OurPositionX = getPositionX();
			Old_OurPositionY = getPositionY();			
			objectPositionX = getPickupX();
			objectPositionY = getPickupY();
			dropOffPositionX = getDisposalX();
			dropOffPositionY = getDisposalY();
			distanceToDropOff = getDistanceToDropOff();
			distanceToObjekt = getDistanceToObject();
		
			
			current_case = 1;
			//current_case = 1; när allt är klart
			// current_case = next_case;
			break;
			
			case(1):		// Calculates the angle to object, turns to object, drives towards object in loop until distanceToObject <= 42.5
			angle = getAngle(Old_OurPositionX, Old_OurPositionY, objectPositionX, objectPositionY);		// Gets angle. The function calculates the angle to the object
			rotate(angle);
			
			// while(distanceToObject > 42.5){
			// DRIVE();							// Pseudo				
			//}
			
			// DRIVE() = 0;			// SET DRIVE TO 0
			//current_case = 2;
			break;
			
			
			case(2):			// Detect object. Go to sensor mode instead of positiondata. LOOP: Look for object until found

			//if(sensorvalue withing range of ca 15-30){
				rotate(3);
			//}
			
			//else(){
				// CORRECTIONCODE		// "Finjustering"
				//}
			
			
			//current_case = 3
			break;			
			
			
			case(3):// meddela påbyggnad "object found" och vänta på ack
			//if (ack mottaget)
			// current_case = 4;
			break;	
			
			
			case(4)://fråga efter lyckat upplock
			//if(om objekt upplockat)
			//current_case = 5;
			break;
			
			
			case(5)://kör mot avlämningsplats
			//if(framme vid avlämningsplats)
			//current_case = 6;
			break;
			
			
			case(6)://meddela påbyggnad; lämna objekt
			
			break;		
		
		}
	}
}