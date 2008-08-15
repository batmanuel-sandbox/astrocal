#include	"all.h"
/*
 ***************************************************************************
 *
 *  polyfit  --  1-dimensional polynomial fit
 */
double polyfit(n,x,w,z,r,c,who,nc,co,sco,sumn,sumw,kk)
int n,nc,*sumn;
double *x,*w,*z,*r,*c,*co,*sco,*sumw;
long *who;
struct key *kk;
{
	int i, j, k, sn;
	double xc, xr, chisq, zlhs[NCMAX], zrhs[NCMAX][NCMAX], sw, dv[NCMAX],
		sig;
/*
 * Initialization
 */
	for (i=0; i<NCMAX; i++) {
		zlhs[i] = 0.0;
		co[i] = 0.0;
		sco[i] = TAG;
		for (j=0; j<NCMAX; j++)
			zrhs[i][j] = 0.0;
	}
	chisq = 0.0;
/*
 * Accumulation
 */
	sn = 0;
	sw = 0.0;
	for (i=0; i<n; i++) {
		if (w[i] > 0.0) {
			sn++;
			sw += w[i];
			fillpdv(nc,x[i],dv);
			for (j=0; j<nc; j++) {
				zlhs[j] += w[i]*z[i]*dv[j];
				for (k=0; k<nc; k++)
					zrhs[j][k] += w[i]*dv[j]*dv[k];
			}
		}
	}
	if (sn < nc)
		return((double)TAG);
/*
 * Inversion
 */
	i = gaussj(zrhs,nc);
	if (i != 0) {
		printf("Inversion %d\n", i);
		return((double)TAG);
	}
/*
 * Coefficients
 */
	for (i=0; i<nc; i++) {
		for (j=0; j<nc; j++)
			co[i] += zrhs[i][j]*zlhs[j];
	}
/*
 * Residuals And ChiSquared
 */
	for (i=0; i<n; i++) {
		fillpdv(nc,x[i],dv);
		xc = 0.0;
		for (j=0; j<nc; j++)
			xc += dv[j]*co[j];
		r[i] = xr = z[i]-xc;
		c[i] = xc;
		if (w[i] > 0.0)
			chisq += w[i]*xr*xr;
		if (kk->verbose > 1)
			printf("%d %lf %lf %lf %lf %lf\n",
				i,x[i],w[i],z[i],c[i],r[i]);
	}
/*
 * Errors
 */
	sig = sqrt(chisq/sw);
	for (i=0; i<nc; i++) {
		sco[i] = sig*sqrt(zrhs[i][i]);
		if (kk->verbose != 0) {
			printf("%d %lf %lf\n", i,co[i],sco[i]);
		}
	}
	return(sig);
}
