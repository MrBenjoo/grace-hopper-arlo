/*
 * I2CFunctions.h
 *
 * Created: 2018-05-01 16:16:01
 *  Author: Benji
 */ 

#ifndef I2CFUNCTIONS_H_
#define I2CFUNCTIONS_H_

#define TWI_SLAVE_PABYGGNAD 8

void init_twi(void);
void send_package(uint8_t data, uint8_t slave);

#endif /* I2CFUNCTIONS_H_ */