#ifndef SIMBOX2D_H_
#define SIMBOX2D_H_

#include <se2d.h>
#include <SimPar.h>

#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<iostream>

//typedef SEllipse Particle;
typedef Ellipse Particle;

//template <class Particle>
class SimBox2d :  public SimPar {
public:
	int Npart; /* number of particles */
	Vec2d L; /* sides of the box*/
	
//	Particle particle;
	Particle *particles;
	
	SimBox2d():Npart(0) {}
	
	~SimBox2d(){
		if(Npart>0) delete[] particles;
	}

	// prototypes
/*	
	int read(char* name);
	int write(char* name);

	int read(FILE* fp);
	int write(FILE* fp);
*/	
	bool create_SQ(double phi, Particle particle, IVec2d Ncell);
//	bool create_HEX(double phi, double sigma, IVec2d const& cell);
	
	void enforce_periodic();
	
	bool any_overlap();
	int count_overlaps();
	bool some_overlap(int I, Particle &particle);
	
	
};





#endif //_SIMBOX2D_H_
