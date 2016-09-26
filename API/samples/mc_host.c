/*
 * mc_host.c
 *
 *  Created on: Jan 28, 2011
 *      Author: andy
 */

#include <conio.h>
#include <stdio.h>

#include "../mc_api_dll.h"

int main(){
	printf("Starting server.\n");
	/** Start the server**/
	SharedMemory_handle sm=MC_API_StartServer();

	int k=0;
	int max=10;
	for (k = 0; k < max; ++k) {

		printf("Hit enter  to continue (%d of %d)\n",k,max);
		getch();
		printf("\n\n=====================\n");
		printf("Frame number is %d\n",k);
		MC_API_SetCurrentFrame(sm,k);

		printf("Setting DLP %d\n", k % 2);
		MC_API_SetDLPOnOff(sm,k%2);

		if (MC_API_isLaserControllerPresent(sm)== MC_API_TRUE){
			printf("Laser Controller present! Power is Green %d, Blue %d\n",MC_API_GetGreenLaserPower(sm), MC_API_GetBlueLaserPower(sm) );
		} else{
			printf("Laser Controller is not present.\n");
		}


	}

	printf("Stopping server.. %d\n",MC_API_StopServer(sm));
	printf("Goodbye!");



}
