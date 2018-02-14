#ifndef SELLIPSE_H_
#define SELLIPSE_H_

#include <iostream>
#include <cmath>

#include <Vec2d.h>

//#include <Ellipse.h>

//lass SEllipse: public Ellipse {
class SEllipse {
public:
	Vec2d  r;  /* CofM coordinates */
	Vec2d  a;  /* lengths of the axis */
	Vec2d  u[2]; /* u[i] is the direction (versor) of the i-th axis */ 

	double rmin,rmax;
	Vec2d  a2;  /* lengths squared of the axis */

	Vec2d  e;  /* exponents of the SE */


	SEllipse(){
		u[0].x=u[1].y=1; 
		rmin=a.x=1; rmax=a.y=2;  
		a2.x=a.x*a.x; a2.y=a.y*a.y;
		e.x=4; e.y=2;
		}

	SEllipse(Vec2d const &R): r(R) {
		u[0].x=u[1].y=1; 
		rmin=a.x=1; rmax=a.y=2;  
		a2.x=a.x*a.x; a2.y=a.y*a.y;
		e.x=4; e.y=2;
		}

	SEllipse(Vec2d const &R, Vec2d const &A): r(R), a(A) { 
		u[0].x=u[1].y=1; 
		if(a.x<a.y) {rmin=a.x; rmax=a.y;} else {rmin=a.y; rmax=a.x;}  
		a2.x=a.x*a.x; a2.y=a.y*a.y;
		e.x=4; e.y=2;
	}

	SEllipse(Vec2d const &R, Vec2d const &A, Vec2d const &E): r(R), a(A), e(E) {
		u[0].x=u[1].y=1; 
		if(a.x<a.y) {rmin=a.x; rmax=a.y;}
		else {rmin=a.y; rmax=a.x;} 
		a2.x=a.x*a.x; a2.y=a.y*a.y;
		}
	
//	stream operators
	friend std::ostream& operator<<(std::ostream& pStr, const SEllipse& pE);
	friend std::istream& operator>>(std::istream pStr, SEllipse& pE);
	
	void in_box(Vec2d const& L);
	
	// prototypes
	double perimeter();
	double area();

	void rotate(double const angle);
	
	Vec2d const on_surf_omotopy(Vec2d const r);	
	Vec2d const on_surf(const double angle);
	Vec2d const Don_surf(double const angle);
	
	double const dir2angle(Vec2d const& r);
	double const angle2angle(const double theta);
	
	double const fsurf(Vec2d const& point);
	double const fsurf(Vec2d const& point, Vec2d const& L);
	
	Vec2d const grad(Vec2d const& point);
	Vec2d const grad(double const angle);
	
	Vec2d const Dgrad(double const angle);
	
	
/*
	Vec2d const Dfsurf(Vec2d const& point);
	Vec2d const Dfsurf(double const& angle);
*/

	double minimize_fsurf(double start_angle, SEllipse &other_sellipse);
	double overlap(double &start_angle, SEllipse &other_sellipse);

}; // end class SEllipse

// Generic functions

//bool overlap(SEllipse &seI, SEllipse &seJ);
//bool overlap(SEllipse &seI, SEllipse &seJ, Vec2d const& L);


class SEllipseMD : public SEllipse {
public:
	double mass;
	Vec2d v; // center of mass velocity
	double I; // inertia tensor
	double omega; // angular velocity
};

#endif //SELLIPSE_H_ 
