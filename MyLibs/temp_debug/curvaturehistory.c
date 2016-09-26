int HandleCurvaturePhaseAnalysis(Experiment* exp){

		_TICTOC_TIC_FUNC
	TICTOC::timer().tic("_CurvaturePhaseAnalysis",exp->e);

	/** Define the head in worm coordinates **/
	int HEAD_BEGIN=10;
	int HEAD_END=30;

	/** prep memory space for storing curvatue info **/
	double* curvature= (double*) malloc(N* (sizeof(double)));
	RefreshWormMemStorage(exp->Worm);

	/** Smooth and Extract Curvature **/
	if (extractCurvatureOfSeq( headcent,curvature,sigma,exp->Worm->MemScratchStorage)< 0) return EXP_ERROR;
	RefreshWormMemStorage(exp->Worm);
	if (DEBUG_FLAG!=0) printDoubleArr(curvature,N);


/** Store worm pos from prev 6 frames**/
	if (AddMeanHeadCurvature(exp->Worm->TimeEvolution,median_curvature,exp->Params)!=A_OK) printf("Error adding mean curvature!!\n");
		printf("exp->Worm->TimeEvolution->WormVelocityBuffer->total=%d\n",exp->Worm->TimeEvolution->WormVelBuffer->total);
		printSeqScalarDoubles(exp->Worm->TimeEvolution->MeanHeadCurvatureBuffer);
	

	/** Calculate the acceleration **/
	double* headPhaseBuff=NULL;
	SeqDoublesToArr((const CvSeq*) exp->Worm->TimeEvolution->MeanHeadCurvatureBuffer,&headPhaseBuff);
	int N_curr=exp->Worm->TimeEvolution->MeanHeadCurvatureBuffer->total;

	if (DEBUG_FLAG!=0){
		printf("headPhaseBuff\n");
		printDoubleArr(headPhaseBuff,N_curr);
	}

	double negative_k_dot;//our buffer is backwards. 0th index is most recent.

	mean_derivative(headPhaseBuff,&negative_k_dot,N_curr);
	exp->Worm->TimeEvolution->derivativeOfHeadCurvature=-negative_k_dot;


	/** Deallocate memory for head phase buffer **/
	free(headPhaseBuff);
	if (DEBUG_FLAG!=0) {
		printf("k*%d=%f\t, kdot* %d: %f\n",factor, (double)factor *median_curvature, factor, (double)factor* (exp->Worm->TimeEvolution->derivativeOfHeadCurvature));
		printf("NumFrames: %d, kdot+/-: %d, k+/-: %d, Thresh: %d\n",exp->Params->CurvaturePhaseNumFrames, exp->Params->CurvaturePhaseDerivThresholdPositive,exp->Params->CurvaturePhaseThresholdPositive,exp->Params->CurvaturePhaseThreshold);
		cvWaitKey(1000);
	}


	/** If triggering based on phase, decide weather to turn the DLP on or off**/
	double k, kdot, trig, desiredSignk, desiredSignkdot, signOfk, signOfkdot;

	if (exp->Params->CurvaturePhaseTriggerOn != 0){
		struct timeval curr_tv;

		/*
		 * This is subtle. There is k and kdot. k is the median curvature. kdot is the derivative of the median curvature.
		 * We want to trigger based upon when |k| > trig and when sign(kdot) == desiredSign .
		 */
		kdot=exp->Worm->TimeEvolution->derivativeOfHeadCurvature;
		k=median_curvature*factor;

		/** find signOfkdot**/
		signOfkdot=-1;
		if (kdot>0) signOfkdot=1;

		/** find sign(k) **/
		signOfk=-1;
		if (k>0) signOfk=1;

		/** get desiredSign  for k and kdot**/
		desiredSignkdot= 1;
		desiredSignk =1;
		if (exp->Params->CurvaturePhaseDerivThresholdPositive ==0) desiredSignkdot=  -1;
		if (exp->Params->CurvaturePhaseThresholdPositive ==0) desiredSignk=  -1;


		trig= (double) exp->Params->CurvaturePhaseThreshold  / 10; //Divide by 10 because the slider bar is multiplied by 10

		/** trigger if the abs(k)>trig AND signOfk==desiredSign **/
		if (  (signOfk * k) > trig   && (signOfkdot==desiredSignkdot)   && (signOfk==desiredSignk))  {


			/*
			 * We want to implement a minimum DLP on-time, and a refactory
			 * period. E.g. once the DLP goes on it should stay on a minimimum of n seconds
			 * and once it goes off it should stay off a minimum of m seconds.
			 *
			 */

			/** If we are in Illumination-Stay-On-and-Refractory-Period-Mode **/
			if (exp->Params->StayOnAndRefract==1){

				/** Get timing info to Find out if Refractory Period is Over **/
				gettimeofday(&curr_tv, NULL);
				double diff = curr_tv.tv_sec + (curr_tv.tv_usec / 1000000.0) - exp->illumFinished;
				if ( diff  >  (double) exp->Params->IllumRefractoryPeriod / 10.0){

					/** Turn on the DLP for a preset amount of time **/
					exp->Params->DLPOnFlash=1;

					/** TRICKY!!  **/
					exp->Params->DLPOn=1; // let's also turn the DLP on right now! this shoudln't mess with HAndle Illumination Timing


				} else {
					// Don't actually turn on the DLP, because the refractory period isn't met.
				}

			}else{

			/** Turn on the DLP **/
			exp->Params->DLPOn = 1;

			}

		} else {
			/** The curvature is such that we are no longer triggering **/

			 if (exp->Params->StayOnAndRefract==1){
				//don't do anything because the Handle IllumiantionTiming DLP function will take care of turning things off
			 } else {
				/** Turn the DLP Off **/
				exp->Params->DLPOn = 0;
			 }
		}


	}
	TICTOC::timer().toc("_CurvaturePhaseAnalysis",exp->e);
	return A_OK;
}


void CalculateAndPrintFrameRateAndInfo(Experiment* exp) {
	/*** Print out Frame Rate ***/
	int fps,factor;
	if ((exp->Worm->timestamp - exp->prevTime) > CLOCKS_PER_SEC) {

		/** Simply count the frames given in the last second **/
		fps=exp->Worm->frameNum - exp->prevFrames;

		/** If we are doing real time analysis of head curvature **/
		if (exp->Params->CurvatureAnalyzeOn) {
			factor=exp->Params->CurvaturePhaseVisualaziationFactor;
			/** display the head curvature and derivative along with the frame rate **/
			printf("%d fps \tk*%d=%Lf \tkdot*%d=%Lf \n", fps, factor, (double)factor*exp->Worm->TimeEvolution->currMeanHeadCurvature,factor, (double)factor* exp->Worm->TimeEvolution->derivativeOfHeadCurvature);
		}else{
			/** Print only frames **/
			printf("%d fps\n", fps);
		}

		/** In all cases, reset the timer **/
		exp->prevFrames = exp->Worm->frameNum;
		exp->prevTime = exp->Worm->timestamp;
	}
}