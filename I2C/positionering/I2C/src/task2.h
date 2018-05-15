/*
 * task2.h
 *
 * Created: 2018-05-09 13:53:36
 *  Author: gustav
 */ 
#ifndef TASK2_H_
#define TASK2_H_

#define TASK_2_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_2_PRIORITY (1)

void task2(void *pvParamters);

#endif /* TASK2_H_ */
