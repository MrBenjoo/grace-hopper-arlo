#include <asf.h>

#include "I2CFunctions.h"

int main (void)
{
	sysclk_init();
	board_init();
	init_twi();
	send_package(3,8);
}
