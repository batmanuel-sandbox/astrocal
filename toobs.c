#include	"all.h"
/*
 *****************************************************************************
 *
 *  toobs  --  Sky To Focal Plane.  Order is EVERYTHING!
 */
void toobs(r,d,mura,mudec,px,rv, xi,eta,kk,ss)
double r,d,mura,mudec,px,rv,*xi,*eta;
struct key *kk;
struct sla *ss;
{
	int j;
	double x, y, ar, ad, or, od, az, zd, ha;

	if (ss->epoch == TAG) {
		*xi = r;
		*eta = d;
		return;
	}
	slaMapqk(r,d,mura,mudec,px,rv, ss->amprms, &ar,&ad);
	slaAopqk(ar,ad, ss->aoprms, &az,&zd,&ha,&od,&or);
	slaDs2tp(or,od, ss->ora,ss->odec, &x,&y,&j);
	if (j != 0) {
		fprintf(stderr, "TOOBS SLALIB %d\n", j);
		exit(EX_UNAVAILABLE);
	}
	slaPcd(kk->pcd,&x,&y);
	*xi = x*kk->radunits;
	*eta = y*kk->radunits;
	if (kk->verbose > 1)
		printf("TOOBS %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", r,d,
			ss->mjd,ha,zd,or,od,x,y,*xi,*eta);
}
