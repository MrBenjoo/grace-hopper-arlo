/*
* task_i2c.c
*
* Created: 2018-05-09 11:45:35
*  Author: gustav
*/
#include <asf.h>
#include "taskPOS.h"
#include "../I2C/I2CFunctions.h"
#include "taskHandler.h"

#define xTimeT1 250

#define kub		1
#define vinglas 2

int target = vinglas;	// this variable determines which item is the target

int pickupX;			// X-coordinates for the pick up
int pickupY;			// Y-coordinates for the pick up
int posX;				// X-coordinates for ARLO-robot
int posY;				// Y-coordinates for ARLO-robot
int disposalX;			// X-coordinates for the disposal area
int disposalY;			// Y-coordinates for the disposal area

void taskPOS(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = xTimeT1/portTICK_RATE_MS;
	xLastWakeTime = xTaskGetTickCount();
	
	printf("taskPOS\n");
	uint8_t cnt = 0;
	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
		
		if (read_package(TWI_SLAVE_ADR_POS)==DATA_READ)
		{
			disposalX=2*rec_data_pos[0];
			disposalY=2*rec_data_pos[1];
			
			posX=2*rec_data_pos[8];
			posY=2*rec_data_pos[9];
			
			/* print coordinates every eight times */
			if(cnt == 255)
			{
				cnt = 0;
			}
			
			if(cnt%8 == 0)
			{
				printf("xpos %i\n",rec_data_pos[8]);
				printf("ypos %i\n",rec_data_pos[9]);
			}
			cnt++;
			//printf("--reading from positionering--\n");
			//printf("xpos %i",rec_data_pos[8]);
			
			
			if(target==kub)
			{
				pickupX=2*rec_data_pos[2];
				pickupY=2*rec_data_pos[3];
			}
			else if(target==vinglas)
			{
				pickupX=2*rec_data_pos[6];
				pickupY=2*rec_data_pos[7];
			}
			xSemaphoreGive(semaphorePAB);
			
		}
		else
		{
			printf("Couldn't read position\n");
		}
		
	}
}

//returns the X-coordinates for the pickup
int getPickupX()
{
	return pickupX;
}

//returns the Y-coordinates for the pickup
int getPickupY()
{
	return pickupY;
}

//returns current X-coordinate
int getPositionX()
{
	return posX;
}

//returns current Y-coordinate
int getPositionY()
{
	return posY;
}

//returns the X-coordinates for the disposal-area
int getDisposalX()
{
	return disposalX;
}

//returns the Y-coordinates for the disposal-area
int getDisposalY()
{
	return disposalY;
}

//sets which item to target
void setTarget(int item)
{
	target=item;
}