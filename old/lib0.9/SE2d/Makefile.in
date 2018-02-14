#LIBDIR=/home/scala/lib
LIBDIR=..
INC = -I./ -I$(LIBDIR)/VecNd/
LIB = -L./ -L$(LIBDIR)/VecNd/ -lVec2d

OPT = -O0 -g -D_RSEED=1234

CC = gcc $(OPT) $(INC) 
CPP = g++ $(OPT) $(INC)

ALLOBJS = Circle.o Ellipse.o SEllipse.o Segment.o SphericalCap.o Rectangle.o se2d_overlap.o
all: $(ALLOBJS)
	rm -fr libSE2d*.a
	ar rcv libSE2d.a  $(ALLOBJS)

#test: test.cpp 
#	$(CPP) $(LNK) test.cpp -o test.x -lVec2d -lSE2d 

Rectangle.o: Rectangle.h Rectangle.cpp
	$(CPP) -c $*.cpp

Circle.o: Circle.h Circle.cpp
	$(CPP) -c $*.cpp

Ellipse.o: Ellipse.h Ellipse.cpp
	$(CPP) -c $*.cpp

Segment.o: Segment.h Segment.cpp
	$(CPP) -c $*.cpp

SEllipse.o: SEllipse.h SEllipse.cpp
	$(CPP) -c $*.cpp

SphericalCap.o: SphericalCap.h SphericalCap.cpp
	$(CPP) -c $*.cpp

se2d_overlap.o: se2d_overlap.h se2d_overlap.cpp
	$(CPP) -c $*.cpp 

clean: 
	rm *.o *.do *~ *.x *.db 

