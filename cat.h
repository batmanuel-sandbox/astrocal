/*
 * Location Offsets Into USNOB Entry
 */
#define		B_WIDE		20
#define		B_RA		0
#define		B_SPD		1
#define		B_MU		2
#define		B_DET		3
#define		B_1STB		5
#define		B_1STR		6
#define		B_2NDB		7
#define		B_2NDR		8
#define		B_IR		9
/*
 * Location Offsets Into TRUECAT Entry
 */
#define		T_B_STAR	1
#define		T_B_REFERENCE	2
#define		T_B_GALAXY	4
#define		T_WIDE		11
#define		T_RA		0
#define		T_SPD		1
#define		T_BMAG		2
#define		T_RMAG		3
#define		T_FLAG		4
#define		T_MUX		5
#define		T_MUY		6
#define		T_PI		7
#define		T_SID		8
#define		T_HEALPATCH	9
#define		T_HEALSTORE	10
/*
 * Location Offsets For SIMOBS Output
 */
#define		P_WIDE		8
#define		P_SCALE		100000.0
#define		P_OID		0
#define		P_SID		1
#define		P_RAFT		2
#define		P_CCD		3
#define		P_X		4
#define		P_Y		5
#define		P_MAG		6
#define		P_HEAL		7
/*
 * Location Offsets For CATNEW
 */
#define		N_WIDE		20
#define		N_XX		0
#define		N_EXX		1
#define		N_YY		2
#define		N_EYY		3
#define		N_MX		4
#define		N_EMX		5
#define		N_MY		6
#define		N_EMY		7
#define		N_PX		8
#define		N_EPX		9
#define		N_PY		10
#define		N_EPY		11
#define		N_ZX		12
#define		N_EZX		13
#define		N_ZY		14
#define		N_EZY		15
#define		N_W		16
#define		N_N		17
#define		N_DX		18
#define		N_DY		19
/*
 * Offsets For HEAL
 */
#define		H_WIDE		5
#define		H_HEAL		0
#define		H_FRST		1
#define		H_LAST		2
#define		H_RA		3
#define		H_DEC		4
#define		HEALMULT	(3.0e08)
/*
 * Offsets For AUXCAT
 */
#define		A_SID		0
#define		A_HEALSTORE	1
#define		A_SUMNX		2
#define		A_SUMNY		3
#define		A_SIGMAX	4
#define		A_SIGMAY	5
#define		A_SUMWX		6
#define		A_SUMWY		7
#define		A_ERA		8
#define		A_EDEC		9
#define		A_EMUX		10
#define		A_EMUY		11
#define		A_EPIX		12
#define		A_EPIY		13
/*
 * Generic Structure For Any Catalog
 */
struct cat {
	int wide;
	int count;
	int key;
	int *base;
};
struct tcat {
	int ra;
	int spd;
	int bmag;
	int rmag;
	int flag;
	int mux;
	int muy;
	int pi;
	long sid;
	int patchHeal;
	int storeHeal;
};
struct dcat {
	double ra;
	double dec;
	double bmag;
	double rmag;
	int flag;
	double mux;
	double catmux;
	double muy;
	double catmuy;
	double pix;
	double piy;
	double catpi;
	double zdx;
	double zdy;
	double catzd;
	double rv;
	double catxi;
	double cateta;
	long sid;
	int patchHeal;
	int storeHeal;
	double era;
	double edec;
	double emux;
	double emuy;
	double epix;
	double epiy;
	double ezdx;
	double ezdy;
	double sigmax;
	double sumwx;
	int nfirst;
	int sumnx;
	int nxcoef;
	double sigmay;
	double sumwy;
	int sumny;
	int nycoef;
	double tpr0;
	double tpd0;
	double tpt0;
};
struct pcat {
	int oid;
	long sid;
	int raft;
	int ccd;
	int x;
	int y;
	int mag;
	int patchHeal;
};
struct acat {
	long sid;
	int storeHeal;
	int sumnx;
	int sumny;
	double sigmax;
	double sigmay;
	double sumwx;
	double sumwy;
	double era;
	double edec;
	double emux;
	double emuy;
	double epix;
	double epiy;
};
