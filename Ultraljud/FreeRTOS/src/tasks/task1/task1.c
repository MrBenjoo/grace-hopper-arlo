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
static uint8_t arrcounter;



void task1(void *pvParamters) {
	uint8_t angels[60]={};
		int angle;
		uint8_t bestAngle;
	//int counter=-1;
	while(1){			
			uint8_t dis;
			uint32_t valuesArray[30] = {};
			for(int i = 0; i < 30; i++) {
				usTrig();
				dis=distansUs();
				//printf("dis: %i \n", dis);
				valuesArray[i] = dis;
			}
			
			saveValues(counter, valuesArray);
			dis=get_values(counter);
			printf("values: %i \n",dis);
			
			if (dis>0 && dis <40)
			{		
				angels[arrcounter]=counter;
				arrcounter++;
			}
		
			
			if (!check) {
				rotate(1);			// ändra här om fel
				counter++;
				if (counter==29) {
					rotate(-30);
					//counter=0;
					check=1;
				}
				} else if (check==1) {
				rotate(-1);
				counter++;
				if (counter==59)
				{
					rotate(30);
					check=2;		//lägg den till 2 sen om det inte går
				}
				}
			
			//int dis= distansUs();
			//ultraSound();
			//printf("avstånd: %li \n",distansUs());
			//vTaskDelayUntil(xLastWakeTime,100);
		
		if (check==2)
		{	
			bestAngle=get_values(0);
			uint8_t i;
			uint8_t index;
			// hittar vinklen där roboten ska rotera framför armen
			for ( i=0;i<60;i++)
			{
				if (bestAngle>get_values(i) && get_values(i) != 0)
				{
					bestAngle=get_values(i);
					index=i;
				}
			}
			if (index >= 0 && index < 30)
			{
				rotate(index);
			}
			else
			{
				rotate(index - 29);
			}
			
			
			check=3;
		}else if (check==3);
		{
			driveCm(bestAngle-18);
		}
		
	}
		
}

