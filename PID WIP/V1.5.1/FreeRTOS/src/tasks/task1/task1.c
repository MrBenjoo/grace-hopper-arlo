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
//OBS FÖRSIKTIG MED UINTS_16 och 8 beräkningarna blir konstiga med dem!!!!!!!///
//OBS UNDVIK DOUBLE ANVÄND ISTÄLLET FLOATS
	int resolution = 144; //Upplösningen, antal pulser per revolution
	long N_Left = 0; //Antalet pulser för vänster encoder, long = 64bits
	long N_Right = 0;	//Antalet pulser för vänster encoder, long = 64bits	
	float radius = 7.9; //Hjulens radie är 7.9cm
	//float dPP = 0.3447; //distance per pulse in cm	
	float WheelCircum = (float)(2*M_PI*radius); //Hjulets omkrets. Kan beräknas mer korrekt genom att mäta omkretsen fysiskt eftersom hjulet inte är helt runt 	
	float distanceLeft = 0; //Distans färdad är produkten av hjul revolutioner och omkretsen
	float distanceRight = 0;
	float Ts = (float)(sampleTime/(float)1000); //samplingtiden i sekunder 
	float linearLeftDesired = 0; //Önskade linjära hastighet för vänster hjul i cm/s
	float linearRightDesired = 0; 
	float linearLeftActual = 0; //Aktuella linjära hastighet för vänster hjul i cm/s
	float linearRightActual = 0;
	int doubleToIntFactor = 100000; 
	/*
	float b = 39.5;//Distans mellan hjulen är 39.5cm
	float V = 0; //aktuella linjära hastigheten
	float W = 0; //aktuella angulära hastigheten = vinkelfrekvensen
	float Vd = 0;//Önskade linjära hastigheten
	float Wd = 0; //Önskade angulära hastigheten = vinkelfrekvensen
	*/
	float OldP_err_Left = 0; //Gamla felvärdet behövs för differentialen
	float OldP_err_Right = 0; //Gamla felvärdet behövs för differentialen
	float P_err_Left = 0; //Proportions felvärdet 
	float P_err_Right = 0; //Proportions felvärdet 
	float I_err_Left = 0; //Integrations felvärdet
	float I_err_Right = 0; //Integrations felvärdet
	float D_err_Left = 0; //Differentials felvärdet
	float D_err_Right = 0; //Differentials felvärdet
	float Kp = 0.5;
	float Ki = 0;
	float Kd = 0; 
	float mcPulseLeft = 0;
	float mcPulseRight = 0;
	float mcPulseLeftOld = 0;
	float mcPulseRightOld = 0;
	/*
	float RPM_Left = (V_Left+(b/2)*W_angular)*radius;  //Formel för att beräkna Revolutions Per Minutes
	float RPM_Right = (V_Right-(b/2)*W_angular)*radius; //Hastighet i RPM för höger hjul
	float RPM_desired_Left = 0; //Önskade RPM, systemets bör-värde
	float RPM_desired_Right = 0; //Önskade RPM, systemets bör-värde
	float RPM_actual_Left= 0; //Aktuella RPM, systemets är-värde
	float RPM_actual_Right= 0; //Aktuella RPM, systemets är-värde
	float PWM_New_Left= 0; //Här lagras de nya PWM pulserna 
	float PWM_New_Right= 0; //Här lagras de nya PWM pulserna 
	*/
	
	while(1){
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); //Taskdelay = SampleTime
			ioport_set_pin_level(PIO_PB27_IDX, HIGH); //För att räkna Tasktime
			printf("---------------sampleTime: %i ----------------\n",(int)(Ts*doubleToIntFactor));
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//%%%%%%%%%%    TEST         %%%%%%%%%%%
	    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%		
			linearLeftDesired = 20.000; // Börvärden i cm/s ,lika stora värden om den ska köra rakt 
			linearRightDesired = 20.000;
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			
//MODUL 1/////////////////////////////////////////////////////////		
		//fetcha pulser från vänser och höger encoder sedan senast samplen
		N_Left = getLeftPulses(); 
		N_Right = getRightPulses(); 
		resetCounter(); //Nollställ pulsräknarna
		printf("N_RIGHT %li \n",N_Right);
		printf("N_LEFT %li \n",N_Left);
		//Beräkna distansen som varje hjul färdats
		printf("RES: %i\n",resolution);
		printf("CIRC: %i\n",(int)(WheelCircum*doubleToIntFactor));
		distanceLeft = (float)(WheelCircum * N_Left / resolution); //Distans färdad är produkten av hjul revolutioner och omkretsen
		distanceRight = (float)(WheelCircum * N_Right / resolution);
		printf("distanceLeft: %i \n",(int)(distanceLeft*doubleToIntFactor));
		printf("distanceRight: %i \n",(int)(distanceRight*doubleToIntFactor));
//MODUL 2/////////////////////////////////////////////////////////			
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$						PID CONTROLLERN			                $$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

		//Lagra föregående felvärde
		OldP_err_Left = P_err_Left;
		OldP_err_Right = P_err_Right;
		
		//Beräkna proportions felvärdet: skillnaden mellan önskad hastighet och aktuell hastighet
		P_err_Left = linearLeftDesired-linearLeftActual;
		P_err_Right = linearRightDesired-linearRightActual;
		
		//Beräkna differential felvärdet: skillnaden mellan nuvarande och föregående fel
		D_err_Left = P_err_Left - OldP_err_Left;
		D_err_Right = P_err_Right - OldP_err_Right;
		
		//Beräkna integral felvärdet: Summan av alla fel
		I_err_Left += P_err_Left;
		I_err_Right += P_err_Right;
		
		//Beräkna den nya PWM pulsen för varje hjul
		mcPulseLeftOld = getSetLeftSpeed();
		mcPulseRightOld = getSetRightSpeed();
		mcPulseLeft = (float)((Kp * P_err_Left + Ki * I_err_Left * Ts + Kd *D_err_Left / Ts)+mcPulseLeftOld);
		mcPulseRight = (float)((Kp * P_err_Right + Ki * I_err_Right * Ts + Kd *D_err_Right / Ts)+mcPulseRightOld);
		
		//Begränsa styrvärdet för vänstra motorkontrollerar pulsen
		if(mcPulseLeft>500){
			mcPulseLeft = 500;
		}else if(mcPulseLeft<-500){
			mcPulseLeft = -500;
		}
		//Begränsa styrvärdet för högra motorkontrollerar pulsen
		if(mcPulseRight>500){
			mcPulseRight = 500;
			}else if(mcPulseRight<-500){
			mcPulseRight = -500;
		}
		//Skicka ut de nya PWM pulserna till motorkontrollerarna
		drive(mcPulseLeft,mcPulseRight);
		
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$		
	
/*	
	//Beräkna den aktuella hastigheten från datan av hjulkodarna
		V = (float)((distanceLeft+distanceRight)/(2*Ts)); //linjära hastigheten
		W = (float)((distanceLeft-distanceRight)/(b*Ts)); //angulära hastigheten
		printf("Linear V: %i \n",(int)((float)V*doubleToIntFactor));
		printf("Angular W: %i \n",(int)((float)W*doubleToIntFactor));
		linearLeftActual = (float)(distanceLeft/Ts);
		linearRightActual = (float)(distanceRight/Ts);
		printf("Linear V LEFT: %i \n",(int)((float)linearLeftActual*doubleToIntFactor));
		printf("Linear V RIGHT: %i \n",(int)((float)linearRightActual*doubleToIntFactor));
	
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

