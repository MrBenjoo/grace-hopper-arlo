/*
 * test.c
 *
 * Created: 2018-05-03 11:43:01
 *  Author: Benji
 */ 

#include <asf.h>
#include "test.h"
#include "I2CFunctions.h"

void test_fs_1(void)
{
	send_package(LED_ON,TWI_SLAVE_ADR_PAB);
	send_package(LED_ON,TWI_SLAVE_ADR_POS);
}

void test_fs_2(void)
{
	while(1)
	{
		send_package(LED_ON, TWI_SLAVE_ADR_PAB);
		send_package(LED_OFF, TWI_SLAVE_ADR_POS );
		delay_ms(3000);
		send_package(LED_OFF, TWI_SLAVE_ADR_PAB);
		send_package(LED_ON, TWI_SLAVE_ADR_POS);
		delay_ms(3000);
	}
}

void test_fs_3()
{
	if(send_package(NULL,TWI_SLAVE_ADR_PAB) == DATA_SENT) 
		printf("test_fs_3() = PASSED");
	else
		printf("test_fs_3() = NOT PASSED");
}

void test_fs_4()
{
	if(send_package(NULL,TWI_SLAVE_ADR_POS) == DATA_SENT)
		printf("test_fs_4() = PASSED");
	else
		printf("test_fs_4() = NOT PASSED");
}

void test_fs_5()
{
	if(send_package(LED_ON,TWI_SLAVE_ADR_PAB) == DATA_SENT)
		printf("test_fs_5() = NOT PASSED");
	else
		printf("test_fs_5() = PASSED");
}

void test_fs_6()
{
	if(send_package(LED_ON,TWI_SLAVE_ADR_POS) == DATA_SENT) 
		printf("test_fs_6() = NOT PASSED");
	else
		printf("test_fs_6() = PASSED");
}

void test_fs_7()
{
	if(send_package(LED_ON,TWI_SLAVE_ADR_POS) == DATA_SENT)
		printf("test_fs_7() = PASSED");
	else
		printf("test_fs_7() = NOT PASSED");
}
void test_fs_8()
{
	if(send_package(LED_ON,TWI_SLAVE_ADR_PAB) == DATA_SENT)
	printf("test_fs_8() = PASSED");
	else
	printf("test_fs_8() = NOT PASSED");
}
void test_fs_9()
{
	
}

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