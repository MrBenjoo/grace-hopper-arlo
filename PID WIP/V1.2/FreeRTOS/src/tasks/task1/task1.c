/* 
	The code in this file was used to test FreeRTOS. 
	Change the code for your purpose.
*/

#include <asf.h>
#include <math.h>
#include <limits.h> 
#include "task1.h"
#include "../initializations/pins_init.h"
#include "Reglering/Reglering.h"
#include "../motorController.h"
#include "../encoderISR.h"
//#define sampleTime 200 //Samplingtid f�r PID-regleringen i millisekunder

/*
* Function: task1
* -------------------
* Performs an action every xTimeT1 milliseconds
*/
void task1(void *pvParamters)
{
	//portTickType xLastWakeTime;
	//portTickType xTimeIncrement = 200/portTICK_RATE_MS; /* set ticks (xTimeT1) in milliseconds */
	//xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
	
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
		//OBS F�RSIKTIG MED UINTS_16 och 8 ber�kningarna blir konstiga med dem!!!!!!!///
		int resolution = 144; //Uppl�sningen, antal pulser per revolution
		//double b = 39.5;//Distans mellan hjulen �r 39.5cm
		double radius = 7.9; //Hjulens radie �r 7.9cm
		double WheelCircum = (double)(2*M_PI*radius); //Hjulets omkrets. Kan ber�knas mer korrekt genom att m�ta omkretsen fysiskt eftersom hjulet inte �r helt runt
		int doubleToIntFactor = 100000;
	
		////////////////////////////////////////////////////////////////////////////
		int ticksPassed = 0;	//Do not modify
		int	ticksReference = 0; //Do not modify
		uint8_t testNbr = 1; //Do not modify
		uint8_t secondsPerTest = 3; //MODIFY for yout test, NOTE: take into account limits of data type if needed
		//double Ts = (double)(sampleTime/(double)1000); //samplingtiden i sekunder
		uint8_t speedIncrementFactor = 50; //MODIFY for your test, NOTE: Motorspeed is limited to 0-100
		int totalNbrTests = 700/speedIncrementFactor; //Do not modify
		int pulses[2][totalNbrTests]; //Do not modify
		uint8_t testRounds = 1; //Do not modify
		uint8_t TotalTestRounds = 10; //MODIFY the number of re-runs that all values will then be divided by to get an average
		double linearActual[2][totalNbrTests]; //�nskade linj�ra hastighet f�r v�nster hjul i cm/s
		double distance[2][totalNbrTests]; //f�rflyttning i cm
	//	double V[totalNbrTests]; //aktuella linj�ra hastigheten
	//	double W[totalNbrTests]; //aktuella angul�ra hastigheten = vinkelfrekvensen
		/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		/*$$$$$$$$$$$        TEST PROGRAM: F�R PULSER FR�N V�NSTER OCH      $$$$$$$$$$$$$$$$*/
		/*$$$$$$$$$$$        H�GER STEGAR IGENOM OLIKA MOTORSTYRKA          $$$$$$$$$$$$$$$$*/
		/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		while(testRounds <= TotalTestRounds){
			printf("Test Round:%i",testRounds);
			testRounds++;
			testNbr = 0;
			while(testNbr <= totalNbrTests){
				printf("Test#%i speed:%i is startning...\n",testNbr,speedIncrementFactor*testNbr);
				getLeftPulses();
				getRightPulses();
				printf("------\n");
				ticksReference = xTaskGetTickCount();
				drive(speedIncrementFactor*testNbr,speedIncrementFactor*testNbr);
				while(ticksPassed<secondsPerTest*1000){
					ticksPassed =  xTaskGetTickCount() - ticksReference;
				}
				drive(0,0);
				
				
				pulses[1][testNbr] += getLeftPulses();
				pulses[2][testNbr] += getRightPulses();
				distance[1][testNbr] = (double)(WheelCircum * pulses[1][testNbr] / resolution); //Distans f�rdad �r produkten av hjul revolutioner och omkretsen
				distance[2][testNbr] = (double)(WheelCircum * pulses[2][testNbr] / resolution);
				//V[testNbr] = (double)((distance[1][testNbr]+distance[2][testNbr])/(2*secondsPerTest)); //linj�ra hastigheten
				//W[testNbr] = (double)((distance[1][testNbr]-distance[2][testNbr])/(b*secondsPerTest)); //angul�ra hastigheten
				linearActual[1][testNbr]  = (double)(distance[1][testNbr]/secondsPerTest);
				linearActual[2][testNbr] = (double)(distance[2][testNbr]/secondsPerTest);
				
		
				printf("Test#%i speed:%i is ending...\n",testNbr,speedIncrementFactor*testNbr);
				printf("------\n");
				resetCounter();
				testNbr++;
				ticksPassed = 0;
			}
		}
		//// LAGRA MAX OCH MIN V�RDET FR�N HELA ARRAYEN MED LINJ�R HASTIGHET
		double lsMin[2] = {LONG_LONG_MIN,LONG_LONG_MIN}; //H�GSTA V�RDET EN DOUBLE KAN ANTA
		double lsMax[2] = {LONG_LONG_MAX,LONG_LONG_MAX}; //L�GSTA V�RDET EN DOUBLE KAN ANTA
		for(uint8_t p=1;p<3;p++){
			for(uint8_t q=1;q<totalNbrTests+1;q++){
					lsMin[p] = min(lsMin[p],linearActual[p][q]);
					lsMax[p] = max(lsMin[p],linearActual[p][q]);
			}
		}
		
		
		
		for(uint8_t i = 1;i<3;i++){
			for(uint8_t k=1;k<totalNbrTests+1;k++){
				pulses[i][k] = pulses[i][k]/TotalTestRounds;
				linearActual[i][k] = linearActual[i][k]/TotalTestRounds;
				if(i==1)
				printf("Left Wheel Speed:%i Pulses:%i LinearSpeed Avg:%i Max:%i Min:%i\n",k*speedIncrementFactor,pulses[i][k],(int)(linearActual[i][k]*doubleToIntFactor),(int)(lsMax[0]),(int)(lsMin[0]));
				if(i==2)
				printf("Right Wheel Speed:%i Pulses:%i  LinearSpeed Avg:%i Max:%i Min:%i\n",k*speedIncrementFactor,pulses[i][k],(int)(linearActual[i][k]*doubleToIntFactor),(int)(lsMax[1]),(int)(lsMin[1]));
			}
		}
		
		drive(0,0);
		printf("All tests have been run through...\n");
		while(1){
		}
		/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		
	}
}

