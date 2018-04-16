#ifndef INIT_MAIN_H_
#define INIT_MAIN_H_

int misc_init (void);	/* initializes system clock, board and console. */
int rtos_init (void);	/* initializes FreeRTOS by creating a number of tasks and starting the scheduler. */
int console_init(void); /* initializes console */

#endif /* INIT_MAIN_H_ */