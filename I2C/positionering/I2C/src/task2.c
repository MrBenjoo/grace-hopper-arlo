/*
 * task2.c
 *
 * Created: 2018-05-09 13:49:44
 *  Author: gustav
 */ 
/*
The code in this file was used to test FreeRTOS.
Change the code for your purpose.
*/

#include <asf.h>
#include "task2.h"
#include "taskPOS.h"
//#include "../initializations/pins_init.h"

#define xTimeT2 1000
int x;
int xx;
int y;
int yy;

/*
* Function: task2
* -------------------
* Performs an action every xTimeT2 milliseconds
*/
void task2(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = xTimeT2/portTICK_RATE_MS; /* set ticks (xTimeT2) in milliseconds */
	xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
	
	while(1) /* the task must be looping infinitely */
	{
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* constant period, independent of execution time */
		//vTaskDelay(50);								 /* no constant period, dependent of execution time */
		x=getPositionX();
		y=getPositionY();
		yy=getPickupY();
		xx=getPickupX();
		printf("\nposition: %i,%i",x,y);
		printf("\ntargetX: %i,%i",xx,yy);
	
	}
}
