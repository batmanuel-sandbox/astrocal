#include	"all.h"
#define	NCCD	60
#define	NAXIS	8
#define	FMT0	"SELECT sid,ccd,col,row FROM ophobs WHERE (oid=%d)"
#define	FMT1	"%2d %4d %6.3lf %6.3lf %6.3lf %6.3lf %6.3lf %6.3lf\n"
#define	FMT2	"Scale=%6.4lf+/- %6.4lf  Angle=%6.2lf+/-%5.2lf\n"
/*
 ******************************************************************************
 *
 *  bigast  --  Worry about whole PS focal plane
 */
int main(int argc, char *argv[])
{
	MYSQL q;
	MYSQL_RES *result;
	MYSQL_ROW r;
	struct key k;
	struct cam c;
	struct sla s;
	double ra0, dec0, mjd0, air0, *cra, *cdec, *cmag, *tmp, *ccol, *crow,
		*ocol, *orow, theta, pmra, pmdec, plx, rv, *xi, *eta, *xfit,
		*yfit, *zxfit, *zyfit, *wfit, *cxfit, *cyfit, *rxfit, *ryfit,
		xcoef[NCMAX], sxcoef[NCMAX], ycoef[NCMAX], sycoef[NCMAX],
		sigmax, sigmay, sumw, xsc, xth, ysc, yth, zcoef[NCMAX],
		camsc[NCCD], camth[NCCD], sx, sxx, sy, syy, szcoef[NCMAX],
		sigmaz, x0, y0, dx, dy;
	float im[NAXIS][NAXIS];
	long *csid, sid, *who;
	int oid0, sec0, *idx, i, n, j, ncat, *cccd, *occd, m, raft, ncoef,
		sumn, camx[NCCD], camy[NCCD];
	static int which[NCCD] =    {10, 20, 30, 40, 50, 60,
				  1, 11, 21, 31, 41, 51, 61, 71,
				  2, 12, 22, 32, 42, 52, 62, 72,
				  3, 13, 23, 33, 43, 53, 63, 73,
				  4, 14, 24, 34, 44, 54, 64, 74,
				  5, 15, 25, 35, 45, 55, 65, 75,
				  6, 16, 26, 36, 46, 56, 66, 76,
				     17, 27, 37, 47, 57, 67};
	char filt0, lb[BIGLINE];
/*
 * Initialization
 */
	keyinit(0,&k);
	k.model = MODEL_PS;
	k.pcd = 6.0;
	getcamera(&k,&c);
	if (!mysql_init(&q)) {
		fprintf(stderr, "Cannot Initialize MySQL\n");
		exit(EX_UNAVAILABLE);
	}
	if ((n=mysql_options(&q, MYSQL_READ_DEFAULT_GROUP, "client")) != 0) {
		fprintf(stderr, "Cannot Read Defaults %d\n", n);
		exit(EX_UNAVAILABLE);
	}
	if (!mysql_real_connect(&q, NULL, NULL, NULL, NULL, 0, NULL, 0)) {
		fprintf(stderr, "%d: %s\n", mysql_errno(&q),mysql_error(&q));
		exit(EX_UNAVAILABLE);
	}
	for (i=0; i<NCCD; i++) {
		camx[i] = which[i]/10;
		camy[i] = which[i]%10;
	}
/*
 * Any observation will do
 */
	strcpy(lb, "SELECT * FROM ophep LIMIT 1");
	if (mysql_query(&q,lb)) {
		fprintf(stderr, "Cannot %s\n", lb);
		exit(EX_UNAVAILABLE);
	}
	result = mysql_store_result(&q);
	n = mysql_num_rows(result);
	if (n != 1) {
		fprintf(stderr, "Error doing %s\n", lb);
		exit(EX_UNAVAILABLE);
	}
	r = mysql_fetch_row(result);
	sscanf(r[0], "%d", &oid0);
	sscanf(r[1], "%lf", &mjd0);
	sscanf(r[2], "%lf", &ra0);
	sscanf(r[3], "%lf", &dec0);
	sscanf(r[4], "%c", &filt0);
	sscanf(r[5], "%d", &sec0);
	sscanf(r[6], "%lf", &air0);
	mysql_free_result(result);
ra0 += 0.0031;
dec0 += 0.0031;
	slaps(ra0,dec0,mjd0,k.refwave,&k,&s);
	printf("OID=%d  DeltaAir=%6.3lf\n", oid0,air0-s.oam);
/*
 * Load reference catalog to get nominal positions
 */
	strcpy(lb, "SELECT ra,spd,rmag,sid FROM ophcat");
	if (mysql_query(&q,lb)) {
		fprintf(stderr, "Cannot %s\n", lb);
		exit(EX_UNAVAILABLE);
	}
	result = mysql_store_result(&q);
	ncat = mysql_num_rows(result);
	cra = (double *)malloc(ncat*sizeof(double));
	cdec = (double *)malloc(ncat*sizeof(double));
	cmag = (double *)malloc(ncat*sizeof(double));
	csid = (long *)malloc(ncat*sizeof(long));
	idx = (int *)malloc(ncat*sizeof(int));
	tmp = (double *)malloc(ncat*sizeof(double));
	if ((cra==NULL) || (cdec==NULL) || (cmag==NULL) || (csid==NULL)
	 || (idx==NULL) || (tmp==NULL)) {
		fprintf(stderr, "Cannot MALLOC Reference Catalog\n");
		exit(EX_UNAVAILABLE);
	}
	for (i=0; i<ncat; i++) {
		r = mysql_fetch_row(result);
		sscanf(r[0], "%d", &j);
		cra[i] = j/(3600000.0*k.radian);
		sscanf(r[1], "%d", &j);
		cdec[i] = (j/3600000.0 - 90.0)/k.radian;
		sscanf(r[2], "%d", &j);
		cmag[i] = j/1000.0;
		sscanf(r[3], "%ld", &csid[i]);
		idx[i] = i;
	}
	mysql_free_result(result);
	juqsrt(ncat,csid,idx);
	dreord(ncat,idx, cra,tmp);
	dreord(ncat,idx, cdec,tmp);
	dreord(ncat,idx, cmag,tmp);
	printf("Found %8d catalog stars\n", ncat);
/*
 * Now get the observations.
 */
	cccd = (int *)malloc(ncat*sizeof(int));
	occd = (int *)malloc(ncat*sizeof(int));
	ccol = (double *)malloc(ncat*sizeof(double));
	ocol = (double *)malloc(ncat*sizeof(double));
	crow = (double *)malloc(ncat*sizeof(double));
	orow = (double *)malloc(ncat*sizeof(double));
	xi = (double *)malloc(ncat*sizeof(double));
	eta = (double *)malloc(ncat*sizeof(double));
	if ((cccd==NULL) || (occd==NULL) || (ccol==NULL) || (ocol==NULL)
	 || (crow==NULL) || (orow==NULL) || (xi==NULL) || (eta==NULL)) {
		fprintf(stderr, "Cannot MALLOC Observations\n");
		exit(EX_UNAVAILABLE);
	}
	for (i=0; i<ncat; i++)
		occd[i] = TAG;
	sprintf(lb, FMT0, oid0);
	if (mysql_query(&q,lb)) {
		fprintf(stderr, "Cannot %s\n", lb);
		exit(EX_UNAVAILABLE);
	}
	result = mysql_store_result(&q);
	n = mysql_num_rows(result);
	for (i=0; i<n; i++) {
		r = mysql_fetch_row(result);
		sscanf(r[0], "%ld", &sid);
		j = jbisect(sid, ncat,csid);
		if ((j>=0) && (j<ncat)) {
			sscanf(r[1], "%d", &occd[j]);
			sscanf(r[2], "%d", &m);
			ocol[j] = m/P_SCALE;
			sscanf(r[3], "%d", &m);
			orow[j] = m/P_SCALE;
		}
	}
	mysql_free_result(result);
	m = 0;
	for (i=0; i<ncat; i++) {
		if (occd[i] != TAG) {
			cra[m] = cra[i];
			cdec[m] = cdec[i];
			cmag[m] = cmag[i];
			csid[m] = csid[i];
			occd[m] = occd[i];
			ocol[m] = ocol[i];
			orow[m] = orow[i];
			m++;
		}
	}
	ncat = m;
	printf("Found %8d observations of catalog stars\n", ncat);
/*
 * Now compute the predicted camera positions
 */
	theta = 0.0;
	pmra = pmdec = plx = rv = 0.0;
	m = 0;
	rotlsst(theta,&c);
	for (i=0; i<ncat; i++) {
		toobs(cra[i],cdec[i],pmra,pmdec,plx,rv, &xi[i],&eta[i],&k,&s);
		dorot(&xi[i],&eta[i],&c);
		j=docamera(xi[i],eta[i],&raft,&cccd[i],&ccol[i],&crow[i],&k,&c);
		if (j >= 0)
			m++;
	}
	printf("Found %8d stars on camera\n", m);
/*
 * Loop over observed CCDs to try and see what is going on
 */
	xfit = (double *)malloc(ncat*sizeof(double));
	yfit = (double *)malloc(ncat*sizeof(double));
	zxfit = (double *)malloc(ncat*sizeof(double));
	zyfit = (double *)malloc(ncat*sizeof(double));
	wfit = (double *)malloc(ncat*sizeof(double));
	cxfit = (double *)malloc(ncat*sizeof(double));
	cyfit = (double *)malloc(ncat*sizeof(double));
	rxfit = (double *)malloc(ncat*sizeof(double));
	ryfit = (double *)malloc(ncat*sizeof(double));
	who = (long *)malloc(ncat*sizeof(long));
	if ((xfit==NULL) || (yfit==NULL) || (zxfit==NULL) || (zyfit==NULL)
	 || (cxfit==NULL) || (cyfit==NULL) || (rxfit==NULL) || (ryfit==NULL)
	 || (wfit==NULL) || (who==NULL)) {
		fprintf(stderr, "Cannot MALLOC Fit\n");
		exit(EX_UNAVAILABLE);
	}
	sx = sxx = sy = syy = 0.0;
	for (j=0; j<c.nccd; j++) {
		m = 0;
		for (i=0; i<ncat; i++) {
			if (occd[i] == which[j]) {
				if (which[j] >= 40) {
					xfit[m] = ocol[i];
					yfit[m] = orow[i];
				} else {
					xfit[m] = c.ncol - ocol[i];
					yfit[m] = c.nrow - orow[i];
				}
				zxfit[m] = xi[i]/k.arcpix;
				zyfit[m] = eta[i]/k.arcpix;
				who[m] = csid[i];
				wfit[m] = 1.0;
				m++;
			}
		}
		ncoef = 3;
		sigmax = ls2fit(m,xfit,yfit,wfit,zxfit,rxfit,cxfit,who,
			ncoef,xcoef,sxcoef,&sumn,&sumw,&k);
		xsc = sqrt(xcoef[1]*xcoef[1] + xcoef[2]*xcoef[2]);
		xth = k.radian*atan2(xcoef[2],xcoef[1]);
		sigmay = ls2fit(m,xfit,yfit,wfit,zyfit,ryfit,cyfit,who,
			ncoef,ycoef,sycoef,&sumn,&sumw,&k);
		ysc = sqrt(ycoef[1]*ycoef[1] + ycoef[2]*ycoef[2]);
		yth = k.radian*atan2(-ycoef[1],ycoef[2]);
		printf(FMT1, which[j],m,sigmax,sigmay,xsc,ysc,xth,yth);
		camsc[j] = 0.5*(xsc+ysc);
		camth[j] = 0.5*(xth+yth);
		sx += camsc[j];
		sxx += camsc[j]*camsc[j];
		sy += camth[j];
		syy = camth[j]*camth[j];
	}
/*
 * Save bulk camera parameters
 */
	sx = sx/NCCD;
	sxx = sqrt(sxx/NCCD - sx*sx);
	sy = sy/NCCD;
	syy - sqrt(syy/NCCD - sy*sy);
	for (i=0; i<NCCD; i++) {
		camsc[i] = (camsc[i]-sx)*1000.0;
		camth[i] = camth[i]-sy;
	}
	printf(FMT2, sx,sxx,sy,syy);
	for (i=0; i<NAXIS; i++) {
		for (j=0; j<NAXIS; j++)
			im[i][j] = 0;
	}
	for (i=0; i<NCCD; i++)
		im[camy[i]][camx[i]] = camsc[i];
	strcpy(lb, "!sc.fits");
	i = kpwfits(lb,NAXIS,NAXIS,im);
	for (i=0; i<NAXIS; i++) {
		for (j=0; j<NAXIS; j++)
			im[i][j] = 0.0;
	}
	for (i=0; i<NCCD; i++)
		im[camy[i]][camx[i]] = camth[i];
	strcpy(lb, "!th.fits");
	i = kpwfits(lb,NAXIS,NAXIS,im);
/*
 * Look at radial profile
 */
	x0 = y0 = 3.5;
	for (m=0; m<NCCD; m++) {
		dx = camx[m]-x0;
		dy = camy[m]-y0;
		xfit[m] = sqrt(dx*dx + dy*dy);
		zxfit[m] = camsc[m];
		wfit[m] = 1.0;
		who[m] = m;
	}
	ncoef = 1;
	sigmaz = polyfit(NCCD,xfit,wfit,zxfit,rxfit,cxfit,who,
		ncoef,zcoef,szcoef,&sumn,&sumw,&k);
printf("%lf %lf %lf %lf\n",x0,y0,sigmaz,zcoef[0]);
/*
 * Clean Up Our Mess
 */
	mysql_close(&q);
	free(cra);
	free(cdec);
	free(cmag);
	free(csid);
	free(cccd);
	free(occd);
	free(ccol);
	free(ocol);
	free(crow);
	free(orow);
	free(xi);
	free(eta);
	free(xfit);
	free(yfit);
	free(zxfit);
	free(zyfit);
	free(wfit);
	free(cxfit);
	free(cyfit);
	free(rxfit);
	free(ryfit);
	free(who);
	free(idx);
	free(tmp);
	exit(EX_OK);
}
