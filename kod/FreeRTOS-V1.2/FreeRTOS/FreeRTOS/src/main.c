#include "initializations/main_init.h"

int main (void)
{
	misc_init();
	console_init();
	interrupt_init();		
	rtos_init();
}