/*
 * Structure To Hold Fit
 */
struct fit {
	int oid;
	long sid;
	int flag;
	double mjd;
	double fyear;
	double xi;
	double rxi;
	double eta;
	double reta;
	double xi0;
	double eta0;
	double weight;
	double wfirst;
	int raft;
	int ccd;
	double x;
	double y;
	double bmag;
	double rmag;
	double effw;
	int patchHeal;
	int storeHeal;
	int xfit;
	int yfit;
	double xhat;
	double yhat;
	double rxhat;
	double ryhat;
	double pfx;
	double pfy;
	double rra;
	double rdec;
	double rv;
	int catidx;
	int obsidx;
	int nfirst;
};
