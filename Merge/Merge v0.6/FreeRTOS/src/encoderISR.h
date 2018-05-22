
#ifndef ENCODERISR_H_
#define ENCODERISR_H_


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


#endif
/*
 * encoderISR.h
 *
 * Created: 2018-04-22 23:00:56
 *  Author: gustav
 */ 
