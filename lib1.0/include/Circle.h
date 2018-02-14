#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <vector2d.h>

class Circle {
public:
	Vec2d r; 
	double rmax, rmax2;
	
	Circle(): rmax(0.5), rmax2(0.25){}
	Circle(double const &Rmax): rmax(Rmax), rmax2(Rmax*Rmax) {}
	Circle(Vec2d const &pos, double const &Rmax): 
		r(pos), rmax(Rmax), rmax2(Rmax*Rmax) {}

	// input/output
	
	friend std::ostream& operator<<(std::ostream& pStr, const Circle& s)
	{ return (pStr << "center: " << s.r << " radius: " << s.rmax); }

/*
	friend std::istream& operator>>(std::istream pStr, Circle& s)
	{ return (pStr >> s.r >> s.sigma ); }
*/

// prototypes 

	double perimeter();
	double area();

	Vec2d const on_surf(const double angle);
	Vec2d const Don_surf(double const angle);
	
	double const dir2angle( Vec2d const& r);

	double const fsurf(Vec2d const& point);
//	double const fsurf(double const angle);
	
	Vec2d const grad(Vec2d const& point);
	Vec2d const grad(double const angle);
	
	Vec2d const Dgrad(double const angle);

//

	void copy(Circle &B);
	void in_box(Vec2d &L);
	
	bool overlap(Circle &B, double sigmaAB2, Vec2d &L);
	bool overlap(Circle &B, Vec2d &L);
};

// Generic functions

//bool overlap(Circle &cI, Circle &cJ);
//bool overlap(Circle &cI, Circle &cJ, Vec2d const& L);

#endif /*CIRCLE_H_*/

