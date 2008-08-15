#include	"all.h"
/*
 ************************************************************************
 *
 *  lsstcamera  --  fill CAM struct
 *
 *	As per Chuck Claver - Mar 2008
 */
void lsstcamera(kk,cc)
struct key *kk;
struct cam *cc;
{
	int ix, iy, jx, jy, doit, n, i, j, k, m, deepest, nstep, done;
	double xmin, xmax, ymin, ymax, x, y, step;
/*
 * These are probably in the wrong structure
 *
 *	radunits == radians to fitting units (currently arcsec)
 *	pixunits == pixels to fitting units  (    "        "  )
 */
	kk->mmpix = 0.010;
	kk->arcpix = 0.20;
	kk->scale = kk->arcpix/kk->mmpix;
	kk->radunits = 3600.0 * kk->radian;
	kk->pixunits = kk->arcpix;
/*
 * Initialize.  Width refers to lattice so includes extra dead space.
 */
	cc->ncol = 4072;
	cc->nrow = 4000;
	cc->ccdpercam = 15;
	cc->ccdperraft = 3;
	cc->raftmult = cc->ccdpercam/cc->ccdperraft;
	cc->chipwide = cc->ncol*kk->mmpix + 2*0.190 + 0.100;
	cc->chiptall = cc->nrow*kk->mmpix + 2*0.425 + 0.100;
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
			case 14: if ((ix<=2) || (ix>=12)) doit = 0;	break;
			case 1:
			case 13: if ((ix<=1) || (ix>=13)) doit = 0;	break;
			case 2:
			case 12: if ((ix==0) || (ix==14)) doit = 0;	break;
			default:					break;
			}
			if (doit != 0) {
				cc->xpos[n] = ix;
				cc->ypos[n] = iy;
				cc->xraft[n] = jx;
				cc->yraft[n] = jy;
				cc->ccdx0[n] = (ix%cc->ccdperraft)*cc->chipwide
						 + jx*cc->raftwide;
				cc->ccdy0[n] = (iy%cc->ccdperraft)*cc->chiptall
						 + jy*cc->rafttall;
				i = iy*cc->ccdpercam + ix;
				cc->iccd[i] = n;
				cc->colflip[n] = cc->rowflip[n] = 1;
				n++;
			}
		}
	}
/*
 *  Set (0,0) To The Middle Of The Camera
 */
	xmin = xmax = cc->ccdx0[0];
	ymin = ymax = cc->ccdy0[0];
	for (i=1; i<n; i++) {
		if (cc->ccdx0[i] < xmin)
			xmin = cc->ccdx0[i];
		if (cc->ccdx0[i] > xmax)
			xmax = cc->ccdx0[i];
		if (cc->ccdy0[i] < ymin)
			ymin = cc->ccdy0[i];
		if (cc->ccdy0[i] > ymax)
			ymax = cc->ccdy0[i];
	}
	x = 0.5*(xmin+xmax+cc->chipwide);
	y = 0.5*(ymin+ymax+cc->chipwide);
	for (i=0; i<n; i++) {
		cc->ccdx0[i] -= x;
		cc->ccdy0[i] -= y;
	}
	cc->nccd = n;
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
