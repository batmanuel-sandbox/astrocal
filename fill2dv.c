#include	"all.h"
/*
 ****************************************************************************
 *
 *  fill2dv  --  Just fill array of derivatives for 2-D fit
 */
void fill2dv(nc,x,y,dv)
int nc;
double x,y;
long double dv[];
{
	dv[0] = 1.0;
	dv[1] = x;
	dv[2] = y;
	if (nc > 3) {
		dv[3] = x*x;
		dv[4] = x*y;
		dv[5] = y*y;
		if (nc > 6) {
			dv[6] = x*x*x;
			dv[7] = x*x*y;
			dv[8] = x*y*y;
			dv[9] = y*y*y;
			if (nc > 10) {
				fprintf(stderr, "Illegal FILL2DV %d\n", nc);
				exit(EX_UNAVAILABLE);
			}
		}
	}
}
