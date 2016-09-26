/*
 * mc_api_dll.h
 *
 *  Created on: Jan 27, 2011
 *      Author: andy
 */

#ifndef MC_API_DLL_H_
#define MC_API_DLL_H_


#ifdef __cplusplus
extern "C" {
#endif



#ifdef BUILDING_MC_API_DLL
#define MC_API_DLL __declspec(dllexport)
#else
#define MC_API_DLL __declspec(dllimport)
#endif




#define MC_API_OK 0
#define MC_API_ERROR -1

#define MC_API_TRUE 1
#define MC_API_FALSE 0

/*
 * This is the SharedMemory object from interprocess.h

 *
 */
typedef struct SharedMemory_t *SharedMemory_handle;

/*
 * Returns MC_API_OK if server is running
 * Returns MC_API_ERROR otherwise
 */
int MC_API_PingServer(SharedMemory_handle sm);

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
SharedMemory_handle MC_API_StartServer();


/*
 * To Be Used Only by MindControl
 *
 * Returns MC_API_OK or
 * Returns MC_API_ERROR otherwise
 *
 */
int MC_API_StopServer(SharedMemory_handle sm);

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
SharedMemory_handle MC_API_StartClient();

/*
 * Returns MC_API_OK or
 * Returns MC_API_ERROR otherwise
 *
 */
int MC_API_StopClient(SharedMemory_handle sm);

/*
 *  Registers the presence of a laser controller software
 *  that will provide the power level of
 *  the blue or green lasers.
 *
 */
int MC_API_RegisterLaserController(SharedMemory_handle sm);

/*
 * Check to see if laser controller is present
 *  Returns MC_API_TRUE 1 if laser controller is present
 * Returns MC_API_FALSE 0 if no laser controller is present
 * Returns MC_API_ERROR -1 otherwise
 *
 */
int MC_API_isLaserControllerPresent(SharedMemory_handle sm);


/*
 * Unregisters Laser Controller
 *
 */
int MC_API_UnRegisterLaserController(SharedMemory_handle sm);

/*
 *  Set the Laser Power, an integer value between 1 and 100
 *  Returns MC_API_OK
 *  Returns MC_API_ERROR if error.
 */
int MC_API_SetGreenLaserPower(SharedMemory_handle sm, int power);
int MC_API_SetBlueLaserPower(SharedMemory_handle sm, int power);

/*
 * Get the laser power. An integer value between 1 and 100
 * Returns MC_API_ERROR if the value cannot be acquired.
 */
int MC_API_GetGreenLaserPower(SharedMemory_handle sm);
int MC_API_GetBlueLaserPower(SharedMemory_handle sm);



/*
 * Set current frame
 *  Returns MC_API_OK
 *  Returns MC_API_ERROR if error.
 */
int MC_API_SetCurrentFrame(SharedMemory_handle sm, int frame);


/*
 * Get current frame
 *  Returns frame number
 *  Returns MC_API_ERROR if error.
 */
int MC_API_GetCurrentFrame(SharedMemory_handle sm);

/*
 * Set DLP on/off
 *  Returns MC_API_OK
 *  Returns MC_API_ERROR if error.
 */
int MC_API_SetDLPOnOff(SharedMemory_handle sm, int isOn);


/*
 * Get DLP on/off
 *  Returns 1 if on
 *  Returns 0 if off
 *  Returns MC_API_ERROR if error.
 */
int MC_API_GetDLPOnOff(SharedMemory_handle sm);








#ifdef __cplusplus
}
#endif



#endif /* MC_API_DLL_H_ */
