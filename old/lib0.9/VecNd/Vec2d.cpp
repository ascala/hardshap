/*

    Copyright 2007, Antonio Scala

    This file is part of HardShap, "Simulation of Hard Shaped Particles".

    HardShaP is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HardShaP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HardShaP.  If not, see <http://www.gnu.org/licenses/>.

*/


#include <Vec2d.h>

Vec2d::Vec2d() :x(0),y(0) {}

Vec2d::Vec2d(double const v) :x(v),y(v) {}

Vec2d::Vec2d(double const vx, double const vy) :x(vx),y(vy) {}

Vec2d::Vec2d(Vec2d const & other) : x(other.x) , y(other.y) {}

Vec2d::~Vec2d() {}

//	stream operators
std::ostream& operator<<(std::ostream& pStr, Vec2d const& pV)
{ return (pStr << '(' << pV.x << ',' << pV.y << ')'); }
std::istream& operator>>(std::istream pStr, Vec2d& pV)
{ return (pStr >> pV.x >> pV.y ); }


// assignment (overloading =)
Vec2d &Vec2d::operator=(Vec2d const& other)
{
	if (this != &other)
	{   x = other.x;
		y = other.y;
	}
	return *this;
}

// vector sum
Vec2d &Vec2d::operator+=(Vec2d const& other)
{ x+=other.x; y+=other.y; return *this;}
Vec2d const Vec2d::operator+(void){return Vec2d(x,y);}
Vec2d const Vec2d::operator+(Vec2d const& rvalue)
{ return Vec2d(x+rvalue.x,y+rvalue.y); }
Vec2d const operator+(Vec2d const &l_hand, Vec2d const &r_hand)// friend +
{ return Vec2d(l_hand) += r_hand;}

// vector difference
Vec2d &Vec2d::operator-=(Vec2d const& other)
{ x-=other.x; y-=other.y; return *this;}
Vec2d const Vec2d::operator-(void){return Vec2d(-x,-y);}
Vec2d const Vec2d::operator-(Vec2d const& rvalue)
{ return Vec2d(x-rvalue.x,y-rvalue.y); }
Vec2d const operator-(Vec2d const& l_hand, Vec2d const& r_hand)// friend -
{ return Vec2d(l_hand) -= r_hand;}

// dot product (also overloading *) and norm
double Vec2d::dot(Vec2d const& rvalue)
{ return x*rvalue.x+y*rvalue.y; }
double const operator*(Vec2d const& l_hand, Vec2d const& r_hand) // friend *
{ return l_hand.x*r_hand.x+l_hand.y*r_hand.y;} 

// normalization
double Vec2d::norm(void)
{ return sqrt(x*x+y*y); }
double Vec2d::norm2(void)
{ return x*x+y*y; }
double Vec2d::normalize(void) 
{ double n=sqrt(x*x+y*y); x/=n; y/=n; return n;}

// multiplication by a scalar
Vec2d const operator*(double const &l_hand, Vec2d const& r_hand) // friend *
{ return Vec2d(l_hand*r_hand.x,l_hand*r_hand.y);} 
Vec2d const operator*(Vec2d const& l_hand, double const &r_hand) // friend *
{ return Vec2d(l_hand.x*r_hand,l_hand.y*r_hand);} 
Vec2d const Vec2d::operator*=(double const &scalar) 
{ x*=scalar; y*=scalar; return *this; } 

// division by a scalar
Vec2d const operator/(Vec2d const& l_hand, double const &r_hand) // friend /
{ return Vec2d(l_hand.x/r_hand,l_hand.y/r_hand);} 
Vec2d const Vec2d::operator/=(double const &scalar) 
{ x/=scalar; y/=scalar; return *this; } 

// equality & inequality
bool const Vec2d::operator==(Vec2d const &rvalue)
{ return ((x==rvalue.x)&&(y==rvalue.y)); }
bool const operator==(Vec2d const& l_hand, Vec2d const& r_hand)
{ return Vec2d(l_hand)==r_hand; }
bool const Vec2d::operator!=(Vec2d const &rvalue)
{ return ((x!=rvalue.x)||(y!=rvalue.y)); }
bool const operator!=(Vec2d const& l_hand, Vec2d const& r_hand)
{ return Vec2d(l_hand)!=r_hand; }

// cross product
double const Vec2d::cross(Vec2d const& other)
{return x*other.y-y*other.x; }

// 2d rotations
	void Vec2d::rotate(double const angle){
        double sa=sin(angle), ca=cos(angle);
        double xr(ca*x + sa*y), yr(-sa*x + ca*y);
        x=xr; y=yr;
}

// random vectors
	void Vec2d::rnd(void){x=drand48();y=drand48();}
	void Vec2d::rnd(double const s){x=s*(2*drand48()-1);y=s*(2*drand48()-1);}
	void Vec2d::rnd(double const sx, double const sy)
	{x=sx*(2*drand48()-1);y=sy*(2*drand48()-1);}
	void Vec2d::rnd(Vec2d const s)
	{x=s.x*(2*drand48()-1);y=s.y*(2*drand48()-1);}
	
	void Vec2d::gauss(void){x=gaussdev();y=gaussdev();}
	void Vec2d::gauss(double const W){x=W*gaussdev();y=W*gaussdev();}
	void Vec2d::gauss(Vec2d const W){x=W.x*gaussdev();y=W.y*gaussdev();}
		
// random displacements
	void Vec2d::rnd_displ(void){x+=drand48();y+=drand48();}
	void Vec2d::rnd_displ(double const s){x+=s*(2*drand48()-1);y+=s*(2*drand48()-1);}
	void Vec2d::rnd_displ(double const sx, double const sy)
	{x+=sx*(2*drand48()-1);y+=sy*(2*drand48()-1);}
	void Vec2d::rnd_displ(Vec2d const s)
	{x+=s.x*(2*drand48()-1);y+=s.y*(2*drand48()-1);}
	
	void Vec2d::gauss_displ(void){x+=gaussdev();y+=gaussdev();}
	void Vec2d::gauss_displ(double const W){x+=W*gaussdev();y+=W*gaussdev();}
	void Vec2d::gauss_displ(Vec2d const W){x+=W.x*gaussdev();y+=W.y*gaussdev();}

// periodic boundaries
	void Vec2d::in_box(void){x-=rint(x);y-=rint(y);}
	void Vec2d::in_box(double const L){x-=L*rint(x/L);y-=L*rint(y/L);}
	void Vec2d::in_box(double const Lx, double const Ly)
	{x-=Lx*rint(x/Lx);y-=Ly*rint(y/Ly);}
	void Vec2d::in_box(Vec2d const L)
	{x-=L.x*rint(x/L.x);y-=L.y*rint(y/L.y);}

//////////////////////////////////////////////////////////
// prototypes
double const norm(Vec2d const& v)
{return sqrt(v.x*v.x+v.y*v.y);}
double const norm2(Vec2d const& v)
{return v.x*v.x+v.y*v.y;}

