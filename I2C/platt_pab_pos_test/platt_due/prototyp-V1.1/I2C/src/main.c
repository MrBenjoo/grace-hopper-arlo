#include <asf.h>
#include "I2C/I2CFunctions.h"
#include "tasks/taskPAB.h"
#include "tasks/taskPOS.h"
#include "console/console.h"

int main (void)
{
	sysclk_init();
	board_init();
	console_init();
	printf("startup");
	if(init_twi())
	{
		xTaskCreate(taskPOS, (const signed char * const) "taskPOS", TASK_POS_STACK_SIZE, NULL, TASK_POS_PRIORITY, NULL);
		//xTaskCreate(taskPAB, (const signed char * const) "taskPAB", TASK_PAB_STACK_SIZE, NULL, TASK_PAB_PRIORITY, NULL);
		vTaskStartScheduler();
	}
}
