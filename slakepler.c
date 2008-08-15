#include	"all.h"
/*
 ***************************************************************************
 *
 *  slakepler - Initialize SLALIB structure for KEPLER - Total GUESS!
 */
void slakepler(r,d,jd,w,kk,ss)
double r,d,jd,w;
struct key *kk;
struct sla *ss;
{
	ss->epoch = kk->nomepoch;
	ss->ira = r;
	ss->idec = d;
	ss->mjd = jd;
	ss->wave = w;
/*
 */
	ss->pfx = 0.0;
	ss->pfy = 0.0;
	ss->rra = 0.0;
	ss->rdec = 0.0;
}
