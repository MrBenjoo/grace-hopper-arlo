/*
 * I2CFunctions.c
 *
 * Created: 2018-05-01 16:15:46
 *  Author: Benji
 */

#include <asf.h>
#include "I2CFunctions.h"

#define TWI_SPEED					100000						
#define TWI_SLAVE_MEM_ADDR			0x00						
#define TWI_MASTER_PAB				TWI1
#define TWI_DATA_SEND_LENGTH_PA		1						

uint8_t send_data_pab[TWI_DATA_SEND_LENGTH_PA] = {};			// Datan som skickas till påbyggnaden

twi_package_t packet_pab = {
	.addr[0]		= TWI_SLAVE_MEM_ADDR,						// TWI slave memory address data (Most significant bit)
	.addr[1]		= 0,										// a ‘zero’ indicates a transmission (WRITE), a ‘one’ indicates a request for data (READ) (Least significant bit)
	.addr_length	= 0,										// Length of the TWI data address segment (1-3 bytes) (TWI slave memory address data size)
	.chip			= TWI_SLAVE_PABYGGNAD,						// TWI chip address to communicate with (TWI slave bus address)
	.buffer			= (void *) send_data_pab,					// transfer data source buffer (pointer on the data to write to slave)
	.length			= TWI_DATA_SEND_LENGTH_PA					// How many bytes do we want to transfer (bytes)
};

void init_twi(void)
{
	twi_master_options_t opt;
	opt.speed = TWI_SPEED;
	twi_master_setup(TWI_MASTER_PAB, &opt);
}

void send_package(uint8_t data, uint8_t slave)
{
	send_data_pab[0] = data;
	packet_pab.chip = slave;
	packet_pab.buffer = (void *)send_data_pab;
	while(twi_master_write(TWI_MASTER_PAB, &packet_pab));
}
