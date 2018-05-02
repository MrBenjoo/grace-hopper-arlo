/*
 * motorController.c
 * Sets the speed of each motor (on a 2 wheel motorized robot) separately with one and the same function.
 * Follows the protocoll for speed and direction used with two Parallax HB-25 Motorcontrollers in Mode 2, 
 * using one communication bus for sending pulses to both motorcontrollers. 
 * Created: 2018-04-18 13:01:59
 *  Author: filip,Carl,Sebastian
 */ 
 #include <asf.h>
 #include "../initializations/pins_init.h"
 rSpeed = 0;
 lSpeed = 0;
 rDirection = 0;
 lDirection = 0;
 /*
 Takes speed in percentage 0-100 as input and -1,1 as direction where 1 is forward and -1 is reverse.
 */
 void drive(int rSpeed, int lSpeed, int rDirection, int lDirection) {
	rSpeed = rSpeed;
	lSpeed = lSpeed;
	rDirection = rDirection;
	lDirection = lDirection;
	
	int rMotorSpeed = (1500 + 7 * rSpeed * rDirection);
	int lMotorSpeed = (1500 + 7 * lSpeed * lDirection);
	
	ioport_set_pin_level(pin2, HIGH);
	delay_us(rMotorSpeed);
	ioport_set_pin_level(pin2, LOW);
	delay_us(1100);
	ioport_set_pin_level(pin2, HIGH);
	delay_us(lMotorSpeed);
	ioport_set_pin_level(pin2, LOW);
	delay_us(5250);
}
/*Returns the value of latest speed set for the left motor*/
int getSetLSpeed(){
	printf("Set Speed for Left Motor is: %i\n%%",lSpeed);
	return lSpeed;
}
/*Returns the value of latest speed set for the right motor*/
int getSetRSpeed(){
	printf("Set Speed for Right Motor is: %i\n%%",rSpeed);
	return rSpeed;
}
/*Returns the value of latest direction set for the left motor*/
int getSetLDirection(){
	printf("Set Direction for Left Motor is: %i\n",lDirection);
	return lDirection;
}
/*Returns the value of latest direction set for the right motor*/
int getSetRDirection(){
	printf("Set Direction for Right Motor is: %i\n",rDirection);
	return rDirection;
}