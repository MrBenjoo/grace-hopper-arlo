#ifndef CONTROLCENTER_H_
#define CONTROLCENTER_H_

#include <asf.h>
#include "../I2C/I2CFunctions.h"
#include "../initializations/pins_init.h"
#include <math.h>

#define TASK_CC_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_CC_PRIORITY (1)
#define ccSampleTime 200 //sampletime
void controlCenter(void *pvParamters);


#endif /* CONTROLCENTER_H_ */