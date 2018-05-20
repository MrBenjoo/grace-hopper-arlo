
#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#include <asf.h>
#include <math.h>
#include <stdio.h>
#include "../I2C/I2CFunctions.h"
#include "../initializations/pins_init.h"
#include "../tasks/position.h"
#include "../tasks/regulator.h"
#include "../dimensions.h"

#pragma once

void setExtension(int extension);
int getDistanceToDropOff(void);
int getDistanceToObject(void);
void rotate(int degree);
void driveCm(int cm);
int getAngle(int p1X, int p1Y, int p2X, int p2Y);
int angleCorrection(int rX,int rY,int cX,int cY,int u1);


#endif /* NAVIGATION_H_ */




