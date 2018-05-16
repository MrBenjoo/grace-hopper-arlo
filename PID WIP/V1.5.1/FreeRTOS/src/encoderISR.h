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
int getRightAPulseTime(void);
int getLeftAPulseTime(void);
int getRightBPulseTime(void);
int getLeftBPulseTime(void);
long getRightAPulses(void);
long getLeftAPulses(void);
long getRightBPulses(void);
long getLeftBPulses(void);
long getRightPulses(void);
long getLeftPulses(void);
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
long lAPulses;
long rAPulses;
int lAPulseTime;
int rAPulseTime;
long lBPulses;
long rBPulses;
int lBPulseTime;
int rBPulseTime;
int msPerTick;

#endif
/*
 * encoderISR.h
 *
 * Created: 2018-04-22 23:00:56
 *  Author: gustav
 */ 
