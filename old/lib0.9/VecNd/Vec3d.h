//	Vec3d.hpp

//	This class defines a three-dimensional vector, with appropriate
//	operators.  (* is cross product.)

#ifndef VEC3D_H
#define VEC3D_H

#include <iostream>
#include <cmath>

extern "C" {
#include <gaussdev.h>
}

class Vec3d {
   public:
	double x,y,z;				// vector components
	
	Vec3d() { x=y=z=0; }			// constructor
	Vec3d(const double xyz): x(xyz), y(xyz), z(xyz){}
	Vec3d(const double vX, const double vY, const double vZ): x(vX), y(vY), z(vZ){}
	Vec3d(const Vec3d& vec): x(vec.x), y(vec.y), z(vec.z){}

	// vector arithmetic

	Vec3d operator+(const Vec3d vec) const
	{ Vec3d out( x+vec.x, y+vec.y, z+vec.z ); return out; }

	Vec3d& operator+=(const Vec3d vec)
	{ x+=vec.x; y+=vec.y; z+=vec.z; return *this; }

	Vec3d operator-(const Vec3d vec) const
	{ Vec3d out( x-vec.x, y-vec.y, z-vec.z ); return out; }

	Vec3d& operator-=(const Vec3d vec)
	{ x-=vec.x; y-=vec.y; z-=vec.z; return *this; }
		

	double Dot(const Vec3d vec) const			// dot product
	{ return x*vec.x + y*vec.y + z*vec.z; }

	friend double Dot( const Vec3d p1, const Vec3d p2 )
	{ return p1.Dot(p2); }


	Vec3d operator*(const Vec3d vec) const		// cross product
	{ Vec3d out( y*vec.z-z*vec.y, z*vec.x-x*vec.z, x*vec.y-y*vec.x ); 
	  return out; }

	Vec3d Cross( const Vec3d vec ) const
	{ return *this * vec; }

	friend Vec3d Cross( const Vec3d p1, const Vec3d p2 )
	{ return p1 * p2; }


	Vec3d operator*(const double scal) const		// * a scalar
	{ Vec3d out( x*scal, y*scal, z*scal); return out; }

	friend Vec3d operator*(const double scal, const Vec3d vec)
	{ Vec3d out( vec.x*scal, vec.y*scal, vec.z*scal); return out; }

	Vec3d& operator*=(const double scal)
	{ x*=scal; y*=scal; z*=scal; return *this; }


	Vec3d operator/(const double scal) const		// / a scalar
	{ Vec3d out( x/scal, y/scal, z/scal); return out; }

	Vec3d& operator/=(const double scal)
	{ x/=scal; y/=scal; z/=scal; return *this; }

	// magnitude

	double LenSqr(void) const
	{ return x*x+y*y+z*z; }

	double Length(void) const
	{ return sqrt(LenSqr()); }

	// projection (component of *this parallel to vec)
	// Note: component perpendicular to vec is:  *this - Proj(vec)

	Vec3d Proj(const Vec3d vec)
	{ Vec3d out( vec * (this->Dot(vec) / vec.LenSqr()) ); return out; }

	// cosine of the angle between two vectors:
	double CosAng( const Vec3d vec)
	{ return this->Dot(vec) / (Length() * vec.Length()); }

	// comparison
	int operator==( const Vec3d vec) const
	{ return (x==vec.x && y==vec.y && z==vec.z); }

	int operator!=( const Vec3d vec) const
	{ return (x!=vec.x || y!=vec.y || z!=vec.z); }

	// input/output
	
	friend std::ostream& operator<<(std::ostream& pStr, const Vec3d& vec)
	{ return (pStr << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')'); }

	friend std::istream& operator>>(std::istream pStr, Vec3d& vec)
	{ return (pStr >> vec.x >> vec.y >> vec.z ); }


/* PROTOTYPES */
	void InBox(const double L);
	void InBox(const Vec3d &L);
	void RandDispl(const double Dmax);
	void RandDispl(const Vec3d &Dmax);
	void Randomize(const double L);
	void Randomize(const Vec3d &L);
	void Gaussian(const double sigma);
	void Gaussian(const Vec3d &sigma);
	
};

#endif//VEC3D_H

