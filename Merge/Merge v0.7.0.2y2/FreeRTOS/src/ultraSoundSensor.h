/*
 * ultraSoundSensor.h
 *
 * Created: 2018-05-18 11:47:21
 *  Author: filip
 */ 

#include <asf.h>
#ifndef ULTRASOUNDSENSOR_H_
#define ULTRASOUNDSENSOR_H_
#define INT_MAX 32767
void us_init();
void echoUs();
void usTrig();
void saveValues(uint32_t i, uint32_t valuesArray[]);
void ultraSound();
void Navigate();
long distansUs();
long echoTime();
uint8_t get_values(uint8_t index);

uint32_t values[60];
long echoTimeStop;
static uint8_t counter;
static uint8_t check;

#endif /* ULTRASOUNDSENSOR_H_ */