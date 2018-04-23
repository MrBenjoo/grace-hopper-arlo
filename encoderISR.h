#ifndef ENCODERISR_H_
#define ENCODERISR_H_


void myISR1(void);
void encoder_init(void);
void rightEncoder(void);
void leftEncoder(void);
void resetCounter(void);
int getRightTickTime(void);
int getLeftTickTime(void);
int getRightTicks(void);
int getLeftTicks(void);
void waitForTicks(int leftTicks,int rightTicks);
int lPrevTick;
int lTickTime;
int lCurrentTick;
int rPrevTick;
int rTickTime;
int rCurrentTick;
int lTick;
int rTick;
#endif
/*
 * encoderISR.h
 *
 * Created: 2018-04-22 23:00:56
 *  Author: gustav
 */ 
