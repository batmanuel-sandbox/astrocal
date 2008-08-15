/*
 */
struct sgcat {
	long sid;
	double ra;
	double dec;
	double gmag;
	double rmag;
	double mura;
	double mudec;
	double parallax;
	int flag;
};
struct sgep {
	int field;
	int oid;
	double mjd;
	double r0;
	double d0;
	double camrot;
	char filter;
	int nsim;
	int ccd;
};
/*
 */
struct sgcat *flsload();
struct sgep *flscadence(), *fls1ep();
void	flsproject(), fls1cat();
