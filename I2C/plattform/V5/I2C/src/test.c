/*
* test.c
*
* Created: 2018-05-03 11:43:01
*  Author: Benji
*/

#include <asf.h>
#include "test.h"
#include "I2CFunctions.h"



/************************************************************************/
/*							  TEST TVÅ SLAVAR                           */
/************************************************************************/
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
	bool sent_to_pos = send_package(NULL, TWI_SLAVE_ADR_POS) == DATA_SENT;
	bool sent_to_pab = send_package(NULL, TWI_SLAVE_ADR_PAB) == DATA_SENT;
	if(sent_to_pos && sent_to_pab)
		printf("test_fs_7() = PASSED");
	else
		printf("test_fs_7() = NOT PASSED");
}

void test_fs_8()
{
	bool ok = 1;
	while(ok) 
	{
		printf("Test package from Påbyggnad:\n");
		bool rec_package_pab = read_package(TWI_SLAVE_ADR_PAB);
		delay_ms(3000);
		printf("Test package from Positionering:\n");
		bool rec_package_pos = read_package(TWI_SLAVE_ADR_POS);
		delay_ms(3000);
		if(!rec_package_pos || !rec_package_pab) 
			ok = 0;
	}
	printf("test_fs_8 not passed");
}

void test_fs_9()
{
	uint8_t counter = 0;
	while(counter<20)
	{
		//send_package(data_01,TWI_SLAVE_ADR_POS);
		counter++;
	}
}


/************************************************************************/
/*							  TEST EN SLAV                              */
/************************************************************************/
void test_s_1()
{
	if (send_package(LED_ON,TWI_SLAVE_ADR_PAB))
	printf("test_fs_9() = PASSED");
	else
	printf("test_s_1() = NOT PASSED");
}

void test_s_2()
{
	uint8_t counter=0;
	while(counter<20)
	{
		send_package(LED_ON,TWI_SLAVE_ADR_PAB);
		delay_ms(3000);
		send_package(LED_OFF,TWI_SLAVE_ADR_PAB);
		delay_ms(3000);
	}
	printf("test_fs_9() = PASSED");
}

void test_s_3()
{
	if (send_package(SERVO_CLOCKWISE,TWI_SLAVE_ADR_PAB)== DATA_SENT)
		printf("test_s_3() = PASSED");
	else
		printf("test_s_3() = NOT PASSED");
}

void test_s_4()
{
	if (send_package(SERVO_ANTI_CLOCKWISE,TWI_SLAVE_ADR_PAB)== DATA_SENT)
		printf("%s", "test_s_4() = PASSED");
	else
		printf("test_s_4() = NOT PASSED");
}

void test_s_5()
{
	send_package(SERVO_CLOCKWISE,TWI_SLAVE_ADR_PAB);
	delay_ms(3000);
	send_package(SERVO_STOP,TWI_SLAVE_ADR_PAB);
}

void test_s_6()
{
	if (read_package(TWI_SLAVE_ADR_PAB)==DATA_READ)
		printf("test_s_6() = PASSED");
	else
		printf("test_s_6() = NOT PASSED");
}

void test_s_7()
{
	if (read_package(TWI_SLAVE_ADR_PAB)==DATA_READ)
		printf("test_s_7() = PASSED");
	else
		printf("test_s_7() = NOT PASSED");
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