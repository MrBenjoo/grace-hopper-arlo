/*
initializes various shit
*/

#include <stdio_serial.h>
#include <asf.h>
#include "conf_board.h"
#include "main_init.h"
#include "tasks/task1/task1.h"
#include "tasks/task2/task2.h"

/*
* Function: misc_init
* -------------------
* initializes system clock & board.
*/
int misc_init (void)
{
	sysclk_init();
	board_init();
	
	/* Used only for testing purposes. You can remove the code below if you want */
	ioport_init();
	ioport_set_pin_dir(PIO_PB27_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(PIO_PD8_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PB27_IDX, LOW);
	ioport_set_pin_level(PIO_PD8_IDX, LOW);
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
	xTaskCreate(task2, (const signed char * const) "task2", TASK_2_STACK_SIZE, NULL, TASK_2_PRIORITY, NULL);
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
