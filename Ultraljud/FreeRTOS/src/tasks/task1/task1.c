/* 
	The code in this file was used to test FreeRTOS. 
	Change the code for your purpose.
*/

#include <asf.h>
#include <stdio.h>
#include "task1.h"
#include "../initializations/pins_init.h"
#include "Reglering/Reglering.h"
#include "../motorController.h"
#include "../ultraSoundSensor.h"

//#define xTimeT1 50

/*
* Function: task1
* -------------------
* Performs an action every xTimeT1 milliseconds
*/
static uint8_t counter=0;
static uint8_t check=0;

void task1(void *pvParamters)
{
	
	while(1){

		/*uint8_t dis;
		uint8_t*/
		usTrig();
		/*dis=distansUs();
		if (!dis && !check)
		{
		rotate(1);
		delay_ms(1);
		counter++;
		if (counter==30)
		{
		rotate(-30);
		counter=0;
		check=1;
		}
		} 
		else if (!dis && check)
		{
		rotate(-1);
		delay_ms(1);
		counter++;
		/*if (counter==30)
		{

		
		}

		
		}else if (dis )
		{
		}*/
		
		//int dis= distansUs();
		printf("avstånd: %li \n",distansUs());
		//vTaskDelayUntil(xLastWakeTime,100);
		
	}
}

