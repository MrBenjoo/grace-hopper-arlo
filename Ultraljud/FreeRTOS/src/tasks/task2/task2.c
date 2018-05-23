/*
The code in this file was used to test FreeRTOS.
Change the code for your purpose.
*/

#include <asf.h>
#include "task2.h"
#include "../initializations/pins_init.h"

#define xTimeT2 20
#define A0 0
/*
* Function: task2
* -------------------
* Performs an action every xTimeT2 milliseconds
*/
void task2(void *pvParamters)
{
					
	
	analog_init(A0);
	uint16_t adc_value = 0;
	int distance = 0;
	int oldDistans=INT_MAX;
	int check=0;
	
	while (1)
	{
		/* For-loopen används för att ge ett pålitligare värde */
		for(int i = 0; i < 11; i++)
		{
			adc_value += analog_read(A0);
		}
		adc_value  = adc_value/10; /* ta medelvärdet */
		
		distance = ir_get_distance(adc_value);
		if (oldDistans>distance)
		{
		}
		printf("%i\n", distance);
	}
}
