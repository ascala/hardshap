#LIBDIR=/home/scala/lib
LIBDIR=..
INC = -I./ -I$(LIBDIR)/VecNd  -I$(LIBDIR)/SE2d -I$(LIBDIR)/Wrap_plplot
LNK = -L$(LIBDIR)/VecNd -L$(LIBDIR)/SE2d -L$(LIBDIR)/Wrap_plplot 
LIB = -lVec2d -lSE2d -lwrap_pl 

OPT = -g -O0 -D_DEBUG -D_RSEED=1234

CPP = g++ $(OPT) $(INC) $(LNK)
CC = gcc $(OPT) $(INC) $(LNK)

#PROVAFILES =  LLcells2d.o

all: 
	@echo "This is a template for Linked List cells"

PL = `pkg-config --cflags --libs plplotd-c++` 

#test:
#	$(CPP) $(LNK) -U_USE_PL test.cpp -o test.x $(LIB) 
#	$(CPP) $(LNK) -D_USE_PL test.cpp -o test_pl.x $(LIB) $(PL) 

#LLcells2d.o: LLcells2d.h LLcells2d.cpp
#	$(CPP) -c $*.cpp
	
clean:
	rm -f *.x *.o *~
