/*
 * motorController.c
 *
 * Created: 2018-04-18 13:01:59
 *  Author: Filip och Carl och Sebastian
 */ 
 #include <asf.h>
 #include <stdio.h>
 #include <math.h>
 #include "motorController.h"
 #include "../initializations/pins_init.h"
 #define PWM_35 IOPORT_CREATE_PIN(PIOC, 3) // pin 35
 #define PWM_42 IOPORT_CREATE_PIN(PIOA, 19) // pin 42
 float mcPLeftLatest = 0;
 float mcPRightLatest = 0;
 int motorSpeed = 0;
 pwm_channel_t pwm_channel_instance;
 
 //speedPulse (-)475 - (+)475, negagative is reverse direction

void testDriveL(float speedPulseL) {
	ioport_set_pin_level(PIO_PD8_IDX, HIGH); //För att räkna tiden det tar från anrop till skickad puls
	if(speedPulseL<-475){
		printf("ERROR! mcPulseLeft param is over defined negative limit\n");
	}
	else if(speedPulseL>475){
		printf("ERROR! mcPulseLeft param is over defined positive limit\n");
	}
	else if(speedPulseL>-100 && speedPulseL<100){
		printf("ERROR! mcPulseLeft param is over defined positive limit\n");
	}
	mcPLeftLatest = speedPulseL;
	//Makes positive values represent forward direction and negative values represent reverse direction
	speedPulseL = round(speedPulseL);
	speedPulseL = speedPulseL*-1;
	motorSpeed = (int)(1500 + speedPulseL);

	//connect peripheral B to pin A19
	pio_configure_pin(PWM_42, PIO_TYPE_PIO_PERIPH_B);

	//enable the peripheral clock for the PWM hardware
	pmc_enable_periph_clk(ID_PWM);

	//disable the channel until it is properly configured
	pwm_channel_disable(PWM, PWM_CHANNEL_1);

	//PWM clock configuration
	pwm_clock_t PWMDAC_clock_config =
	{
		.ul_clka = 1000000,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};

	//apply the clock configuration
	pwm_init(PWM, &PWMDAC_clock_config);

	//sets the wave pulse properties
	pwm_channel_instance.channel = PWM_CHANNEL_1;
	pwm_channel_instance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel_instance.polarity = PWM_HIGH;
	pwm_channel_instance.alignment = PWM_ALIGN_LEFT;
	pwm_channel_instance.ul_period = 5250 + motorSpeed;
	pwm_channel_instance.ul_duty = motorSpeed;
	//apply the channel configuration
	pwm_channel_init(PWM, &pwm_channel_instance);

	//configuration is complete, so enable the channel
	pwm_channel_enable(PWM, PWM_CHANNEL_1);
	ioport_set_pin_level(PIO_PD8_IDX, LOW); //För att räkna tiden det tar från anrop till skickad puls
}

void testDriveR(float speedPulseR) {
		if(speedPulseR<-475){
			printf("ERROR! mcPulseRight param is over defined negative limit\n");
		}
		else if(speedPulseR>475){
			printf("ERROR! mcPulseRight param is over defined positive limit\n");
		}
		else if(speedPulseR>-100 && speedPulseR<100){
			printf("ERROR! mcPulseRight param is over defined positive limit\n");
		}
	mcPRightLatest = speedPulseR;
	//Makes positive values represent forward direction and negative values represent reverse direction
	speedPulseR = round(speedPulseR);
	speedPulseR = speedPulseR*-1;
	motorSpeed = (int)(1500 + speedPulseR);

	//connect peripheral B to pin C3
	pio_configure_pin(PWM_35, PIO_TYPE_PIO_PERIPH_B);

	//enable the peripheral clock for the PWM hardware
	pmc_enable_periph_clk(ID_PWM);

	//disable the channel until it is properly configured
	pwm_channel_disable(PWM, PWM_CHANNEL_0);

	//PWM clock configuration
	pwm_clock_t PWMDAC_clock_config =
	{
		.ul_clka = 1000000,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};

	//apply the clock configuration
	pwm_init(PWM, &PWMDAC_clock_config);

	//sets the wave pulse properties
	pwm_channel_instance.channel = PWM_CHANNEL_0;
	pwm_channel_instance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel_instance.polarity = PWM_HIGH;
	pwm_channel_instance.alignment = PWM_ALIGN_LEFT;
	pwm_channel_instance.ul_period = 5250 + motorSpeed;
	pwm_channel_instance.ul_duty = motorSpeed;
	//apply the channel configuration
	pwm_channel_init(PWM, &pwm_channel_instance);

	//configuration is complete, so enable the channel
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
}


/*Returns the value of latest speed set for the left motor*/
float getSetLeftSpeed(){
	//printf("Set Speed for Left Motor is: %i\n%%",lSpeedLatest);
	return mcPLeftLatest;
}
/*Returns the value of latest speed set for the right motor*/
float getSetRightSpeed(){
	//printf("Set Speed for Right Motor is: %i\n%%",rSpeedLatest);
	return mcPRightLatest;
}
/*Returns the value of latest direction set for the left motor*/
int getSetLeftDirection(){
	//printf("Set Direction for Left Motor is: %i\n",lDirectionLatest);
		if(mcPLeftLatest>0){
			return 1;
			}else if(mcPLeftLatest<0){
			return -1;
		}
		return 0;
}
/*Returns the value of latest direction set for the right motor*/
int getSetRightDirection(){
	//printf("Set Direction for Right Motor is: %i\n",rDirectionLatest);
	if(mcPRightLatest>0){
		return 1;
	}else if(mcPRightLatest<0){
		return -1;
	}
	return 0;
}