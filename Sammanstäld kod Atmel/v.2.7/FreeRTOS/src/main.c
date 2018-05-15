#include "initializations/main_init.h"
#include "initializations/pins_init.h"
#include "Reglering/Reglering.h"
#include "encoderISR.h"
#include "motorController.h"
#include "I2C/I2CFunctions.h"
#include <asf.h>
/*
This version Experiment 1.1 of our FreeRTOS program is ment to test the encoders, if we can count them and save the counter value 
with appropiate values in two separate variables, one for each wheel. Clear?[]
And does it count positive for positive direction and negative for negative direction? Clear?[]

Next version (1.2) will test if we can add in P-regulation to make the wheels go at the same speed. Clear?[]

Next version (1.3) will test if we can add in the distance the robot has travelled. Clear?[]

Next version (1.4) will test if we can implement PWM to control the signal to the motorcontrollers. Clear?[] 

*/
int main (void)
{

	misc_init(); //pin 2 out, pin5&7 in
	console_init();
	//interrupt_init();	//	pin 7 and 8 as interrupt pins	
	encoder_init(); //also initialises pin 5 (left encoder) & 7 (right encoder) as interrupt pins
	//rtos_init(); //Starts RTOS scheduler
	//delay_us(3000000);
	//controlCenter(50);
	//delay_init();
	init_twi();
	
	int current_case = 0;
	int next_case = 0;
	
	while(1){
		switch(current_case){
			case(0): //h�mta positioner p� objekt, sig sj�lv och avlastningsplats
			
			//	current_case = 1; n�r allt �r klart
			//current_case = next_case;
			break;
			
			case(1): //ber�knar position f�r objekt, vrida oss mot objektet, loop[ med reglerad k�rning mot objekt[medans positionens's avs�nd > 42.5]]
			
						
			//if (positionens's avs�nd <= 42.5)
			//current_case = 2;
			break;
			
			
			case(2):// detektera objekt ( sensor p�), loop[leta efter objekt till hittat]
			//if(objekt funnet p� utsat avst�nd)
			//current_case = 3
			break;			
			
			
			case(3):// meddela p�byggnad "object found" och v�nta p� ack
			//if (ack mottaget)
			// current_case = 4;
			break;	
			
			
			case(4)://fr�ga efter lyckat upplock
			//if(om objekt upplockat)
			//current_case = 5;
			break;
			
			
			case(5)://k�r mot avl�mningsplats
			//if(framme vid avl�mningsplats)
			//current_case = 6;
			break;
			
			
			case(6)://meddela p�byggnad; l�mna objekt
			
			break;		
		
		}
	}
}