/*
* taskPAB.c
*
* Created: 2018-05-18 13:01:39
*  Author: Benji
*/

#include <asf.h>
#include "taskPAB.h"
#include "../I2C/I2CFunctions.h"
#include "taskHandler.h"


#define BORJA_PLOCKA			0x22	// 34
#define LAMNA_AV_OBJEKT			0x25	// 37
#define LYCKAT_LYFT				0x14	// 20
#define MISSLYCKAT_LYFT			0x15    // 21
#define LYCKAD_AVLAMNING		0x16	// 22
#define MISSLYCKAD_AVLAMNING	0x17	// 23
#define READ_MODE				1
#define DONE					2


void taskPAB(void *pvParamters)
{
	/* Delay stuff */
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 200/portTICK_RATE_MS;     /* set ticks (xTimeT1) in milliseconds */
	xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
	/*-------------*/
	
	uint8_t current_state = BORJA_PLOCKA;
	semaphorePAB = 0;
	vSemaphoreCreateBinary(semaphorePAB);
	xSemaphoreTake(semaphorePAB, 0);
	
	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
		
		if(xSemaphoreTake(semaphorePAB, 0) == pdTRUE)
		{
			switch(current_state)
			{
				case BORJA_PLOCKA:
				if(send_package(BORJA_PLOCKA, TWI_SLAVE_ADR_PAB) == DATA_SENT)
				{
					printf("->sending BORJA_PLOCKA to PAB\n");
					current_state = READ_MODE;
				}
				break;
				
				case READ_MODE:
				if(read_package(TWI_SLAVE_ADR_PAB) == DATA_READ)
				{
					switch(rec_data_pab[0])
					{
						case LYCKAT_LYFT:
						printf("received LYCKAT_LYFT\n");
						current_state = LAMNA_AV_OBJEKT;
						break;
						
						case MISSLYCKAT_LYFT:
						printf("received MISSLYCKAT_LYFT\n");
						current_state = DONE;
						break;
						
						case LYCKAD_AVLAMNING:
						printf("received LYCKAD_AVLAMNING\n");
						current_state = DONE;
						break;
						
						case MISSLYCKAD_AVLAMNING:
					printf("received MISSLYCKAD_AVLAMNING}\n");
					current_state = DONE;
					break;
				}
			}
			break;
			
			case LAMNA_AV_OBJEKT:
			if(send_package(LAMNA_AV_OBJEKT, TWI_SLAVE_ADR_PAB) == DATA_SENT)
			{
				printf("->sending LAMNA_AV_OBJEKT to PAB\n");
				current_state = READ_MODE;
			}
			break;
		}
	}
}
}