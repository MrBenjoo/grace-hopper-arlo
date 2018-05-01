/*
 * motorController.h
 *
 * Created: 2018-04-18 13:02:08
 *  Author: filip
 */ 


#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_
 int rSpeed;
 int lSpeed;
 int rDirection;
 int lDirection;
void drive(int rSpeed, int lSpeed, int rDirection, int lDirection);
int getSetLSpeed(void);
int getSetRSpeed(void);
int getSetLDirection(void);
int getSetRDirection(void);


#endif /* MOTORCONTROLLER_H_ */