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
//#define sampleTime 200 //Samplingtid för PID-regleringen i millisekunder

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
		//OBS FÖRSIKTIG MED UINTS_16 och 8 beräkningarna blir konstiga med dem!!!!!!!///
		int resolution = 144; //Upplösningen, antal pulser per revolution
		//double b = 39.5;//Distans mellan hjulen är 39.5cm
		double radius = 7.9; //Hjulens radie är 7.9cm
		double WheelCircum = (double)(2*M_PI*radius); //Hjulets omkrets. Kan beräknas mer korrekt genom att mäta omkretsen fysiskt eftersom hjulet inte är helt runt
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
		double linearActual[2][totalNbrTests]; //Önskade linjära hastighet för vänster hjul i cm/s
		double distance[2][totalNbrTests]; //förflyttning i cm
	//	double V[totalNbrTests]; //aktuella linjära hastigheten
	//	double W[totalNbrTests]; //aktuella angulära hastigheten = vinkelfrekvensen
		/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		/*$$$$$$$$$$$        TEST PROGRAM: FÅR PULSER FRÅN VÄNSTER OCH      $$$$$$$$$$$$$$$$*/
		/*$$$$$$$$$$$        HÖGER STEGAR IGENOM OLIKA MOTORSTYRKA          $$$$$$$$$$$$$$$$*/
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
				distance[1][testNbr] = (double)(WheelCircum * pulses[1][testNbr] / resolution); //Distans färdad är produkten av hjul revolutioner och omkretsen
				distance[2][testNbr] = (double)(WheelCircum * pulses[2][testNbr] / resolution);
				//V[testNbr] = (double)((distance[1][testNbr]+distance[2][testNbr])/(2*secondsPerTest)); //linjära hastigheten
				//W[testNbr] = (double)((distance[1][testNbr]-distance[2][testNbr])/(b*secondsPerTest)); //angulära hastigheten
				linearActual[1][testNbr]  = (double)(distance[1][testNbr]/secondsPerTest);
				linearActual[2][testNbr] = (double)(distance[2][testNbr]/secondsPerTest);
				
		
				printf("Test#%i speed:%i is ending...\n",testNbr,speedIncrementFactor*testNbr);
				printf("------\n");
				resetCounter();
				testNbr++;
				ticksPassed = 0;
			}
		}
		//// LAGRA MAX OCH MIN VÄRDET FRÅN HELA ARRAYEN MED LINJÄR HASTIGHET
		double lsMin[2] = {LONG_LONG_MIN,LONG_LONG_MIN}; //HÖGSTA VÄRDET EN DOUBLE KAN ANTA
		double lsMax[2] = {LONG_LONG_MAX,LONG_LONG_MAX}; //LÄGSTA VÄRDET EN DOUBLE KAN ANTA
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

