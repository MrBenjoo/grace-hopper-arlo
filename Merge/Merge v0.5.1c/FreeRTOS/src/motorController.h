/*
 * motorController.h
 *
 *  Author: Group Grace Hopper
 */ 



#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

void drive(float velL, float velR);
void testDriveL(float speedPulseL);
void testDriveR(float speedPulseR);
float getSetLeftSpeed(void);
float getSetRightSpeed(void);
int getSetLeftDirection(void);
int getSetRightDirection(void);

pwm_channel_t pwm_channel_instance;
 float mcPLeftLatest;
 float mcPRightLatest;
 int motorSpeed;
 

#endif /* MOTORCONTROLLER_H_ */






