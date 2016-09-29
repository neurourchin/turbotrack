/*
 * Copyright 2010 Andrew Leifer et al <leifer@fas.harvard.edu>
 * This file is part of MindControl.
 *
 * MindControl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU  General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MindControl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MindControl. If not, see <http://www.gnu.org/licenses/>.
 *
 * For the most up to date version of this software, see:
 * http://github.com/samuellab/mindcontrol
 *
 *
 *
 * NOTE: If you use any portion of this code in your research, kindly cite:
 * Leifer, A.M., Fang-Yen, C., Gershow, M., Alkema, M., and Samuel A. D.T.,
 * 	"Optogenetic manipulation of neural activity with high spatial resolution in
 *	freely moving Caenorhabditis elegans," Nature Methods, Submitted (2010).
 */


/** C includes **/
#include    <stdio.h>
#include    <conio.h>


/** BitFlow SDK includes **/


#include    "CiApi.h"
#include	"BFApi.h"
#include	"BFErApi.h"
#include	"DSapi.h"
#include 	"BiApi.h"
#include	"Gn2TabError.h"
#include "Talk2FrameGrabber.h"






FrameGrabber* CreateFrameGrabberObject(){
	FrameGrabber* fg;

	fg= (FrameGrabber*) malloc(sizeof(FrameGrabber));

	fg->pBitmap = BFNULL;
	fg->hDspSrf = -1;
	fg->Running = FALSE;
	fg->hBoard=NULL;
	fg->HostBuf=BFNULL;
	fg->WasOneShot = FALSE;
	fg->ContinuousData= FALSE;
	return fg;

}


/*
 * Higher Level Function to Ready the frameGrabber
 * Creates framegragbber object
 * Initilizes the frame grabber
 * sets the region of interest
 * and prepares the FrameGrabber for Acuisiation
 *
 */
FrameGrabber* TurnOnFrameGrabber(){
	FrameGrabber* fg= CreateFrameGrabberObject();
	InitializeFrameGrabber(fg);
	FrameGrabberSetRegionOfInterest(fg,0,0,1024,544); //2048 1088
	PrepareFrameGrabberForAcquire(fg);
	return fg;
}



/*
 * Initializes the frame grabber with a fg object
 * that has already been created using CreateFrameGrabberObject()
 *
 */
int InitializeFrameGrabber(FrameGrabber* fg){


	/** Choose a Board **/
	BFU32 Type, Num, Init, SerNum; // Board information
	if (DoBrdOpenDialog(BOD_HIDEJUSTOPEN, FF_BITFLOW_MODERN, &Type, &Num,
			&Init, &SerNum)) {
		return -1;
	}

	//** Choose Camera Interface **/
	CiENTRY entry;
	printf("We are choosing a framegrabber board\n");
	if (CiSysBrdFind(Type, Num, &entry)) {
		printf("Could not find board.\n");
		return -1;
	}


	/** Open the Board **/
	// open the board using default camera file
	if (CiBrdOpen(&entry, &(fg->hBoard), CiSysInitialize)) {
		printf("Could not open board.\n");
		return -1;
	}


	//
	// Here we request host based, QTABs. We don't really
	// care what we get as this app will work either way.
	//

	BFU32 ModeGot;
	BFQTabModeRequest(fg->hBoard, BFQTabModeHost, &ModeGot);

	printf("Board has been opened.\n");
	return 1;

}

/**
 * Set the region of interest to grab from from the frame grabber.
 * This in effect will override the camera file settings.
 * xsize must be  multiple of 4
 *
 * Runthis before PrepareFrameGrabberForAcquire
 */
int FrameGrabberSetRegionOfInterest(FrameGrabber* fg,int xoff, int yoff,int xsize,int ysize){
	BFRC ret=CiAqROISet(fg->hBoard,(BFU32) xoff, (BFU32) yoff,(BFU32) xsize, (BFU32) ysize, AqEngJ);

	printf("Setting Region of Interest\n");
	printf(" ret=%d\n",(int) ret);
	//BiErrorShow(fg->hBoard, ret);


	if (ret==CI_OK) printf("FrameGrabberSetRegionOfInterst= is Good!!\n\n");
	return 1;
}


