#ifndef RECTANGLE_H_
#define RECTANGLE_H_
#include <iostream>
#include <cmath>

#include <Vec2d.h>

class Rectangle {
public:
	Vec2d r;       // center of the rectangle
	Vec2d a;	   // axis lengths
	Vec2d u[2];    // axis directions
	
	Rectangle();
	Rectangle(const Vec2d& center, const Vec2d& lengths, const Vec2d dir[2]);
	Rectangle(Rectangle const &);

	double perimeter();
	double area();
	
	void rotate(double const angle);

//	stream operators
	friend std::ostream& operator<<(std::ostream& pStr, const Rectangle& pS);
	friend std::istream& operator>>(std::istream pStr, Rectangle& pS);
	
	
private:
};

#endif /*RECTANGLE_H_*/
