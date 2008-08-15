#include	"all.h"
/*
 ***************************************************************************
 *
 *  slalsst - Initialize SLALIB structure for LSST
 */
void slalsst(r,d,jd,w,kk,ss)
double r,d,jd,w;
struct key *kk;
struct sla *ss;
{
	double z, ar, ad, br, bd;
/*
 * Passed or specific to LSST site
 */
	ss->epoch = kk->nomepoch;
	ss->ira = r;
	ss->idec = d;
	ss->mjd = jd;
	ss->olon = -(70.0 + 43.4/60.0)/kk->radian;
	ss->olat = -(30.0 + 13.7/60.0)/kk->radian;
	ss->elev = 2725.0;
	ss->temp = 285.0;
	ss->pres = 1013.25*exp(-ss->elev/8149.9415);
	ss->humid = 0.25;
	ss->wave = w;
	ss->tlr = 0.0065;
	ss->xpolar = 0.0;
	ss->ypolar = 0.0;
	ss->dut = 0.0;
	ss->disco = 0.0;
/*
 * Computed
 */
	slaMappa(ss->epoch, ss->mjd, ss->amprms);
	slaAoppa(ss->mjd, ss->dut, ss->olon, ss->olat, ss->elev, ss->xpolar,
		 ss->ypolar, ss->temp, ss->pres, ss->humid, ss->wave,
		 ss->tlr, ss->aoprms);
	slaMapqkz(ss->ira, ss->idec, ss->amprms, &ss->ara, &ss->adec);
	slaAopqk(ss->ara, ss->adec, ss->aoprms, &ss->oaz, &ss->ozd,
		 &ss->oha, &ss->odec, &ss->ora);
	ss->oalt = kk->halfpi - ss->ozd;
	ss->oam = slaAirmas(ss->ozd);
	z = sin(ss->oha)*sin(kk->halfpi - ss->olat)/sin(ss->ozd);
	ss->opa = asin(z);
	z = tan(ss->ozd);
	ss->rra = z*sin(ss->opa);
	ss->rdec = z*cos(ss->opa);
	slaMapqk(ss->ira, ss->idec, 0.0, 0.0, 1.0, 0.0, ss->amprms, &ar, &ad);
	slaMapqk(ss->ira, ss->idec, 0.0, 0.0, 0.0, 0.0, ss->amprms, &br, &bd);
	z = ar-br;
	if (z < -kk->pi)
		z += kk->twopi;
	else if (z > kk->pi)
		z -= kk->twopi;
	ss->pfx = z*3600.0*kk->radian*cos(ss->idec);
	ss->pfy = (ad-bd)*3600.0*kk->radian;
}
