/*
 * I2CFunctions.h
 *
 * Created: 2018-05-01 16:16:01
 *  Author: Benji
 */ 

#ifndef I2CFUNCTIONS_H_
#define I2CFUNCTIONS_H_

#define TWI_SLAVE_ADR_PAB 8
#define TWI_SLAVE_ADR_POS 9

/* Commands to send to the slave */
#define LED_ON					1
#define LED_OFF					2
#define SERVO_CLOCKWISE			3
#define SERVO_ANTI_CLOCKWISE	4
#define SERVO_STOP				5
/*-------------------------------*/

#define DATA_SENT     1
#define DATA_NOT_SENT 0

uint8_t init_twi(void);
uint8_t send_package(uint8_t data, uint8_t slave);

#endif /* I2CFUNCTIONS_H_ */