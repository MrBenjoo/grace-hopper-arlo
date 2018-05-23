/*
 * adcFunctions.c
 *
 * Created: 2018-05-20 19:50:49
 *  Author: Benji
 */ 
#include <asf.h>
#include "adcFunctions.h"

int analog_init(int pinNumber)
{	
	pmc_enable_periph_clk(ID_ADC);	/* power the clock for the ADC with pmc_enable_periph_clk(ID_ADC) */

	if(pinNumber == 0) /* IF pinNumber == A0 */
	{ 
		adc_init(ADC, sysclk_get_main_hz(), 1000000, 8);
		adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
		adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_10);
		adc_enable_channel(ADC, ADC_CHANNEL_7);
		adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
	}
	
	return 0;
}

uint16_t analog_read(int pinNumber)
{
	adc_start(ADC);
	delay_ms(1);
	uint16_t result = 1;
	if(pinNumber == 0)
	{
		result = adc_get_channel_value(ADC, ADC_CHANNEL_7);
	}
	return result;
}