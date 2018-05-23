
#ifndef POSITION_H_
#define POSITION_H_


#pragma once

#define TASK_POS_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_POS_PRIORITY (2)
#define posSampleTime 300 //sampletime

void position(void *pvParamters);
int getPositionX(void);
int getPositionY(void);
int getDisposalX(void);
int getDisposalY(void);
int getPickupX(void);
int getPickupY(void);




#endif /* POSITION_H_ */