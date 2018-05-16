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
	
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$$$$$$$$$$$    MINI-TEST    $$$$$$$$$$$$$$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/*
while(1){
	drive(-120,-120);
	printf("L: %i \n",getLeftPulses());
	printf("R: %i \n",getRightPulses());		
}
*/
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$					 PID REGLERING					    $$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$											            $$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
//OBS F�RSIKTIG MED UINTS_16 och 8 ber�kningarna blir konstiga med dem!!!!!!!///
//OBS UNDVIK DOUBLE ANV�ND IST�LLET FLOATS
	int resolution = 144; //Uppl�sningen, antal pulser per revolution
	long N_Left = 0; //Antalet pulser f�r v�nster encoder, long = 64bits
	long N_Right = 0;	//Antalet pulser f�r v�nster encoder, long = 64bits	
	float radius = 7.9; //Hjulens radie �r 7.9cm
	//float dPP = 0.3447; //distance per pulse in cm	
	float WheelCircum = (float)(2*M_PI*radius); //Hjulets omkrets. Kan ber�knas mer korrekt genom att m�ta omkretsen fysiskt eftersom hjulet inte �r helt runt 	
	float distanceLeft = 0; //Distans f�rdad �r produkten av hjul revolutioner och omkretsen
	float distanceRight = 0;
	float Ts = (float)(sampleTime/(float)1000); //samplingtiden i sekunder 
	float linearLeftDesired = 0; //�nskade linj�ra hastighet f�r v�nster hjul i cm/s
	float linearRightDesired = 0; 
	float linearLeftActual = 0; //Aktuella linj�ra hastighet f�r v�nster hjul i cm/s
	float linearRightActual = 0;
	int doubleToIntFactor = 100000; 
	/*
	float b = 39.5;//Distans mellan hjulen �r 39.5cm
	float V = 0; //aktuella linj�ra hastigheten
	float W = 0; //aktuella angul�ra hastigheten = vinkelfrekvensen
	float Vd = 0;//�nskade linj�ra hastigheten
	float Wd = 0; //�nskade angul�ra hastigheten = vinkelfrekvensen
	*/
	float OldP_err_Left = 0; //Gamla felv�rdet beh�vs f�r differentialen
	float OldP_err_Right = 0; //Gamla felv�rdet beh�vs f�r differentialen
	float P_err_Left = 0; //Proportions felv�rdet 
	float P_err_Right = 0; //Proportions felv�rdet 
	float I_err_Left = 0; //Integrations felv�rdet
	float I_err_Right = 0; //Integrations felv�rdet
	float D_err_Left = 0; //Differentials felv�rdet
	float D_err_Right = 0; //Differentials felv�rdet
	float Kp = 0.5;
	float Ki = 0;
	float Kd = 0; 
	float mcPulseLeft = 0;
	float mcPulseRight = 0;
	float mcPulseLeftOld = 0;
	float mcPulseRightOld = 0;
	/*
	float RPM_Left = (V_Left+(b/2)*W_angular)*radius;  //Formel f�r att ber�kna Revolutions Per Minutes
	float RPM_Right = (V_Right-(b/2)*W_angular)*radius; //Hastighet i RPM f�r h�ger hjul
	float RPM_desired_Left = 0; //�nskade RPM, systemets b�r-v�rde
	float RPM_desired_Right = 0; //�nskade RPM, systemets b�r-v�rde
	float RPM_actual_Left= 0; //Aktuella RPM, systemets �r-v�rde
	float RPM_actual_Right= 0; //Aktuella RPM, systemets �r-v�rde
	float PWM_New_Left= 0; //H�r lagras de nya PWM pulserna 
	float PWM_New_Right= 0; //H�r lagras de nya PWM pulserna 
	*/
	
	while(1){
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); //Taskdelay = SampleTime
			ioport_set_pin_level(PIO_PB27_IDX, HIGH); //F�r att r�kna Tasktime
			printf("---------------sampleTime: %i ----------------\n",(int)(Ts*doubleToIntFactor));
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//%%%%%%%%%%    TEST         %%%%%%%%%%%
	    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%		
			linearLeftDesired = 20.000; // B�rv�rden i cm/s ,lika stora v�rden om den ska k�ra rakt 
			linearRightDesired = 20.000;
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			
//MODUL 1/////////////////////////////////////////////////////////		
		//fetcha pulser fr�n v�nser och h�ger encoder sedan senast samplen
		N_Left = getLeftPulses(); 
		N_Right = getRightPulses(); 
		resetCounter(); //Nollst�ll pulsr�knarna
		printf("N_RIGHT %li \n",N_Right);
		printf("N_LEFT %li \n",N_Left);
		//Ber�kna distansen som varje hjul f�rdats
		printf("RES: %i\n",resolution);
		printf("CIRC: %i\n",(int)(WheelCircum*doubleToIntFactor));
		distanceLeft = (float)(WheelCircum * N_Left / resolution); //Distans f�rdad �r produkten av hjul revolutioner och omkretsen
		distanceRight = (float)(WheelCircum * N_Right / resolution);
		printf("distanceLeft: %i \n",(int)(distanceLeft*doubleToIntFactor));
		printf("distanceRight: %i \n",(int)(distanceRight*doubleToIntFactor));
