#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <vector2d.h>

class Circle {
public:
	Vec2d r; 
	double radius, radius2;
	
	Circle(): radius(0.5), radius2(0.25){}
	Circle(double const &Rmax): radius(Rmax), radius2(Rmax*Rmax) {}
	Circle(Vec2d const &pos, double const &Rmax): 
		r(pos), radius(Rmax), radius2(Rmax*Rmax) {}

	// input/output
	friend std::ostream& operator<<(std::ostream& output, const Circle& s)
	{ return (output << s.r << " " << s.radius); }
	friend std::istream& operator>>(std::istream& input, Circle& s)
	{ input >> s.r >> s.radius; s.radius2=s.radius*s.radius; return input; }

// prototypes 
	double rmax(){return radius;}
	double perimeter();
	double area();
	
	void in_box(Vec2d const& L){ r.in_box(L);}
	void rotate(double const angle){}

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

