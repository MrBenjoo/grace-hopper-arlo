/*
 * I2CFunctions.h
 *
 * Created: 2018-05-01 16:16:01
 *  Author: Benji
 */ 

#ifndef I2CFUNCTIONS_H_
#define I2CFUNCTIONS_H_

#define TWI_SLAVE_ADR_PAB 8
#define TWI_SLAVE_ADR_POS 0x10
//#define TWI_SLAVE_ADR_POS 8

/* Commands to send to the slave */
#define data_01					10
#define data_02					20
#define data_03					30
#define LED_ON					1
#define LED_OFF					2
#define SERVO_CLOCKWISE			3
#define SERVO_ANTI_CLOCKWISE	4
#define SERVO_STOP				5
/*-------------------------------*/

#define DATA_SENT     1
#define DATA_READ     1

#define DATA_NOT_SENT 0
#define DATA_NOT_READ 0

#define TWI_DATA_REC_LENGTH_POS		10	
#define TWI_DATA_REC_LENGTH_PA     10

 uint8_t rec_data_pos[TWI_DATA_REC_LENGTH_POS];
 uint8_t rec_data_pab[TWI_DATA_REC_LENGTH_PA];


uint8_t init_twi(void);
uint8_t send_package(uint8_t data, uint8_t slave);
uint8_t read_package(uint8_t slave);
uint8_t twi_send(uint8_t data_arr[], uint8_t data, twi_packet_t packet, uint8_t slave);
uint8_t twi_read(uint8_t rec_data[], uint8_t data_length, twi_packet_t packet_rec);



#endif /* I2CFUNCTIONS_H_ */