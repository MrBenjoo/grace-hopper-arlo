/*
 * motorController.c
 *
 * Created: 2018-04-18 13:01:59
 *  Author: filip
 */ 
 #include <asf.h>
 #include <stdio.h>

 void drive(int rSpeed, int lSpeed, int rDirection, int lDirection) { //speed 0-100, direction -1,1
	int rMotorSpeed = (1500 + 7 * rSpeed * rDirection);
	int lMotorSpeed = (1500 + 7 * lSpeed * lDirection);
	
	ioport_set_pin_level(PIO_PB27_IDX, HIGH);
	delay_us(rMotorSpeed);
	ioport_set_pin_level(PIO_PB27_IDX, LOW);
	delay_us(1100);
	ioport_set_pin_level(PIO_PB27_IDX, HIGH);
	delay_us(lMotorSpeed);
	ioport_set_pin_level(PIO_PB27_IDX, LOW);
	delay_us(5250);
}