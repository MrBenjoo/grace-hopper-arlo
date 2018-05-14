/*
* task1.c
*
* Created: 2018-05-14 10:51:51
*  Author: Benji
*/

#include <asf.h>
#include "task_i2c.h"
#include "I2CFunctions.h"

#define READ_MODE 1

void task1(void *pvParamters)
{
	uint8_t currentState = 0x22;
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 100/portTICK_RATE_MS;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
		
		switch(currentState)
		{
			case 0x22: // BORJA_PLOCKA
				printf("BORJA_POCKA\n");
				if(send_package(0x22, TWI_SLAVE_ADR_PAB) == DATA_SENT)
					currentState = READ_MODE;
				break;
			
			case 0x25: // LAMNA_AV_OBJEKT
				printf("LAMNA_AV_OBJEKT\n");
				if(send_package(0x25, TWI_SLAVE_ADR_PAB) == DATA_SENT)
					currentState = READ_MODE;
				break;
			
			case 0x14: // LYCKAT_LYFT
				printf("LYCKAT LYFT\n");
				currentState = READ_MODE;
				break;
			
			case 0x15: // MISSLYCKAT_LYFT
				printf("MISSLYCKAT_LYFT\n");
				break;
			
			case 0x16: // LYCKAD_AVLAMNING
				printf("LYCKAD_AVLAMNING\n");
				currentState = READ_MODE;
				break;
			
			case 0x17: // MISSLYCKAD_AVLAMNING
				printf("MISSLYCKAD_AVLAMNING\n");
				break;
			
			case READ_MODE:
				printf("READ_MODE\n");
				if(read_package(TWI_SLAVE_ADR_PAB) == DATA_READ) 
				{
					currentState = rec_data_pab[0];
					printf("currentState after READING = %i\n", currentState);
				}
				else
					printf("FAILED TO READ FROM PAB\n");
				break;
		}
	}
}
