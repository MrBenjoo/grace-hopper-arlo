/*
 * encoderISR.c
 *
 * Counts pulses for each wheel and keeps track of distance travelled.
 *  Author: Group Grace Hopper
 */ 

#include "encoderISR.h"

int lAPrevTick = 0;
int rAPrevTick = 0;
int lACurrentTick = 0;
int rACurrentTick = 0;
int lBPrevTick = 0;
int rBPrevTick = 0;
int lBCurrentTick = 0;
int rBCurrentTick = 0;
long lAPulses = 0;
long rAPulses = 0;
int lAPulseTime = 0;
int rAPulseTime = 0;
long lBPulses = 0;
long rBPulses = 0;
int lBPulseTime = 0;
int rBPulseTime = 0;
int msPerTick = 1;
	

void rightEncoderAISR(){ //ISR for the right encoder A
	//Counts pulses on the right wheel encoder	
	if(getSetRightDirection()>0){
		rAPulses++; 
	}
	else if(getSetRightDirection()<0){
		rAPulses--;
	}else if (getSetRightDirection()==0 && ((int)(getSetRightSpeed()))==0){
	//	printf("ERROR: no direction could be fetched from the right motor but pulse was still triggered. Encoder pulse data will be unreliable.\n");
	}

	//Compares tick-count since last time it was here to get a measurement of the pulsetime in units of ticks
	//It uses the inbuilt tick counter as reference 
	rAPrevTick = rACurrentTick;
	rACurrentTick = xTaskGetTickCountFromISR();
	rAPulseTime = rACurrentTick-rAPrevTick*msPerTick;
	//printf("RightPulseTime A: %i ms\n",rAPulseTime);
	
}

void rightEncoderBISR(){ //ISR for the right encoder B
	//Counts pulses on the right wheel encoder
	if(getSetRightDirection()>0){
		rBPulses++;
	}
	else if(getSetRightDirection()<0){
		rBPulses--;
	}else if(getSetRightDirection()==0 && ((int)(getSetRightSpeed()))==0){
		//	printf("ERROR: no direction could be fetched from the right motor but pulse was still triggered. Encoder pulse data will be unreliable.\n");
	}
	
	//Compares tick-count since last time it was here to get a measurement of the pulsetime in units of ticks
	//It uses the inbuilt tick counter as reference
	rBPrevTick = rBCurrentTick;
	rBCurrentTick = xTaskGetTickCountFromISR();
	rBPulseTime = rBCurrentTick-rBPrevTick*msPerTick;
	//printf("RightPulseTime B: %i ms\n",rBPulseTime);
	
}

void leftEncoderAISR(){ //ISR for the left encoder A
	//Counts pulses on the left wheel encoder
	if(getSetLeftDirection()>0){
		lAPulses++;
	}
	else if(getSetLeftDirection()<0){
		lAPulses--;
	}else if(getSetLeftDirection()==0 && ((int)(getSetLeftSpeed()))==0){
		//	printf("ERROR: no direction could be fetched from the left motor but pulse was still triggered. Encoder pulse data will be unreliable.\n");
	}
	
	//Compares tick-count since last time it was here to get a measurement of the pulsetime in units of ticks
	//It uses the inbuilt tick counter as reference
	lAPrevTick = lACurrentTick;
	lACurrentTick = xTaskGetTickCountFromISR();
	lAPulseTime = (lACurrentTick-lAPrevTick)*msPerTick;
	//printf("LeftPulseTime A: %i ms\n",lAPulseTime);
	
}

void leftEncoderBISR(){ //ISR for the left encoder B
	//Counts pulses on the left wheel encoder
	if(getSetLeftDirection()>0){
		lBPulses++;
	}
	else if(getSetLeftDirection()<0){
		lBPulses--;
	}else if(getSetLeftDirection()==0 && ((int)(getSetLeftSpeed()))==0){
		//printf("ERROR: no direction could be fetched from the left motor but pulse was still triggered. Encoder pulse data will be unreliable.\n");
	}
	
	//Compares tick-count since last time it was here to get a measurement of the pulsetime in units of ticks
	//It uses the inbuilt tick counter as reference
	lBPrevTick = lBCurrentTick;
	lBCurrentTick = xTaskGetTickCountFromISR();
	lBPulseTime = (lBCurrentTick-lBPrevTick)*msPerTick;
	//printf("LeftPulseTime B: %i ms\n",lBPulseTime);
	
}

