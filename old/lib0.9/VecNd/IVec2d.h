//	IVec2d.hpp

#ifndef IVEC2D_H
#define IVEC2D_H


#include <iostream>
#include <cmath>

#include <Vec2d.h>


class IVec2d {
   public:
	int x,y;				// vector components
	
	IVec2d() { x=y=0; }			// constructor
	IVec2d(int const xy): x(xy), y(xy){}
	IVec2d(double const xy): x((int)xy), y((int)xy) {}
	IVec2d(int const vX, int const vY): x(vX), y(vY) {}
	IVec2d(double const vX, double const vY): x((int)vX), y((int)vY) {}
	IVec2d(IVec2d const& vec): x(vec.x), y(vec.y) {}

	// dot product
	double dot(IVec2d const& vec) {return x*vec.x+y*vec.y;}

	// vector arithmetic (* is not the dot product !!!)

	IVec2d operator+(IVec2d const& vec) const
	{ IVec2d out( x+vec.x, y+vec.y ); return out; }

	IVec2d operator-(IVec2d const& vec) const
	{ IVec2d out( x-vec.x, y-vec.y ); return out; }

	IVec2d operator*(IVec2d const& vec) const
	{ IVec2d out( x*vec.x, y*vec.y ); return out; }

	IVec2d operator/(IVec2d const& vec) const
	{ IVec2d out( x/vec.x, y/vec.y ); return out; }

	IVec2d operator%(IVec2d const& vec) const
	{ IVec2d out( x%vec.x, y%vec.y ); return out; }


	IVec2d& operator+=(IVec2d const& vec)
	{ x+=vec.x; y+=vec.y; return *this; }

	IVec2d& operator-=(IVec2d const& vec)
	{ x-=vec.x; y-=vec.y; return *this; }

	IVec2d& operator*=(IVec2d const& vec)
	{ x*=vec.x; y*=vec.y; return *this; }

	IVec2d& operator/=(IVec2d const& vec)
	{ x/=vec.x; y/=vec.y; return *this; }

	IVec2d& operator%=(IVec2d const& vec)
	{ x%=vec.x; y%=vec.y; return *this; }


// scalar * and /

	IVec2d operator*(int const scal) const		// * an integer 
	{ IVec2d out( x*scal, y*scal ); return out; }

	friend IVec2d operator*(int const scal, IVec2d const vec)
	{ IVec2d out( vec.x*scal, vec.y*scal ); return out; }

	IVec2d& operator*=(int const scal)
	{ x*=scal; y*=scal; return *this; }


	Vec2d operator*(double const scal) const		// * a scalar
	{ Vec2d out( x*scal, y*scal ); return out; }

	friend Vec2d operator*(double const scal, IVec2d const vec)
	{ Vec2d out( vec.x*scal, vec.y*scal ); return out; }

	IVec2d operator/(int const scal) const		// / an integer scalar
	{ IVec2d out( x/scal, y/scal ); return out; }

	IVec2d& operator/=(int const scal)
	{ x/=scal; y/=scal; return *this; }


	Vec2d operator/(double const scal) const		// / a scalar
	{ Vec2d out( x/scal, y/scal ); return out; }


	// comparison
	int operator==( IVec2d const& vec) const
	{ return ( x==vec.x && y==vec.y ); }

	int operator!=( IVec2d const& vec) const
	{ return ( x!=vec.x || y!=vec.y ); }


	// mapping to a lattice
	int index(IVec2d const &L){
		return x +  y * L.x;
	}
	
	int volume(void){return x*y;}
	
	
	// input/output
	
	friend std::ostream& operator<<(std::ostream& pStr, IVec2d const& vec)
	{ return (pStr << '(' << vec.x << ',' << vec.y << ')'); }

	friend std::istream& operator>>(std::istream pStr, IVec2d& vec)
	{ return (pStr >> vec.x >> vec.y); }
	
	// prototypes
	IVec2d from_index(int ind, IVec2d const &L);
	
};

/*
IVec2d IVec2d::from_index(int ind, IVec2d &L){
	IVec2d vec;
	vec.x = ind % L.x; ind /= L.x;
	vec.y = ind % L.y; ind /= L.y;
	vec.z = ind; //vec.z = ind % L.z;
	return vec;
}
*/

#endif//IVEC2D_H

