#include	"all.h"
/*
 *************************************************************************
 *
 *  getcamera  --  Load proper camera
 */
void getcamera(kk,cc)
struct key *kk;
struct cam *cc;
{
	if (kk->model == MODEL_LSST)
		lsstcamera(kk,cc);
	else if (kk->model == MODEL_PS)
		pscamera(kk,cc);
	else if (kk->model == MODEL_KEPLER)
		kepcamera(kk,cc);
	else if (kk->model == MODEL_ESSENCE)
		esscamera(kk,cc);
	else {
		kk->mmpix = 1.0;
		kk->arcpix = 1.0;
		kk->scale = kk->arcpix/kk->mmpix;
		kk->radunits = 3600.0 * kk->radian;
		kk->pixunits = kk->arcpix;
		printf("Unknown Model - Adopting Generic\n");
	}
}
