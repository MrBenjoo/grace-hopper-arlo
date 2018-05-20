#ifndef CONTROLCENTER_H_
#define CONTROLCENTER_H_

#include <asf.h>
#include "../I2C/I2CFunctions.h"
#include "../initializations/pins_init.h"
#include <math.h>

#define TASK_CC_STACK_SIZE (2048/ sizeof(portSTACK_TYPE))
#define TASK_CC_PRIORITY (1)

void controlCenter(void *pvParamters);

int current_case;
int Old_OurPositionX;		// Stores old position in X (State 0)
int Old_OurPositionY;		// Stores old position in Y (State 0)
int New_OurPositionX;		// Stores new position in X (State 1)
int New_OurPositionY;		// Stores new position in Y (State 1)
int objectPositionX;		// Object position X
int objectPositionY;		// Object position Y
int dropOffPositionX;		// Drop off X
int dropOffPositionY;		// Drop off Y
int distanceToDropOff;		// (Kommer eventuellt användas för att beräkna dropoff-positionen)
int ourDirection;
int angle;					// Angle to object
int correction;				// angle for correction
int done;				// checks if the task is done
int fromStartToObject;
int corrected;
int valueFromArmTest;
bool not_sent;

#endif /* CONTROLCENTER_H_ */