//MODUL 2/////////////////////////////////////////////////////////			
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$						PID CONTROLLERN			                $$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

		//Lagra f�reg�ende felv�rde
		OldP_err_Left = P_err_Left;
		OldP_err_Right = P_err_Right;
		
		//Ber�kna proportions felv�rdet: skillnaden mellan �nskad hastighet och aktuell hastighet
		P_err_Left = linearLeftDesired-linearLeftActual;
		P_err_Right = linearRightDesired-linearRightActual;
		
		//Ber�kna differential felv�rdet: skillnaden mellan nuvarande och f�reg�ende fel
		D_err_Left = P_err_Left - OldP_err_Left;
		D_err_Right = P_err_Right - OldP_err_Right;
		
		//Ber�kna integral felv�rdet: Summan av alla fel
		I_err_Left += P_err_Left;
		I_err_Right += P_err_Right;
		
		//Ber�kna den nya PWM pulsen f�r varje hjul
		mcPulseLeftOld = getSetLeftSpeed();
		mcPulseRightOld = getSetRightSpeed();
		mcPulseLeft = (float)((Kp * P_err_Left + Ki * I_err_Left * Ts + Kd *D_err_Left / Ts)+mcPulseLeftOld);
		mcPulseRight = (float)((Kp * P_err_Right + Ki * I_err_Right * Ts + Kd *D_err_Right / Ts)+mcPulseRightOld);
		
		//Begr�nsa styrv�rdet f�r v�nstra motorkontrollerar pulsen
		if(mcPulseLeft>500){
			mcPulseLeft = 500;
		}else if(mcPulseLeft<-500){
			mcPulseLeft = -500;
		}
		//Begr�nsa styrv�rdet f�r h�gra motorkontrollerar pulsen
		if(mcPulseRight>500){
			mcPulseRight = 500;
			}else if(mcPulseRight<-500){
			mcPulseRight = -500;
		}
		//Skicka ut de nya PWM pulserna till motorkontrollerarna
		drive(mcPulseLeft,mcPulseRight);
		
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$		
	
/*	
	//Ber�kna den aktuella hastigheten fr�n datan av hjulkodarna
		V = (float)((distanceLeft+distanceRight)/(2*Ts)); //linj�ra hastigheten
		W = (float)((distanceLeft-distanceRight)/(b*Ts)); //angul�ra hastigheten
		printf("Linear V: %i \n",(int)((float)V*doubleToIntFactor));
		printf("Angular W: %i \n",(int)((float)W*doubleToIntFactor));
		linearLeftActual = (float)(distanceLeft/Ts);
		linearRightActual = (float)(distanceRight/Ts);
		printf("Linear V LEFT: %i \n",(int)((float)linearLeftActual*doubleToIntFactor));
		printf("Linear V RIGHT: %i \n",(int)((float)linearRightActual*doubleToIntFactor));
	
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

