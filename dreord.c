/*
 ***************************************************************************
 *
 *  dreord  --  Inplace Reorder
 */
void dreord(n,idx,val,tmp)
int n,idx[];
double val[],tmp[];
{
	int i;

	for (i=0; i<n; i++)
		tmp[i] = val[i];
	for (i=0; i<n; i++)
		val[i] = tmp[idx[i]];
}
