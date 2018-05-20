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
	int ourDirection;
	int angle;					// Angle to object
	int correction;				// angle for correction
	int fromStartToObject;
	int corrected = 0;
	int valueFromArmTest;
	
			
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* constant period, independent of execution time */
		
		switch(current_case){

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
			
			/* Case X - Orientation. 
			This case answers the question: How am I oriented? 
			ARLO will drive a short distance, get new position data (compare) and calculate new angle. 
			This case will be entered twice (between cases 0-1 and 4-5).*/
			case(orientation):
			printf("Test_print: Case X entered");
				
			oldPositionX = getPositionX();
			oldPositionY = getPositionY();
			
			//driveCm(int cm);		// Drive short distance
			
			actualPositionX = getPositionX();
			actualPositionY =getPositionY();
			
			//angle = getAngle(Old_OurPositionX,Old_OurPositionY,New_OurPositionX,New_OurPositionY);		// Gets angle we are looking at 
										
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
			
			/* Case 0 - Initialization. 
			This case gets position, object position and drop-off position. It also test the communication with the ARM extension */
			case(initialization):
			printf("Test_print: Case 0 entered\n");
			
			
			setExtension(kub); //skall vara getExtension()
			
			dropOffPositionX = getDisposalX();
			dropOffPositiony = getDisposalY();
			objectPositionX = getPickupX();
			objectPositionY = getPickupY();
											
			
			//valueFromArmTest = send_package();  //	Send package to arm, if 1 is returned communication is successfull.			
			
			// Villkor(SE ÖVER): Return values are != NULL AND test communication with extension is working
			if(!(objectPositionX || objectPositionY || dropOffPositionX || dropOffPositionY || Old_OurPositionX || Old_OurPositionY) == NULL)  // && (valueFromArmTest == 1) //care for NOT
			{
				//printf("case 0: received coordinates\n");
				current_case = 1;
			} else {
				//printf("case 0: no coordinates received\n");
			}		
			break;
	
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/		
			
			/* Case 1 - DestinationPickupSensorZone. 
			This case answers the question: How does Arlo get to the PickupSensorZone? 
			Arlo will: get out position data, desired position data, calculate angle to desired position and drive. */
			case(destination_pickup_reference):		
			//printf("Test_print: Case 1 entered\n");

			// CAR Section - Will be used in case 1, 4 and 5
			actualPositionX = getPositionX();		// Stores new position in X (State 1)
			actualPositionY = getPositionY();		// Stores new position in Y (State 1)
			// WantedPosition();		
			correction = angleCorrection(actualPositionX,actualPositionY,dropOffPositionX,dropOffPositionY,angle);
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

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/			

			/* Case 2 - DestinationPickupZone. 
			This case answers the question: How does Arlo get to desired distance from object? 
											How does Arlo position itself to pick up object?
			Arlo will: Start scanningroutin "A",  a: rotate and scan b: drive  */			
			case(destination_pickup_sensorzone):			
			//printf("Test_print: Case 2 entered");
			
			//  FINJUSTERING  KOD  
						
			current_case = 3;
			break;

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/			

			/* Case 3 - PickUp. 
			This case answers the question:  
			Arlo will: Activate pick up. Wait for status answer from extension */			
			case(destination_pickup_zone):
			//printf("Test_print: Case 3 entered\n");
			
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
			

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/			

			/* Case 4 - DestinationDropOffReference. 
			This case answers the question: How does Arlo get to DropOffReference ? 
			Arlo will: Get current position, get wanted position(DropOffReference), Calculate angle to object, Rotate, Drive */			
			case(pickup):
			//printf("Test_print: Case 4 entered\n");
			
			// CAR Section - Will be used in case 1, 4 and 5
			New_OurPositionX = getPositionX();		// Stores new position
			New_OurPositionY = getPositionY();		// Stores new position
			// WantedPosition();
			correction = angleCorrection(New_OurPositionX, New_OurPositionY, dropOffPositionX, dropOffPositionY, angle);
			rotate(correction);
			// DRIVE
						
			break;

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/			

			/* Case 5 - DestinationDropOffSensorZone. 
			This case answers the question: How do i get to the PickupSensorZone? 
			We will: Get current position, get wanted position(DropOffReference), Calculate angle to object, Rotate, Drive */			
			case(destination_dropoff_reference):
			
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

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/			

			/* Case 6 - DestinationDropOffZone. 
			This case answers the question: How does Arlo find distance to the box?
											How does Arlo angle itself to the box?  
			Arlo will: Run Scanning routine "B" */			
			case(destination_dropoff_sensorzone):
			//printf("Test_print: Case 6 entered\n");
			
			// SCANNINGROUTINE "B"
			
			break;
			
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

			/* Case 7 - DropOff. 
			This case answers the question:  
			We will: */
			case(destination_dropoff_zone):
			//printf("Test_print: Case 7 entered\n");
			
			if(send_package(lamnaAvObject, TWI_SLAVE_ADR_PAB) == DATA_SENT)
			{
				//done = 1;
			}
			break;

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/			

			/* Case 8 - VictoryDance. 
			This case answers the question: 
			We will: Cheerfully buzz around and gloat over its success*/
			case(dropoff):
			//printf("Test_print: Case 8 entered\n");
			
			// Go crazy
			
			break;	
			
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
								
								/*------------------------------------------------------------------------------------------------------------------------------------------------------*/			

			/* Case 8 - VictoryDance. 
			This case answers the question: 
			We will: Cheerfully buzz around and gloat over its success*/
			case(victorydance):
			//printf("Test_print: Case 8 entered\n");
			
			// Go crazy
			
			break;	
			
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
								
			
		}
	}
}