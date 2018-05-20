/*
initializes interrupts, pins, console and RTOS
*/

#include <stdio_serial.h>
#include <asf.h>
#include "conf_board.h"
#include "main_init.h"
#include "tasks/controlCenter.h"
#include "tasks/navigation.h"
#include "tasks/regulator.h"
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
	init_twi();
	ioport_init();
		
		
		ioport_set_pin_dir(pin12, IOPORT_DIR_OUTPUT); //tasktime
		ioport_set_pin_dir(pin13, IOPORT_DIR_OUTPUT); //tasktime
				
		ioport_set_pin_dir(pin5, IOPORT_DIR_INPUT); //Encoder Interrupt
		ioport_set_pin_dir(pin7, IOPORT_DIR_INPUT); //Encoder Interrupt
		ioport_set_pin_dir(pin10, IOPORT_DIR_INPUT); //Encoder Interrupt
		ioport_set_pin_dir(pin33, IOPORT_DIR_INPUT); //Encoder Interrupt

		//BEHÖVS PWM PINNARNA INITLIALISERAS SOM PWM?
		
		//VAD ANVÄNDS DESSA TILL?
		//ioport_set_pin_dir(pin8, IOPORT_DIR_INPUT); 
		//ioport_set_pin_dir(pin34, IOPORT_DIR_INPUT);
		//ioport_set_pin_dir(pin2, IOPORT_DIR_OUTPUT);
	
	
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
	xTaskCreate(regulator, (const signed char * const) "regulator", TASK_REG_STACK_SIZE, NULL, TASK_REG_PRIORITY, NULL);
	xTaskCreate(navigation, (const signed char * const) "navigation", TASK_NAV_STACK_SIZE, NULL, TASK_NAV_PRIORITY, NULL);
	xTaskCreate(controlCenter, (const signed char * const) "controlCenter", TASK_CC_STACK_SIZE, NULL, TASK_CC_PRIORITY, NULL);
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

int interrupt_init(void) 
{
	//pmc_enable_periph_clk(ID_PIOC);
	
	/* Interrupt 1 */ 
	//pio_set_input(PIOC, pin8, NULL);
	//pio_handler_set(PIOC, ID_PIOC, pin8, PIO_IT_RE_OR_HL, ISR1);
	//pio_handler_set(PIOC, ID_PIOC, pin8, PIO_IT_EDGE, ISR1);
	//pio_enable_interrupt(PIOC, pin8);
	/* ------------ */
	
	/* Interrupt 2 */ 
	//pio_set_input(PIOC, pin7, PIO_PULLUP);
	//pio_set_input(PIOC, pin7, NULL);
	//pio_handler_set(PIOC, ID_PIOC, pin7, PIO_IT_EDGE, ISR2);
	//pio_enable_interrupt(PIOC, pin7);
	/* ------------ */
	
	
		pmc_enable_periph_clk(ID_PIOC);
		
		/* Initializes interrupt pin for the right encoder A, trigger on rise edge, pin7*/
		pio_set_input(PIOC,pin7i,NULL);
		pio_handler_set(PIOC,ID_PIOC,pin7i,PIO_IT_RE_OR_HL,rightEncoderAISR);
		pio_enable_interrupt(PIOC,pin7i); //digital pin 7

		/* Initializes interrupt pin for the left encoder A, trigger on rise edge, pin5*/
		pio_set_input(PIOC,pin5i,NULL);
		pio_handler_set(PIOC, ID_PIOC,pin5i,PIO_IT_RE_OR_HL, leftEncoderAISR);
		pio_enable_interrupt(PIOC,pin5i); //digital pin 5

		/* Initializes interrupt pin for the left encoder B, trigger on rise edge, pin8*/
		pio_set_input(PIOC,pin33,NULL);
		pio_handler_set(PIOC, ID_PIOC,pin33,PIO_IT_RE_OR_HL, rightEncoderBISR);
		pio_enable_interrupt(PIOC,pin33); //digital pin 33

		/* Initializes interrupt pin for the right encoder B, trigger on rise edge, pin10*/
		pio_set_input(PIOC,pin10i,NULL);
		pio_handler_set(PIOC,ID_PIOC,pin10i,PIO_IT_RE_OR_HL,leftEncoderBISR);
		pio_enable_interrupt(PIOC,pin10i); //digital pin 10
		
		NVIC_EnableIRQ(PIOC_IRQn);
	
	return 0;
}



