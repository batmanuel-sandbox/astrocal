/*
 * Used In Most Places
 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<sysexits.h>
#include	<math.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<string.h>
#include	<errno.h>
#include	<sys/stat.h>
#include	<sys/types.h>
/*
 */
#include	"local.h"
#include	"sla.h"
#include	"key.h"
#include	"cam.h"
#include	"sim.h"
#include	"cronos92.h"
#include	"cat.h"
#include	"heal.h"
#include	"fit.h"
#include	"sol.h"
#include	"bf.h"
#include	"fls.h"
#include	"xp6.h"
#include	"cent.h"
#include	"ub.h"
/*
 */
#define		EVER		;;
void	slalsst(), lsstcamera(), keyinit(), byfield(), byrow(), getlim(),
	gimmeb(), dorasort(), iuqsrt(), trueload(), myfree(), simsort(),
	gaussrand(), simcat(), rotlsst(), toobs(), toradec(), dorot(), juqsrt(),
	simlut(), probload(), catload(), gencatlut(), scribble(), gobble(),
	cat2sql(), docatsql(), myfield(), tgobble(), rescull(), getoldnew(),
	allheal(), simsetup(), resproc(), getupper(), resorder(), xy2xieta(),
	fill2dv(), xieta2sky(), resgetcat(), fit2cat(), onproc(), toskyfit(),
	toradec(), pscamera(), getcamera(), duqsrt(), kepcamera(), slakepler(),
	kepupper(), keptoobs(), kepxieta(), digits(), keptoradec(), csproc(),
	csanal(), esscamera(), slaess(), essupper(), fromskyfit(), keptofit(),
	solsave(), fitsave(), catsave(), s1anal(), s2anal(), s3anal(),
	s4anal(), ireord(), dreord(), jreord(), skync(), kepfromfit(),
	kepradec(), getkill(), fill3dv(), slanone(), topixfit(), frompixfit(),
	freord(), ophupper(), slaps(), ophnodup(), getbigcat(), fillpdv();
int	gimmeline(), bdecode(), docamera(), fakemag(), true2sim(),
	simlist(), tdecode(), ibisect(), resgetobs(), gaussj(), fill1dv(),
	trim2(), trim1(), jbisect(), ldgaussj(), gpc1a(), rdtokep(),
	dbisect(), dfbisect(), dlbisect(), findmag(), gimmebig(), dfbisect(),
	dlbisect(), gimmecount();
long	genlen();
int	*mymalloc();
double	effwave(), unitrand(), ls2fit(), ls1fit(), compwgt(), lincorr(),
	wgtkill(), ls3fit(), chunkfit(), polyfit();
struct healsla *reslist(), *keplist();
struct fit *resgetfit(), *kepgetfit(), *gimmefit();
struct sol *resbyccd(), *resbystar(), *gimmesol();
struct dcat *gimmedcat();
