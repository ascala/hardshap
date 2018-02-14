#ifndef VEC2d_H_
#define VEC2d_H_

#include <iostream>
#include <cmath>

extern "C" {
#include <gaussdev.h>
}

class Vec2d
{
public:
	double x;
	double y;
	
	Vec2d();
	Vec2d(double const);
	Vec2d(double const, double const);
	Vec2d(Vec2d const & other);
	virtual ~Vec2d();
	
//	stream operators
	friend std::ostream& operator<<(std::ostream& pStr, Vec2d const& pV);
	friend std::istream& operator>>(std::istream pStr, Vec2d& pV);

// assignment (overloading =)
	Vec2d &operator=(Vec2d const& other);
	
// vector sum
	Vec2d &operator+=(Vec2d const& other);
	Vec2d const operator+(void); // sign
	Vec2d const operator+(Vec2d const &rvalue); // asymmetrical 
	friend Vec2d const operator+(Vec2d const &l_hand, Vec2d const &r_hand);

// vector difference
	Vec2d &operator-=(Vec2d const& other);
	Vec2d const operator-(void); // change sign
	Vec2d const operator-(Vec2d const& rvalue); // asymmetrical 
	friend Vec2d const operator-(Vec2d const& l_hand, Vec2d const& r_hand);
	
// dot product (also overloading *) and norm
	double dot(Vec2d const& rvalue);
	friend double const operator*(Vec2d const& l_hand, Vec2d const& r_hand);
	
// normalization
	double norm(void);
	double norm2(void);
	double normalize(void);
	
// multiplication by a scalar
	friend Vec2d const operator*(double const &l_hand, Vec2d const& r_hand);
	friend Vec2d const operator*(Vec2d const& l_hand, double const &r_hand);
	Vec2d const operator*=(double const &scalar);
	
// division by a scalar
	friend Vec2d const operator/(Vec2d const& l_hand, double const &r_hand);
	Vec2d const operator/=(double const &scalar);

// equality & inequality
	bool const operator==(Vec2d const& rvalue); // asymmetrical 
	friend bool const operator==(Vec2d const& l_hand, Vec2d const& r_hand);
	bool const operator!=(Vec2d const& rvalue); // asymmetrical 
	friend bool const operator!=(Vec2d const& l_hand, Vec2d const& r_hand);

// cross product
	double const cross(Vec2d const& other);
	
// 2d rotations
	void rotate(double const angle);
	
// random vectors
	void rnd(void);
	void rnd(double const);
	void rnd(double const,double const);
	void rnd(Vec2d const);

	void gauss(void);
	void gauss(double const);
	void gauss(Vec2d const);

// random displacements
	void rnd_displ(void);
	void rnd_displ(double const);
	void rnd_displ(double const,double const);
	void rnd_displ(Vec2d const);

	void gauss_displ(void);
	void gauss_displ(double const);
	void gauss_displ(Vec2d const);

// periodic boundaries 
	void in_box(void);
	void in_box(double const);
	void in_box(double const,double const);
	void in_box(Vec2d const);

};

//////////////////////////////////////////////////////////
// prototypes
double const norm(Vec2d const& v);
double const norm2(Vec2d const& v);

#endif /*VEC2d_H_*/
