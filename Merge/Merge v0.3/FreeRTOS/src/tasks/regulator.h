#ifndef REGULATOR_H_
#define REGULATOR_H_

#define TASK_REG_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_REG_PRIORITY (1)
#define sampleTime 300 //Sampletime for PID-regulation [in milliseconds]

#include <asf.h>
#include <math.h>
#include "../initializations/pins_init.h"
#include "../motorController.h"
#include "../encoderISR.h"

void regulator(void *pvParamters);

int resolution;
long N_Left;
long N_Right;
float radius;
float dPP;
float WheelCircum;
float distanceLeft;
float distanceRight;
float Ts;
float linearLeftDesired;
float linearRightDesired;
float linearLeftActual;
float linearRightActual;
int doubleToIntFactor;
float OldP_err_Left;
float OldP_err_Right;
float P_err_Left;
float P_err_Right;
long double I_err_Left;
long double I_err_Right;
float D_err_Left;
float D_err_Right;
float Kp;
float Ki;
float Kd;
float mcPulseLeft;
float mcPulseRight;
float mcPulseLeftOld;
float mcPulseRightOld;
float linearSpeedMargin;
int leftTrue;
int rightTrue;

#endif /* REGULATOR_H_ */