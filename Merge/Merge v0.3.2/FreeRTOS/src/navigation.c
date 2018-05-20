/*
 *
 *  Author: 
 */ 

#include "navigation.h"


//Returns the difference between the actual position of the robot and the object it will pick up 
int getDistanceToObject(){
	return sqrt(pow(abs(getPositionX()-getPickupX()),2) +pow(abs(getPositionY()-getPickupY()),2));
}

//Returns the difference between the actual position of the robot and the disposal box where the object will be dropped of
int getDistanceToDropOff(){
	return sqrt(pow(abs(getPositionX()-getDisposalX()),2) +pow(abs(getPositionY()-getDisposalY()),2));
}

// BEHÖVER SKRIVAS OM////////////////////////////////////////
void driveCm(int cm) {
	int p = cm / (WheelCircum/(float)resolution);
// getAvståndKört spara undan kolla om den kört färdigt
	while(!waitForXPulsesRL(p,p)) {
		if(p > 0) {
			drive(10,10,1,1);
			} else {
			drive(10,10,-1,-1);
		}
	}
	drive(0,0,1,1);
}
//////////////////////////////////////////////////////////////

void rotate(int degree) { //degree 1 - 180 or -1 - -180
	resetCounter();//HMMMMMMMMM KAN BEHÖVAS EXTRA RESETCOUNTERS (SEPARATA COUNTERS AV PULSER, EN FÖR REGLERING, EN FÖR NAV)
	float radian = (degree * M_PI) / 180;
	int p = (radian * 0.4 * 144) / (PI * 0.16);
	
	while(!waitForXPulsesRL(p/2,p/2)) {
		if(radian > 0) {
			drive(25,25,-1,1);
			} else if(radian < 0) {
			drive(25,25,1,-1);
		}
	}
	drive(0,0,1,1);
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
	int v1 = atan2(rY-cY, rX-cX) *(180/M_PI) + 180; // the angle we want to have.
	if((v1-u1) > 180)
	return -360 + (v1-u1);
	else if(v1-u1 < -180)
	return 360+(v1-u1);
	else
	return (v1-u1);
	
	//skickar så många pulser som behövs för att svänga correctionAngle många grader.
}