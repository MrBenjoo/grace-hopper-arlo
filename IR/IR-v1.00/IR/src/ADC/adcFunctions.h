/*
 * adcFunctions.h
 *
 * Created: 2018-05-20 19:51:29
 *  Author: Benji
 */ 


#ifndef ADCFUNCTIONS_H_
#define ADCFUNCTIONS_H_

int analog_init(int pinNumber);
uint16_t analog_read(int pinNumber);

#endif /* ADCFUNCTIONS_H_ */