void resetCounter(){ //resets left and right encoders pulse counters
	lAPulses=0;
	rAPulses=0;
	rBPulses=0;
	lBPulses=0;
	//printf("Reseting pulse counters:\n LeftPulses A: #%i\n LeftPulses B: #%i\n RightPulses A: #%i\n RightPulses B: #%i\n",lAPulses,lBPulses,rAPulses,rBPulses);
}
/////////////////////PULSE COUNTER//////////////////////////////////////////
long getLeftPulses(){ //returns the sum of pulses from left encoder A and B since last reset
	//printf("LeftPulses : ##[%i]##\n",(getLeftAPulses()+getLeftBPulses()));
	return (getLeftAPulses()+getLeftBPulses());
}
long getLeftAPulses(){ //returns the amount of pulses from left encoder A since last reset
	//printf("LeftPulses A: #%i\n",lAPulses);
	return lAPulses;
}
long getLeftBPulses(){ //returns the amount of pulses from left encoder B since last reset
	//printf("LeftPulses B: #%i\n",lBPulses);
	return lBPulses;
}
long getRightPulses(){ //returns the sum of pulses from right encoder A and B since last reset
	//printf("RightPulses : ##[%i]##\n",(getRightAPulses()+getRightBPulses()));
	return (getRightAPulses()+getRightBPulses());
}
long getRightAPulses(){ //returns the amount of pulses from right encoder A since last reset
	//printf("RightPulses A: #%i\n",rAPulses);
	return rAPulses;
}
long getRightBPulses(){ //returns the amount of pulses from right encoder B since last reset
	//printf("RightPulses B: #%i\n",rBPulses);
	return rBPulses;
}

/////////////////////////PULSE TIMES///////////////////////////////////////
int getRightAPulseTime(){ //returns the latest pulse time for the right encoder A in milliseconds
	//printf("RightPulseTime A: %i ms\n",rAPulseTime);
	return rAPulseTime;
	
}
int getRightBPulseTime(){ //returns the latest pulse time for the right encoder B  in milliseconds
	//printf("RightPulseTime B: %i ms\n",rBPulseTime);
	return rBPulseTime;
}
int getLeftAPulseTime(){  //returns the latest pulse time for the left encoder A in milliseconds
	//printf("LeftPulseTime A: %i ms\n",lAPulseTime);
	return lAPulseTime;
}
int getLeftBPulseTime(){  //returns the latest pulse time for the left encoder B in milliseconds
	//printf("LeftPulseTime B: %i ms\n",lBPulseTime);
	return lBPulseTime;
}

/////////////////////////CONTROL BY PULSE COUNTER///////////////////////////////
int waitForXPulsesRL(int lPulses,int rPulses){//wait for a specified amount of pulses, returns 1 when first of two conditions of X pulses is met
	if(getLeftPulses()>lPulses || getRightPulses()>rPulses)
		printf("RL True\n");
		return 1;
	printf("RL False\n");	
	return 0;
}
 
int waitForXPulsesL(int lPulses){//wait for a specified amount of pulses from the left wheel encoder, returns 1 if condition X pulses is met
	if(getLeftPulses()>lPulses)
		printf("L True\n");	
		return 1;
	printf("L False\n");		
	return 0;
}

int waitForXPulsesR(int rPulses){//wait for a specified amount of pulses from the right wheel encoder, returns 1 if condition X pulses is met
	if(getRightPulses()>rPulses)
	    printf("R True\n");	
		return 1;
	printf("R False\n");	
	return 0;
}
