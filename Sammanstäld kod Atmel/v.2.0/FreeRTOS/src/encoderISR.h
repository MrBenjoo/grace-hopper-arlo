#include <asf.h>
#ifndef ENCODERISR_H_
#define ENCODERISR_H_


//void myISR1(void);
void encoder_init(void);
void rightEncoderAISR(void);
void leftEncoderAISR(void);
void rightEncoderBISR(void);
void leftEncoderBISR(void);
void resetCounter(void);
uint8_t getRightAPulseTime(void);
uint8_t getLeftAPulseTime(void);
uint8_t getRightBPulseTime(void);
uint8_t getLeftBPulseTime(void);
int getRightAPulses(void);
int getLeftAPulses(void);
int getRightBPulses(void);
int getLeftBPulses(void);
int getRightPulses(void);
int getLeftPulses(void);
int waitForXPulsesRL(int lPulses,int rPulses);
int waitForXPulsesL(int lPulses);
int waitForXPulsesR(int rPulses);

int lAPrevTick;
int rAPrevTick;
int lACurrentTick;
int rACurrentTick;
int lBPrevTick;
int rBPrevTick;
int lBCurrentTick;
int rBCurrentTick;
int lAPulses;
int rAPulses;
uint8_t lAPulseTime;
uint8_t rAPulseTime;
int lBPulses;
int rBPulses;
uint8_t lBPulseTime;
uint8_t rBPulseTime;
uint8_t msPerTick;

#endif
/*
 * encoderISR.h
 *
 * Created: 2018-04-22 23:00:56
 *  Author: gustav
 */ 
