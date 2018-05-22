/*
 * consoleFunctions.c
 *
 * Created: 2018-05-20 23:56:30
 *  Author: Benji
 */ 
#include <asf.h>
#include "consoleFunctions.h"

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