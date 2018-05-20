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

/* Packet related */
#define TWI_DEF_SPEED				100000			    /* Default I2C transfer speed */
#define TWI_SLAVE_MEM_ADDR			0x00				/* 0 = general call address (reserved), addresses all devices on the bus */
#define TWI_PORT					TWI1				/* Use SDA 20 and SCL 21 on Arduino Due because they provide pull ups */

#define TWI_DATA_SEND_LENGTH_PA		1					/* The length of the package that is sent to påbyggnad */
#define TWI_DATA_SEND_LENGTH_POS	1					/* The length of the package that is sent to positionering */
#define TWI_DATA_REC_LENGTH_PA		1					/* The length of the package that is received from påbyggnad */
#define TWI_DATA_REC_LENGTH_POS		10					/* The length of the package that is received from positionering */

extern uint8_t send_data_pab[TWI_DATA_SEND_LENGTH_PA];		/* stores the data which will be sent to påbyggnad */
extern uint8_t send_data_pos[TWI_DATA_SEND_LENGTH_POS];		/* stores the data which will be sent to positionering */
extern uint8_t rec_data_pab[TWI_DATA_REC_LENGTH_PA];		/* stores the data which will be received from påbyggnad */
extern uint8_t rec_data_pos[TWI_DATA_REC_LENGTH_POS];		/* stores the data which will be received from positionering */

#endif /* I2CFUNCTIONS_H_ */