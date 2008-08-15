#include	"all.h"
/*
 **************************************************************************
 *
 *  slanone  --  TAG into SLALIB to avoid TOOBS/TORADEC
 */
void slanone(r,d,jd,w,kk,ss)
double r,d,jd,w;
struct key *kk;
struct sla *ss;
{
	ss->epoch = TAG;
	ss->mjd = jd;
	ss->ira = r;
	ss->idec = d;
	ss->wave = w;
}
