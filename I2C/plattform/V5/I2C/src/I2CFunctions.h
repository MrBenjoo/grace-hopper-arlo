/*
* I2CFunctions.h
*
* Created: 2018-05-01 16:16:01
*  Author: Benji
*/

#ifndef I2CFUNCTIONS_H_
#define I2CFUNCTIONS_H_

#define TWI_SLAVE_ADR_PAB 8			/* The address of uno (påbyggnad) */
#define TWI_SLAVE_ADR_POS 0x10		/* The address of mega (positionering) */

/* -------- MOCKUP TEST --------*/
#define LED_ON					1
#define LED_OFF					2
#define SERVO_CLOCKWISE			3
#define SERVO_ANTI_CLOCKWISE	4
#define SERVO_STOP				5
/*------------------------------*/

/*   Return values   */
#define DATA_SENT     1
#define DATA_READ     1
#define DATA_NOT_SENT 0
#define DATA_NOT_READ 0
/* ----------------- */

/* Functions */
uint8_t init_twi(void);
uint8_t send_package(uint8_t data, uint8_t slave);
uint8_t twi_send(uint8_t data_arr[], twi_packet_t packet, uint8_t slave);
uint8_t read_package(uint8_t slave);
uint8_t twi_read(uint8_t rec_data[], uint8_t data_length, twi_packet_t packet_rec);
/* -------- */

#endif /* I2CFUNCTIONS_H_ */