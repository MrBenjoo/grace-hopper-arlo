/*
 * encoderISR.c
 *
 * Created: 2018-04-20 11:13:29
 *  Author: Gustav,Sebastian
 */ 
#include <asf.h>
#include <stdio.h>
#include "encoderISR.h"
#include "motorController.h"
#include "../initializations/pins_init.h"

void encoder_init(){ //initialise the encoders
	lAPrevTick=0; 
	rAPrevTick=0;
	lACurrentTick=0;
	rACurrentTick=0;
	lBPrevTick=0;
	rBPrevTick=0;
	lBCurrentTick=0;
	rBCurrentTick=0;
	lAPulses=0;
	lAPulseTime=0;
	rAPulses=0;
	rAPulseTime=0;
	lBPulses=0;
	lBPulseTime=0;
	rBPulses=0;
	rBPulseTime=0;
	msPerTick=1; // Time for a tick is 1 ms on SAM3X8E CPU
	pmc_enable_periph_clk(ID_PIOC);
/* Initializes interrupt pin for the right encoder A, trigger on rise edge, pin7*/
pio_set_input(PIOC,pin7i,NULL);
pio_handler_set(PIOC,ID_PIOC,pin7i,PIO_IT_RE_OR_HL,rightEncoderAISR);
pio_enable_interrupt(PIOC,pin7i); //digital pin 7

/* Initializes interrupt pin for the left encoder A, trigger on rise edge, pin5*/
pio_set_input(PIOC,pin5i,NULL);
pio_handler_set(PIOC, ID_PIOC,pin5i,PIO_IT_RE_OR_HL, leftEncoderAISR);
pio_enable_interrupt(PIOC,pin5i); //digital pin 5 

/* Initializes interrupt pin for the left encoder B, trigger on rise edge, pin8*/
pio_set_input(PIOC,pin33,NULL);
pio_handler_set(PIOC, ID_PIOC,pin33,PIO_IT_RE_OR_HL, rightEncoderBISR);
pio_enable_interrupt(PIOC,pin33); //digital pin 33 

/* Initializes interrupt pin for the right encoder B, trigger on rise edge, pin10*/
pio_set_input(PIOC,pin10i,NULL);
pio_handler_set(PIOC,ID_PIOC,pin10i,PIO_IT_RE_OR_HL,leftEncoderBISR);
pio_enable_interrupt(PIOC,pin10i); //digital pin 10 


NVIC_EnableIRQ(PIOC_IRQn); 
	
	
	
}

/* 
	void myISR1(){ //used for testing purposes
	lPrevTick = lCurrentTick;
	lCurrentTick = xTaskGetTickCountFromISR();
	lTickTime = lCurrentTick-lPrevTick;
	printf("Time:\n");
	printf("%i\n",lTickTime);
	
} 
*/
//////////////////////////////ENCODER ISR//////////////////////////////////////////
void rightEncoderAISR(){ //ISR for the right encoder A
	//Counts pulses on the right wheel encoder	
	if(getSetRDirection()>0){
		rAPulses++; 
	}
	else if(getSetRDirection()<0){
		rAPulses--;
	}else if(getSetRDirection()==0){
		printf("ERROR: no direction could be fetched from the right motor but pulse was still triggered. Encoder pulse data will be unreliable.\n");
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
	if(getSetRDirection()>0){
		rBPulses++;
	}
	else if(getSetRDirection()<0){
		rBPulses--;
		}else if(getSetRDirection()==0){
			printf("ERROR: no direction could be fetched from the right motor but pulse was still triggered. Encoder pulse data will be unreliable.\n");
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
	if(getSetLDirection()>0){
		lAPulses++;
	}
	else if(getSetLDirection()<0){
		lAPulses--;
		}else if(getSetLDirection()==0){
			printf("ERROR: no direction could be fetched from the left motor but pulse was still triggered. Encoder pulse data will be unreliable.\n");
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
	if(getSetLDirection()>0){
		lBPulses++;
	}
	else if(getSetLDirection()<0){
		lBPulses--;
	}else if(getSetLDirection()==0){
		printf("ERROR: no direction could be fetched from the left motor but pulse was still triggered. Encoder pulse data will be unreliable.\n");
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
	printf("Reseting pulse counters:\n LeftPulses A: #%i\n LeftPulses B: #%i\n RightPulses A: #%i\n RightPulses B: #%i\n",lAPulses,lBPulses,rAPulses,rBPulses);
}
/////////////////////PULSE COUNTER//////////////////////////////////////////
int getLeftPulses(){ //returns the sum of pulses from left encoder A and B since last reset
	printf("LeftPulses : ##[%i]##\n",(getLeftAPulses()+getLeftBPulses()));
	return (getLeftAPulses()+getLeftBPulses());
}
int getLeftAPulses(){ //returns the amount of pulses from left encoder A since last reset
	//printf("LeftPulses A: #%i\n",lAPulses);
	return lAPulses;
}
int getLeftBPulses(){ //returns the amount of pulses from left encoder B since last reset
	//printf("LeftPulses B: #%i\n",lBPulses);
	return lBPulses;
}
int getRightPulses(){ //returns the sum of pulses from right encoder A and B since last reset
	printf("RightPulses : ##[%i]##\n",(getRightAPulses()+getRightBPulses()));
	return (getRightAPulses()+getRightBPulses());
}
int getRightAPulses(){ //returns the amount of pulses from right encoder A since last reset
	//printf("RightPulses A: #%i\n",rAPulses);
	return rAPulses;
}
int getRightBPulses(){ //returns the amount of pulses from right encoder B since last reset
	//printf("RightPulses B: #%i\n",rBPulses);
	return rBPulses;
}

/////////////////////////PULSE TIMES///////////////////////////////////////
uint16_t getRightAPulseTime(){ //returns the latest pulse time for the right encoder A in milliseconds
	printf("RightPulseTime A: %i ms\n",rAPulseTime);
	return rAPulseTime;
	
}
uint16_t getRightBPulseTime(){ //returns the latest pulse time for the right encoder B  in milliseconds
	printf("RightPulseTime B: %i ms\n",rBPulseTime);
	return rBPulseTime;
}
uint16_t getLeftAPulseTime(){  //returns the latest pulse time for the left encoder A in milliseconds
	printf("LeftPulseTime A: %i ms\n",lAPulseTime);
	return lAPulseTime;
}
uint16_t getLeftBPulseTime(){  //returns the latest pulse time for the left encoder B in milliseconds
	printf("LeftPulseTime B: %i ms\n",lBPulseTime);
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
