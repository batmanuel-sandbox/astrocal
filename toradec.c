#include	"all.h"
/*
 *****************************************************************************
 *
 *  toradec  --  Focal Plane To Sky.  Order is EVERYTHING!
 */
void toradec(xi,eta,r,d,kk,ss)
double xi,eta,*r,*d;
struct key *kk;
struct sla *ss;
{
	char c;
	double x, y, ar, ad, or, od;

	if (ss->epoch == TAG) {
		*r = xi;
		*d = eta;
		return;
	}
	x = xi/kk->radunits;
	y = eta/kk->radunits;
	slaUnpcd(kk->pcd,&x,&y);
	slaDtp2s(x,y, ss->ora,ss->odec, &or,&od);
	c = 'r';
	slaOapqk(&c,or,od, ss->aoprms, &ar,&ad);
	slaAmpqk(ar,ad, ss->amprms, r,d);
	if (kk->verbose > 1)
		printf("TORAD %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", ss->mjd,xi,eta,
			or,od,ar,ad,*r,*d);
}
