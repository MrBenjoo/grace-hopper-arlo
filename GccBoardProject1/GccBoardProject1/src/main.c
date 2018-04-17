/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#define P22 IOPORT_CREATE_PIN(PIOC, 22)

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	sysclk_init();
	board_init();

	ioport_set_pin_dir(PIO_PB27_IDX, IOPORT_DIR_OUTPUT);
	while(1) {
		//delay_s(1);
		ioport_set_pin_level(PIO_PB27_IDX, HIGH);
		delay_us(800);
		ioport_set_pin_level(PIO_PB27_IDX, LOW);
		delay_us(1500);
		ioport_set_pin_level(PIO_PB27_IDX, HIGH);
		delay_us(800);
		ioport_set_pin_level(PIO_PB27_IDX, LOW);
		delay_us(5500);
	}
	
	

	/* Insert application code here, after the board has been initialized. */
}
