/*
 * IncFile1.h
 *
 * Created: 2018-05-18 18:04:54
 *  Author: Sebastian
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_


#pragma once

#define TASK_POS_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_POS_PRIORITY (2)


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

#endif /* INCFILE1_H_ */