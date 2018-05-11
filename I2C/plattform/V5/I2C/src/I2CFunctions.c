/*
* I2CFunctions.c
*
* Created: 2018-05-01 16:15:46
*  Author: Benji
*/

#include <asf.h>
#include "I2CFunctions.h"


/*-------------- Packet related ------------*/
#define TWI_DEF_SPEED				100000			    /* Default I2C transfer speed */
#define TWI_SLAVE_MEM_ADDR			0x00				/* 0 = general call address (reserved), addresses all devices on the bus */
#define TWI_PORT					TWI1				/* Use SDA 20 and SCL 21 on Arduino Due because they provide pull ups */

#define TWI_DATA_SEND_LENGTH_PA		1					/* The length of the package that is sent to p�byggnad */
#define TWI_DATA_SEND_LENGTH_POS	1					/* The length of the package that is sent to positionering */
#define TWI_DATA_REC_LENGTH_PA		1					/* The length of the package that is received from p�byggnad */
#define TWI_DATA_REC_LENGTH_POS		10					/* The length of the package that is received from positionering */

uint8_t send_data_pab[TWI_DATA_SEND_LENGTH_PA]	= {};	/* stores the data which will be sent to p�byggnad */
uint8_t send_data_pos[TWI_DATA_SEND_LENGTH_POS] = {};	/* stores the data which will be sent to positionering */
uint8_t rec_data_pab[TWI_DATA_REC_LENGTH_PA]	= {};	/* stores the data which will be received from p�byggnad */
uint8_t rec_data_pos[TWI_DATA_REC_LENGTH_POS]	= {};	/* stores the data which will be received from positionering */


/* ---------- Packets to send ---------- */
twi_package_t packet_pab = {
	.addr[0]		= TWI_SLAVE_MEM_ADDR,				/* TWI slave memory address data (Most significant bit) */
	.addr[1]		= 0,								/* Least significant bit */
	.addr_length	= 0,								/* Length of the TWI data address segment (1-3 bytes) (TWI slave memory address data size) */
	.chip			= TWI_SLAVE_ADR_PAB,				/* Slave address to communicate with */
	.buffer			= (void *) send_data_pab,			/* Pointer to the data array that we want to send */
	.length			= TWI_DATA_SEND_LENGTH_PA			/* Sets the number of bytes we want to transfer */
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
	.buffer			= (void *) rec_data_pab,		    /* Pointer to the data array which will be filled with the received data */
	.length			= TWI_DATA_REC_LENGTH_PA		    /* Sets the number of bytes we are expected to receive */
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
*  Setup the Arduino due card as the master on pin 20 and 21 (SDA, SCL) with a fixed transfer rate.
*  The function returns 1 if the master was successfully initialized else 0.
*/
uint8_t init_twi(void)
{
	twi_master_options_t opt;
	opt.speed = TWI_DEF_SPEED;
	return twi_master_setup(TWI_PORT, &opt) == TWI_SUCCESS;
}

/*
*	Sends a packet (1 byte) to the slave (uno or mega)
*/
uint8_t send_package(uint8_t data, uint8_t slave)
{
	
	/* Send to P�byggnadsenhet (UNO) */
	if(TWI_SLAVE_ADR_PAB == slave)
	{
		send_data_pab[0] = data;
		
		/* Anv�nds som test f�r att skicka 3 bytes, dock m�ste TWI_DATA_SEND_LENGTH_PA �ndras till 3 */
		/*send_data_pab[0] = 0x05;
		send_data_pab[1] = 0x10;
		send_data_pab[2] = 0x15;*/
		/* --------------------------------------- */
		
		return twi_send(send_data_pab, packet_pab, TWI_SLAVE_ADR_PAB);
	}
	
	/* Send to Positioneringsenhet (MEGA) */
	else if(TWI_SLAVE_ADR_POS == slave)
	{
		send_data_pos[0] = data;
		
		/* Anv�nds som test f�r att skicka 3 bytes, dock m�ste TWI_DATA_SEND_LENGTH_POS �ndras till 3 */
		/*send_data_pos[0] = 0x20;
		send_data_pos[1] = 0x30;
		send_data_pos[2] = 0x40;*/
		/* --------------------------------------- */
		
		return twi_send(send_data_pos, packet_pos, TWI_SLAVE_ADR_POS);
	}
	
	else
		return !TWI_SUCCESS;
}

/*
*  The function "twi_master_write" will NOT return until all data has been written or error occurred.
*  It will return TWI_SUCCESS if all bytes were written, error code otherwise.
*/
uint8_t twi_send(uint8_t data_arr[], twi_packet_t packet, uint8_t slave)
{
	packet.chip = slave;
	packet.buffer = (void *)data_arr;
	if(twi_master_write(TWI_PORT, &packet) == TWI_SUCCESS)
		return DATA_SENT;
	else
		return DATA_NOT_SENT;
}


uint8_t read_package(uint8_t slave)
{
	if (slave == TWI_SLAVE_ADR_PAB)
		return twi_read(rec_data_pab, TWI_DATA_REC_LENGTH_PA, packet_rec_pab);
	else if (slave == TWI_SLAVE_ADR_POS)
		return twi_read(rec_data_pos, TWI_DATA_REC_LENGTH_POS, packet_rec_pos);
	else
		return !TWI_SUCCESS;
}

uint8_t twi_read(uint8_t rec_data[], uint8_t data_length, twi_packet_t packet_rec)
{
	if(twi_master_read(TWI_PORT, &packet_rec) == TWI_SUCCESS)
	{
		for(int i = 0; i < data_length; i++)
			printf("%i\n", rec_data[i]);
		return DATA_READ;
	}
	else
		return DATA_NOT_READ;
}