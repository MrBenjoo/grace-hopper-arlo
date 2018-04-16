/*
The code in this file was used to test FreeRTOS.
Change the code for your purpose.
*/

#include <asf.h>
#include "task2.h"

#define xTimeT2 20

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
		
		
		/* ----------------------------------- simulate a function/task that is working ----------------------------------- */
		ioport_set_pin_level(PIO_PD8_IDX, HIGH); /* set pin to HIGH to indicate that the task has entered the running state */
		volatile int j=0;
		for (int i=0; i < 100000; i++)
		{
			j++;
		}
		ioport_set_pin_level(PIO_PD8_IDX, LOW); /* set pin to LOW to indicate that the task is no longer in the running state */
		/* ---------------------------------------------------------------------------------------------------------------- */
	}
}
