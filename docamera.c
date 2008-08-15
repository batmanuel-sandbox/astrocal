#include	"all.h"
/*
 *****************************************************************************
 *
 *  docamera  --  Compute Camera Coordinates  --  Watch out for units!
 */
int docamera(xobs,yobs,raft,ccd,x,y,kk,cc)
double xobs,yobs,*x,*y;
int *raft,*ccd;
struct key *kk;
struct cam *cc;
{
	double xmin, xmax, ymin, ymax, xmm, ymm;
	int ix, iy, i, j, n;
/*
 *  No guarantee that (xi,eta) lies on camera
 */
	*x = *y = TAG;
	*raft = *ccd = TAG;
	xmm = xobs/kk->scale;
	ymm = yobs/kk->scale;
	ix = xmm/QUANTUM + NQDIM;
	if ((ix<0) || (ix>=NQP1))
		return(-2);
	iy = ymm/QUANTUM + NQDIM;
	if ((iy<0) || (iy>=NQP1))
		return(-3);
	if ((n=cc->ndeep[iy][ix]) <= 0)
		return(-4);
/*
 *  Look for it
 */
	for (j=0; j<n; j++) {
		i = cc->deep[iy][ix][j];
		if ((i<0) || (i>=CCDMAX)) {
			fprintf(stderr, "Fatal DEEP %d\n", i);
			exit(EX_UNAVAILABLE);
		}
		xmin = cc->ccdx0[i];
		xmax = xmin+cc->chipwide;
		ymin = cc->ccdy0[i];
		ymax = ymin+cc->chipwide;
		if ((xmm>=xmin) && (xmm<xmax) && (ymm>=ymin) && (ymm<ymax)) {
			*x = 1.0 + (xmm-xmin)/kk->mmpix;
			*y = 1.0 + (ymm-ymin)/kk->mmpix;
			*ccd = cc->ccdpercam*cc->ypos[i] + cc->xpos[i];
			*raft = cc->raftmult*cc->yraft[i] + cc->xraft[i];
			if (cc->colflip[i] != 1)
				*x = cc->ncol - (*x);
			if (cc->rowflip[i] != 1)
				*y = cc->nrow - (*y);
			return(*raft);
		}
	}
	return(-1);
}
