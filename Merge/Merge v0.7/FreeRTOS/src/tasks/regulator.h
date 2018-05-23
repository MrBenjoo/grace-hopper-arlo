#ifndef REGULATOR_H_
#define REGULATOR_H_

#define TASK_REG_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_REG_PRIORITY (1)
#define sampleTime 300 //Sampletime for PID-regulation [in milliseconds]



void regulator(void *pvParamters);
long getPulsesSinceStartLeft(void);
long getPulsesSinceStartRight(void);
float getDisplacementLeft(void);
float getDisplacementRight(void);
float getDisplacementAverage(void);
float getChangeInAngle(void);
	
#endif /* REGULATOR_H_ */