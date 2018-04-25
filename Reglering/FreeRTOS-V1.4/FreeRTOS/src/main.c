#include "initializations/main_init.h"
#include "Reglering/Reglering.h"
#include "encoderISR.h"
#include <asf.h>

int main (void)
{
	sysclk_init();
	board_init();

	ioport_set_pin_dir(PIO_PB25_IDX, IOPORT_DIR_OUTPUT);
	misc_init();
	console_init();
	//interrupt_init();		
	//rtos_init();
	encoder_init();
	delay_us(3000000);
	controlCenter(50);
}