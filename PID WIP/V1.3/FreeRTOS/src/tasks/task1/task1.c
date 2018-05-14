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
#define TESTS 14//Formula to calculate value of TESTS: (700/speedIncrementFactor)*totalTestRounds
#define STEPS 7//Formula to calculate value of STEPS: (700/speedIncrementFactor)
/*
* Function: task1
* -------------------
* Performs an action every xTimeT1 milliseconds
*/

void task1(void *pvParamters)
{
	while(1){
		
		
		//OBS FÖRSIKTIG MED UINTS_16 och 8 beräkningarna blir konstiga med dem!!!!!!!///
		int resolution = 144; //Upplösningen, antal pulser per revolution
		double radius = 7.9; //Hjulens radie är 7.9cm
		double WheelCircum = (double)(2*M_PI*radius); //Hjulets omkrets. Kan beräknas mer korrekt genom att mäta omkretsen fysiskt eftersom hjulet inte är helt runt
		//int doubleToIntFactor = 100000;
		////////////////////////////////////////////////////////////////////////////
		int ticksPassed = 0;	//Do not modify
		int	ticksReference = 0; //Do not modify
		int testNbr = 1; //Do not modify
		int secondsPerTest = 3; //MODIFY for yout test, NOTE: take into account limits of data type if needed
		int speedIncrementFactor = 100; //MODIFY for your test, NOTE: Motorspeed is limited to 0-100
		int step = 0;
		int stepsPerTest = (700/speedIncrementFactor);	
		int pulsesLeft[TESTS] = {};
		int pulsesRight[TESTS] = {};
		int linearActualLeft[TESTS] = {}; //Önskade linjära hastighet för vänster hjul i cm/s
		int linearActualRight[TESTS] = {};
		int distanceLeft[TESTS] = {}; //förflyttning i cm
		int distanceRight[TESTS] = {}; //förflyttning i cm
			//// LAGRA MAX OCH MIN VÄRDET FRÅN HELA ARRAYEN MED LINJÄR HASTIGHET
			int lsMinLeft[TESTS] = {}; //HÖGSTA VÄRDET EN DOUBLE KAN ANTA
			int lsMaxLeft[TESTS] = {};
			int lsMinRight[TESTS] = {};
			int lsMaxRight[TESTS] = {};
					int minimumLeft[STEPS] = {};
					int minimumRight[STEPS] = {};
					int maximumLeft[STEPS] = {};
					int maximumRight[STEPS] = {};
		int testRounds = 1; //Do not modify
		int totalTestRounds = 2; //MODIFY the number of re-runs that all values will then be divided by to get an average
		int totalNbrTests = (700/speedIncrementFactor)*totalTestRounds;
		//KÖR FÖR VARJE RUNDA
		
		
		while(testRounds <= totalTestRounds){
			printf("[[[[[[Test Round:%i]]]]]]\n",testRounds);		
			step = 1;
			while(step < stepsPerTest+1){
				printf("Round#%i Test#%i speed:%i is startning...\n",testRounds,testNbr,speedIncrementFactor*step);
				printf("------\n");
				ticksReference = xTaskGetTickCount(); //BÖRJA KLOCKA
				drive(speedIncrementFactor*step,speedIncrementFactor*step); //SÄTT HASTIGHET
				while(ticksPassed<secondsPerTest*1000){
					ticksPassed =  xTaskGetTickCount() - ticksReference;
				}//NÄR TIDEN ÄR ÖVER
				drive(0,0);
				
				pulsesLeft[testNbr] = getLeftPulses();
				pulsesRight[testNbr] = getRightPulses();
				distanceLeft[testNbr] = (int)(WheelCircum * pulsesLeft[testNbr] / resolution); //Distans färdad är produkten av hjul revolutioner och omkretsen
				distanceRight[testNbr] = (int)(WheelCircum * pulsesRight[testNbr] / resolution);
				//V[f] = (double)((distance[0][f]+distance[1][f])/(2*secondsPerTest)); //linjära hastigheten
				//W[f] = (double)((distance[0][f]-distance[1][f])/(b*secondsPerTest)); //angulära hastigheten
				linearActualLeft[testNbr]  = (int)(distanceLeft[testNbr]/secondsPerTest);
				linearActualRight[testNbr] = (int)(distanceRight[testNbr]/secondsPerTest);
				printf("VL:%i VR:%i \n",linearActualLeft[testNbr],linearActualRight[testNbr]);
				printf("is ending...\n");
				printf("------\n");
				resetCounter();
				step++;
				testNbr++;
				ticksPassed = 0;
			}
			testRounds++;	
		}
		//DENNA DEL VAR TÄNKT ATT TA FRAM MIN OCH MAX VÄRDEN SÅ ATT MAN KAN FÅ EN ANING OM MEDELVÄRDETS TROVÄRDIGHET FÖR DEN LINJÄRA HASTIGHETEN
		//TYVÄRR SÅ FUNGERAR DET INTE MED ATMEL: NÄR ALL KOD AVKOMMENTERAS SÅ AVSLUTAS EXEKVERINGEN FÖR TIDIGT (REDAN VID UTSKRIFTEN AV FÖRSTA RUNDAN)
		//EX. Output: [[[[[[Test R                     SOM KAN SES AVBRYTS EXEKVERINGEN MITT UNDER UTSKRIFTEN VID BÖRJAN OCH ÅTERUPPTAS EJ
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% START %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		/*	
		for(int w = 0;w<(totalTestRounds);w++){
				lsMinLeft[w] = INT_MAX;
				lsMaxLeft[w] = INT_MIN;
				lsMinRight[w] = INT_MAX;
				lsMaxRight[w] = INT_MIN;
		}
		
		for(int a = 0; a < stepsPerTest; a++){
			int minimumL = 7;
			int minimumR = 8;
			int maximumL = 9;
			int maximumR = 10;
			for(int h = a; h < (totalNbrTests);(h=h+stepsPerTest)){
					minimumL = (min(lsMinLeft[a],linearActualLeft[a]));
					minimumR = (min(lsMinRight[a],linearActualRight[a]));
					maximumL = (max(lsMaxLeft[a],linearActualLeft[a]));
					maximumR = (max(lsMaxRight[a],linearActualRight[a]));
			}
			minimumLeft[a] = minimumL;
			minimumRight[a] = minimumR;
			maximumLeft[a] = maximumL;
			maximumRight[a] = maximumR;
		}
		
		for(int u = 0; u<stepsPerTest;u++){
				printf("Min Left:%i\n",minimumLeft[u]);
				printf("Max Left:%i\n",maximumLeft[u]);
				printf("Min Right :%i\n",minimumRight[u]);
				printf("Max Right:%i\n",maximumRight[u]);
		}
		
		for(int j = 0;j<(totalTestRounds);j++){
				for(int i = 0; i < (stepsPerTest);i++){
			pulsesLeft[i]=(pulsesLeft[i]+pulsesLeft[i+stepsPerTest])/totalTestRounds;	
			pulsesRight[i]=(pulsesRight[i]+pulsesRight[i+stepsPerTest])/totalTestRounds;		
			linearActualLeft[i] = (linearActualLeft[i]+linearActualLeft[i+stepsPerTest])/totalTestRounds;
			linearActualRight[i] = (linearActualRight[i]+linearActualRight[i+stepsPerTest])/totalTestRounds;		
				}
		}
		*/
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%	
	
		for(int v = 0; v < stepsPerTest; v++){
			
			printf("--------------------------------------------------------------------------------\n");
			printf("\n");
			printf("$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			printf("Left Wheel Speed:%i Pulses:%i \n",(v+1)*speedIncrementFactor,pulsesLeft[v]);
			printf("LinearSpeed Avg:%i\n",linearActualLeft[v]);
			printf("$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			printf("Right Wheel Speed:%i Pulses:%i \n",(v+1)*speedIncrementFactor,pulsesRight[v]);
			printf("LinearSpeed Avg:%i\n",linearActualRight[v]);
			printf("$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			printf("\n");
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

