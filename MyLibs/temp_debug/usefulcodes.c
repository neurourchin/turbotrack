(exp->Worm->timestamp - exp->prevTime) 
CLOCKS_PER_SEC
/** Simply count the frames given in the last second **/
fps=exp->Worm->frameNum - exp->prevFrames;
factor=exp->Params->CurvaturePhaseVisualaziationFactor;

exp->prevFrames = exp->Worm->frameNum;
exp->prevTime = exp->Worm->timestamp;

printf("exp->Worm->TimeEvolution->MeanHeadCurvatureBuffer->total=%d\n",exp->Worm->TimeEvolution->MeanHeadCurvatureBuffer->total);
printSeqScalarDoubles(exp->Worm->TimeEvolution->MeanHeadCurvatureBuffer);
		
printDoubleArr(headPhaseBuff,N_curr);

	mean_derivative(headPhaseBuff,&negative_k_dot,N_curr);
	exp->Worm->TimeEvolution->derivativeOfHeadCurvature=-negative_k_dot;