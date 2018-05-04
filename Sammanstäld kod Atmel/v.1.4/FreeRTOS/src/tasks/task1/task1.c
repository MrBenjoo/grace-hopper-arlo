/* 
	The code in this file was used to test FreeRTOS. 
	Change the code for your purpose.
*/

#include <asf.h>
#include "task1.h"
#include "../initializations/pins_init.h"
#include "Reglering/Reglering.h"
#include "../motorController.h"
#include "../encoderISR.h"
//#define xTimeT1 50

/*
* Function: task1
* -------------------
* Performs an action every xTimeT1 milliseconds
*/
void task1(void *pvParamters)
{
	//portTickType xLastWakeTime;
	//portTickType xTimeIncrement = xTimeT1/portTICK_RATE_MS; /* set ticks (xTimeT1) in milliseconds */
	//xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
	
		//vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* constant period, independent of execution time */
		//vTaskDelay(xTimeT1);								 /* no constant period, dependent of execution time */ 
		
		//int ticksContinously = 0;
		//int ticksPassed = 0;
		//int ticksReference = 0;
	drive(20, 20, 1, 1); //uses pin35 and pin42 vänster/höger

	while(1){
		//drive(30, 30, 1, 1); //uses pin35 and pin42
		getRightBPulseTime();
		getLeftAPulseTime();
		getRightPulses();
		getLeftPulses();
	//ticksReference = xTaskGetTickCount();
	}
	/*while(ticksPassed<3000){
		ticksPassed =  xTaskGetTickCount() - ticksReference;
	}
	drive(0, 0, 1, 1);
	getRightPulses();
	getLeftPulses();
	*/	
	}

