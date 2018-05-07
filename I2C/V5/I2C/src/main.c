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
		test_fs_8();
		//test_fs_9();
		
		/* Olika testfall från testprotokollet "I2C" */
		//test_s_1();
 		//test_s_2();
 		//test_s_3();
		//test_s_4();
        //test_s_5();
 		//test_s_6();
		//test_s_7();
			
		/* Testa random saker */
		//read_package(TWI_SLAVE_ADR_POS);
		//send_package(LED_OFF, TWI_SLAVE_ADR_PAB);
	}
	
}
