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
volatile uint8_t rPulse=1;
void task1(void *pvParamters)
{
	
	while(rPulse == getRightAPulses()){
		
			rPulse= getRightAPulses();
		
		if (rPulse= getRightAPulses())
		{
			int Vl=getLeftAPulseTime();
			int Vh=getRightAPulseTime();
			int lineDef= Vl-Vh;
			printf("%i",lineDef);
			rPulse++;
		}
		
		//drive(50-lineDef,  50+lineDef, 1, 1);
		//delay_ms(5)
		
	
	}
}

