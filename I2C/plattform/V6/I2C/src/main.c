#include <asf.h>
#include "I2CFunctions.h"
#include "test.h"
#include "task_i2c.h"

int main (void)
{
	sysclk_init();
	board_init();
	delay_init();
	console_init();
	
	if(init_twi())
	{
		xTaskCreate(task1, (const signed char * const) "task1", TASK_I2C_STACK_SIZE, NULL, TASK_I2C_PRIORITY, NULL);
		vTaskStartScheduler();
		
		
		/* Olika testfall fr�n testprotokollet "I2C - Flera slaves" */
			//test_fs_1();
			//test_fs_2();
			//test_fs_3();
			//test_fs_4();
			//test_fs_5();
			//test_fs_6();
			//test_fs_7();
			//test_fs_8();
			//test_fs_9();
		/* -------------------------------------------------------- */
		
		
		/* Olika testfall fr�n testprotokollet "I2C" */
			//test_s_1();
			//test_s_2();
			//test_s_3();
			//test_s_4();
			//test_s_5();
			//test_s_6();
			//test_s_7();
		/* ----------------------------------------- */
		
	}	
}
