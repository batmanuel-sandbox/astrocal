#include	"all.h"
/*
 ****************************************************************************
 *
 *  fillpdv  --  Fill dv[] for polynomial fit
 */
void fillpdv(nc,x,dv)
int nc;
double x,*dv;
{
	int i;

	dv[0] = 1.0;
	for (i=1; i<nc; i++)
		dv[i] = x*dv[i-1];
}
