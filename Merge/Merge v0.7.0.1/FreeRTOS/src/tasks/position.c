/*
 * position.c
 *
 * Created: 2018-05-20 13:47:41
 *  Author: Sebastian
 */ 

#include "position.h"
#include <asf.h>
#include "../I2C/I2CFunctions.h"
#include "../initializations/pins_init.h"
#include <math.h>
#include <asf.h>
#include <stdio.h>
//#include "../dimensions.h"
int extensionID = 0; //this variable determines which item is the target

	int pickupX = 0; //X-coordinates for the pick up
	int pickupY = 0; //Y-coordinates for the pick up
	int posX = 0; //X-coordinates for ARLO-robot
	int posY = 0; //Y-coordinates for ARLO-robot
	int disposalX = 0; //X-coordinates for the disposal area
	int disposalY = 0; //Y-coordinates for the disposal area
	int ex = 0;

void position(void *pvParamters)
{
	printf("inside position task");
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = posSampleTime/portTICK_RATE_MS; /* set ticks (xTimeT1) in milliseconds */
	xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
	
	while (1) /* the task must be looping infinitely */
	{
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* constant period, independent of execution time */
		if (read_package(TWI_SLAVE_ADR_POS)==DATA_READ) //retrieves data from the positioning-squad
		{
			disposalX=2*rec_data_pos[0]; //Factor 2 because data sent is divided to save space 
			disposalY=2*rec_data_pos[1];
			
			posX=2*rec_data_pos[8];
			posY=2*rec_data_pos[9];
			
			printf("posX %i",rec_data_pos[8]);
			printf("posY %i",rec_data_pos[9]);
			
			//target byts ut mot getExtensionID om vi har tid, annars hårdkodar vi det
			if(extensionID==1){
				pickupX=2*rec_data_pos[2];
				pickupY=2*rec_data_pos[3];
			}
			else if(extensionID==2){
				pickupX=2*rec_data_pos[6];
				pickupY=2*rec_data_pos[7];
			}else{
				//possibly add some error handling here;
				printf("ERROR: failed to fetch position data from MEGA\n");
			}
			
		}
	
	}
}
	void setExtension(int extension){ //sets which item to target
		extensionID=extension;
	}
	int getPickupX(){ //returns the X-coordinates for the pickup
		return pickupX;
	}
	int getPickupY(){ //returns the Y-coordinates for the pickup
		return pickupY;
	}
	int getPositionX(){ //returns current X-coordinate
		return posX;
	}
	int getPositionY(){ //returns current Y-coordinate
		return posY;
	}
	int getDisposalX(){ //returns the X-coordinates for the disposal-area
		return disposalX;
	}
	int getDisposalY(){ //returns the Y-coordinates for the disposal-area
		return disposalY;
	}