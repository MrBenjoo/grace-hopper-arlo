/*
 * task_i2c.c
 *
 * Created: 2018-05-09 11:45:35
 *  Author: gustav
 */ 
#include <asf.h>
#include "taskPOS.h"
#include "../I2C/I2CFunctions.h"
#include <math.h>

#define xTimeT1 500


#define kub 1
#define vinglas 2

int target = kub; //this variable determines which item is the target

int pickupX; //X-coordinates for the pick up
int pickupY; //Y-coordinates for the pick up 
int posX; //X-coordinates for ARLO-robot
int posY; //Y-coordinates for ARLO-robot
int disposalX; //X-coordinates for the disposal area
int disposalY; //Y-coordinates for the disposal area

/*
* Function: task1
* -------------------
* Performs an action every xTimeT1 milliseconds
*/
void taskPOS(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = xTimeT1/portTICK_RATE_MS; /* set ticks (xTimeT1) in milliseconds */
	xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
	
	while (1) /* the task must be looping infinitely */
	{
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* constant period, independent of execution time */
		
		if (read_package(TWI_SLAVE_ADR_POS)==DATA_READ) //retrieves data from the positioning-squad
		{
			disposalX=2*rec_data_pos[0];
			disposalY=2*rec_data_pos[1];
			
			posX=2*rec_data_pos[8];
			posY=2*rec_data_pos[9];
			
			printf("xpos %i",rec_data_pos[8]);
			
			
			if(target==kub){
				pickupX=2*rec_data_pos[2];
				pickupY=2*rec_data_pos[3];
			}
			else if(target==vinglas){
				pickupX=2*rec_data_pos[6];
				pickupY=2*rec_data_pos[7];
			}
			
			}else{
			//possibly add some error handling here;
			printf("FAIL");
		}
		
	}
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
void setTarget(int item){ //sets which item to target
	target=item;
}
int getDistanceToObject(){
	return sqrt(pow(abs(getPositionX()-getPickupX()),2) +pow(abs(getPositionY()-getPickupY()),2));
}
int getDistanceToDropOff(){
	return sqrt(pow(abs(getPositionX()-getDisposalX()),2) +pow(abs(getPositionY()-getDisposalY()),2));
}





