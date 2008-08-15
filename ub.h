#define	UBWIDE	20
#define	NOWIDE	22
#define	UBDEG	(1.0/360000.0)
#define	UBROOT	"/nofs/zos0/sel/Catalogues/usnob"
#define	NODEG	(1.0/3600000.0)
#define	NOROOT	"/nofs/reg1/xpmm/omerge"
struct usnob {
	int nn;
	double *ra;
	double *dec;
	double *bmag;
	double *rmag;
	int *xid;
};
struct acc {
	int spd;
	int first[NACC];
	int count[NACC];
};
struct ubraw {
	int ubint[UBWIDE];
};
struct noraw {
	int noint[NOWIDE];
};
/*
 */
int	ubgetlim(), ubread(), ubcorrel(), getub(), noread(), getno();
double	ubmag(), nomag();
