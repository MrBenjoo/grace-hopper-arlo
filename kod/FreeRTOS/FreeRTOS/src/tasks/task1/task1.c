/* 
	The code in this file was used to test FreeRTOS. 
	Change the code for your purpose.
*/

#include <asf.h>
#include "task1.h"

#define xTimeT1 50

/*
* Function: task1
* -------------------
* Performs an action every xTimeT1 milliseconds
*/
void task1(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = xTimeT1/portTICK_RATE_MS; /* set ticks (xTimeT1) in milliseconds */
	xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
	
	while (1) /* the task must be looping infinitely */
	{
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* constant period, independent of execution time */
		//vTaskDelay(50);								 /* no constant period, dependent of execution time */ 
		
		
		/* ----------------------------------- simulate a function/task that is working ----------------------------------- */
		ioport_set_pin_level(PIO_PB27_IDX, HIGH); /* set pin to HIGH to indicate that the task has entered the running state */
		volatile int j=0;
		for (int i=0; i < 100000; i++)
		{
			j++;
		}
		ioport_set_pin_level(PIO_PB27_IDX, LOW); /* set pin to LOW to indicate that the task is no longer in the running state */
		/* ---------------------------------------------------------------------------------------------------------------- */
	}
}

