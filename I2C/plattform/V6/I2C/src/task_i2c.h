/*
 * task1.h
 *
 * Created: 2018-05-14 18:36:47
 *  Author: Benji
 */ 


#ifndef TASK1_H_
#define TASK1_H_


#define TASK_I2C_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_I2C_PRIORITY (1)

void task1(void *pvParamters);


#endif /* TASK1_H_ */