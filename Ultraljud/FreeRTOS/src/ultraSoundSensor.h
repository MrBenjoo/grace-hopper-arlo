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
long distansUs();
long echoTime();

long echoTimeStop;

#endif /* ULTRASOUNDSENSOR_H_ */