int PrepareFrameGrabberForAcquire(FrameGrabber* fg){
	// find out how big the image is
		CiBrdInquire(fg->hBoard, CiCamInqFrameSize0, &(fg->ImageSize));
		CiBrdInquire(fg->hBoard, CiCamInqPixBitDepth, &(fg->BitDepth));

		/** Find out the image width **/
		// printf("%d\n",CiCamInqXSize);
		// printf("%d\n",fg->xsize);
		BFRC ret = CiBrdInquire(fg->hBoard,CiCamInqXSize,&(fg->xsize));
		// printf("%d\n",ret);
		CiBrdInquire(fg->hBoard,CiCamInqYSize0,&(fg->ysize)); 
		printf("%d\n",fg->xsize);
		printf("%d\n",fg->ysize);

		// allocate host memory to hold the image
		fg->HostBuf = (PBFU8) malloc(fg->ImageSize);
			printf("Memory allocated to hold the image.\n");

		// did we get the memory?
		if (fg->HostBuf == BFNULL) {
				printf("Host memory buffer could not be allocated - exit.\n");
			CiBrdClose(fg->hBoard);
			return -1;
		}


		printf("About to setup board for acquisition.\n");
		printf("%d",fg->ImageSize);
		// set up board for acquisistion
		/*fg->hBoard, (PBFVOID)fg->HostBuf, fg->ImageSize, 0, CiDMADataMem,
			CiLutBypass, CiLut8Bit, CiQTabBank0, TRUE, CiQTabModeOneBank,
			AqEngJ)*/
		if (CiAqSetup(fg->hBoard, (PBFVOID)fg->HostBuf, fg->ImageSize, 0, CiDMADataMem,
			CiLutBypass, CiLut8Bit, CiQTabBank0, TRUE, CiQTabModeOneBank,
			AqEngJ)) {
			printf("Entered if");
			BFErrorShow(fg->hBoard);
			printf("Setting up for acquisition failed - exit.\n");
			free(fg->HostBuf);
			CiBrdClose(fg->hBoard);
			return -1;
		}


		printf("About to get trigger mode.\n");
		// get the trigger mode

		if (CiConVTrigModeGet(fg->hBoard, &(fg->TrigMode), &(fg->TrigAssign), &(fg->TrigAPolarity),
				&(fg->TrigBPolarity))) {
			BFErrorShow(fg->hBoard);
			printf("Getting trigger mode failed - exit.\n");
			free(fg->HostBuf);
			CiBrdClose(fg->hBoard);
			return -1;

		}

		// save off trigger mode to restore too later.
		fg->OrigTrigMode = fg->TrigMode;

		// find out if the camera file put the board in one shot mode
		if (fg->TrigMode == CiTrigOneShot || fg->TrigMode == CiTrigOneShotSelfTriggered
				|| fg->TrigMode == CiTrigOneShotStartAStopA || fg->TrigMode
				== CiTrigOneShotStartAStopB) {
			// switch the board to free run
			CiConVTrigModeSet(fg->hBoard, CiTrigFreeRun, fg->TrigAssign, fg->TrigAPolarity,
					fg->TrigBPolarity);
			fg->WasOneShot = TRUE;
		}

		// check if board is in uous data mode

		if (fg->TrigMode == CiTrigContinuousData) {
			//
			// Raise the software trigger to start uous data flow.
			// If you are using a hardware trigger of data valid line,
			// you do not have to do this.
			//
			CiConSwTrig(fg->hBoard, CiTrigA, CiTrigAssert);
			fg->ContinuousData = TRUE;

		}

		// enable fifo interrupts
		CiConInt(fg->hBoard, CiIntTypeFIFO, CiConEnable);


		// Set the timout to be very short
		printf("Setting acquisition timeout time.\n");
		setAcquisitionTimeout(fg, 1000); //in Aravis lab this was 4


		printf("Prepare frame grabber for acquire completed.");

		return 1;

}

/*
 * Set the acquisition timeout time, t, in ms.
 *
 * This must be greater than the exposure time, or all of your exposures will timeout.
 * If this number is too high, then when the camera has an error, it will hang your program for a long time.
 *
 */
int setAcquisitionTimeout(FrameGrabber* fg, int t){
	// Set the timout to be very short
	printf("Setting acquisition timeout time...");
	if (CiBrdAqTimeoutSet(fg->hBoard,(BFU32) t)==CI_OK){
		printf("OK!\n");
		return T2FG_SUCCESS;
	} else{
		printf("ERROR!\n");
		T2FG_ERROR;
	}

}


/*
 * The acquired frame is plopped into fg->Hostbuf
 */
int AcquireFrame(FrameGrabber* fg){
	BFRC ret=CiAqCommand(fg->hBoard, CiConSnap, CiConWait, CiQTabBank0, AqEngJ);
	//BFRC ret=CiAqCommand(fg->hBoard, CiSnap, CiWait, CiQTabBank0, AqEngJ);
	//printf("ret value to be output\n");
	//printf("ret =%d\n",ret);
	//printf("gn2_timeout = %d\n",GN2_AQEND_TIMEOUT);
	if (ret!=CI_OK) {
				// check for overflow
				printf("Acquire command failed.\n");
				printf("Could the camera's exposure time be greater than the time specified in setAcquisitionTimeout()?\n");
				//BiErrorShow(fg->hBoard, ret);
				if (CiAqCommand(fg->hBoard, CiConReset, CiConWait, CiQTabBank0, AqEngJ)) {
				//if (CiAqCommand(fg->hBoard, CiReset, CiWait, CiQTabBank0, AqEngJ)) {
							printf("Board reset failed.\n");
							} else {
								printf("Board reset successfully!\n");
							}
//
				BFU32 Overflow;
				CiAqOverflowCheck(fg->hBoard, (int *) &Overflow);


				if (Overflow) {
						printf("Framgrabber overflow occurred.\n");
					if (CiAqCommand(fg->hBoard, CiConReset, CiConWait, CiQTabBank0,
							AqEngJ)) {
							printf("Board reset failed.\n");
						fg->keeplooping++;
					} else {
						printf("Board reset!\n");
						fg->overflowcount++;
					}
				} else {
					printf("Error in AcquireFrame().\n");

					return T2FG_ERROR;

				}
			}
	return T2FG_SUCCESS;
}


int CloseFrameGrabber(FrameGrabber* fg){

	// put board back in oneshot mode
		if (fg->WasOneShot)
			CiConVTrigModeSet(fg->hBoard, fg->OrigTrigMode, fg->TrigAssign, fg->TrigAPolarity,
					fg->TrigBPolarity);

		// lower trigger in uous data mode
		if (fg->ContinuousData)
			CiConSwTrig(fg->hBoard, CiTrigA, CiTrigDeassert);

		// clean up acquisition resources
		CiAqCleanUp(fg->hBoard, AqEngJ);

		// free buffer
		free(fg->HostBuf);

		// close system
		CiBrdClose(fg->hBoard);

		free(fg);
		printf("Frame grabber is cloed.\n");
		return 1;

}
