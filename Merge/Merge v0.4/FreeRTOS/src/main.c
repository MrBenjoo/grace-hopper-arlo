#include "initializations/main_init.h"
#include <asf.h>

/*
Author: Group Grace Hopper

When RTOS is initiated the code in main will no longer be run. 
The RTOS task ControlCenter will take precedence.
*/
int main (void)
{
	misc_init(); //initiate interrupts, pins, console and RTOS		
}

//KOM IH�G ATT AVKOMMENTERA FR�N CONFIG N�R VI L�GGER TILL BIBLIOTEKET F�R TVi