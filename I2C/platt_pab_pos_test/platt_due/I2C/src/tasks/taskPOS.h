/*
 * task_i2c.h
 *
 * Created: 2018-05-09 11:47:45
 *  Author: gustav
 */ 

#pragma once

#define TASK_POS_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_POS_PRIORITY (2)

extern xSemaphoreHandle semaphorePOS;

void taskPOS(void *pvParamters);
void setTarget(int item);
int getPositionX(void);
int getPositionY(void);
int getDisposalX(void);
int getDisposalY(void);
int getPickupX(void);
int getPickupY(void);


//#endif /* TASK1_H_ */
