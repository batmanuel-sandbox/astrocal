/*
 * Definitions for big file ASCII reader
 */
#define		BF_CHUNK	8*1024
struct bf {
	int mode;
	int count;
	int total;
	int fd;
	char fname[BIGLINE];
	char buf[BF_CHUNK];
};
