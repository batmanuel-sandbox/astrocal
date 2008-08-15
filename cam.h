/*
 * LSST Camera Stuff
 */
#define		CCDMAX		(15*15)
#define		RAFTMAX		(8*8)
#define		NROTM		3
#define		QUANTUM		10.0
#define		NQDIM		31
#define		NQP1		(2*NQDIM+1)
#define		NQDEEP		4
/*
 */
struct cam {
	double chipwide;
	double chiptall;
	double raftwide;
	double rafttall;
	double fov;
	double extrad;
	double xrot[NROTM];
	double yrot[NROTM];
	double ccdx0[CCDMAX];
	double ccdy0[CCDMAX];
	int nccd;
	int ncol;
	int nrow;
	int xpos[CCDMAX];
	int ypos[CCDMAX];
	int xraft[CCDMAX];
	int yraft[CCDMAX];
	int iccd[CCDMAX];
	int ndeep[NQP1][NQP1];
	int deep[NQP1][NQP1][NQDEEP];
	int extnra;
	int extrl[2];
	int extrh[2];
	int extdl;
	int extdh;
	int ccdpercam;
	int ccdperraft;
	int raftmult;
	int colflip[CCDMAX];
	int rowflip[CCDMAX];
};
