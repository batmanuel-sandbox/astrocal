#include	"all.h"
/*
 ***************************************************************************
 *
 *  kepcamera  --  fake CAM on the basis of Koch's RA2fpix
 */
void kepcamera(kk,cc)
struct key *kk;
struct cam *cc;
{
	int j;
/*
 * These are probably in the wrong structure
 *
 *	radunits == radians to fitting units (currently arcsec)
 *	pixunits == pixels to fitting units  (    "        "  )
 */
	kk->mmpix = 0.027;
	kk->arcpix = 3.9753235;
	kk->scale = kk->arcpix/kk->mmpix;
	kk->radunits = 3600.0 * kk->radian;
	kk->pixunits = kk->arcpix;
/*
 * Initialize Only What Is Needed
 */
	kk->refr0 = 15.0*(19.0 + 14.5/60.0)/kk->radian;
	kk->refd0 = (34.0 + 40.0/60.0)/kk->radian;
	slaCaldj(2009, 3, 1, &kk->refjd0, &j);
	if (j != 0) {
		fprintf(stderr, "Fatal CALDJ Error %d\n", j);
		exit(EX_UNAVAILABLE);
	}
	kk->wlong = 170.0;
	cc->extrad = 8.0/kk->radian;
	kk->nomepoch = slaEpj(kk->refjd0);
}
