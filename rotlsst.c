#include	"all.h"
/*
 ****************************************************************************
 *
 *  rotlsst  --  Initialize Camera Rotation
 */
void rotlsst(r,cc)
double r;
struct cam *cc;
{
	double s, c;
	int i;

	s = sin(r);
	c = cos(r);
	for (i=0; i<NROTM; i++)
		cc->xrot[i] = cc->yrot[i] = 0.0;
	cc->xrot[1] =  c;
	cc->xrot[2] =  s;
	cc->yrot[1] = -s;
	cc->yrot[2] =  c;
}
