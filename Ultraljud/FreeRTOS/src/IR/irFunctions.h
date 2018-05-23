/*
 * IRFunctions.h
 *
 * Created: 2018-05-20 23:32:57
 *  Author: Benji
 */ 


#ifndef IRFUNCTIONS_H_
#define IRFUNCTIONS_H_

typedef struct {
	const int a;
	const int b;
	const int k; // korrigeringskonstant
} ir_distance_parameters;

int ir_get_distance(int adc_value);

#endif /* IRFUNCTIONS_H_ */