//	IVec3d.hpp

//	This class defines a three-dimensional vector, with appropriate
//	operators.  (* is cross product.)

#ifndef IVEC3D_H
#define IVEC3D_H


#include <iostream>
#include <cmath>

#include <Vec3d.h>


class IVec3d {
   public:
	int x,y,z;				// vector components
	
	IVec3d() { x=y=z=0; }			// constructor
	IVec3d(const int xyz): x(xyz), y(xyz), z(xyz){}
	IVec3d(const double xyz): x((int)xyz), y((int)xyz), z((int)xyz){}
	IVec3d(const int vX, const int vY, const int vZ): x(vX), y(vY), z(vZ){}
	IVec3d(const double vX, const double vY, const double vZ): x((int)vX), y((int)vY), z((int)vZ){}
	IVec3d(const IVec3d& vec): x(vec.x), y(vec.y), z(vec.z){}

	// vector arithmetic

	IVec3d operator+(const IVec3d vec) const
	{ IVec3d out( x+vec.x, y+vec.y, z+vec.z ); return out; }

	IVec3d operator-(const IVec3d vec) const
	{ IVec3d out( x-vec.x, y-vec.y, z-vec.z ); return out; }

	IVec3d operator/(const IVec3d vec) const
	{ IVec3d out( x/vec.x, y/vec.y, z/vec.z ); return out; }

	IVec3d operator%(const IVec3d vec) const
	{ IVec3d out( x%vec.x, y%vec.y, z%vec.z ); return out; }


	IVec3d& operator+=(const IVec3d vec)
	{ x+=vec.x; y+=vec.y; z+=vec.z; return *this; }

	IVec3d& operator-=(const IVec3d vec)
	{ x-=vec.x; y-=vec.y; z-=vec.z; return *this; }

	IVec3d& operator/=(const IVec3d vec)
	{ x/=vec.x; y/=vec.y; z/=vec.z; return *this; }

	IVec3d& operator%=(const IVec3d vec)
	{ x%=vec.x; y%=vec.y; z%=vec.z; return *this; }


// scalar * and /

	IVec3d operator*(const int scal) const		// * an integer 
	{ IVec3d out( x*scal, y*scal, z*scal); return out; }

	friend IVec3d operator*(const int scal, const IVec3d vec)
	{ IVec3d out( vec.x*scal, vec.y*scal, vec.z*scal); return out; }

	IVec3d& operator*=(const int scal)
	{ x*=scal; y*=scal; z*=scal; return *this; }


	Vec3d operator*(const double scal) const		// * a scalar
	{ Vec3d out( x*scal, y*scal, z*scal); return out; }

	friend Vec3d operator*(const double scal, const IVec3d vec)
	{ Vec3d out( vec.x*scal, vec.y*scal, vec.z*scal); return out; }

	IVec3d operator/(const int scal) const		// / an integer scalar
	{ IVec3d out( x/scal, y/scal, z/scal); return out; }

	IVec3d& operator/=(const int scal)
	{ x/=scal; y/=scal; z/=scal; return *this; }


	Vec3d operator/(const double scal) const		// / a scalar
	{ Vec3d out( x/scal, y/scal, z/scal); return out; }


	// comparison
	int operator==( const IVec3d vec) const
	{ return (x==vec.x && y==vec.y && z==vec.z); }

	int operator!=( const IVec3d vec) const
	{ return (x!=vec.x || y!=vec.y || z!=vec.z); }


	// mapping to a lattice
	int index(IVec3d &L){
		return x + ( y + z*L.y ) * L.x;
	}
	
	int volume(void){return x*y*z;}
	
	
	// input/output
	
	friend std::ostream& operator<<(std::ostream& pStr, const IVec3d& vec)
	{ return (pStr << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')'); }

	friend std::istream& operator>>(std::istream pStr, IVec3d& vec)
	{ return (pStr >> vec.x >> vec.y >> vec.z ); }
	
	// prototypes
	IVec3d from_index(int ind, IVec3d &L);
	
};

/*
IVec3d IVec3d::from_index(int ind, IVec3d &L){
	IVec3d vec;
	vec.x = ind % L.x; ind /= L.x;
	vec.y = ind % L.y; ind /= L.y;
	vec.z = ind; //vec.z = ind % L.z;
	return vec;
}
*/

#endif//IVEC3D_H

