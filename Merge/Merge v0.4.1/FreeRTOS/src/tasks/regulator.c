#include "regulator.h"
/*

*/
void regulator(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = sampleTime/portTICK_RATE_MS; /* set ticks (xTimeT1) in milliseconds */
	xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
long	N_ss_Left = 0; //pulses since start
long    N_ss_Right = 0;
float displacementLeft = 0;
float displacementRight = 0;
float displacementAverage = 0;
float changeInAngle = 0;
long	N_Left = 0; //Antalet pulser för vänster encoder, long = 64bits
long	N_Right = 0;	//Antalet pulser för vänster encoder, long = 64bits	
float	distanceLeft = 0; //Distans färdad är produkten av hjul revolutioner och omkretsen
float	distanceRight = 0;
float	Ts = (float)(sampleTime/(float)1000); //samplingtiden i sekunder 
float	linearLeftDesired = 0; //Önskade linjära hastighet för vänster hjul i cm/s
float	linearRightDesired = 0; 
float	linearLeftActual = 0; //Aktuella linjära hastighet för vänster hjul i cm/s
float	linearRightActual = 0;
float	OldP_err_Left = 0; //Gamla felvärdet behövs för differentialen
float	OldP_err_Right = 0; //Gamla felvärdet behövs för differentialen
float	P_err_Left = 0; //Proportions felvärdet 
float	P_err_Right = 0; //Proportions felvärdet 
long double	I_err_Left = 0; //Integrations felvärdet
long double	I_err_Right = 0; //Integrations felvärdet
float	D_err_Left = 0; //Differentials felvärdet
float	D_err_Right = 0; //Differentials felvärdet
float	Kp = 1.23;
float	Ki = 0.020;
float	Kd = 0.0001; 
float	mcPulseLeft = 0;
float	mcPulseRight = 0;
float	mcPulseLeftOld = 0;
float	mcPulseRightOld = 0;
float	linearSpeedMargin = 5.0;
int	leftTrue = 0;
int	rightTrue = 0;

	
	while(1){
		
			vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); //Taskdelay = SampleTime
			ioport_set_pin_level(PIO_PB27_IDX, HIGH); //För att räkna Tasktime
			printf("---------------sampleTime: %i ----------------\n",(int)(Ts*doubleToIntFactor));	
			linearLeftDesired = 40.000; // Börvärden i cm/s ,lika stora värden om den ska köra rakt 
			linearRightDesired = 40.000;

			
//MODUL 1/////////////////////////////////////////////////////////		
		//fetcha pulser från vänser och höger encoder sedan senast samplen
		N_Left = getLeftPulses(); 
		N_Right = getRightPulses(); 
		N_ss_Left += N_Left;
		N_ss_Right += N_Right;
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
		linearLeftActual = (float)(distanceLeft/Ts);
		linearRightActual = (float)(distanceRight/Ts);
		printf("linearLeftActual %i \n",(int)(linearLeftActual*doubleToIntFactor));
		printf("linearRightActual %i \n",(int)(linearRightActual*doubleToIntFactor));
//MODUL 2/////////////////////////////////////////////////////////			
		//Lagra föregående felvärde
		OldP_err_Left = P_err_Left;
		OldP_err_Right = P_err_Right;
		
		//Beräkna proportions felvärdet: skillnaden mellan önskad hastighet och aktuell hastighet
		P_err_Left = linearLeftDesired-linearLeftActual;
		P_err_Right = linearRightDesired-linearRightActual;
		printf("P_err_Left: %i\n",(int)(P_err_Left*doubleToIntFactor));
		printf("P_err_High: %i\n",(int)(P_err_Right*doubleToIntFactor));
		//Beräkna differential felvärdet: skillnaden mellan nuvarande och föregående fel
		D_err_Left = P_err_Left - OldP_err_Left;
		D_err_Right = P_err_Right - OldP_err_Right;
		printf("D_err_Left %i \n",(int)(D_err_Left*doubleToIntFactor));
		printf("D_err_Right %i \n",(int)(D_err_Right*doubleToIntFactor));
		//Beräkna integral felvärdet: Summan av alla fel
		I_err_Left += (long double)(round(P_err_Left));
		I_err_Right += (long double)(round(P_err_Right));
		printf("I_err_Left %i \n",(int)(I_err_Left*doubleToIntFactor));
		printf("I_err_Right %i \n",(int)(I_err_Right*doubleToIntFactor));
		//Beräkna den nya PWM pulsen för varje hjul
		mcPulseLeftOld = getSetLeftSpeed();
		mcPulseRightOld = getSetRightSpeed();
		printf("mcPulseLeftOld: %i\n",(int)(mcPulseLeftOld*doubleToIntFactor));
		printf("mcPulseRightOld: %i\n",(int)(mcPulseRightOld*doubleToIntFactor));
		printf("PROPORTIONELLA KOMPENSERINGEN: %i\n",(int)(Kp * P_err_Left * doubleToIntFactor));
		printf("DERIVERINGS KOMPENSERINGEN: %i\n",(int)(Kd *(D_err_Left / Ts) * doubleToIntFactor));
		printf("INTEGRERINGS KOMPENSERINGEN: %i\n",(int)(Ki * I_err_Right * Ts * doubleToIntFactor));
		
		mcPulseLeft = (float)((Kp * P_err_Left + Ki * I_err_Left * Ts + Kd *D_err_Left / Ts)+mcPulseLeftOld);
		
		mcPulseRight = (float)((Kp * P_err_Right + Ki * I_err_Right * Ts + Kd *D_err_Right / Ts)+mcPulseRightOld);
		
		if(mcPulseLeft > 300 || mcPulseRight > 300){
			printf("OVER THREE HUNDRED\n");
		}
		
		printf("mcPulseLeft BF correction %i\n",(int)(mcPulseLeft*doubleToIntFactor));
		printf("mcPulseRight BF correction %i\n",(int)(mcPulseRight*doubleToIntFactor));
	
		if( !((int)(mcPulseLeft*doubleToIntFactor) == (int)(getSetLeftSpeed()*doubleToIntFactor) || ((abs(linearLeftActual - linearLeftDesired)>linearSpeedMargin) && !((int)(linearLeftActual*doubleToIntFactor)==(int)(linearRightActual*doubleToIntFactor))))){
					//Begränsa styrvärdet för vänstra motorkontrollerar pulsen till 100-475
			if(mcPulseLeft>475){
				mcPulseLeft = 475;
			}else if(mcPulseLeft<-475){
				mcPulseLeft = -475;
			}
			leftTrue = 1;
		}	
																	
		if( !((int)(mcPulseRight*doubleToIntFactor) == (int)(getSetRightSpeed()*doubleToIntFactor) || ((abs(linearRightActual - linearRightDesired)>linearSpeedMargin) && !((int)(linearRightActual*doubleToIntFactor)==(int)(linearLeftActual*doubleToIntFactor))))){
			//Begränsa styrvärdet för vänstra motorkontrollerar pulsen till 100-475
			if(mcPulseRight>475){
				mcPulseRight = 475;
			}else if(mcPulseRight<-475){
				mcPulseRight = -475;
			}
			rightTrue = 1;
		}
		
		//Skicka ut de nya PWM pulserna till motorkontrollerarna
		if(leftTrue){
			testDriveL(mcPulseLeft);
		}
		if(rightTrue){
			testDriveR(mcPulseRight);
		}
		leftTrue = 0;
		rightTrue = 0;
		printf("mcPulseLeft AF correction %i\n",(int)(mcPulseLeft*doubleToIntFactor));
		printf("mcPulseRight AF correction %i\n",(int)(mcPulseRight*doubleToIntFactor));
	
		
	ioport_set_pin_level(PIO_PB27_IDX, LOW);
	}
	
	
	//returns pulses counted on left wheel since start  
	long getPulsesSinceStartLeft(){
		return N_ss_Left;
	}
	
	//pulses counted on right wheel since start  
	long getPulsesSinceStartRight(){
		return N_ss_Right;
	}
	
	//returns total displacement of left wheel
	float getDisplacementLeft(){
			return (float)(dPP*N_ss_Left);
	}
	//returns total displacement of right wheel
	float getDisplacementRight(){
		return (float)(dPP*N_ss_Right);
	}
	//returns average displacement
	float getDisplacementAverage(){
		return (float)((getDisplacementLeft()+getDisplacementRight())/2);
	}
	//returns total change in rotation
	float getChangeInAngle(){
		return (float)(((displacementLeft-displacementRight)/wheelToWheel)*(180/M_PI));
	}

}

