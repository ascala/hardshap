#ifndef SPHERICALCAP_H_
#define SPHERICALCAP_H_

#include <iostream>
#include <cmath>

#include <vector2d.h>
//#include <Ellipse.h>
//#include <SEllipse.h>

class SphericalCap {
public:
	Vec2d r;       // center of 
	Vec2d dir;     
	double halflen;
	double rmax,rmax2; // radius (squared) of the spherical cap
	
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
	
	void rotate(double const angle);

// square distance between the axis of two spherical cap
	double dist2( SphericalCap const &);
	double dist2( SphericalCap const &, double &u1, double &u2);
// square distance from the axis to a point	
	double dist2(Vec2d const &point);
	double dist2(Vec2d const &point, double &u);
	
private:
};

// Generic functions

//bool overlap(SphericalCap &scI, SphericalCap &scJ);
//bool overlap(SphericalCap &scI, SphericalCap &scJ, Vec2d const& L);


#endif /*SPHERICALCAP_H_*/
