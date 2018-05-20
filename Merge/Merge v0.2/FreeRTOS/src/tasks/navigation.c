/*
 *
 *  Author: 
 */ 

#include "navigation.h"

target = kub; //this variable determines which item is the target

void navigation(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = xTimeT1/portTICK_RATE_MS; /* set ticks (xTimeT1) in milliseconds */
	xLastWakeTime = xTaskGetTickCount();					/* the count of ticks since vTaskStartScheduler was called */
	
	while (1) /* the task must be looping infinitely */
	{
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* constant period, independent of execution time */
		
		if (read_package(TWI_SLAVE_ADR_POS)==DATA_READ) //retrieves data from the positioning-squad
		{
			disposalX=2*rec_data_pos[0];
			disposalY=2*rec_data_pos[1];
			
			posX=2*rec_data_pos[8];
			posY=2*rec_data_pos[9];
			
			printf("xpos %i",rec_data_pos[8]);
			
			
			if(target==kub){
				pickupX=2*rec_data_pos[2];
				pickupY=2*rec_data_pos[3];
			}
			else if(target==vinglas){
				pickupX=2*rec_data_pos[6];
				pickupY=2*rec_data_pos[7];
			}else{
			//possibly add some error handling here;
			printf("FAIL");
			}
		
		}
}


int getPickupX(){ //returns the X-coordinates for the pickup
	return pickupX;
}
int getPickupY(){ //returns the Y-coordinates for the pickup
	return pickupY;
}
int getPositionX(){ //returns current X-coordinate
	return posX;
}
int getPositionY(){ //returns current Y-coordinate
	return posY;
}
int getDisposalX(){ //returns the X-coordinates for the disposal-area
	return disposalX;
}
int getDisposalY(){ //returns the Y-coordinates for the disposal-area
	return disposalY;
}
void setTarget(int item){ //sets which item to target
	target=item;
}
int getDistanceToObject(){
	return sqrt(pow(abs(getPositionX()-getPickupX()),2) +pow(abs(getPositionY()-getPickupY()),2));
}
int getDistanceToDropOff(){
	return sqrt(pow(abs(getPositionX()-getDisposalX()),2) +pow(abs(getPositionY()-getDisposalY()),2));
}

void driveCm(int cm) {
	int p = cm / (50/(float)144);

	while(!waitForXPulsesRL(p,p)) {
		if(p > 0) {
			drive(10,10,1,1);
			} else {
			drive(10,10,-1,-1);
		}
	}
	drive(0,0,1,1);
}

void rotate(int degree) { //degree 1 - 180 or -1 - -180
	resetCounter();
	float radian = (degree * PI) / 180;
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
	int angle = (atan2(p1Y-p2Y, p1X-p2X) * (180/PI)) + 180;
	if(angle == 360)
	angle = 0;
	return angle;
}
int angleCorrection(int rX,int rY,int cX,int cY,int u1) { // r = robotic position, c = coordinate position, u1 = angle of robot.
	// atan2 returns angle in radians, we multiply by (180/PI) to change it to degrees and add 180 to change the reference
	int v1 = atan2(rY-cY, rX-cX) *(180/PI) + 180; // the angle we want to have.
	if((v1-u1) > 180)
	return -360 + (v1-u1);
	else if(v1-u1 < -180)
	return 360+(v1-u1);
	else
	return (v1-u1);
	
	//skickar så många pulser som behövs för att svänga correctionAngle många grader.
}