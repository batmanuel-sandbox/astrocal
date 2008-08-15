FFLAGS	= -O -Wall -pedantic
CFLAGS	= -O -Wall -I../linux/sm/src
LFLAGS	=
MS	= -L/usr/local/mysql/include/mysql.h \
	-L/usr/local/mysql/lib \
	-lmysqlclient
MYLIB	= -L/home/dgm/linux/lib \
	-lsla \
	-lcfitsio \
	-lchealpix \
	-lplotsub \
	-ldevices \
	-lutils \
	-L/usr/X11R6/lib64 \
	-lX11
MYH	= all.h cam.h key.h sla.h cronos92.h cat.h sim.h heal.h fit.h sol.h \
	local.h bf.h fls.h xp6.h cent.h

all:	bigast

RP	= bigast.o keyinit.o effwave.o getcamera.o pscamera.o lsstcamera.o \
	esscamera.o kepcamera.o slaps.o juqsrt.o dreord.o jbisect.o rotlsst.o \
	toobs.o dorot.o docamera.o ls2fit.o fill2dv.o ldgaussj.o kpwfits.o \
	polyfit.o fillpdv.o gaussj.o

bigast: $(RP)
	cc -o bigast $(RP) $(MS) $(MYLIB)

$(RP):	$(MYH)

clean:
	rm -f *.o bigast
