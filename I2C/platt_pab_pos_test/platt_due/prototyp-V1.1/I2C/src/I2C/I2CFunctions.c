/*
* I2CFunctions.c
*
* Created: 2018-05-01 16:15:46
*  Author: Benji
*/

#include <asf.h>
#include "I2CFunctions.h"

/*-------------- Packet related ------------*/
uint8_t send_data_pab[TWI_DATA_SEND_LENGTH_PAB]	= {};	/* stores the data which will be sent to påbyggnad */
uint8_t send_data_pos[TWI_DATA_SEND_LENGTH_POS] = {};	/* stores the data which will be sent to positionering */
uint8_t rec_data_pab[TWI_DATA_REC_LENGTH_PAB]	= {};	/* stores the data which will be received from påbyggnad */
uint8_t rec_data_pos[TWI_DATA_REC_LENGTH_POS]	= {};	/* stores the data which will be received from positionering */

/* ---------- Packets to send ---------- */
twi_package_t packet_pab = {
	.addr[0]		= TWI_GENERAL_CALL_ADDRESS,			/* TWI general call address (Most significant bit) */
	.addr[1]		= 0,								/* Least significant bit */
	.addr_length	= 0,								/* Length of the TWI data address segment (1-3 bytes) (TWI slave memory address data size) */
	.chip			= TWI_SLAVE_ADR_PAB,				/* Slave address to communicate with */
	.buffer			= (void *) send_data_pab,			/* Pointer to the data array that we want to send */
	.length			= TWI_DATA_SEND_LENGTH_PAB			/* Sets the number of bytes we want to transfer */
};

twi_package_t packet_pos = {
	.addr[0]		= TWI_GENERAL_CALL_ADDRESS,
	.addr[1]		= 0,
	.addr_length	= 0,
	.chip			= TWI_SLAVE_ADR_POS,
	.buffer			= (void *) send_data_pos,
	.length			= TWI_DATA_SEND_LENGTH_POS
};
/* ------------------------------------ */

/* ---------- Packets to receive ---------- */
twi_package_t packet_rec_pab = {
	.addr[0]		= TWI_GENERAL_CALL_ADDRESS,
	.addr[1]		= 0,
	.addr_length	= 0,
	.chip			= TWI_SLAVE_ADR_PAB,
	.buffer			= (void *) rec_data_pab,		    /* Pointer to the data array which will be filled with the received data */
	.length			= TWI_DATA_REC_LENGTH_PAB		    /* Sets the number of bytes we are expected to receive */
};

twi_package_t packet_rec_pos = {
	.addr[0]		= TWI_GENERAL_CALL_ADDRESS,
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
	/* Send to Påbyggnadsenhet (UNO) */
	if(TWI_SLAVE_ADR_PAB == slave)
	{
		send_data_pab[0] = data;
		return twi_send(send_data_pab, packet_pab, TWI_SLAVE_ADR_PAB);
	}
	
	/* Send to Positioneringsenhet (MEGA) */
	else if(TWI_SLAVE_ADR_POS == slave)
	{
		send_data_pos[0] = data;
		return twi_send(send_data_pos, packet_pos, TWI_SLAVE_ADR_POS);
	}
	
	/* Send failed */
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
		return (twi_master_read(TWI_PORT, &packet_rec_pab) == TWI_SUCCESS);
	else
		return (twi_master_read(TWI_PORT, &packet_rec_pos) == TWI_SUCCESS);
}
