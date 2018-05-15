/*
 * Reglering.c
 *
 * Created: 2018-04-25 11:22:28
 *  Author: yohan
 */ 
/*
#include <asf.h>
#include <stdio.h>
#include "encoderISR.h"
#include "motorController.h"

void controlCenter( int distans){
	int tiks= distans/1.379;
	drive(50,  50, 1, 1);
	
	while(tiks<getLeftTicks()){
		int Vl=getLeftTickTime();
		int Vh=getRightTickTime();
		int lineDef= Vl-Vh;
		drive(50-lineDef,  50+lineDef, 1, 1);
		
	}
		drive(0,0,1,1);
	
	
}
*/