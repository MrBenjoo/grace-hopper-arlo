/*
 * dimensions.h
 *
 * Created: 2018-05-20 16:26:44
 *  Author: Sebastian
 */ 
#include <math.h>
#include <asf.h>

#ifndef DIMENSIONS_H_
#define DIMENSIONS_H_

#define kub 1
#define vinglas 2
#define stop 0

int	resolution = 144; //Upplösningen, antal pulser per revolution
float	radius = 7.9; //Hjulens radie är 7.9cm
float	dPP = 0.3447; //distance per pulse in cm
float	WheelCircum = 49.63716393; //Hjulets omkrets. Kan beräknas mer korrekt genom att mäta omkretsen fysiskt eftersom hjulet inte är helt runt
float	wheelToWheel = 39.5; //Distans mellan hjulen är 39.5cm
int	doubleToIntFactor = 100000; //conversion from float/double to int and keeping decimals 

#endif /* DIMENSIONS_H_ */