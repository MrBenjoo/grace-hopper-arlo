/*
 * I2CFunctions.c
 *
 * Created: 2018-05-01 16:15:46
 *  Author: Benji
 */

#include <asf.h>
#include "I2CFunctions.h"


/*-------------- Definitions ---------------*/
#define TWI_SPEED					100000					/* Default I2C transfer speed = 100.000 */						
#define TWI_SLAVE_MEM_ADDR			0x00					
#define TWI_PORT					TWI1					/* Use SDA 20 and SCL 21 on Arduino Due */ 
#define TWI_DATA_SEND_LENGTH_PA		3						/* The length of the package that is sent to PAB */
#define TWI_DATA_SEND_LENGTH_POS	1						/* The length of the package that is sent to POS */
#define TWI_DATA_REC_LENGTH_PA		1						/* The length of the package that is received from PAB */
#define TWI_DATA_REC_LENGTH_POS		10						/* The length of the package that is received from POS */
/*------------------------------------------*/						


/*-------------- Packet related ------------*/
uint8_t send_data_pab[TWI_DATA_SEND_LENGTH_PA]	= {};		/* stores the data which will be sent to UNO */
uint8_t send_data_pos[TWI_DATA_SEND_LENGTH_POS] = {};		/* stores the data which will be sent to MEGA */
uint8_t rec_data_pab[TWI_DATA_REC_LENGTH_PA]	= {};		/* stores the data which will be received from UNO */
uint8_t rec_data_pos[TWI_DATA_REC_LENGTH_POS]	= {};		/* stores the data which will be received from MEGA */


	/* ---------- Packets to send ---------- */
	twi_package_t packet_pab = {
		.addr[0]		= TWI_SLAVE_MEM_ADDR,				/* TWI slave memory address data (Most significant bit) */
		.addr[1]		= 0,								/* Least significant bit */
		.addr_length	= 0,								/* Length of the TWI data address segment (1-3 bytes) (TWI slave memory address data size) */
		.chip			= TWI_SLAVE_ADR_PAB,				/* TWI chip address to communicate with (TWI slave bus address) */
		.buffer			= (void *) send_data_pab,			/* transfer data source buffer (pointer on the data to write to slave) */
		.length			= TWI_DATA_SEND_LENGTH_PA			/* How many bytes do we want to transfer (bytes) */
	};

	twi_package_t packet_pos = {
		.addr[0]		= TWI_SLAVE_MEM_ADDR,					
		.addr[1]		= 0,									
		.addr_length	= 0,									
		.chip			= TWI_SLAVE_ADR_POS,					
		.buffer			= (void *) send_data_pos,				
		.length			= TWI_DATA_SEND_LENGTH_POS				
	};
	/* ------------------------------------ */

	/* ---------- Packets to receive ---------- */
	twi_package_t packet_rec_pab = {
		.addr[0]		= TWI_SLAVE_MEM_ADDR,
		.addr[1]		= 0,
		.addr_length	= 0,
		.chip			= TWI_SLAVE_ADR_PAB,
		.buffer			= (void *) rec_data_pab,
		.length			= TWI_DATA_REC_LENGTH_PA
	};
	
	twi_package_t packet_rec_pos = {
		.addr[0]		= TWI_SLAVE_MEM_ADDR,
		.addr[1]		= 0,
		.addr_length	= 0,
		.chip			= TWI_SLAVE_ADR_POS,
		.buffer			= (void *) rec_data_pos,
		.length			= TWI_DATA_REC_LENGTH_POS
	};
	/* ------------------------------------ */

/* ------------------------------------ */


/*
 *	Setup due as the master
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
 *  The function "twi_master_write" will NOT return until all data has been written or error occurred.
 *  It will return TWI_SUCCESS if all bytes were written, error code otherwise.
 */
uint8_t send_package(uint8_t data, uint8_t slave)
{
	/* Påbyggnadsenhet (UNO) */
	if(TWI_SLAVE_ADR_PAB == slave)
	{
		send_data_pab[0] = data;
		
		/* används för testning */
// 		send_data_pab[0] = data_01;
// 		send_data_pab[1] = data_02;
// 		send_data_pab[2] = data_03;
		/* -------------------- */
		
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
		
		// array, slave, packet
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
	else 
		return !TWI_SUCCESS;
}


uint8_t read_package(uint8_t slave)
{
	if (slave == TWI_SLAVE_ADR_PAB)
	{
		if(twi_master_read(TWI_PORT, &packet_rec_pab) == TWI_SUCCESS) 
		{
			printf("%s", "following shit was successfully read from the MEGA: \n");
			for(int i = 0; i < TWI_DATA_REC_LENGTH_PA; i++)
				printf("%i\n", rec_data_pab[i]);
			return 1;
		}
	}
	else if (slave == TWI_SLAVE_ADR_POS)
	{
		if(twi_master_read(TWI_PORT, &packet_rec_pos) == TWI_SUCCESS)
		{
			printf("%s", "following shit was successfully read from the UNO: \n");
			for(int i = 0; i < TWI_DATA_REC_LENGTH_POS; i++)
				printf("%i\n", rec_data_pos[i]);
			return 1;
		}
	}
	else
		return !TWI_SUCCESS;
}

