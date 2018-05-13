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
#define sampleTime 200 //Samplingtid f�r PID-regleringen i millisekunder

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
//OBS F�RSIKTIG MED UINTS_16 och 8 ber�kningarna blir konstiga med dem!!!!!!!///
	int resolution = 144; //Uppl�sningen, antal pulser per revolution
	long N_Left = 0; //Antalet pulser f�r v�nster encoder, long = 64bits
	long N_Right = 0;	//Antalet pulser f�r v�nster encoder, long = 64bits	
	double b = 39.5;//Distans mellan hjulen �r 39.5cm
	double radius = 7.9; //Hjulens radie �r 7.9cm
	double dPP = 0.3447; //distance per pulse in cm	
	double WheelCircum = (double)(2*M_PI*radius); //Hjulets omkrets. Kan ber�knas mer korrekt genom att m�ta omkretsen fysiskt eftersom hjulet inte �r helt runt 	
	double distanceLeft = 0; //Distans f�rdad �r produkten av hjul revolutioner och omkretsen
	double distanceRight = 0;
	double Ts = (double)(sampleTime/(double)1000); //samplingtiden i sekunder 
	double linearLeftDesired = 0; //�nskade linj�ra hastighet f�r v�nster hjul i cm/s
	double linearRightDesired = 0; 
	double linearLeftActual = 0; //Aktuella linj�ra hastighet f�r v�nster hjul i cm/s
	double linearRightActual = 0;
	int doubleToIntFactor = 100000; 
	double V = 0; //aktuella linj�ra hastigheten
	double W = 0; //aktuella angul�ra hastigheten = vinkelfrekvensen
	double Vd = 0;//�nskade linj�ra hastigheten
	/*double OldP_err_Left = 0; //Gamla felv�rdet beh�vs f�r differentialen
	double OldP_err_Right = 0; //Gamla felv�rdet beh�vs f�r differentialen
	double P_err_Right = 0; //Proportions felv�rdet 
	double I_err_Left = 0; //Integrations felv�rdet
	double D_err_Left = 0; //Differentials felv�rdet
	double D_err_Right = 0; //Differentials felv�rdet
	double Wd = 0; //�nskade angul�ra hastigheten = vinkelfrekvensen
	double Kp = 0.5;
	double Ki = 0;
	double Kd = 0; */
	//double RPM_Left = (V_Left+(b/2)*W_angular)*radius;  //Formel f�r att ber�kna Revolutions Per Minutes
	//double RPM_Right = (V_Right-(b/2)*W_angular)*radius; //Hastighet i RPM f�r h�ger hjul
/*	double RPM_desired_Left = 0; //�nskade RPM, systemets b�r-v�rde
	double RPM_desired_Right = 0; //�nskade RPM, systemets b�r-v�rde
	double RPM_actual_Left= 0; //Aktuella RPM, systemets �r-v�rde
	double RPM_actual_Right= 0; //Aktuella RPM, systemets �r-v�rde
	double PWM_New_Left= 0; //H�r lagras de nya PWM pulserna 
	double PWM_New_Right= 0; //H�r lagras de nya PWM pulserna 
	*/
	
	while(1){
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
			ioport_set_pin_level(PIO_PB27_IDX, HIGH);
			printf("---------------sampleTime: %i ----------------\n",(int)(Ts*doubleToIntFactor));
			drive(300,300);
			
//MODUL 1/////////////////////////////////////////////////////////		
		//fetcha pulser fr�n v�nser och h�ger encoder
		N_Left = getLeftPulses(); 
		N_Right = getRightPulses(); //DENNA BER�KNING BORDE SKE INUTI ENCODER ISR VID INTTTERUPTS
		resetCounter(); //Nollst�ll pulsr�knarna
		printf("N_RIGHT %i \n",N_Right);
		printf("N_LEFT %i \n",N_Left);
		//Ber�kna distansen som varje hjul f�rdats
		printf("RES: %i\n",resolution);
		printf("CIRC: %i\n",(int)(WheelCircum*doubleToIntFactor));
		distanceLeft = (double)(WheelCircum * N_Left / resolution); //Distans f�rdad �r produkten av hjul revolutioner och omkretsen
		distanceRight = (double)(WheelCircum * N_Right / resolution);
		printf("distanceLeft: %i deci\n",(int)(distanceLeft*doubleToIntFactor));
		printf("distanceRight: %i deci\n",(int)(distanceRight*doubleToIntFactor));
//MODUL 2/////////////////////////////////////////////////////////			
		
	//Ber�kna den aktuella hastigheten fr�n datan av hjulkodarna
		V = (double)((distanceLeft+distanceRight)/(2*Ts)); //linj�ra hastigheten
		W = (double)((distanceLeft-distanceRight)/(b*Ts)); //angul�ra hastigheten
		printf("Linear V: %i deci\n",(int)(V*doubleToIntFactor));
		printf("Angular W: %i deci\n",(int)(W*doubleToIntFactor));
		linearLeftActual = (double)(distanceLeft/Ts);
		linearRightActual = (double)(distanceRight/Ts);
		printf("Linear V LEFT: %i deci\n",(int)((double)linearLeftActual*doubleToIntFactor));
		printf("Linear V RIGHT: %i deci\n",(int)((double)linearRightActual*doubleToIntFactor));
	/*	
	//Ber�kna den aktuella hastigheten i RPM (Revolutioner Per Minut)
		RPM_actual_Left = (V+(b/2)*W)/radius; //Formel f�r att ber�kna Revolutions Per Minutes
		RPM_actual_Right = (V-(b/2)*W)/radius; //Hastighet i RPM f�r h�ger hjul
	
	//Ber�kna den �nskade hastigheten i RPM (Revolutioner Per Minut)
		RPM_desired_Left = (Vd+(b/2)*Wd)/radius; //Formel f�r att ber�kna Revolutions Per Minutes
		RPM_desired_Right = (Vd-(b/2)*Wd)/radius; //Hastighet i RPM f�r h�ger hjul



*/
	ioport_set_pin_level(PIO_PB27_IDX, LOW);
}  

}

