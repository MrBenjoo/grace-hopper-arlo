#include "controlCenter.h"

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
	
	
	
	int current_case = 0;
	int oldPositionX;		// Stores old position in X (State 0)
	int oldPositionY;		// Stores old position in Y (State 0)
	int actualPositionX;		// Stores new position in X (State 1)
	int actualPositionY;		// Stores new position in Y (State 1)
	int objectPositionX;		// Object position X
	int objectPositionY;		// Object position Y
	int dropOffPositionX;		// Drop off X
	int dropOffPositionY;		// Drop off Y
	int distanceToDropOff;		// (Kommer eventuellt användas för att beräkna dropoff-positionen)
	int startAngle;					// Angle to object
	int correction;				// angle for correction
	int fromStartToObject;
	int corrected = 0;
	int valueFromArmTest;
	
			
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* constant period, independent of execution time */
		
		switch(current_case){
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
////////////////////////   CASE: X ORIENTATION   /////////////////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
			case(orientation):
			printf("Test_print: Case X entered");
				
			oldPositionX = getPositionX();
			oldPositionY = getPositionY();
			
			driveCm(10,150);		// Drive short distance 10cm with speedPulse 150
			
			actualPositionX = getPositionX();
			actualPositionY = getPositionY();
			
			printf("actualPositionX %i\n",actualPositionX);
			printf("actualPositionY %i\n",actualPositionY);
			
			startAngle = getAngle(oldPositionX,oldPositionY,actualPositionX,actualPositionY);		// Gets angle we are looking at 
			
			printf("startAngle %i\n",startAngle);
			
			current_case = destination_pickup_reference;							
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
////////////////////////   CASE: 0 INITIALIZATION   //////////////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
			case(initialization):
			printf("Test_print: Case 0 entered\n");
			
			
			setExtension(kub); //skall vara getExtension()
			
			dropOffPositionX = getDisposalX();
			dropOffPositiony = getDisposalY();
			objectPositionX = getPickupX();
			objectPositionY = getPickupY();
											
			
			//valueFromArmTest = send_package();  //	Send package to arm, if 1 is returned communication is successfull.			
			
			
			if(objectPositionX != NULL || objectPositionY != NULL || dropOffPositionX  != NULL || dropOffPositionY != NULL)  
			{
				printf("SUCCESS: received coordinates!\n");
				current_case = orientation;
			} else {
				printf("ERROR: No coordinates received from MEGA!\n");
			}		
			break;
	
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
///////////////   CASE: 1 DESTINATION PICKUP REFERENCE   /////////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
			case(destination_pickup_reference):		
			printf("Test_print: Case 1 entered\n");

			// CAR Section - Will be used in case 1, 4 and 5
			actualPositionX = getPositionX();		// Stores new position in X (State 1)
			actualPositionY = getPositionY();		// Stores new position in Y (State 1)
			// WantedPosition();		
			correction = angleCorrection(actualPositionX,actualPositionY,dropOffPositionX,dropOffPositionY,startAngle);
			rotate(correction);			
			// DRIVE			
			

			//printf("Test_print\n", angle);
			
			//VILLKOR MODIFIERA/ÄNDRA/TA BORT			
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

			current_case = 2;
			break;

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
///////////////   CASE: 2 DESTINATION PICKUP SENSOR ZONE   ///////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤		
			case(destination_pickup_sensorzone):			
			printf("Test_print: Case 2 entered");
			
			//  FINJUSTERING  KOD  
						
			current_case = 3;
			break;

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
///////////////   CASE: 3 DESTINATION PICKUP ZONE    /////////////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤	
			case(destination_pickup_zone):
			printf("Test_print: Case 3 entered\n");
			
			// Sends message to extension to start Pick up.
			not_sent = true;
			if(send_package(borjaPlocka, TWI_SLAVE_ADR_PAB) == DATA_SENT && not_sent){
				printf("case 3: send_package SUCCESFUL... \n");	
				not_sent = false;			
			}

			// Reads package to see that the object has been picked up.
			if(read_package(TWI_SLAVE_ADR_PAB) == DATA_READ && !not_sent){
				if(rec_data_pab[0] == 0x14)								// Lift successful
				{
					current_case = 4;
				}
				else
				{
					// VAD VILL VI GÖRA HÄR OM OBJEKTET INTE HAR KLARAT LYFTET?
				}
			}
			break;
			

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
///////////////					CASE: 4 PICKUP			  ////////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤	
			case(pickup):
			printf("Test_print: Case 4 entered\n");
			
			// CAR Section - Will be used in case 1, 4 and 5
			actualPositionY = getPositionX();		// Stores new position
			actualPositionY = getPositionY();		// Stores new position
			// WantedPosition();
			correction = angleCorrection(New_OurPositionX, New_OurPositionY, dropOffPositionX, dropOffPositionY, angle);
			rotate(correction);
			// DRIVE
						
			break;

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
///////////////   CASE: 5 DESTINATION DROP OFF REFERENCE   ///////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ 		
			case(destination_dropoff_reference):
			printf("Test_print: Case 5 entered\n");
			// CAR Section - Will be used in case 1, 4 and 5
			New_OurPositionX = getPositionX();		// Stores new position
			New_OurPositionY = getPositionY();		// Stores new position
			// WantedPosition();
			correction = angleCorrection(New_OurPositionX, New_OurPositionY, dropOffPositionX, dropOffPositionY, angle);
			rotate(correction);
			// DRIVE			

			
			//while(getDistanceToDropOff() > 5){ // så nära som möjligt	
			//drive()
			//}	
			current_case = 6;
			break;

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
///////////////   CASE: 6 DESTINATION DROP OFF SENSOR ZONE   /////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤	
			case(destination_dropoff_sensorzone):
			printf("Test_print: Case 6 entered\n");
			
			// SCANNINGROUTINE "B"
			
			break;
			
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
///////////////   CASE: 7 DESTINATION DROP OFF ZONE   /////////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
			case(destination_dropoff_zone):
			printf("Test_print: Case 7 entered\n");
			
			if(send_package(lamnaAvObject, TWI_SLAVE_ADR_PAB) == DATA_SENT)
			{
				//done = 1;
			}
			break;

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
///////////////				CASE: 8 DROP OFF			  ////////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
			case(dropoff):
			printf("Test_print: Case 8 entered\n");
			
			// Go crazy
			
			break;	
			
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
///////////////				CASE: 9 VICTORY DANCE			  ////////////////
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
			case(victorydance):
			printf("Test_print: Case 8 entered\n");
			
			// Go crazy
			
			break;	
			
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
								
			
		}
	}
}