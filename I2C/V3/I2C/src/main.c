#include <asf.h>
#include "I2CFunctions.h"
#include "test.h"

int main (void)
{
	sysclk_init();
	board_init();
	delay_init();
	console_init();
	
	if(init_twi())
	{
		
		/* Olika testfall från testprotokollet "I2C med FreeRTOS" */
			// TODO
		
		/* Olika testfall från testprotokollet "I2C - Flera slaves" */
		//test_fs_1();
		//test_fs_2();
		//test_fs_3();
		//test_fs_4();
		//test_fs_5();
		//test_fs_6();
		//test_fs_7();
		//test_fs_8();
		//test_fs_9();
			
			read_package(TWI_SLAVE_ADR_PAB);
	}
	
}
