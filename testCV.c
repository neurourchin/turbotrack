#include <stdio.h>
#include "opencv2/highgui/highgui_c.h"

int main(){
printf("Hello World.\nWait\n");
cvNamedWindow("RectWorm",CV_WINDOW_AUTOSIZE);
cvWaitKey(0);
cvWaitKey(500);
printf("Done.\n");
return 0;
}

