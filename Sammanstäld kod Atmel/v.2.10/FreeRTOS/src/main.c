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

	misc_init(); //initiate all the nesisary stuff
	
	
	int current_case = 0;
	int Old_OurPositionX;		// Stores old position in X (State 0)
	int Old_OurPositionY;		// Stores old position in Y (State 0)
	int New_OurPositionX;		// Stores new position in X (State 1)
	int New_OurPositionY;		// Stores new position in Y (State 1)
	int objectPositionX;		// Object position X
	int objectPositionY;		// Object position Y
	int dropOffPositionX;		// Drop off X
	int dropOffPositionY;		// Drop off Y
	int distanceToDropOff;		// (Kommer eventuellt användas för att beräkna dropoff-positionen)
	int ourDirection;
	int angle;					// Angle to object
	int correction;				// angle for correction
	int done = 0;				//checks if the task is done
	int fromStartToObject;
	int corrected = 0;
		
	while(done == 0){
		switch(current_case){
			case(0):								//Get ARLO position, object position and dropoff position
			Old_OurPositionX = getPositionX();
			Old_OurPositionY = getPositionY();
			objectPositionX = getPickupX();
			objectPositionY = getPickupY();
			dropOffPositionX = getDisposalX();
			dropOffPositionY = getDisposalY();
			distanceToDropOff = getDistanceToDropOff();
			fromStartToObject = getDistanceToObject();
			
			
			if(!(objectPositionX || objectPositionY || dropOffPositionX || dropOffPositionY || Old_OurPositionX || Old_OurPositionY) == NULL)
			{
				//printf("case 0: received coordinates");
				current_case = 1;
			} else {
				//printf("case 0: no coordinates received ");
			}
			
			break;
			
			case(1):		// Calculates the angle to object, turns to object, drives towards object in loop until distanceToObject <= 42.5
			printf("case 1: BEGIN... ");
		//	driveCm(5);
			New_OurPositionX = getPositionX();
			New_OurPositionY = getPositionY();
			angle = getAngle(Old_OurPositionX,Old_OurPositionY,New_OurPositionX,New_OurPositionY);
			correction = angleCorrection(New_OurPositionX,New_OurPositionY,objectPositionX,objectPositionY,angle);
			//rotate(correction);
	
			//drive(50, 50, 1, 1);	/* används endast för testning */
			
			/*while(getDistanceToObject() > 42.5){
				// DRIVE();							// Pseudo
				if(getDistanceToObject() <= fromStartToObject/2 && corrected  == 0)
				{	
					Old_OurPositionX = getPositionX();
					Old_OurPositionY = getPositionY();
					driveCm(5);
					New_OurPositionX = getPositionX();
					New_OurPositionY = getPositionY();
					angle = getAngle(Old_OurPositionX,Old_OurPositionY,New_OurPositionX,New_OurPositionY);
					correction = angleCorrection(New_OurPositionX,New_OurPositionY,dropOffPositionX,dropOffPositionY,angle);
					rotate(correction);			
					corrected = 1;
					
				}
			}*/
			delay_s(3);			    /* används endast för testning */
			//drive(0, 0, 1, 1);		/* används endast för testning */
			// DRIVE() = 0;			// SET DRIVE TO 0
			corrected = 0;
			current_case = 2;
			break;
			
			
			case(2):			// Detect object. Go to sensor mode instead of positiondata. LOOP: Look for object until found
			printf("case 2: BEGIN... ");
			//if(!sensorvalue withing range of ca 15-30){
			//rotate(90);
			//}
			
			//else(){
			// CORRECTIONCODE		// "Finjustering"
			//}
			
			
			current_case = 3;
			break;
			
			
			case(3):// tell the "arm" that we are at the object and wait for a ack
			if(send_package(borjaPlocka, TWI_SLAVE_ADR_PAB) == DATA_SENT){
				printf("case 3: send_package SUCCESFUL... ");
				current_case = 4;
			}
			break;
			
			
			case(4)://asks for a successfully
			if(read_package(TWI_SLAVE_ADR_PAB) == DATA_READ){
				if(rec_data_pab[0] == 0x14) // lyckat lyft
				{
					current_case = 5;
				}
				else{
					// LYFT FAILED
				}
			}
			break;
			
			
			case(5)://kör mot avlämningsplats
			Old_OurPositionX = getPositionX();
			Old_OurPositionY = getPositionY();	
			//driveCm(5);
			delay_s(3); /* används endast för testning */
			New_OurPositionX = getPositionX();
			New_OurPositionY = getPositionY();
		    angle = getAngle(Old_OurPositionX,Old_OurPositionY,New_OurPositionX,New_OurPositionY);
			correction = angleCorrection(New_OurPositionX,New_OurPositionY,dropOffPositionX,dropOffPositionY,angle);
			//rotate(correction);
			
			//while(getDistanceToDropOff() > 5){ // så nära som möjligt	
			//drive()
			//}	
			current_case = 6;
			break;
			
			
			case(6)://meddela påbyggnad; lämna objekt
			if(send_package(lamnaAvObject, TWI_SLAVE_ADR_PAB) == DATA_SENT)
			{
				done = 1;
			}
			break;
			
		}
	}
}