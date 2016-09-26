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


/*
 * AndysComputations.c
 *
 *  Created on: Aug 18, 2009
 *      Author: Andy
 */

/*
 * This library contains functions that perform custom image processing-related computations that are independent
 * of the OpenCV library.
 *
 * Other custom computer vision routines are stored in AndysOpenCVLib.h and AndysOpenCVLib.c
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "AndysComputations.h"



/*
 * Calculates the distance between two points on a ciruclar boundary
 * with total points PtsOnBound for two points with zero-indexed indices
 * IndexA and IndexB.
 *
 */
int DistBetPtsOnCircBound(int PtsOnBound, int IndexA, int IndexB){
	int distance;
	if (labs(IndexA-IndexB)<labs(PtsOnBound- labs(IndexA-IndexB))){//go with the smallest value
		distance=labs(IndexA-IndexB);
	}else{
		distance=labs(PtsOnBound- labs(IndexA-IndexB));
	}
	return distance;
}


/*
 * This is a wrapper for the modulo function.
 * Every time frameNum is divisible by HowOften with no remainder
 * the function returnst true (1).
 * Otherwise it returns false (0).
 *
 * If HowOften is 0 then the function always returns false.
 * If the inputs are invalid then the function returns -1.
 *
 */
int EverySoOften(int frameNum, int HowOften){
	if ( frameNum<0 || HowOften<0) return -1;
	if (HowOften==0) return 0;
	if ((frameNum % HowOften)==0){
		return 1;
	}
	return 0;
}


/*
 * Given two clock_t objects, this function returns an int
 * containing the elapsed time in milliseconds
 *
 */
unsigned long msElapsed(clock_t start, clock_t end){
	unsigned long temp = (end-start * 1000);
	return temp / CLOCKS_PER_SEC;
}



/*
 * Takes a clock_t type and returns an integer with the number of seconds
 * For the reamining milliseconds use GetMilliseconds
 *
 */
int GetSeconds(clock_t time){
	double seconds = (double) time / (double) CLOCKS_PER_SEC;
	return (int) seconds;
}

/*
 * Takes a clock_t type and returns the remaining number of ms
 * since GetSeconds();
 *
 *
 */
int GetMilliSeconds(clock_t time){
	/* Get number of seconds very accurately */
	double seconds = (double) time / (double) CLOCKS_PER_SEC;

	/* Round off to get the whole number of seconds */
	int rounded= (int) seconds;

	/* Subtract off the whole number of secods and multiply by 1000 */
	double ms= ( (double) seconds-rounded) *1000;
	return (int) ms;
}

/*
 * Toggles an integer from zero to 1.
 * If x is nonzero, sets x to zero.
 * If x is zero, sets x to one.
 */
void Toggle(int* x){
	if (*x==0) {
		*x=1;
	} else {
		*x=0;
	}
	return;
}

/*
 * Safely decrement an integer value, as long as the result will not be less than min.
 */
void Decrement(int* x, int min){
	if ((*x) >min) (*x)--;
	return;
}

/*
 * Safely increment an integer value as long as the result will not be grater than max.
 */
void Increment (int* x, int max){
	if ((*x) < max) (*x)++;
	return;
}

/*
 * Returns the larger of either a or b.
 * If a and b are equal, returns a.
 */
int LargerOf(int a, int b){
	if (a==b) return a;
	if (a>b){
		return a;
	} else {
		return b;
	}
}


/*
 * Returns the smaller of either a or b.
 * If a and b are equal, returns a.
 */
int SmallerOf(int a, int b){
	if (a==b) return a;
	if (a<b){
		return a;
	} else {
		return b;
	}

}

/* Sum over an array of N doubles */
double SumDoubleArray(const double* arr,int N){
	int k;
	double s=0;
	for (k = 0; k < N; ++k) {
		s+=arr[k];
	}
	return s;
}


/*
 * Returns the mean derivative of a series of n values in buffer x
 * Written by Quan Wen
 * It assumes that the zeroth index is at t=0.
 */
int mean_derivative(double *x, double *x_dot, int n)
{
	int PO=0; //print out?

	/** If there are no elements in the buffer, then the derivative is zero **/
	if (n<1){
		printf("no elements in the buffer!\n");
		*x_dot=0;
		return A_OK;
	}


	if (x==NULL){
		printf("Mean_derivative: Error!\n");
		return A_ERROR;
	}

    int i;
    double s_xx, s_xy, s_x, s_y, delta;

    s_y=0;
    s_xy=0;
    s_xx=0;
    s_x=  ((double) (n*(n-1)) ) /(double)2;

    for (i=0;i<n;i++){
        s_xx+=  (double) (i*i);
        s_y+=*(x+ i);
        s_xy+=(*(x+ i))* (double)i;
        if (PO!=0)  printf("i=%d, s_xy=%f, s_x=%f, ,s_xx=%f, s_y=%f \n",i,s_xy,s_x,s_xx,s_y);

    }

    delta=n*s_xx-s_x*s_x;
    *x_dot=(n*s_xy-s_x*s_y)/delta;  /*using linear fit to find the slope x_dot */
    if (PO!=0) {
    	printf("numerator=%f\n\n",(n*s_xy-s_x*s_y));
    	printf("denom=%f\n",delta);
    	printf("*x_dot=%f\n",*x_dot);
    }

}

/*
 * Simple comparer for finding median
 */
int compareDouble (const void * a, const void * b)
{
  return (int) ( *(double*)a - *(double*)b );
}


/*
 *get the median of an array of doubles
 *uses qsort under the hood
 */
double MedianOfDoubleArr(const double* arr, int N){

	double* temp=(double*) malloc(N*sizeof(double));
	memcpy(temp,arr,N*sizeof(double));
	qsort(temp, N, sizeof(arr[0]), compareDouble);
	double result= temp[N/2];
	free(temp);
	return result;
}


/*
 * Print out the values of a double array
 * with N elements
 */
void printDoubleArr(const double* arr, int N){
	if (N<1) return;
	if (arr==NULL) return;
	int i;
	for (i = 0; i < N; ++i) {
		printf("%d: %f\n",i,arr[i]);
	}
}
