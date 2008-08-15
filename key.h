/*
 * Definitions and stuff used everywhere
 */
#define		TAG		(-987654321)
#define		NACC		(4*24)
#define		TOBIN		(4.0/15.0)
#define		HALF		(180*3600*1000)
#define		CIRCLE		(HALF+HALF)
#define		HT		011
#define		MYWIDE		30
#define		NMEMKEY		100
#define		TENE1		10
#define		TENE2		100
#define		TENE3		1000
#define		TENE4		(10*1000)
#define		TENE5		(100*1000)
#define		TENE6		(1000*1000)
#define		TENE7		(10*1000*1000)
#define		TENE8		(100*1000*1000)
#define		TENE9		(1000*1000*1000)
#define		BIGLINE		200
#define		FAKE_NOMOVE	1
#define		FAKE_MUPI	2
#define		FIT_POS		0x1
#define		FIT_MU		0x2
#define		FIT_ZD		0x4
#define		FIT_PI		0x8
#define		FIT_MP		(FIT_POS | FIT_MU | FIT_PI)
#define		FIT_ALL		(FIT_POS | FIT_MU | FIT_ZD | FIT_PI)
#define		FIT_NC		4
#define		NVMAX		100
#define		RV		0.0
#define		MODEL_LSST	1
#define		MODEL_PS	2
#define		MODEL_KEPLER	3
#define		MODEL_ESSENCE	4
#define		KILL_SallO	-1
#define		KILL_OallS	-2
#define		SAVE_NEWCAT	1
#define		SAVE_SX		2
struct key {
	int *mbase[NMEMKEY];
	int model;
	int verbose;
	int fakeit;
	int simul;
	int ndefccd;
	int starfit;
	long storeside;
	long storepix;
	double storeres;
	long patchside;
	long patchpix;
	double patchres;
	double mmpix;
	double arcpix;
	double scale;
	double pixunits;
	double radunits;
	double halfpi;
	double pi;
	double twopi;
	double radian;
	double demin;
	double dpmin;
	double dzmin;
	int iter;
	int itmax;
	long curstore;
	long curpatch;
	long loaded;
	double nomepoch;
	double refjd0;
	double refr0;
	double refd0;
	double refwave;
	struct sla refsla;
	double wlong;
	int counter;
	int firstflag;
	double maxmu;
	int trim1few;
	double trim1mu;
	double trim1zd;
	double trim1pi;
	int ccdtoofew;
	int nverb;
	int verbid[NVMAX];
	int lastiter;
	int nkill;
	int *ktype;
	long *kval;
	int docatsave;
	char outroot[BIGLINE];
	int pixels;
	int cleanup;
	int redo;
	double bright;
	double faint;
	double pcd;
};
/*
 *  Declare Unique KVALs To Avoid Memory Leaks
 */
#define		K0KVAL		0
#define		K1KVAL		1
#define		K2KVAL		2
#define		K3KVAL		3
#define		K4KVAL		4
#define		K5KVAL		5
#define		K6KVAL		6
#define		K7KVAL		7
#define		K8KVAL		8
#define		K9KVAL		9
