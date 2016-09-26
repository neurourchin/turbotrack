#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "MyLibs/Talk2Stage.h"


int main(){
	printf("Testing the Ludl stage.\nWait\n");
	HANDLE stage=InitializeUsbStage();
	
	
	int k=1;
	int key=0;
	
	float x;
	float y;
	float t;
	
	int commandInterval=5;
	
	printf("Sending commands with %d ms interval\n",commandInterval);
	while (1) {
		Sleep(commandInterval);
		t=(float) k;
		
		//Generate circle in velocity space
		x=10000*sin(t/300);
		y=10000*cos(t/300);
		
		// Convert floats to int
		int vx, vy;
		vx=(int) x;
		vy= (int) y;
		
		//Send velocity command to stage
		//moveStageRel(stage,vx,vy);
		spinStage(stage,vx,vy);
		
		if (k%100==0){
			printf("\n%d commands sent",k);	
			printf(" current velocity: %d, %d\n",vx, vy);
		}
		printf(".");
		k=k+1;
	}



	return 0;
}
