/*
 *
 *  Author: 
 */ 

#include "navigation.h"

		
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
				drive(velocity,velocity);
			}	
			drive(stop,stop);
		}


		//turndir: rotate left = 0, rotate right = 1
		void rotate(float degree,float angVel,int turnDir) { //degree 1 - 180 or -1 - -180
			float startAngle = getChangeInAngle();
			while((abs(getChangeInAngle()-startAngle))<degree){
				if(turnDir) //rotate right
					drive(angVel,((-1)*angVel));
				if(!turnDir) //rotate left
					drive(((-1)*angVel),angVel);
			} 
			drive(stop,stop);
		}

		int getAngle(int p1X, int p1Y, int p2X, int p2Y) {
			// atan2 returns angle in radians, we multiply by (180/PI) to change it to degrees and add 180 to change the reference
			int angle = (int)((atan2(p1Y-p2Y, p1X-p2X) * (180/M_PI)) + 180);
			if(angle == 360)
				angle = 0;
			return angle;
		}
	
	
		int angleCorrection(int rX,int rY,int cX,int cY,int u1) { // r = robotic position, c = coordinate position, u1 = angle of robot.
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
	
