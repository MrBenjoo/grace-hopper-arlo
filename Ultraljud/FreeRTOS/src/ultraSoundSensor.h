/*
 * ultraSoundSensor.h
 *
 * Created: 2018-05-17 22:07:56
 *  Author: filip
 */ 


#ifndef ULTRASOUNDSENSOR_H_
#define ULTRASOUNDSENSOR_H_

void us_init();
void echoUs();
void usTrig();
long distansUs();
long getEchoTime();

long echoTimeStop;



#endif /* ULTRASOUNDSENSOR_H_ */