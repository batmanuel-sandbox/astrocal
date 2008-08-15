#include	"all.h"
#define	SWAP(a,b)	{temp=(a);(a)=(b);(b)=temp;}
int ldgaussj(long double a[NCMAX][NCMAX], int n)
{
	int i,icol,irow,j,k,l,ll;
	long double big,dum,pivinv,temp;
	int indxc[NCMAX], indxr[NCMAX], ipiv[NCMAX];

	icol = irow = 0;
	for (j=0;j<n;j++) ipiv[j]=0;
	for (i=0;i<n;i++) {
		big=0.0;
		for (j=0;j<n;j++)
			if (ipiv[j] != 1)
				for (k=0;k<n;k++) {
					if (ipiv[k] == 0) {
						if (fabs(a[j][k]) >= big) {
							big=fabs(a[j][k]);
							irow=j;
							icol=k;
						}
					}
				}
		++(ipiv[icol]);
		if (irow != icol) {
			for (l=0;l<n;l++) SWAP(a[irow][l],a[icol][l]);
		}
		indxr[i]=irow;
		indxc[i]=icol;
		if (a[icol][icol] == 0.0) return(-1);
		pivinv=1.0/a[icol][icol];
		a[icol][icol]=1.0;
		for (l=0;l<n;l++) a[icol][l] *= pivinv;
		for (ll=0;ll<n;ll++)
			if (ll != icol) {
				dum=a[ll][icol];
				a[ll][icol]=0.0;
				for (l=0;l<n;l++) a[ll][l] -= a[icol][l]*dum;
			}
	}
	for (l=n-1;l>=0;l--) {
		if (indxr[l] != indxc[l]) {
			for (k=0;k<n;k++)
				SWAP(a[k][indxr[l]],a[k][indxc[l]]);
		}
	}
	return(0);
}
