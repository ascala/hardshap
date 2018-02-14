#ifndef SIMBOX2D_H_
#define SIMBOX2D_H_

#include <se2d.h>
#include <SimPar.h>

#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<iostream>
#include<fstream>

typedef Circle Particle;
#if defined(_CIRCLE)
   	typedef Circle BigParticle;
#elif defined(_ELLIPSE)
    typedef Ellipse BigParticle;
#elif defined(_SELLIPSE)
    typedef SEllipse BigParticle;
#elif defined(_RECTANGLE)
 	typedef Rectangle BigParticle;
#else
	typedef Circle BigParticle;
#endif 	

class SimBox2d :  public SimPar {
public:
	int Npart; /* number of particles */
	Vec2d L; /* sides of the box*/
	
	BigParticle bigparticles[2];
	Particle *particles;
	
	SimBox2d():Npart(0) {}
	
	~SimBox2d(){if(Npart>0) delete[] particles;}

        // input/output
	friend std::ostream& operator<<(std::ostream& output, const SimBox2d& box){ 
    	output << box.Npart << std::endl;  	
    	output << box.L << std::endl;  	
    	output << box.MaxDisp << std::endl;  	
		output << box.MaxRot << std::endl;  	
		output << box.BigMaxDisp << std::endl;  	
		output << box.BigMaxRot << std::endl;  	
    	for (int i = 0; i < 2; ++i) output << box.bigparticles[i] << std::endl; 
    	for (int i = 0; i < box.Npart; ++i) output << box.particles[i] << std::endl; 
    	return output; 
	}

	friend std::istream& operator>>(std::istream& input, SimBox2d& box){ 
    	if(box.Npart>0) { delete[] box.particles; box.Npart=0;}
    	input >> box.Npart;
    	input >> box.L;
    	input >> box.MaxDisp;  	
		input >> box.MaxRot;  	
		input >> box.BigMaxDisp;  	
		input >> box.BigMaxRot;  	
    	for (int i = 0; i < 2; ++i) input >> box.bigparticles[i];
    	box.particles = new Particle[box.Npart];
    	for (int i = 0; i < box.Npart; ++i) input >> box.particles[i];
    	return input; 
	}

	bool write_conf(char *namefile){
		std::fstream myfile;
    	myfile.precision(16);
    
    	myfile.open(namefile,std::ios::out);
    	myfile<<*this;
    	myfile.close();
        
    	return true;
	}       

	bool read_conf(char *namefile){
        std::fstream myfile;
        myfile.open(namefile,std::ios::in);
        myfile >> *this;
        myfile.close();
        
        return true;
} 

	double packing_fraction(){
		double area=0;
    	for (int i = 0; i < Npart; ++i) area+=particles[i].area();
    	return area/(L[0]*L[1]-bigparticles[0].area()-bigparticles[1].area());
	}

	bool create_RND(double phi, BigParticle bigparticle, Particle particle, int Nsmall, double angle=0);
	bool create_RND(double phi, const Vec2d& side, BigParticle bigparticle, Particle particle, double angle=0);
	
	void enforce_periodic();
	
	bool any_overlap();
	int count_overlaps();

	bool some_overlap(int I, Particle &particle);
	bool some_big_overlap(int I, BigParticle &bigparticle);
	
	
};





#endif //_SIMBOX2D_H_
