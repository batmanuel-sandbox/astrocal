#include	"all.h"
/*
 ***************************************************************************
 *
 *  esscamera  --  ESSENCE Camera is CTIO MOSAIC-2
 */
void esscamera(kk,cc)
struct key *kk;
struct cam *cc;
{
/*
 * These are probably in the wrong structure
 *
 *	radunits == radians to fitting units (currently arcsec)
 *	pixunits == pixels to fitting units  (    "        "  )
 */
	kk->mmpix = 0.015;
	kk->arcpix = 0.27;
	kk->scale = kk->arcpix/kk->mmpix;
	kk->radunits = 3600.0 * kk->radian;
	kk->pixunits = kk->arcpix;
}
