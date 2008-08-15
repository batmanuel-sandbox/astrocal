#include	"all.h"
/*
 *****************************************************************************
 *
 *   Initialize constants used in lots of places
 */
void keyinit(v,kk)
int v;
struct key *kk;
{
	int i;
	double sky, arcmin;
/*
 * Camera Stuff
 */
	kk->verbose = v;
	kk->cleanup = 1;
	kk->redo = 0;
	kk->storeside = 64;
	kk->storepix = nside2npix(kk->storeside);
	kk->patchside = 256;
	kk->patchpix = nside2npix(kk->patchside);
/*
 * Ugly defaults to make sure user calls Xcamera.c next
 */
	kk->mmpix = kk->arcpix = kk->scale = kk->radunits = kk->pixunits = 0.0;
/*
 * Monet memory leak keys
 */
	for (i=0; i<NMEMKEY; i++)
		kk->mbase[i] = (int *)TAG;
/*
 * Constants
 */
	kk->pi = M_PI;
	kk->halfpi = 0.5*kk->pi;
	kk->twopi = 2.0*kk->pi;
	kk->radian = 360.0/kk->twopi;
	sky = 4.0*kk->pi*kk->radian*kk->radian;
	arcmin = 60.0*60.0*sky;
	kk->storeres = sqrt(arcmin/kk->storepix);
	kk->patchres = sqrt(arcmin/kk->patchpix);
	kk->nomepoch = 2000.0;
	kk->refwave = effwave('r');
/*
 * Miminim ranges for fitting
 */
	kk->counter = 0;
	kk->firstflag = 0;
	kk->maxmu = 0.0;
	kk->ndefccd = NCMAX;
	kk->starfit = FIT_MP;
	kk->demin = 0.5;
	kk->dzmin = 0.2;
	kk->dpmin = 0.4;
	kk->trim1few = 3*FIT_NC;
	kk->trim1mu = 2.5;
	kk->trim1zd = 3.0;
	kk->trim1pi = 3.0;
	kk->ccdtoofew = 2*NCMAX;
	kk->bright = 0.0;
	kk->faint = 25.0;
	kk->pcd = 0.0;
/*
 * Iteration Control
 */
	kk->itmax = 3;
	kk->lastiter = 0;
	printf("StoreSide=%3ld  StorePix=%7ld  StoreRes=%lf\n", kk->storeside,
		kk->storepix,kk->storeres);
	printf("PatchSide=%3ld  PatchPix=%7ld  PatchRes=%lf\n", kk->patchside,
		kk->patchpix,kk->patchres);
	kk->curstore = kk->curpatch = kk->loaded = TAG;
/*
 * West Longitude Needed For GETUPPER Before Call To SLALIB
 */
	kk->wlong = -150.0;
/*
 * Controls Software Development
 */
	kk->fakeit = 0;
	kk->simul = 0;
	kk->nverb = 0;
/*
 * Default To Not Kill OIDs or SIDs
 */
	kk->nkill = 0;
	kk->ktype = NULL;
	kk->kval = NULL;
/*
 * Default Is To Not Save Catalogs To Disk
 */
	kk->docatsave = 0;
	strcpy(kk->outroot, "./resroot");
/*
 * Default is to work in (RA,Dec)
 */
	kk->model = 0;
	kk->pixels = 0;
}
