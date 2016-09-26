/*
 * mc_api_dll.c
 *
 *  Created on: Jan 27, 2011
 *      Author: andy
 */

#include <stdio.h>
#include "InterProcess/src/interprocess.h"
#include "mc_api_dll.h"


/*
 * Start Server
 *
 * To Be Used Only by MindControl
 *
 * The server has some unique properties. It does not wait to acquire a mutex.
 * If it tries to access shared memory, and the memory is busy, it will simply return
 * that the memory is busy.
 *
 * The server also has no refractory period. It can read or write in sequence
 * as often as it wants. If the server reads repeatedly in a loop it oculd theoretically
 * lock out other processes from accessing the shared memory, but thats ok, because its the server.
 *
 * By default the client has a 7ms refractory period.
 * When the client reads from shared memory, the process
 * sleeps for 7ms. This ensures that a client cannot lock up the shared memory
 * A client will also wait up to 4ms to acquire a mutex lock.
 *
 *
 * Returns handle to shared memory object
 * Returns NULL if there is an error
 *
 *
 */
SharedMemory_handle  MC_API_StartServer(){

	/* Create shared memory object */
	SharedMemory_handle sm = ip_CreateSharedMemoryHost("mcMem");
	ip_SetSharedMemoryLockWaitTime(sm, 0);

	/** Set Refactory Period to 0 **/
	ip_SetSharedMemoryReadRefractoryPeriodTimeDelay(sm,0);

	/* Set Laser Controller to 0 */
	int val=0;
	ip_WriteValue(sm,"int_laserController",(void *) &val, sizeof(int));
	return sm;

}

/*
 * To Be Used Only by MindControl
 *
 * Returns MC_API_OK or
 * Returns MC_API_ERROR otherwise
 *
 */
int MC_API_StopServer(SharedMemory_handle sm){
	return ip_CloseSharedMemory(sm);
}

/********  Start/Stop CLIENT ****/

/*
 * Returns pointer to Shared Memory handle
 * Returns NULL otherwise.
 *
 * By default the client has a 7ms refractory period.
 * When the client reads from shared memory, the process
 * sleeps for 7ms. This ensures that a client cannot lock up the shared memory
 * A client will also wait up to 4ms to acquire a mutex lock.

 *
 */

SharedMemory_handle MC_API_StartClient(){
	SharedMemory_handle sm = ip_CreateSharedMemoryClient("mcMem");
	return sm;

}

/*
 * Returns MC_API_OK or
 * Returns MC_API_ERROR otherwise
 *
 */
int MC_API_StopClient(SharedMemory_handle sm){
	if (ip_CloseSharedMemory(sm)!=MC_API_OK) return MC_API_ERROR;
	return MC_API_OK;
}





/*** Laser Power **/

/*
 * Check to see if laser controller is present
 *  Returns MC_API_TRUE 1 if laser controller is present
 * Returns MC_API_FALSE 0 if no laser controller is present
 * Returns MC_API_ERROR -1 otherwise
 *
 */
int MC_API_isLaserControllerPresent(SharedMemory_handle sm){
	int val;
	int ret=ip_ReadValue(sm,"int_laserController",(void *) &val);
	if (ret!=MC_API_OK) return MC_API_ERROR;
	if (val!=MC_API_FALSE &&  val!=MC_API_TRUE) return MC_API_ERROR;
	return val;
}

/*
 *  Registers the presence of a laser controller software
 *  that will provide the power level of
 *  the blue or green lasers.
 *
 */
int MC_API_RegisterLaserController(SharedMemory_handle sm){

	/* Set Laser Controller to 1 */
	int val=1;
	int ret=ip_WriteValue(sm,"int_laserController",(void *) &val, sizeof(int));
	if (ret!=MC_API_OK) return MC_API_ERROR;
	return MC_API_OK;

}




/*
 * Unregisters Laser Controller
 *
 */
