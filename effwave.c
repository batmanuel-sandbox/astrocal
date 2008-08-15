#include	"all.h"
/*
 ****************************************************************************
 *
 *  effwave  --  return effective wavelength for this filter
 */
double effwave(f)
char f;
{
	double l, h;

	switch (f) {
	case 'u':	l= 330.0; h= 403.0;		break;
	case 'g':	l= 403.0; h= 552.0;		break;
	case 'r':	l= 552.0; h= 691.0;		break;
	case 'i':	l= 691.0; h= 818.0;		break;
	case 'z':	l= 818.0; h= 922.0;		break;
	case 'y':
	case 'Y':	l= 970.0; h=1015.0;		break;
	default:
		fprintf(stderr, "Unknown Filter (%c)\n", f);
		exit(EX_UNAVAILABLE);
	}
	return(0.0005*(l+h));
}
