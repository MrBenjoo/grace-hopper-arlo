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
		
	//drive(20, 20, 1, 1); //uses pin35 and pin42 vänster/höger motorstyrka, vänster/höger direktion

	while(1){
	int ticksPassed = 0;	//Do not modify	
	int	ticksReference = 0; //Do not modify	
	int testNbr = 1; //Do not modify	
	int secondsPerTest = 2; //MODIFY for yout test, NOTE: take into account limits of data type if needed	
	int speedIncrementFactor = 5; //MODIFY for your test, NOTE: Motorspeed is limited to 0-100	
	int totalNbrTests = 20;	//MODIFY for your test, NOTE: calculation: totalNbrTests * speedIncrementFactor = should not exceed 100
	int pulses[2][totalNbrTests]; //Do not modify

	while(testNbr <= totalNbrTests){
		printf("Test#%i speed:%i is startning...\n",testNbr,speedIncrementFactor*testNbr);
		getLeftPulses();
		getRightPulses();
		printf("------\n");	
		ticksReference = xTaskGetTickCount();
		drive(speedIncrementFactor*testNbr,speedIncrementFactor*testNbr, 1, 1);
		while(ticksPassed<secondsPerTest*1000){
			ticksPassed =  xTaskGetTickCount() - ticksReference;
		}
		drive(0,0,1,1);
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
	printf("printing the results:\n");
	printf("------\n");
	printf("Start of results\n");
	printf("------\n");
	for(int j = 1; j <= 2; j++){
		if(j==1){
			printf("WHEEL LEFT:\n");
		}else if(j==2){
			printf("WHEEL RIGHT:\n");
		}
		for(int k = 1; k <= totalNbrTests; k++){
			printf(" %i ",pulses[j][k]);
		}
	}
	printf("------\n");
	printf("End of results\n");
	printf("------\n");
	while(1){		
	}	
	}
	
	
	
}

