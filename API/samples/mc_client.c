/*
 * mc_client.c
 *
 *  Created on: Jan 28, 2011
 *      Author: andy
 */

#include <conio.h>
#include <stdio.h>

#include "../mc_api_dll.h"

int main(){
	printf("Starting client.\n");
	/** Start the server**/
	SharedMemory_handle sm=MC_API_StartClient();

	/** Register the laser controller **/
	printf("Registering the laser controller..\n");
	MC_API_RegisterLaserController(sm);



	/** Set different values for laser power **/

	int k=0;
	int max=10;
	int g=0;
	int b=0;
	for (k = 0; k < max; ++k) {
		printf("Hit enter  to continue (%d of %d)\n",k,max);
		getch();
		printf("\n\n=====================\n");
		g=k;
		b=2*k;
		MC_API_SetGreenLaserPower(sm, g);
		MC_API_SetBlueLaserPower(sm, b);
		printf("Setting blue to %d, and green to %d.\n",b,g);
		int f=MC_API_GetCurrentFrame(sm);
		printf("Current frame is %d\n",f);
		int dlp=MC_API_GetDLPOnOff(sm);
		printf("DLP is %d\n",dlp);
	}
	MC_API_UnRegisterLaserController(sm);
	printf("Stopping client.. %d\n",MC_API_StopClient(sm));
	printf("Goodbye!");



}
