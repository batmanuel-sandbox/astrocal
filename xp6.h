/*
 * Superset of RESLOVE needed for XP6 and SM
 */
#include	"options.h"
#include	"sm_declare.h"
/*
 */
#define	BIGLINE	200
#define		INTOX		0
#define		INTOY		1
#define		SP_PS		0
#define		SP_GRID		1
#define		SP_SQUARE	2
#define		SP_CLICK	3
#define		SP_LIMIT	4
#define		SP_DUMP		5
#define		N_SP		6
struct arg {
	char st[BIGLINE];
	char ca;
	long na;
	char cb;
	int ns1;
	struct sol *s1;
	int ns2;
	struct sol *s2;
	int ns3;
	struct fit *s3;
	int ns4;
	struct dcat *s4;
	int npval;
	double *pval;
	long *plut;
	char label[BIGLINE];
};
int	xp6line(), xp6decode(), xp6local(), xp6global(), xp6bystar(),
	xp6byplate(), xp6platefill(), xp6starfill(), xp6detag(),
	xp6fromplate(), xp6fromstar(), xp6pfroms(), xp6sfromp(),
	xp6platefit(), xp6starfit(), xp6dn();
void	xp6dosm(), xp6reset(), xp6help(), xp6dump(), xp6info(), xp6doa6(),
	xp6fortinc(), xp6emptyline();
/*
 */
#define	ERR_XP6_TooShort	-1
#define	ERR_XP6_ErrC1st		-2
#define	ERR_XP6_ErrC2nd		-3
#define	ERR_XP6_LocalMatch	-4
#define	ERR_XP6_LocalNoF	-5
#define	ERR_XP6_LocalCxCy	-6
#define	ERR_XP6_ByPlate		-6
#define	ERR_XP6_ByStar		-7
#define	ERR_XP6_PlateFill	-8
#define	ERR_XP6_StarFill	-9
#define	ERR_XP6_GlobalCxCy	-10
#define	ERR_XP6_DetagMatch	-11
#define	ERR_XP6_DetagCount	-12
#define	ERR_XP6_FromPlate	-13
#define	ERR_XP6_FromStar	-14
#define	ERR_XP6_PfromS		-15
#define	ERR_XP6_SfromP		-16
