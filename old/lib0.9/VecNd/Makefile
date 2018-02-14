OPT = -O0 -g -D_RSEED=1234

CC = gcc $(OPT) -I./
CPP = g++ $(OPT) -I./

all: gaussdev.o Vec2d.o IVec2d.o Vec3d.o IVec3d.o
	rm -fr libVec?d.a
	ar rcv libVec2d.a gaussdev.o libVec2d.a IVec2d.o Vec2d.o
	ar rcv libVec3d.a gaussdev.o libVec3d.a IVec3d.o Vec3d.o

test: test.cpp all
	$(CPP) -L ./  test.cpp -lVec2d -lVec3d -o test.x

gaussdev.o: gaussdev.h gaussdev.c
	$(CC) -c $*.c

Vec2d.o: Vec2d.h Vec2d.cpp
	$(CPP) -c $*.cpp

IVec2d.o: IVec2d.h IVec2d.cpp
	$(CPP) -c $*.cpp

Vec3d.o: Vec2d.h Vec2d.cpp
	$(CPP) -c $*.cpp

IVec3d.o: IVec2d.h IVec2d.cpp
	$(CPP) -c $*.cpp

clean: 
	rm *.o *.do *~ *.x *.db 
