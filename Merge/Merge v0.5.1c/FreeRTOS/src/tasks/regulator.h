#ifndef REGULATOR_H_
#define REGULATOR_H_

#define TASK_REG_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_REG_PRIORITY (1)
#define sampleTime 300 //Sampletime for PID-regulation [in milliseconds]



void regulator(void *pvParamters);
long getPulsesSinceStartLeft();
long getPulsesSinceStartRight();
float getDisplacementLeft();
float getDisplacementRight();
float getDisplacementAverage();
float getChangeInAngle();
	
#endif /* REGULATOR_H_ */