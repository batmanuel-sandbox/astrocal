#include	"all.h"
/*
 ************************************************************************
 *
 *  pscamera  --  fill CAM struct
 *
 *      Much from Gene Magnier - Apr 2008
 *
 *	Fudge factor for scale from Ophiuchus data
 */
void pscamera(kk,cc)
struct key *kk;
struct cam *cc;
{
	int ix, iy, jx, jy, doit, n, i, j, k, m, deepest, nstep, done;
	double x, y, step;
	static double x0[8] = {-19816.0, -14846.0, -9876.0, -4906.0,
				60.0, 5030.0, 10000.0, 14970.0};
	static double y0[8] = {-20417.0, -15284.0, -10151.0, -5018.0,
				115.0, 5248.0, 10381.0, 15514.0};
/*
 * These are probably in the wrong structure
 *
 *	radunits == radians to fitting units (currently arcsec)
 *	pixunits == pixels to fitting units  (    "        "  )
 */
	kk->mmpix = 0.010;
	kk->arcpix = 0.26 * 0.989;
	kk->scale = kk->arcpix/kk->mmpix;
	kk->radunits = 3600.0 * kk->radian;
	kk->pixunits = kk->arcpix;
/*
 * Initialize.  Width refers to lattice so includes extra dead space.
 */
	cc->ncol = 4846;
	cc->nrow = 4868;
	cc->ccdpercam = 8;
	cc->ccdperraft = 1;
	cc->raftmult = cc->ccdpercam/cc->ccdperraft;
	cc->chipwide = (x0[1]-x0[0])*kk->mmpix;
	cc->chiptall = (y0[1]-y0[0])*kk->mmpix;
	cc->raftwide = cc->ccdperraft*cc->chipwide;
	cc->rafttall = cc->ccdperraft*cc->chiptall;
	for (i=0; i<CCDMAX; i++)
		cc->iccd[i] = TAG;
	n = 0;
/*
 * Fill Arrays Needed Elsewhere
 */
	for (iy=0; iy<cc->ccdpercam; iy++) {
		jy = iy/cc->ccdperraft;
		for (ix=0; ix<cc->ccdpercam; ix++) {
			jx = ix/cc->ccdperraft;
			doit = 1;
			switch (iy) {
			case 0:
			case 7: if ((ix<=0) || (ix>=7)) doit = 0;	break;
			default:					break;
			}
			if (doit != 0) {
				cc->xpos[n] = ix;
				cc->ypos[n] = iy;
				cc->xraft[n] = jx;
				cc->yraft[n] = jy;
				cc->ccdx0[n] = x0[ix]*kk->mmpix;
				cc->ccdy0[n] = y0[iy]*kk->mmpix;
				if (x0[ix] > 0.0)
					cc->ccdy0[n] += 10.0*kk->mmpix;
				i = iy*cc->ccdpercam + ix;
				cc->iccd[i] = n;
				if (cc->ccdx0[n] >= 0.0)
					cc->colflip[n] = cc->rowflip[n] = 1;
				else
					cc->colflip[n] = cc->rowflip[n] = -1;
				n++;
			}
		}
	}
	cc->nccd = n;
	x = fabs(x0[0])*kk->mmpix;
	y = fabs(y0[0])*kk->mmpix;
	if (x > y)
		cc->fov = (2.0*x*kk->scale)/(3600.0*kk->radian);
	else
		cc->fov = (2.0*y*kk->scale)/(3600.0*kk->radian);
	cc->extrad = 0.5*cc->fov + 0.1/kk->radian;
/*
 *  Fill Array To Speed (Xi,Eta) To (RAFT,CCD,X,Y)
 */
	for (iy=0; iy<NQP1; iy++) {
		for (ix=0; ix<NQP1; ix++)
			cc->ndeep[iy][ix] = 0;
	}
	deepest = 0;
	nstep = 5;
	step = cc->chipwide/(nstep-1);
	for (i=0; i<cc->nccd; i++) {
		for (j=0; j<nstep; j++) {
			y = cc->ccdy0[i] + j*step;
			iy = y/QUANTUM + NQDIM;
			if ((iy<0) || (iy>=NQP1)) {
				printf("Illegal Y %d %d %f\n", i,iy,y);
				exit(EX_UNAVAILABLE);
			}
			for (k=0; k<nstep; k++) {
				x = cc->ccdx0[i] + k*step;
				ix = x/QUANTUM + NQDIM;
				if ((ix<0) || (ix>=NQP1)) {
					printf("Illegal X %d %d %f\n", i,ix,x);
					exit(EX_UNAVAILABLE);
				}
				done = 0;
				for (m=0; m<cc->ndeep[iy][ix]; m++) {
					if (cc->deep[iy][ix][m] == i) {
						done++;
						break;
					}
				}
				if (done == 0) {
					m = cc->ndeep[iy][ix];
					cc->deep[iy][ix][m] = i;
					m++;
					cc->ndeep[iy][ix] = m;
					if (m > deepest)
						deepest = m;
				}
			}
		}
	}
	printf("N(ccd)=%d  Deepest=%d\n", cc->nccd,deepest);
}
