/*
 *
 *  Author: 
 */ 

#include "navigation.h"
#include <asf.h>
#include <math.h>
#include <stdio.h>
#include "../I2C/I2CFunctions.h"
#include "../initializations/pins_init.h"
#include "../tasks/position.h"
#include "../tasks/regulator.h"
#include "../encoderISR.h"
#include "../navigation.h"
 #include <math.h>
 #define PI 3.14159265
//#include "dimensions.h"
#include "motorController.h"

float desiredLeftSpeed = 0;
float desiredRightSpeed = 0;
		
		//Sets desired speed for each wheel
		void setDesiredSpeed(float dSpeedL, float dSpeedR){
			desiredLeftSpeed = dSpeedL;
			desiredRightSpeed = dSpeedR;		
		}
		
		//Returns the desired speed for left wheel
		float getDesiredSpeedLeft(){
			return desiredLeftSpeed;
		}
		//Returns the desired speed for right wheel
		float getDesiredSpeedRight(){
			return desiredRightSpeed;
		}
		//Returns the difference between the actual position of the robot and a destination
		int getDistanceToDestination(int x, int y){
			return sqrt(pow(abs(getPositionX()-x),2) +pow(abs(getPositionY()-y),2));
		}
		
		//Returns the difference between the actual position of the robot and the object it will pick up 
		int getDistanceToObject(){
			return sqrt(pow(abs(getPositionX()-getPickupX()),2) +pow(abs(getPositionY()-getPickupY()),2));
		}

		//Returns the difference between the actual position of the robot and the disposal box where the object will be dropped of
		int getDistanceToDropOff(){
			return sqrt(pow(abs(getPositionX()-getDisposalX()),2) +pow(abs(getPositionY()-getDisposalY()),2));
		}

		void driveCm(float cm,float velocity) {
			float startline = getDisplacementAverage();
			while((abs(getDisplacementAverage()-startline))<cm){
				setDesiredSpeed(velocity,velocity);
			}	
			setDesiredSpeed(0,0);
		}

/*		void rotate(int degree) { //degree 1 - 180 or -1 - -180
			//resetCounter();
			long k = 0;
			float radian = (float)((((float)degree * PI) / (float)180)/2);
			int p = (int)((radian * 0.4 * (int)144) / (PI * 0.16));
			long pLStart = getPulsesSinceStartLeft();
			//long pRStart = getPulsesSinceStartRight();
			printf("pLStart_________ %li\n",pLStart);
			while(k < 180){ //&& (getPulsesSinceStartRight() - pRStart) < (long)(p/2)) {
				printf("PULSESESESESSES LEFT: %li\n",k); 
				k = abs(getPulsesSinceStartLeft()-pLStart);
				if(radian > 0) {
					setDesiredSpeed(-150,150);
				} else if(radian < 0) {
					setDesiredSpeed(150,-150);
				}
			}
			setDesiredSpeed(0,0);
		}*/
		void rotate(float degree){
			printf("YY1YY %i\n",(int)degree*100000);
			rotateM(degree,100);
		}
		void rotateM(float degree,float angVel) { //degree 1 - 180 or -1 - -180
			printf("YY2YY %i\n",(int)degree*100000);
			float startAngle = getChangeInAngle();
			while((abs(getChangeInAngle()-startAngle))<abs(degree)){
				if(degree<0) //rotate right
					drive(100,-100);
				if(degree>0) //rotate left
					drive(-100,100);
			} 
			drive(0,0);
			setDesiredSpeed(0,0);
		}
		
		int getAngle(int p1X, int p1Y, int p2X, int p2Y) {
			// atan2 returns angle in radians, we multiply by (180/PI) to change it to degrees and add 180 to change the reference
			int angle = (int)((atan2(p1Y-p2Y, p1X-p2X) * (180/M_PI)) + 180);
			if(angle == 360)
				angle = 0;
			return angle;
		}
	
	
		float angleCorrection(int rX,int rY,int cX,int cY,int u1) { // r = robotic position, c = coordinate position, u1 = angle of robot.
		// atan2 returns angle in radians, we multiply by (180/PI) to change it to degrees and add 180 to change the reference

		
			int v1 = atan2(rY-cY, rX-cX) *(180/M_PI) + 180; // the angle we want to change.
		// The method "rotate" does only take values in the range of 1 to 180 and  -1 to -180. 
		//Because of this we have to check the value that where suppose to be returned and change it with a shift to make it in the acceptable range.					
			if((v1-u1) > 180)
				return -360 + (v1-u1);
			else if(v1-u1 < -180)
				return 360+(v1-u1);
			else
				return (v1-u1);
	//skickar s� m�nga pulser som beh�vs f�r att sv�nga correctionAngle m�nga grader.
		}
	
