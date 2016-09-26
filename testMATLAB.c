#include <stdio.h>
#include "engine.h"

int main(){
printf("Hello World.\n");
	Engine *ep;
		if (!(ep = engOpen(NULL))) {
			printf("Can't start MATLAB engine\n");
		} else {
			printf("Opening Matlab Engine\n");
		}
		
return 0;
}