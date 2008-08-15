/*
 * Structure To Hold Solutions
 */
#define		NCMAX		10
struct sol {
	int sumnx;
	int sumny;
	int nchopx;
	int nchopy;
	int nxcoef;
	int nycoef;
	int xstarfit;
	int ystarfit;
	int oid;
	long sid;
	int ccd;
	int frst;
	int last;
	int nfirst;
	double sumwx;
	double sumwy;
	double sigmax;
	double sigmay;
	double xcoef[NCMAX];
	double sxcoef[NCMAX];
	double ycoef[NCMAX];
	double sycoef[NCMAX];
	double extra0;
	int model;
};
