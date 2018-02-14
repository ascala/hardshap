#ifndef SPHERICALCAP_H_
#define SPHERICALCAP_H_

#include <iostream>
#include <cmath>

#include <Vec2d.h>
//#include <Ellipse.h>
//#include <SEllipse.h>

class SphericalCap {
public:
	Vec2d r;       // center of 
	Vec2d dir;     
	double halflen;
	double radius; // radius (squared) of the spherical cap
	
	SphericalCap();
	SphericalCap(const Vec2d& center, const Vec2d& half, const double rad);
	SphericalCap(SphericalCap const &);
//	SphericalCap(Ellipse const &e);
//	SphericalCap(SEllipse const &e);

//	stream operators
	friend std::ostream& operator<<(std::ostream& pStr, const SphericalCap& pSC);
	friend std::istream& operator>>(std::istream pStr, SphericalCap& pSC);
	

// prototypes 

	double perimeter();
	double area();

// square distance between two segments
	double dist2( SphericalCap const &);
	double dist2( SphericalCap const &, double &u1, double &u2);
	
private:
};

// Generic functions

//bool overlap(SphericalCap &scI, SphericalCap &scJ);
//bool overlap(SphericalCap &scI, SphericalCap &scJ, Vec2d const& L);


#endif /*SPHERICALCAP_H_*/
