#include	"all.h"
/*
 ***************************************************************************
 *
 *  ls2fit  --  2-dimensional polynomial fit
 */
double ls2fit(n,x,y,w,z,r,c,who,nc,co,sco,sumn,sumw,kk)
int n,nc,*sumn;
long who[];
double x[],y[],w[],z[],r[],c[],co[],sco[],*sumw;
struct key *kk;
{
	int i, j, k, sn, qn;
	long double zc, zr, chisq, zlhs[NCMAX], zrhs[NCMAX][NCMAX], dv[NCMAX],
		cc[NCMAX], sc[NCMAX];
	double a1, a2, sig, qw, sw;
/*
 * Initialization
 */
	if ((nc<1) || (nc>NCMAX)) {
		fprintf(stderr, "LS2FIT Crazy %d\n", nc);
		exit(EX_UNAVAILABLE);
	}
	for (i=0; i<nc; i++) {
		zlhs[i] = 0.0;
		cc[i] = 0.0;
		sc[i] = TAG;
		for (j=0; j<nc; j++)
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
			fill2dv(nc,x[i],y[i],dv);
			for (j=0; j<nc; j++) {
				zlhs[j] += w[i]*z[i]*dv[j];
				for (k=0; k<nc; k++)
					zrhs[j][k] += w[i]*dv[j]*dv[k];
			}
		}
	}
	if (sn < nc) {
		if (kk->verbose != 0)
			printf("%d %d %lf\n", nc,sn,sw);
		return((double)TAG);
	}
/*
 * Inversion
 */
	i = ldgaussj(zrhs,nc);
	if (i != 0) {
		printf("Inversion %d\n", i);
		return((double)TAG);
	}
/*
 * Coefficients
 */
	for (i=0; i<nc; i++) {
		for (j=0; j<nc; j++)
			cc[i] += zrhs[i][j]*zlhs[j];
	}
/*
 * Residuals And ChiSquared
 */
	qn = 0;
	qw = 0.0;
	for (i=0; i<n; i++) {
		fill2dv(nc,x[i],y[i],dv);
		zc = 0.0;
		for (j=0; j<nc; j++)
			zc += dv[j]*cc[j];
		r[i] = zr = z[i]-zc;
		c[i] = zc;
		if (w[i] > 0.0)
			chisq += w[i]*zr*zr;
		if (w[i] != 1.0) {
			qw += zr*zr;
			qn++;
		}
		if (kk->verbose != 0) {
			a1 = zc;
			a2 = zr;
			printf("%ld %lf %lf %lf %lf %lf %lf LS2DAT\n", who[i],x[i],
				y[i],w[i],z[i],a1,a2);
		}
	}
/*
 * Errors
 */
	sig = sqrt(chisq/sw);
	if (qn > 0)
		qw = sqrt(qw/qn);
	else
		qw = -1.0;
	for (i=0; i<nc; i++)
		sc[i] = sig*sqrtl(zrhs[i][i]);
	*sumn = sn;
	*sumw = sw;
	if (kk->verbose != 0) {
		for (i=0; i<nc; i++) {
			a1 = cc[i];
			a2 = sc[i];
			printf("%d %lf %lf %lf %lf LS2COEF\n", i,a1,a2,sig,qw);
		}
	}
	for (i=0; i<nc; i++) {
		co[i] = cc[i];
		sco[i] = sc[i];
	}
	return(sig);
}
