#LIBDIR=/home/scala/lib
LIBDIR=..

INC = -I./ -I$(LIBDIR)/VecNd/ -I$(LIBDIR)/SE2d/ -I$(LIBDIR)/LLcells/ -I/usr/include/plplot
PL = `pkg-config --cflags --libs plplotd-c++`
LNK = -L./ -L$(LIBDIR)/VecNd/ -L$(LIBDIR)/SE2d/ $(PL)
libs = -lVec2d -lSE2d 

OPT = -O0 -g -D_RSEED=1234

CC = gcc $(OPT) $(INC) 
CPP = g++ $(OPT) $(INC)

all: wrap_pl.o 
	ar rs libwrap_pl.a wrap_pl.o

wrap_pl.o: wrap_pl.h wrap_pl.cpp
	$(CPP) -c $*.cpp 

clean: 
	rm *.o *.do *~ *.x *.db 

