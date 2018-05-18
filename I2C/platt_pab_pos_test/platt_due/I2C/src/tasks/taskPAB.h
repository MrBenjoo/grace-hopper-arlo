/*
 * taskPAB.h
 *
 * Created: 2018-05-18 13:07:36
 *  Author: Benji
 */ 


#ifndef TASKPAB_H_
#define TASKPAB_H_


#define TASK_PAB_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_PAB_PRIORITY (1)

void taskPAB(void *pvParamters);



#endif /* TASKPAB_H_ */