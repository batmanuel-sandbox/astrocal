/*
 * Structures To Hold Solutions By Heal
 */
#define		A_WIDE		3
#define		A_HEAL		0
#define		A_OID		1
#define		A_SLAIX		2
/*
 * Structure Of REFEPOCH
 */
#define		E_WIDE		4
#define		E_HEAL		0
#define		E_JD0		1
#define		E_R0		2
#define		E_D0		3
/*
 */
struct healsla {
	int oid;
	struct sla slavals;
};
struct healobs {
	int heal;
	int oid;
	int slaix;
};
