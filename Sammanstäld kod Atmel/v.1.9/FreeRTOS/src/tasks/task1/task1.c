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
		
	//drive(30, 30, -1, -1); //uses pin35 and pin42 vänster/höger motorstyrka, vänster/höger direktion
	//getRightPulses();
	while(1){
	int ticksPassed = 0;	//Do not modify	
	int	ticksReference = 0; //Do not modify	
	int testNbr = 1; //Do not modify	
	int secondsPerTest = 2; //MODIFY for yout test, NOTE: take into account limits of data type if needed	
	int dir = -1; //MODIFY direction for wheels +1 = forward , -1 = reverse
	int speedIncrementFactor = 5; //MODIFY for your test, NOTE: Motorspeed is limited to 0-100	
	int totalNbrTests = 100/speedIncrementFactor; //Do not modify
	int pulses[2][totalNbrTests]; //Do not modify

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$        TEST PROGRAM: FÅR PULSER FRÅN VÄNSTER OCH      $$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$        HÖGER STEGAR IGENOM 5-100% MOTORSTYRKA         $$$$$$$$$$$$$$$$*/          
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	while(testNbr <= totalNbrTests){
		printf("Test#%i speed:%i is startning...\n",testNbr,speedIncrementFactor*testNbr);
		getLeftPulses();
		getRightPulses();
		printf("------\n");	
		ticksReference = xTaskGetTickCount();
		drive(speedIncrementFactor*testNbr,speedIncrementFactor*testNbr, dir, dir);
		while(ticksPassed<secondsPerTest*1000){
			ticksPassed =  xTaskGetTickCount() - ticksReference;
		}
		drive(0,0,dir,dir);
		pulses[1][testNbr] = getLeftPulses();
		pulses[2][testNbr] = getRightPulses();
		printf("Test#%i speed:%i is ending...\n",testNbr,speedIncrementFactor*testNbr);
		printf("------\n");
		resetCounter();	
		testNbr++;
		ticksPassed = 0;
	}
	drive(0,0,1,1);
	printf("All tests have been run through...\n");
	while(1){		
	}	
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	
	} 
}

