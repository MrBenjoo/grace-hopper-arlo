/*
 * Reglering.c
 *
 * Created: 2018-04-25 11:22:28
 *  Author: yohan
 */ 
#include <asf.h>
#include <stdio.h>
#include "encoderISR.h"
#include "motorController.h"
/*
Metoden kör och reglerar motorerna ett antal pulser som kan matas in som argument
x-antal pulser till höger motorn, och x-antal pulser till vänster motorn.
*/
void controlCenter( int lWheel,int rWheel){

	while(waitForXPulsesRL(lWheel,rWheel)){
		int rPulse= getRightAPulses();
		
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
		drive(0,0,1,1);
	
	
}