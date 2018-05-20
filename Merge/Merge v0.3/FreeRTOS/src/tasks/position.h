
#ifndef POSITION_H_
#define POSITION_H_

#include <asf.h>
#include "../I2C/I2CFunctions.h"
#include "../initializations/pins_init.h"
#include <math.h>

#pragma once

#define TASK_POS_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_POS_PRIORITY (1)
#define posSampleTime 200 //sampletime

void position(void *pvParamters);
int getPositionX(void);
int getPositionY(void);
int getDisposalX(void);
int getDisposalY(void);
int getPickupX(void);
int getPickupY(void);


int pickupX; //X-coordinates for the pick up
int pickupY; //Y-coordinates for the pick up
int posX; //X-coordinates for ARLO-robot
int posY; //Y-coordinates for ARLO-robot
int disposalX; //X-coordinates for the disposal area
int disposalY; //Y-coordinates for the disposal area

#endif /* POSITION_H_ */