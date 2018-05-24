#ifndef CONTROLCENTER_H_
#define CONTROLCENTER_H_




#define TASK_CC_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_CC_PRIORITY (1)
#define ccSampleTime 200 //sampletime
void controlCenter(void *pvParamters);


#endif /* CONTROLCENTER_H_ */