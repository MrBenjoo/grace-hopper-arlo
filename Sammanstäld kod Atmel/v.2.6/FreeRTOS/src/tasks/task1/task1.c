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
#include "../encoderISR.h"
//#define xTimeT1 50

/*
* Function: task1
* -------------------
* Performs an action every xTimeT1 milliseconds
*/
static uint32_t rPulse=1;

void task1(void *pvParamters)
{
	
	while(1){
		while(!waitForXPulsesRL(2000,2000)){	//längden på loopen
			
			drive(10,10,1,1);
			if (rPulse== getLeftPulses())
			{
				uint32_t Vl=getLeftPulses();
				uint32_t Vh=getRightPulses();
				int32_t lineDef= Vl-Vh;				// skillanden mellan höger och vänster 
				printf("v1%i \n",Vl);
				printf("vh%i \n",Vh);
				printf("%i \n",lineDef);
				//drive(10,  10, 1, 1);
				drive(10+(lineDef*1.7),  10-(lineDef*1.7), 1, 1);
				rPulse++;
			}
		drive(0,0,1,1);
		
		
		}
	}
}

