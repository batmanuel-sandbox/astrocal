#include	"all.h"
/*
 *****************************************************************************
 *
 *  dorot  --  Apply Camera Rotation
 */
void dorot(x,y,cc)
double *x,*y;
struct cam *cc;
{
	double xhat, yhat, dv[NROTM];
	int i;

	xhat = 0.0;
	yhat = 0.0;
	dv[0] = 1.0;
	dv[1] = (*x);
	dv[2] = (*y);
	if (NROTM != 3) {
		fprintf(stderr, "DOROT %d\n", NROTM);
		exit(EX_UNAVAILABLE);
	}
	for (i=0; i<NROTM; i++) {
		xhat += dv[i]*cc->xrot[i];
		yhat += dv[i]*cc->yrot[i];
	}
	*x = xhat;
	*y = yhat;
}
