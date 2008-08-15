#define		NMMAX	65
#define		NMWRK	(4*NMMAX)
#define		NXYMAX	(NMMAX*NMMAX)
#define		N_ALG		3
#define		ALG_1		1
#define		ALG_2		2
#define		ALG_3		4
#define		E_BAD_A		-11
#define		E_BAD_B		-12
#define		E_BAD_WIDTH	-13
#define		E_TOO_FEW	-14
#define		E_SINGULAR	-15
#define		E_DIAGONAL	-16
#define		E_CHI_SQUARED	-17
#define		E_SELECT	-18
#define		E_TOO_CLOSE	-19
#define		E_RANGE		-20
#define		E_LOST		-21
#define		E_CONVERGE	1
#define		E_ITERATE	2
#define		E_ALMOST	3
/*
 */
struct dgm123 {
	int ncoef;
	int nrast;
	int nin;
	int nref;
	int verbose;
	int iter;
	int pixel[NXYMAX];
	double param[NCMAX];
	double eparam[NCMAX];
	double alpha[NCMAX][NCMAX];
	double beta[NCMAX];
	double elold[NCMAX];
	double elnew[NCMAX];
	double sgold[NCMAX];
	double sgnew[NCMAX];
	double alold[NCMAX][NCMAX];
	double alnew[NCMAX][NCMAX];
	double beold[NCMAX];
	double benew[NCMAX];
	int xrast[NXYMAX];
	int yrast[NXYMAX];
	double zorast[NXYMAX];
	double zcrast[NXYMAX];
	double zrrast[NXYMAX];
	double *pxmin;
	double *pxmax;
	double *pymin;
	double *pymax;
	double chisq;
	double stder;
	double chold;
	double stold;
	double chnew;
	double stnew;
	double flamd;
	double pi;
	double rootpi;
	double root2;
	int ncols;
	int nrows;
	int npixels;
	float *image;
	float *imwrk;
	int *idx;
	double *tmp;
	int xoff;
	double xmarg[NMMAX];
	int yoff;
	double ymarg[NMMAX];
	int nmarg;
	double marg[NMMAX];
	double flamdok;
	double ratiomin;
	int nitmax;
	double dc1zmin;
	double dc1zmax;
	double dc1sfract;
	double dc2zmin;
	double dc2zmax;
	double dc2sfract;
	double dc3zmin;
	double dc3zmax;
	double dc3dmin;
	double dc3sfract;
	int dc3nplim;
	double lost;
};
/*
 */
void	errf3(), image123(), catalog123(), nodup(), duqsrt(), dreord(),
	thisccd(), flsinit(), flsgetcat(), flsloop(), flscat2cam(),
	flscat2sky(), flssky2sex();
int	dcalc1(), dcalc2(), dcalc3(), dgminv(), alg3(), cond123(), curf3(),
	headin(), r4in(), dfbisect(), dlbisect(), btin(), fg3(), dcalc2(),
	alg2(), curf2(), fg2(), fg1(), dcalc1(), alg1(), curf1(), getmarg();
struct sgep *flsgenep();
/*
 */
struct kpstore {
	int nn;
	int *stat;
	int *chip;
	int *chan;
	double *ra;
	double *de;
	double *km;
	double *mux;
	double *muy;
	double *plx;
	long *sid;
	double *col;
	double *row;
	double *ocol;
	double *orow;
	double *okm;
	int nep;
	double *ep;
	double *dx;
	double *dy;
	char cat[BIGLINE];
	char root[BIGLINE];
	double bright;
	double faint;
	double point;
	int nseq;
	int seq;
	int ch;
	int get;
	double dt;
	int oid;
	char simroot[BIGLINE];
	char myobs[BIGLINE];
	char cfn[BIGLINE];
	char ffn[BIGLINE];
	char ifn[BIGLINE];
	char lfn[BIGLINE];
	char skycmd[BIGLINE];
	char sexcmd[BIGLINE];
	int algreq;
	int alguse;
	int nheal;
	int *heal;
};
/*
 */
#define	 DT	6.01
#define	NBRIGHT		10
#define	NFAINT		300
#define	KPCOL		1100
#define	KPROW		1024
#define	KPPIX		(KPROW*KPCOL)
/*
 */
void    kpgenep(), kploop(), kpinit(), kpgetcat(), kpcoadd(), kpdosex();
int     kprfits(), kpwfits(), kprhead(), gimmesex();
/*
 */
struct dgmsex {
	char fn[BIGLINE];
	int nn;
	double *xx;
	double *yy;
	double *mm;
};
