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
		float radius = 7.9; //Hjulens radie �r 7.9cm
		float WheelCircum = (float)(2*M_PI*radius); //Hjulets omkrets. Kan ber�knas mer korrekt genom att m�ta omkretsen fysiskt eftersom hjulet inte �r helt runt
		int doubleToIntFactor = 100000;
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
		float linearActualLeft[TESTS] = {}; //�nskade linj�ra hastighet f�r v�nster hjul i cm/s
		float linearActualRight[TESTS] = {};
		float distanceLeft[TESTS] = {}; //f�rflyttning i cm
		float distanceRight[TESTS] = {}; //f�rflyttning i cm
			//// LAGRA MAX OCH MIN V�RDET FR�N HELA ARRAYEN MED LINJ�R HASTIGHET
			float lsMinLeft[TESTS] = {}; //H�GSTA V�RDET EN DOUBLE KAN ANTA
			float lsMaxLeft[TESTS] = {};
			float lsMinRight[TESTS] = {};
			float lsMaxRight[TESTS] = {};
					float minimumLeft[STEPS] = {};
					float minimumRight[STEPS] = {};
					float maximumLeft[STEPS] = {};
					float maximumRight[STEPS] = {}; 
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
				distanceLeft[testNbr] = (float)(WheelCircum * pulsesLeft[testNbr] / resolution); //Distans f�rdad �r produkten av hjul revolutioner och omkretsen
				distanceRight[testNbr] = (float)(WheelCircum * pulsesRight[testNbr] / resolution);
				//V[f] = (double)((distance[0][f]+distance[1][f])/(2*secondsPerTest)); //linj�ra hastigheten
				//W[f] = (double)((distance[0][f]-distance[1][f])/(b*secondsPerTest)); //angul�ra hastigheten
				linearActualLeft[testNbr]  = (float)((distanceLeft[testNbr]/secondsPerTest));
				linearActualRight[testNbr] = (float)((distanceRight[testNbr]/secondsPerTest));
				printf("VL:%i VR:%i \n",(int)(linearActualLeft[testNbr]*doubleToIntFactor),(int)(linearActualRight[testNbr]*doubleToIntFactor));
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
			
		for(int w = 0;w<totalNbrTests;w++){
				lsMinLeft[w] = (float)(9999);
				lsMaxLeft[w] = (float)(-9999);
				lsMinRight[w] = (float)(9999);
				lsMaxRight[w] = (float)(-9999);
		}
		
		for(int a = 0; a < stepsPerTest; a++){
			float minimumL = (float)7; //inget speciellt v�rde, det skrivs �ver om allt fungerar som det skall, bara f�r debugging
			float minimumR = (float)8;
			float maximumL = (float)9;
			float maximumR = (float)10;
			for(int h = a; h < totalNbrTests;h+=stepsPerTest){
					minimumL = (float)(min(lsMinLeft[h],linearActualLeft[h]));
					minimumR = (float)(min(lsMinRight[h],linearActualRight[h]));
					maximumL = (float)(max(lsMaxLeft[h],linearActualLeft[h]));
					maximumR = (float)(max(lsMaxRight[h],linearActualRight[h]));
			}
			minimumLeft[a] = minimumL;
			minimumRight[a] = minimumR;
			maximumLeft[a] = maximumL;
			maximumRight[a] = maximumR;
		}
		
		for(int u = 0; u<stepsPerTest;u++){
				printf("Min Left :%i ",(int)(minimumLeft[u]*doubleToIntFactor));
				printf("Max Left: %i ",(int)(maximumLeft[u]*doubleToIntFactor));
				printf("Min Right :%i ",(int)(minimumRight[u]*doubleToIntFactor));
				printf("Max Right: %i ",(int)(maximumRight[u]*doubleToIntFactor));
		}
		
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		
		/// V1.4 KAN BEH�VA DENNA KODEN NEDAN F�R ATT BER�KNA MEDELV�RDE
		for(int j = 0;j<stepsPerTest;j++){
				for(int i = j+stepsPerTest; i < totalNbrTests;i+=stepsPerTest){
			pulsesLeft[j]+=(int)(pulsesLeft[i]);	
			pulsesRight[j]+=(int)(pulsesRight[i]);		
			linearActualLeft[j] += (float)(linearActualLeft[i]);
			linearActualRight[j] += (float)(linearActualRight[i]);		
				}
		}
		
		for(int e = 0;e <stepsPerTest; e++){
			pulsesLeft[e]=(int)(pulsesLeft[e]/totalTestRounds);
			pulsesRight[e] =(int)(pulsesRight[e]/totalTestRounds);
			linearActualLeft[e] = (float)(linearActualLeft[e]/totalTestRounds);
			linearActualRight[e] = (float)(linearActualRight[e]/totalTestRounds);
		}
		
		
	
		for(int v = 0; v < stepsPerTest; v++){
			
			printf("--------------------------------------------------------------------------------\n");
			printf("\n");
			printf("$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			printf("Left Wheel Speed:%i Pulses:%i \n",(v+1)*speedIncrementFactor,pulsesLeft[v]);
			printf("LinearSpeed Avg:%i\n",(int)(linearActualLeft[v]*doubleToIntFactor));
			printf("$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			printf("Right Wheel Speed:%i Pulses:%i \n",(v+1)*speedIncrementFactor,pulsesRight[v]);
			printf("LinearSpeed Avg:%i\n",(int)(linearActualRight[v]*doubleToIntFactor));
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

