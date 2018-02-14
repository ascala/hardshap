#ifndef RECTANGLE_H_
#define RECTANGLE_H_
#include <iostream>
#include <cmath>

#include <vector2d.h>

class Rectangle {
public:
	Vec2d r;       // center of the rectangle
	Vec2d a;	   // axis lengths
	Vec2d u[2];    // axis directions
	
	Rectangle();
	Rectangle(const Vec2d& center, const Vec2d& lengths);
	Rectangle(const Vec2d& center, const Vec2d& lengths, const Vec2d dir[2]);
	Rectangle(Rectangle const &);

	double rmax(){return sqrt(a[0]*a[0]+a[1]*a[1]);}
	double perimeter();
	double area();
	
	void in_box(Vec2d const& L){ r.in_box(L);}
	void rotate(double const angle);

//	stream operators
	friend std::ostream& operator<<(std::ostream& pStr, const Rectangle& pS)
	{ return ( pStr << pS.r << ' ' << pS.a << ' ' << pS.u[0]<<' '<<pS.u[1]); }

	friend std::istream& operator>>(std::istream& pStr, Rectangle& pS)
	{ return ( pStr >> pS.r >> pS.a >> pS.u[0] >> pS.u[1]); }
	
	
private:
};

#endif /*RECTANGLE_H_*/
