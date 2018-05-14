/*
The code in this file was used to test FreeRTOS.
Change the code for your purpose.
*/

#include <asf.h>
#include "task2.h"
#include "../initializations/pins_init.h"

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
	
	
	while(1){
	}
}