int MC_API_UnRegisterLaserController(SharedMemory_handle sm){
	/* Set Laser Controller to 1 */
	int val=0;
	int ret=ip_WriteValue(sm,"int_laserController",(void *) &val, sizeof(int));
	if (ret!=MC_API_OK) return MC_API_ERROR;
	return MC_API_OK;

}


/*
 *  Set the Laser Power, an integer value between 1 and 100
 *
 */
int MC_API_SetGreenLaserPower(SharedMemory_handle sm, int power){

	int ret=ip_WriteValue(sm,"int_greenLaserPower",(void *) &power, sizeof(int));
	if (ret!=MC_API_OK) return MC_API_ERROR;
	return MC_API_OK;
}


/*
 *  Set the Laser Power, an integer value between 1 and 100
 */
int MC_API_SetBlueLaserPower(SharedMemory_handle sm, int power){

	int ret=ip_WriteValue(sm,"int_blueLaserPower",(void *) &power, sizeof(int));
	if (ret!=MC_API_OK) return MC_API_ERROR;
	return MC_API_OK;
}


/*
 * Get the laser power. An integer value between 1 and 100
 * Returns MC_API_ERROR if the value cannot be acquired.
 */
int MC_API_GetBlueLaserPower(SharedMemory_handle sm){
	int val=0;
	int ret=ip_ReadValue(sm,"int_blueLaserPower",(void *) &val);
	if (ret!=MC_API_OK) return MC_API_ERROR;

	return val;
}


/*
 * Get the laser power. An integer value between 1 and 100
 * Returns MC_API_ERROR if the value cannot be acquired.
 */
int MC_API_GetGreenLaserPower(SharedMemory_handle sm){
	int val=0;
	int ret=ip_ReadValue(sm,"int_greenLaserPower",(void *) &val);
	if (ret!=MC_API_OK) return MC_API_ERROR;
	return val;
}

/** Current Frame **/

/*
 * Set current frame
 *  Returns MC_API_OK
 *  Returns MC_API_ERROR if error.
 */
int MC_API_SetCurrentFrame(SharedMemory_handle sm, int frame){
	int ret=ip_WriteValue(sm,"int_currFrame",(void *) &frame, sizeof(int));
	if (ret!=MC_API_OK) return MC_API_ERROR;
	return MC_API_OK;
}


/*
 * Get current frame
 *  Returns MC_API_OK
 *  Returns MC_API_ERROR if error.
 */
int MC_API_GetCurrentFrame(SharedMemory_handle sm){
	int val=0;
	int ret=ip_ReadValue(sm,"int_currFrame",(void *) &val);
	if (ret!=MC_API_OK) return MC_API_ERROR;
	return val;

}

/************* DLP is on / off ****************/

/*
 * Set DLP on/off
 *  Returns MC_API_OK
 *  Returns MC_API_ERROR if error.
 */
int MC_API_SetDLPOnOff(SharedMemory_handle sm, int isOn){
	int ret=ip_WriteValue(sm,"int_DLPisOn",(void *) &isOn, sizeof(int));
	if (ret!=MC_API_OK) return MC_API_ERROR;
	return MC_API_OK;
}


/*
 * Get DLP on/off
 *  Returns 1 if on
 *  Returns 0 if off
 *  Returns MC_API_ERROR if error.
 */
int MC_API_GetDLPOnOff(SharedMemory_handle sm){
	int val=0;
	int ret=ip_ReadValue(sm,"int_DLPisOn",(void *) &val);
	if (ret!=MC_API_OK) return MC_API_ERROR;
	if (ret!=MC_API_TRUE && ret!=MC_API_FALSE) return MC_API_ERROR;
	return val;
}

/*
 * Returns MC_API_OK if server is running
 * Returns MC_API_ERROR otherwise
 */
int MC_API_PingServer(SharedMemory_handle sm){
	if (ip_GetSharedMemoryStatus(sm) >= 0) return MC_API_OK;
	return MC_API_ERROR;
}



