/*
 * encoderISR.c
 *
 * Created: 2018-04-20 11:13:29
 *  Author: gustav
 */ 
#include <asf.h>
#include <stdio.h>
#include "encoderISR.h"
int lPrevTick;
int lTickTime;
int lCurrentTick;
int rPrevTick;
int rTickTime;
int rCurrentTick;
int lTick;
int rTick;

void encoder_init(){ //initialise the encoders
	lPrevTick=0;
	lTickTime=0;
	lCurrentTick=0;
	rPrevTick=0;
	rTickTime=0;
	rCurrentTick=0;
	lTick=0;
	rTick=0;
	//ioport_set_pin_dir(PIO_PB27,)
	pmc_enable_periph_clk(ID_PIOC);
	pio_set_input(PIOC, PIO_PC25,NULL);
	pio_handler_set(PIOC, ID_PIOC, PIO_PC25, PIO_IT_RISE_EDGE , leftEncoder);
	pio_enable_interrupt(PIOC, PIO_PC25); //digital pin 5
	
	
	pio_set_input(PIOC, PIO_PC23,NULL);
	pio_handler_set(PIOC,ID_PIOC, PIO_PC23,PIO_IT_RISE_EDGE,rightEncoder);
	pio_enable_interrupt(PIOC, PIO_PC23); //digital pin 7
	NVIC_EnableIRQ(PIOC_IRQn);
	
	
}

void myISR1(){ //used for testing purposes
	lPrevTick = lCurrentTick;
	lCurrentTick = xTaskGetTickCountFromISR();
	lTickTime = lCurrentTick-lPrevTick;
	printf("Time:\n");
	printf("%i\n",lTickTime);
	
	
}

void rightEncoder(){ //ISR for the right encoder
	rTick++;
	rPrevTick = rCurrentTick;
	rCurrentTick = xTaskGetTickCountFromISR();
	rTickTime = rCurrentTick-rPrevTick;
	printf("Right Time:\n");
	printf("%i\n",rTickTime);
	
}
void leftEncoder(){ //ISR for the left encoder
	lTick++;
	lPrevTick = lCurrentTick;
	lCurrentTick = xTaskGetTickCountFromISR();
	lTickTime = lCurrentTick-lPrevTick;
	printf("Left Time:\n");
	printf("%i\n",lTickTime);
	
}
void resetCounter(){ //resets the tick counter
	lTick=0;
	rTick=0;
}
int getLeftTicks(){ //returns the amount of ticks from left encoder since last reset
	return lTick;
}
int getRightTicks(){ //returns the amount of ticks from right encoder since last reset
	return rTick;
}
int getRightTickTime(){ //returns the tick time for the right encoder in milliseconds
	return rTickTime;
}
int getLeftTickTime(){  //returns the tick time for the left encoder  in milliseconds
	return lTickTime;
}
void waitForTicks(int leftTicks,int rightTicks){//wait for specified amount of ticks to occur
	leftTicks+=lTick;
	rightTicks+=rTick;
	while (leftTicks>lTick || rightTicks>rTick){
		
	}
}
