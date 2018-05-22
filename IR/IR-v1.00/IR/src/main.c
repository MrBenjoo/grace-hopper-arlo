#include <asf.h>
#include "ADC/adcFunctions.h"
#include "IR/IRFunctions.h"
#include "Console/consoleFunctions.h"

#define A0 0

int main (void)
{
	sysclk_init();
	board_init();
	delay_init();
	console_init();
	printf("analog_init\n");
	analog_init(A0);
	uint16_t adc_value = 0;
	int distance = 0;
	
	while (1)
	{
		/* For-loopen används för att ge ett pålitligare värde */
		for(int i = 0; i < 11; i++)
		{
			adc_value += analog_read(A0);
		}
		adc_value  = adc_value/10; /* ta medelvärdet */
	
		distance = ir_get_distance(adc_value);
		printf("%i\n", distance);
	}
}
