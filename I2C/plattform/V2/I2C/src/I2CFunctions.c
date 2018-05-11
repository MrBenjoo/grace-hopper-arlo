/*
 * I2CFunctions.c
 *
 * Created: 2018-05-01 16:15:46
 *  Author: Benji
 */

#include <asf.h>
#include "I2CFunctions.h"


/*-------------- Definitions ---------------*/
#define TWI_SPEED					100000						
#define TWI_SLAVE_MEM_ADDR			0x00						
#define TWI_PORT					TWI1
#define TWI_DATA_SEND_LENGTH_PA		1
#define TWI_DATA_SEND_LENGTH_POS	1
/*------------------------------------------*/						


/*-------------- Packet related ------------*/
uint8_t send_data_pab[TWI_DATA_SEND_LENGTH_PA] = {};		/* stores the data which will be sent to UNO */
uint8_t send_data_pos[TWI_DATA_SEND_LENGTH_POS] = {};		/* stores the data which will be sent to MEGA */

twi_package_t packet_pab = {
	.addr[0]		= TWI_SLAVE_MEM_ADDR,					/* TWI slave memory address data (Most significant bit) */
	.addr[1]		= 0,									/* Least significant bit */
	.addr_length	= 0,									/* Length of the TWI data address segment (1-3 bytes) (TWI slave memory address data size) */
	.chip			= TWI_SLAVE_ADR_PAB,					/* TWI chip address to communicate with (TWI slave bus address) */
	.buffer			= (void *) send_data_pab,				/* transfer data source buffer (pointer on the data to write to slave) */
	.length			= TWI_DATA_SEND_LENGTH_PA				/* How many bytes do we want to transfer (bytes) */
};

twi_package_t packet_pos = {
	.addr[0]		= TWI_SLAVE_MEM_ADDR,					
	.addr[1]		= 0,									
	.addr_length	= 0,									
	.chip			= TWI_SLAVE_ADR_POS,					
	.buffer			= (void *) send_data_pos,				
	.length			= TWI_DATA_SEND_LENGTH_POS				
};
/*------------------------------------------*/


/*
 *	Initialize the master to the TWI1 port and set the speed to default.
 */
uint8_t init_twi(void)
{
	twi_master_options_t opt;
	opt.speed = TWI_SPEED;
	if(twi_master_setup(TWI_PORT, &opt) == TWI_SUCCESS) 
	{
		printf("MASTER SETUP OK\n");
		return 1;
	}
	else
	{
		printf("MASTER SETUP NOT OK\n");
		return 0;
	}
		
}

/*
 *	Sends a packet (1 byte) to the slave (uno or mega)
 *  twi_master_write will NOT return until all data has been written or error occurred.
 *  It will return TWI_SUCCESS if all bytes were written, error code otherwise.
 */
uint8_t send_package(uint8_t data, uint8_t slave)
{
	/* Påbyggnadsenhet (UNO) */
	if(TWI_SLAVE_ADR_PAB == slave)
	{
		send_data_pab[0] = data;
		packet_pab.chip = slave;
		packet_pab.buffer = (void *)send_data_pab;
		if(twi_master_write(TWI_PORT, &packet_pab) == TWI_SUCCESS)
		{
			printf("package sent\n");
			return DATA_SENT;
		} 
		else 
		{
			printf("package not sent\n");
			return DATA_NOT_SENT;
		}
		
	}
	/* Positioneringsenhet (MEGA */
	else if(TWI_SLAVE_ADR_POS == slave)
	{
		send_data_pos[0] = data;
		packet_pos.chip = slave;
		packet_pos.buffer = (void *)send_data_pos;
		if(twi_master_write(TWI_PORT, &packet_pos) == TWI_SUCCESS) 
		{
			printf("package sent\n");
			return DATA_SENT;
		}
		else 
		{
			printf("package not sent\n");
			return DATA_NOT_SENT;
		}	
	}
}
