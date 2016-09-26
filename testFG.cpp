/* FGTest.cpp 

This is a test of the BitFlow SDK.

*/

#include <stdio.h>
#include "Talk2FrameGrabber.h"
#include "opencv2/highgui/highgui_c.h"
#include "Talk2DLP.h"


int main(){
	printf("Hello world!\n");
	
		printf("Testing the DLP..");
	T2DLP_on();
	
	printf("Calling a framegrabber function\n");
	FrameGrabber* fg;
	fg=CreateFrameGrabberObject();
	printf("Calling an opencv function\n");
	cvNamedWindow("RectWorm",CV_WINDOW_AUTOSIZE);
	cvWaitKey(0);

	
	return 0;
}