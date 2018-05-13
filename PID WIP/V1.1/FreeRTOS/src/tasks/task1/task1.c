/* 
	The code in this file was used to test FreeRTOS. 
	Change the code for your purpose.
*/

#include <asf.h>
#include <math.h>
#include "task1.h"
#include "../initializations/pins_init.h"
#include "Reglering/Reglering.h"
#include "../motorController.h"
#include "../encoderISR.h"
#define sampleTime 200 //Samplingtid för PID-regleringen i millisekunder

/*
* Function: task1
* -------------------
* Performs an action every xTimeT1 milliseconds
*/
void task1(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 200/portTICK_RATE_MS; /* set ticks (xTimeT1) in milliseconds */
	xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
	
		 /* constant period, independent of execution time */
		//vTaskDelay(sampleTime);										 /* no constant period, dependent of execution time */ 

//Mini-Test
/*
while(1){
	drive(-120,-120);
	printf("L: %i \n",getLeftPulses());
	printf("R: %i \n",getRightPulses());		
}
*/

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$					 PID REGLERING					    $$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$											            $$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
//OBS FÖRSIKTIG MED UINTS_16 och 8 beräkningarna blir konstiga med dem!!!!!!!///
	int resolution = 144; //Upplösningen, antal pulser per revolution
	long N_Left = 0; //Antalet pulser för vänster encoder, long = 64bits
	long N_Right = 0;	//Antalet pulser för vänster encoder, long = 64bits	
	double b = 39.5;//Distans mellan hjulen är 39.5cm
	double radius = 7.9; //Hjulens radie är 7.9cm
	double dPP = 0.3447; //distance per pulse in cm	
	double WheelCircum = (double)(2*M_PI*radius); //Hjulets omkrets. Kan beräknas mer korrekt genom att mäta omkretsen fysiskt eftersom hjulet inte är helt runt 	
	double distanceLeft = 0; //Distans färdad är produkten av hjul revolutioner och omkretsen
	double distanceRight = 0;
	double Ts = (double)(sampleTime/(double)1000); //samplingtiden i sekunder 
	double linearLeftDesired = 0; //Önskade linjära hastighet för vänster hjul i cm/s
	double linearRightDesired = 0; 
	double linearLeftActual = 0; //Aktuella linjära hastighet för vänster hjul i cm/s
	double linearRightActual = 0;
	int doubleToIntFactor = 100000; 
	double V = 0; //aktuella linjära hastigheten
	double W = 0; //aktuella angulära hastigheten = vinkelfrekvensen
	double Vd = 0;//Önskade linjära hastigheten
	/*double OldP_err_Left = 0; //Gamla felvärdet behövs för differentialen
	double OldP_err_Right = 0; //Gamla felvärdet behövs för differentialen
	double P_err_Right = 0; //Proportions felvärdet 
	double I_err_Left = 0; //Integrations felvärdet
	double D_err_Left = 0; //Differentials felvärdet
	double D_err_Right = 0; //Differentials felvärdet
	double Wd = 0; //Önskade angulära hastigheten = vinkelfrekvensen
	double Kp = 0.5;
	double Ki = 0;
	double Kd = 0; */
	//double RPM_Left = (V_Left+(b/2)*W_angular)*radius;  //Formel för att beräkna Revolutions Per Minutes
	//double RPM_Right = (V_Right-(b/2)*W_angular)*radius; //Hastighet i RPM för höger hjul
/*	double RPM_desired_Left = 0; //Önskade RPM, systemets bör-värde
	double RPM_desired_Right = 0; //Önskade RPM, systemets bör-värde
	double RPM_actual_Left= 0; //Aktuella RPM, systemets är-värde
	double RPM_actual_Right= 0; //Aktuella RPM, systemets är-värde
	double PWM_New_Left= 0; //Här lagras de nya PWM pulserna 
	double PWM_New_Right= 0; //Här lagras de nya PWM pulserna 
	*/
	
	while(1){
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
			ioport_set_pin_level(PIO_PB27_IDX, HIGH);
			printf("---------------sampleTime: %i ----------------\n",(int)(Ts*doubleToIntFactor));
			drive(300,300);
			
//MODUL 1/////////////////////////////////////////////////////////		
		//fetcha pulser från vänser och höger encoder
		N_Left = getLeftPulses(); 
		N_Right = getRightPulses(); //DENNA BERÄKNING BORDE SKE INUTI ENCODER ISR VID INTTTERUPTS
		resetCounter(); //Nollställ pulsräknarna
		printf("N_RIGHT %i \n",N_Right);
		printf("N_LEFT %i \n",N_Left);
		//Beräkna distansen som varje hjul färdats
		printf("RES: %i\n",resolution);
		printf("CIRC: %i\n",(int)(WheelCircum*doubleToIntFactor));
		distanceLeft = (double)(WheelCircum * N_Left / resolution); //Distans färdad är produkten av hjul revolutioner och omkretsen
		distanceRight = (double)(WheelCircum * N_Right / resolution);
		printf("distanceLeft: %i deci\n",(int)(distanceLeft*doubleToIntFactor));
		printf("distanceRight: %i deci\n",(int)(distanceRight*doubleToIntFactor));
//MODUL 2/////////////////////////////////////////////////////////			
		
	//Beräkna den aktuella hastigheten från datan av hjulkodarna
		V = (double)((distanceLeft+distanceRight)/(2*Ts)); //linjära hastigheten
		W = (double)((distanceLeft-distanceRight)/(b*Ts)); //angulära hastigheten
		printf("Linear V: %i deci\n",(int)(V*doubleToIntFactor));
		printf("Angular W: %i deci\n",(int)(W*doubleToIntFactor));
		linearLeftActual = (double)(distanceLeft/Ts);
		linearRightActual = (double)(distanceRight/Ts);
		printf("Linear V LEFT: %i deci\n",(int)((double)linearLeftActual*doubleToIntFactor));
		printf("Linear V RIGHT: %i deci\n",(int)((double)linearRightActual*doubleToIntFactor));
	/*	
	//Beräkna den aktuella hastigheten i RPM (Revolutioner Per Minut)
		RPM_actual_Left = (V+(b/2)*W)/radius; //Formel för att beräkna Revolutions Per Minutes
		RPM_actual_Right = (V-(b/2)*W)/radius; //Hastighet i RPM för höger hjul
	
	//Beräkna den önskade hastigheten i RPM (Revolutioner Per Minut)
		RPM_desired_Left = (Vd+(b/2)*Wd)/radius; //Formel för att beräkna Revolutions Per Minutes
		RPM_desired_Right = (Vd-(b/2)*Wd)/radius; //Hastighet i RPM för höger hjul



*/
	ioport_set_pin_level(PIO_PB27_IDX, LOW);
}  

}

