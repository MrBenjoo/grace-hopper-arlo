/*
 * motorController.c
 *
 * Created: 2018-04-18 13:01:59
 *  Author: Filip och Carl och Sebastian
 */ 
 #include <asf.h>
 #include <stdio.h>
 #include "motorController.h"
 #include "../initializations/pins_init.h"
 #define PWM_35 IOPORT_CREATE_PIN(PIOC, 3) // pin 35
 #define PWM_42 IOPORT_CREATE_PIN(PIOA, 19) // pin 42
 double rSpeedLatest = 0;
 double lSpeedLatest = 0;
 double DistancePerPulse = 0.3447; //cm 
 double radius = 7.9;
 double b = 39.5;
 int8_t rDirectionLatest = 0;
 int8_t lDirectionLatest = 0;
 pwm_channel_t pwm_channel_instance;
 
 //speed (-)700 - (+)700, negagative is reverse direction
 void drive(double lSpeed, double rSpeed) { 
	rSpeedLatest = rSpeed;
	lSpeedLatest = lSpeed;
	//// MAKE SURE SIGNAL IS WITHIN LIMITS ////////////////////
	if(lSpeed<(-700)){
		lSpeed = -700;
	}
	if(lSpeed>700){
		lSpeed = 700;
	}
	if(rSpeed<(-700)){
		rSpeed = -700;
	}
	if(rSpeed>700){
		rSpeed = 700;
	}
	//// MAKE SURE SIGNAL IS WITHIN LIMITS ////////////////////
	rSpeed = rSpeed*-1;
	lSpeed = lSpeed*-1;
	
	testDriveR(rSpeed); // sets pwm for the right motors 
	testDriveL(lSpeed); // sets pwm for the left motors

	//int rMotorSpeed = (1500 + 7 * rSpeed * rDirection);
	//int lMotorSpeed = (1500 + 7 * lSpeed * lDirection);
	//
	//ioport_set_pin_level(PIO_PB27_IDX, HIGH);
	//delay_us(rMotorSpeed);
	//ioport_set_pin_level(PIO_PB27_IDX, LOW);
	//delay_us(1100);
	//ioport_set_pin_level(PIO_PB27_IDX, HIGH);
	//delay_us(lMotorSpeed);
	//ioport_set_pin_level(PIO_PB27_IDX, LOW);
	//delay_us(5250);
}

void testDriveR(double speed) {
	int motorSpeed = (int)(1500 + speed);

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

void testDriveL(double speed) {
	int motorSpeed = (int)(1500 + speed);

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
}

/*Returns the value of latest speed set for the left motor*/
double getSetLSpeed(){
	//printf("Set Speed for Left Motor is: %i\n%%",lSpeedLatest);
	return lSpeedLatest;
}
/*Returns the value of latest speed set for the right motor*/
double getSetRSpeed(){
	//printf("Set Speed for Right Motor is: %i\n%%",rSpeedLatest);
	return rSpeedLatest;
}
/*Returns the value of latest direction set for the left motor*/
int8_t getSetLDirection(){
	//printf("Set Direction for Left Motor is: %i\n",lDirectionLatest);
		if(lSpeedLatest>0){
			return 1;
			}else if(lSpeedLatest<0){
			return -1;
		}
		return 0;
}
/*Returns the value of latest direction set for the right motor*/
int8_t getSetRDirection(){
	//printf("Set Direction for Right Motor is: %i\n",rDirectionLatest);
	if(rSpeedLatest>0){
		return 1;
	}else if(rSpeedLatest<0){
		return -1;
	}
	return 0;
}