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
#include "pio.h"
#include "pio_handler.h"
#include "interruptz.h"
#define pinA0 PIO_PA16
#define pinD13 PIO_PB27 


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	pmc_enable_periph_clk(ID_PIOA); 
	pio_set_input(PIOA, PIO_PA16,NULL); 
	pio_handler_set(PIOA, ID_PIOA, PIO_PA16, PIO_IT_RE_OR_HL, myISR); 
	pio_enable_interrupt(PIOA, PIO_PA16); 
	NVIC_EnableIRQ(PIOA_IRQn);
	
 
	delay_init();
	ioport_init();
	ioport_set_pin_dir(PIO_PB27_IDX,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PB27_IDX,LOW);
	
	while(1){
	
	}
	
	

	/* Insert application code here, after the board has been initialized. */
}

