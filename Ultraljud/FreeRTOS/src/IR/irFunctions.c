/*
 * IRFunctions.c
 *
 * Created: 2018-05-20 23:32:24
 *  Author: Benji
 */ 
#include "IRFunctions.h"
#include <asf.h>

//const ir_distance_parameters sensor = {10000, -6, 3};
const ir_distance_parameters sensor = {10000, -32, 2};
	
int ir_get_distance(int adc_value)
{
	return sensor.a / (adc_value + sensor.b) - sensor.k;
}	