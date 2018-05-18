/*
 * ultraSoundSensor.h
 *
 * Created: 2018-05-18 11:47:21
 *  Author: filip
 */ 

#include <asf.h>
#ifndef ULTRASOUNDSENSOR_H_
#define ULTRASOUNDSENSOR_H_

void us_init();
void echoUs();
void usTrig();
void saveValues(uint32_t i, uint32_t valuesArray[]);
long distansUs();
long echoTime();

uint32_t values[60];
long echoTimeStop;

#endif /* ULTRASOUNDSENSOR_H_ */