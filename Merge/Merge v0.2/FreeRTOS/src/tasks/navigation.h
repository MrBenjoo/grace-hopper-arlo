
#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#include <asf.h>
#include "../I2C/I2CFunctions.h"
#include "../initializations/pins_init.h"
#include <math.h>

#pragma once

#define TASK_NAV_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_NAV_PRIORITY (1)
#define xTimeT1 500 //sampletime
#define kub 1
#define vinglas 2

void taskPOS(void *pvParamters);
void setTarget(int item);
int getPositionX(void);
int getPositionY(void);
int getDisposalX(void);
int getDisposalY(void);
int getPickupX(void);
int getPickupY(void);
int getDistanceToDropOff(void);
int getDistanceToObject(void);
void rotate(int degree);
void driveCm(int cm);
int getAngle(int p1X, int p1Y, int p2X, int p2Y);
int angleCorrection(int rX,int rY,int cX,int cY,int u1);

int target; //this variable determines which item is the target
int pickupX; //X-coordinates for the pick up
int pickupY; //Y-coordinates for the pick up
int posX; //X-coordinates for ARLO-robot
int posY; //Y-coordinates for ARLO-robot
int disposalX; //X-coordinates for the disposal area
int disposalY; //Y-coordinates for the disposal area

#endif /* NAVIGATION_H_ */




