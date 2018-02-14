#LIBDIR=/home/scala/lib
LIBDIR=..

INC =  -I$(LIBDIR)/VecNd/ -I$(LIBDIR)/SE2d/ -I$(LIBDIR)/LLcells/ -I$(LIBDIR)/Wrap_plplot
LNK =  -L$(LIBDIR)/VecNd/ -L$(LIBDIR)/SE2d/ -L$(LIBDIR)/LLcells/ -L$(LIBDIR)/Wrap_plplot
PLPLOT = `pkg-config --cflags --libs plplotd-c++`
GSL = -lm -lgsl -lgslcblas
LIBS = $(LNK)  -lwrap_pl -lSE2d -lVec2d $(PLPLOT) $(GSL)

#OPT = -O0 -g -D_RSEED=1234
OPT = -O3

CC = gcc $(OPT) $(INC) 
CPP = g++ $(OPT) $(INC)

#all: gsl
all: gsl scap segment overlap vec2d se2d wrap_pl llcells

gsl_fmin: gsl_fmin.cpp gsl_fmin.h
	$(CPP) -c $@.cpp
	
gsl: gsl_fmin test_gsl_simplex.cpp 
	$(CPP) $(LNK) gsl_fmin.o test_$@_simplex.cpp -o test_$@_simplex.x $(PL) $(LIBS) 
#	$(CPP) $(LNK) gsl_fmin.o test_$@_conjgrad.cpp -o test_$@_conjgrad.x $(PL) $(LIBS) 
	
segment: test_segment.cpp
	$(CPP) $(LNK) test_$@.cpp -o test_$@.x $(PL) $(LIBS) 

rectangle: test_rectangle.cpp
	$(CPP) $(LNK) test_$@.cpp -o test_$@.x $(PL) $(LIBS) 

scap: test_scap.cpp
	$(CPP) $(LNK) test_$@.cpp -o test_$@.x $(PL) $(LIBS) 

vec2d: test_vec2d.cpp
	$(CPP) $(LNK) test_$@.cpp -o test_$@.x $(PL) $(LIBS) 

se2d: test_se2d.cpp
	$(CPP) $(LNK) test_$@.cpp -o test_$@.x $(PL) $(LIBS) 
	
wrap_pl: test_wrap_pl.cpp
	$(CPP) $(LNK) test_$@.cpp -o test_$@.x $(PL) $(LIBS) 

overlap: test_overlap.cpp
	$(CPP) $(LNK) test_$@.cpp -o test_$@.x $(PL) $(LIBS) 

llcells: test_llcells.cpp
	$(CPP) $(LNK) test_$@.cpp -o test_$@.x $(PL) $(LIBS) 
	
clean: 
	rm *.o *.do *~ *.x *.db 

