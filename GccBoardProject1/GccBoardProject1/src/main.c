/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "motorController.h"

#define PWM_DAC IOPORT_CREATE_PIN(PIOC, 3)

pwm_channel_t pwm_channel_instance;

int main (void)
{
	//clock configuration and initialization
	sysclk_init();
	
	/*Disable the watchdog timer and configure/initialize
	port pins connected to various components incorporated 
	into the SAM4S Xplained development platform, e.g., the 
	NAND flash, the OLED interface, the LEDs, the SW0 pushbutton.*/  
	board_init();
	
	//connect peripheral B to pin A23
	pio_configure_pin(PWM_DAC, PIO_TYPE_PIO_PERIPH_B);

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
	
	//see the article for details
	pwm_channel_instance.channel = PWM_CHANNEL_0;
	pwm_channel_instance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel_instance.polarity = PWM_HIGH;
	pwm_channel_instance.alignment = PWM_ALIGN_LEFT;
	pwm_channel_instance.ul_period = 100;
	pwm_channel_instance.ul_duty = 50;
	
	//apply the channel configuration
	pwm_channel_init(PWM, &pwm_channel_instance);
	
	//configuration is complete, so enable the channel
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
	
	while(1);
}





//pwm_channel_t pwm_channel_instance;
//
//int main (void)
//{
	////sysclk_init();
	////board_init();
	///* Insert system clock initialization code here (sysclk_init()). */
	//
	//pmc_enable_periph_clk(ID_PWM);
	//pwm_channel_disable(PWM, PWM_CHANNEL_4);
	//pwm_clock_t clock_setting = {
		//.ul_clka = 1000 * 100,
		//.ul_clkb = 0,
		//.ul_mck = 48000000
	//};
	//pwm_init(PWM, &clock_setting);
	//pwm_channel_instance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	//pwm_channel_instance.ul_period = 100;
	//pwm_channel_instance.ul_duty = 50;
	//pwm_channel_instance.channel = PWM_CHANNEL_4;
	//pwm_channel_init(PWM, &pwm_channel_instance);
//
//
	//
//
	//ioport_set_pin_dir(PIO_PB27_IDX, IOPORT_DIR_OUTPUT);
	//while(1) {
		////drive(50,0,1,-1);
		//pwm_channel_enable(PWM, PWM_CHANNEL_4);
	//}
	//
	//
//
	///* Insert application code here, after the board has been initialized. */
//}
