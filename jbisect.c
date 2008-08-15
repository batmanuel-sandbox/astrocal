#include	<stdio.h>
/*
 ****************************************************************************
 *
 *  jbisect  --  Look Up Using Bisection  --  TABLE Must Be Sorted
 */
int jbisect(val,n,table)
long val,table[];
int n;
{
	long zf, zl, zm;
	int i, f, l, m;
/*
 * Initialization
 */
	f = 0;
	zf = table[f];
	if (val < zf)
		return(-1);
	if (val == zf)
		return(f);
	l = n-1;
	zl = table[l];
	if (val == zl)
		return(l);
	if (val > zl)
		return(-2);
/*
 * Search Until Interval Is Small
 */
	while ((l-f) > 10) {
		m = (f+l+1)/2;
		zm = table[m];
		if (zm > val) {
			l = m;
			zl = zm;
		} else if (zm < val) {
			f = m;
			zf = zm;
		} else
			return(m);
	}
	for (i=f+1; i<l; i++) {
		if (val == table[i])
			return(i);
	}
	return(-3);
}
