/*
initializes various shit
*/

#include <stdio_serial.h>
#include <asf.h>
#include "conf_board.h"
#include "main_init.h"
#include "tasks/task1/task1.h"
#include "tasks/task2/task2.h"
#include "../taskPOS.h"
#include "../interrupt/ISR.h"
#include "pins_init.h"
#include "../encoderISR.h"
#include "../I2C/I2CFunctions.h"

/*
* Function: misc_init
* -------------------
* initializes system clock & board.
*/
int misc_init (void)
{	
	
	
	sysclk_init();
	board_init();
	console_init();
	interrupt_init();
	encoder_init();
	init_twi();
	/* ------------------------------------------------------------------------- */
	ioport_init();
	//ioport_set_pin_dir(pin13, IOPORT_DIR_OUTPUT); /* used in task1 as I/O interrupt pin*/
	//ioport_set_pin_dir(pin12, IOPORT_DIR_OUTPUT); /* used in task2 as I/O interrupt pin*/
	
	//ioport_set_pin_dir(pin11, IOPORT_DIR_OUTPUT); /* used for code inside interrupt 1 */
	//ioport_set_pin_dir(pin10, IOPORT_DIR_OUTPUT); /* used for code inside interrupt 2*/
		
		ioport_set_pin_dir(pin2, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(pin5, IOPORT_DIR_INPUT); 
		ioport_set_pin_dir(pin7, IOPORT_DIR_INPUT);
		ioport_set_pin_dir(pin8, IOPORT_DIR_INPUT);
		ioport_set_pin_dir(pin10, IOPORT_DIR_INPUT);
		ioport_set_pin_dir(pin33, IOPORT_DIR_INPUT);
	
	//ioport_set_pin_level(pin13, LOW); 
	//ioport_set_pin_level(pin12, LOW);
	/* ------------------------------------------------------------------------- */
	
	return 0;
}

/*
* Function: rtos_init
* -------------------
* initializes FreeRTOS by creating a number of tasks and starting the scheduler.
*/
int rtos_init (void)
{
	/* -------------------------------- Used for testing purposes ------------------------------------- */
	xTaskCreate(task1, (const signed char * const) "task1", TASK_1_STACK_SIZE, NULL, TASK_1_PRIORITY, NULL);
	xTaskCreate(taskPOS, (const signed char * const) "taskPOS", TASK_POS_STACK_SIZE, NULL, TASK_POS_PRIORITY, NULL);
	//xTaskCreate(task2, (const signed char * const) "task2", TASK_2_STACK_SIZE, NULL, TASK_2_PRIORITY, NULL);
	/* ------------------------------------------------------------------------------------------------ */
	
	vTaskStartScheduler();
	return 0;
}

/*
* Function: console_init
* -------------------
* Enables feedback through the USB-cable back to terminal within Atmel Studio.
* Note that the baudrate, parity and other parameters must be set in conf/conf_uart_serial.h
*/
int console_init(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	
	printf("Console ready\n");
	printf("=============\n");
	return 0;
}

/* author Gustav Dahlman */
int interrupt_init(void) 
{
	pmc_enable_periph_clk(ID_PIOC);
	
	/* Interrupt 1 */ 
	pio_set_input(PIOC, pin8, NULL);
	//pio_handler_set(PIOC, ID_PIOC, pin8, PIO_IT_RE_OR_HL, ISR1);
	pio_handler_set(PIOC, ID_PIOC, pin8, PIO_IT_EDGE, ISR1);
	pio_enable_interrupt(PIOC, pin8);
	/* ------------ */
	
	/* Interrupt 2 */ 
	//pio_set_input(PIOC, pin7, PIO_PULLUP);
	pio_set_input(PIOC, pin7, NULL);
	pio_handler_set(PIOC, ID_PIOC, pin7, PIO_IT_EDGE, ISR2);
	pio_enable_interrupt(PIOC, pin7);
	/* ------------ */
	
	NVIC_EnableIRQ(PIOC_IRQn);
	
	return 0;
}


