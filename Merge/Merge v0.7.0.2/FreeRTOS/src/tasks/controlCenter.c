#include "controlCenter.h"

#include <asf.h>
#include "../I2C/I2CFunctions.h"
#include "../initializations/pins_init.h"
#include "../navigation.h"
#include "../debuggingLEDS.h"
#include "position.h"
#include "regulator.h"
#include <math.h>
#include <stdio.h>

#define orientation 99
#define initialization 0
#define destination_pickup_reference 1 
#define destination_pickup_sensorzone 2
#define destination_pickup_zone 3
#define pickup 4
#define destination_dropoff_reference 5
#define destination_dropoff_sensorzone 6
#define destination_dropoff_zone 7
#define dropoff 8
#define victorydance 9

	
	
void controlCenter(void *pvParamters)
{	
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = ccSampleTime/portTICK_RATE_MS; /* set ticks (xTimeT1) in milliseconds */
	xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
	
	
	
	int current_case = initialization;   //witch case we start on. 
	int oldPositionX;		// Stores old position in X (State 0)
	int oldPositionY;		// Stores old position in Y (State 0)
	int actualPositionX;		// Stores new position in X (State 1)
	int actualPositionY;		// Stores new position in Y (State 1)
	int objectPositionX = 0;		// Object position X
	int objectPositionY = 0;		// Object position Y
	int dropOffPositionX = 0;		// Drop off X
	int dropOffPositionY = 0;		// Drop off Y
	int dropOffReferenceX;
	int dropOffReferenceY;
	int objectReferenceX;
	int objectReferenceY;
	int sensorZoneDepth = 10;
	int correction;				// angle for correction
	int angle;
	int previous_case;
	Bool not_sent;
	
			
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* constant period, independent of execution time */
		
		switch(current_case){
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
////////////////////////   CASE: X ORIENTATION   /////////////////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
			case(orientation):
			printf("Test_print: Case X entered");
			binaryLEDS(10);
			vTaskDelay(5000);
				
			oldPositionX = getPositionX();
			oldPositionY = getPositionY();
			
			printf("before drive");
			
			driveCm(10,100);		// Drive short distance 10cm with speedPulse 150
			
			printf("after drive");
			
			actualPositionX = getPositionX();
			actualPositionY = getPositionY();
			
			printf("actualPositionX AF 10cm %i\n",actualPositionX);
			printf("actualPositionY AF 10cm %i\n",actualPositionY);
			
			angle = getAngle(oldPositionX,oldPositionY,actualPositionX,actualPositionY);		// Gets angle we are looking at 
			
			printf("startAngle %i\n",angle);
			printf(current_case);
			if(previous_case==initialization)
				current_case = destination_pickup_reference;
			if(previous_case==pickup)
				current_case = destination_dropoff_reference;
			break;	 							
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
////////////////////////   CASE: 0 INITIALIZATION   //////////////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
			case(initialization):
			printf("Test_print: Case 0 entered\n");
			binaryLEDS(0);
			
			setExtension(1); //skall vara getExtension()
			
			dropOffPositionX = getDisposalX();
			dropOffPositionY = getDisposalY();
			objectPositionX = getPickupX();
			objectPositionY = getPickupY();
			dropOffReferenceX = dropOffPositionX - 15;
			dropOffReferenceY = dropOffPositionY - 30 - 45/2; 
			objectReferenceX = objectPositionX;								
			objectReferenceY = objectPositionY - 100;
			printf("CC - dropOffPositionX %i\n", dropOffPositionX);	
			printf("CC - dropOffPositionY %i\n", dropOffPositionY);	
			//valueFromArmTest = send_package();  //	Send package to arm, if 1 is returned communication is successfull.			
			
			if(objectPositionX > 0 && objectPositionY > 0 && dropOffPositionX  > 0 && dropOffPositionY > 0)  
			{
				printf("SUCCESS: received coordinates!\n");
				previous_case = current_case;
				current_case = orientation;
				printf("objectPositionX AF %i\n",objectPositionX);
				printf("objectPositionY AF %i\n",objectPositionY);
				printf("dropOffPositionX AF %i\n",dropOffPositionX);
				printf("dropOffPositionY AF %i\n",dropOffPositionY);
			} else {
				printf("ERROR: No coordinates received from MEGA!\n");
			}		
			break;
	
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
///////////////   CASE: 1 DESTINATION PICKUP REFERENCE   /////////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
			case(destination_pickup_reference):		
			printf("Test_print: Case 1 entered\n");
			binaryLEDS(1);
			vTaskDelay(5000);		
			correction = angleCorrection(actualPositionX,actualPositionY,actualPositionX+20,actualPositionY,angle);
			printf("%i", correction);
			rotate(correction);	
			printf("END");
			// DRIVE to reference point from the angle 0*.	
			/*while(getPositionX() < objectReferenceX){
				setDesiredSpeed(100,100);
			}
			setDesiredSpeed(0,0);
			rotate(90,100);
			while(getPositionY() < objectReferenceY){
				setDesiredSpeed(100,100);
			}
			setDesiredSpeed(0,0);
			
			
			previous_case = current_case;
			current_case = destination_pickup_sensorzone;
			*/
			while(1){
			}
			
			break;
			
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
///////////////   CASE: 2 DESTINATION PICKUP SENSOR ZONE   ///////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中		
			case(destination_pickup_sensorzone):			
			printf("Test_print: Case 2 entered");
			binaryLEDS(2);
			
			float cmToSensorZone = (float)(objectPositionY-getPositionY()-20-sensorZoneDepth-22.5); 
			driveCm(cmToSensorZone,150); //The robot is supposed to be at pickUpSensorPosition
			// Vid behov ytterligare kontroll av position
			previous_case = current_case;
			current_case = destination_pickup_zone;
			break;

//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
///////////////   CASE: 3 DESTINATION PICKUP ZONE    /////////////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中	
			case(destination_pickup_zone):
			printf("Test_print: Case 3 entered\n");
			binaryLEDS(3);
			//STARTA SENSORER
			//if( sensorValue > 20)
			//driveCm(20 - sensorValue);
			//if(sensorValue <= 20)
			// driveCm(20 - sensorValue);
			// The Robot is supposed to be at pickUpPosition			
			//
			//SKANNINGS FAS!
			//
			
			current_case = pickup;
			break;
			
			

//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
///////////////					CASE: 4 PICKUP			  ////////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中	
			case(pickup):
			
			printf("Test_print: Case 4 entered\n");
			binaryLEDS(4);
			// Sends message to extension to start Pick up.
			not_sent = true;
			if(send_package(BORJA_PLOCKA, TWI_SLAVE_ADR_PAB) == DATA_SENT && not_sent){
				printf("case 3: send_package SUCCESFUL... \n");
				not_sent = false;
			}

			// Reads package to see that the object has been picked up.
			if(read_package(TWI_SLAVE_ADR_PAB) == DATA_READ && !not_sent){
				if(rec_data_pab[0] == 0x14)								// Lift successful
				{
					previous_case = current_case;
					current_case = orientation;
				}
				else
				{
					driveCm(10,150);
					current_case = destination_pickup_zone;
				}
			}
			break;

//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
///////////////   CASE: 5 DESTINATION DROP OFF REFERENCE   ///////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中 		
			case(destination_dropoff_reference):
			printf("Test_print: Case 5 entered\n");
			binaryLEDS(5);
			// CAR Section - Will be used in case 1, 4 and 5
			correction = angleCorrection(actualPositionX, actualPositionY, actualPositionX+20, actualPositionY, angle);
			rotate(correction);
			
			while(getPositionX() < dropOffReferenceX){
				setDesiredSpeed(150,150);
			}
			setDesiredSpeed(0,0);
			rotate(90);
			while(getPositionY() < dropOffReferenceY){
				setDesiredSpeed(150,150);
			}	
			setDesiredSpeed(0,0);
			previous_case = current_case;
			current_case = destination_dropoff_sensorzone;
			break;

//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
///////////////   CASE: 6 DESTINATION DROP OFF SENSOR ZONE   /////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中	
			case(destination_dropoff_sensorzone):
			printf("Test_print: Case 6 entered\n");
			binaryLEDS(6);
			driveCm(15, 150); // k顤 fr幩 referenspunk till skannings avst幩d
			previous_case = current_case;
			current_case = destination_dropoff_zone;
			break;
			
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
///////////////   CASE: 7 DESTINATION DROP OFF ZONE   /////////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
			case(destination_dropoff_zone):
			printf("Test_print: Case 7 entered\n");
			binaryLEDS(7);
			
			// SCANNINGROUTINE "B"
			// om avst幩d = 5: 
			//current_case = dropoff;
			break;

//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
///////////////				CASE: 8 DROP OFF			  ////////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
			case(dropoff):
			printf("Test_print: Case 8 entered\n");
			binaryLEDS(8);
			if(send_package(LAMNA_OBJEKT, TWI_SLAVE_ADR_PAB) == DATA_SENT)
			{
				current_case = victorydance;
			}			
			
			
			break;	
			
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
///////////////				CASE: 9 VICTORY DANCE			  ////////////////
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
			case(victorydance):
			printf("Test_print: Case 8 entered\n");
			binaryLEDS(9);
			
			driveCm(-30,450);
			rotate(180);
			
			break;	
			
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
			
			
		}
	}
}