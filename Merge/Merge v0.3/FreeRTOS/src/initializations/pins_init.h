/*
	This header file can be used instead of IOPORT to get access to the digital pins. It will be easier to use
	because you do not to check the pin mappings all the time.
*/
#ifndef PINSINIT_H_
#define PINSINIT_H_

#define pin13 PIO_PB27_IDX
#define pin12 PIO_PD8_IDX
#define pin11 PIO_PD7_IDX
#define pin10 PIO_PA28_IDX
#define pin9  PIO_PC21_IDX
#define pin8  PIO_PC22_IDX
#define pin7  PIO_PC23_IDX
#define pin6  PIO_PC24_IDX
#define pin5  PIO_PC25_IDX
#define pin4  PIO_PC26_IDX
#define pin3  PIO_PC28_IDX
#define pin2  PIO_PB25_IDX
#define pin33  PIO_PC1
#define pin34 PIO_PC2
#define pin5i  PIO_PC25
#define pin7i  PIO_PC23
#define pin8i  PIO_PC22
#define pin10i PIO_PC29
#define PWM_35 IOPORT_CREATE_PIN(PIOC, 3) // pin 35
#define PWM_42 IOPORT_CREATE_PIN(PIOA, 19) // pin 42

#endif /* PINSINIT_H_ */