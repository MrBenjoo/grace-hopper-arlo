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
		
		
		//OBS F�RSIKTIG MED UINTS_16 och 8 ber�kningarna blir konstiga med dem!!!!!!!///
		int resolution = 144; //Uppl�sningen, antal pulser per revolution
		double radius = 7.9; //Hjulens radie �r 7.9cm
		double WheelCircum = (double)(2*M_PI*radius); //Hjulets omkrets. Kan ber�knas mer korrekt genom att m�ta omkretsen fysiskt eftersom hjulet inte �r helt runt
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
		int linearActualLeft[TESTS] = {}; //�nskade linj�ra hastighet f�r v�nster hjul i cm/s
		int linearActualRight[TESTS] = {};
		int distanceLeft[TESTS] = {}; //f�rflyttning i cm
		int distanceRight[TESTS] = {}; //f�rflyttning i cm
			//// LAGRA MAX OCH MIN V�RDET FR�N HELA ARRAYEN MED LINJ�R HASTIGHET
			int lsMinLeft[TESTS] = {}; //H�GSTA V�RDET EN DOUBLE KAN ANTA
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
		//K�R F�R VARJE RUNDA
		
		
		while(testRounds <= totalTestRounds){
			printf("[[[[[[Test Round:%i]]]]]]\n",testRounds);		
			step = 1;
			while(step < stepsPerTest+1){
				printf("Round#%i Test#%i speed:%i is startning...\n",testRounds,testNbr,speedIncrementFactor*step);
				printf("------\n");
				ticksReference = xTaskGetTickCount(); //B�RJA KLOCKA
				drive(speedIncrementFactor*step,speedIncrementFactor*step); //S�TT HASTIGHET
				while(ticksPassed<secondsPerTest*1000){
					ticksPassed =  xTaskGetTickCount() - ticksReference;
				}//N�R TIDEN �R �VER
				drive(0,0);
				
				pulsesLeft[testNbr] = getLeftPulses();
				pulsesRight[testNbr] = getRightPulses();
				distanceLeft[testNbr] = (int)(WheelCircum * pulsesLeft[testNbr] / resolution); //Distans f�rdad �r produkten av hjul revolutioner och omkretsen
				distanceRight[testNbr] = (int)(WheelCircum * pulsesRight[testNbr] / resolution);
				//V[f] = (double)((distance[0][f]+distance[1][f])/(2*secondsPerTest)); //linj�ra hastigheten
				//W[f] = (double)((distance[0][f]-distance[1][f])/(b*secondsPerTest)); //angul�ra hastigheten
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
		//DENNA DEL VAR T�NKT ATT TA FRAM MIN OCH MAX V�RDEN S� ATT MAN KAN F� EN ANING OM MEDELV�RDETS TROV�RDIGHET F�R DEN LINJ�RA HASTIGHETEN
		//TYV�RR S� FUNGERAR DET INTE MED ATMEL: N�R ALL KOD AVKOMMENTERAS S� AVSLUTAS EXEKVERINGEN F�R TIDIGT (REDAN VID UTSKRIFTEN AV F�RSTA RUNDAN)
		//EX. Output: [[[[[[Test R                     SOM KAN SES AVBRYTS EXEKVERINGEN MITT UNDER UTSKRIFTEN VID B�RJAN OCH �TERUPPTAS EJ
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

