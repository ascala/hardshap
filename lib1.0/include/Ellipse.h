#ifndef ELLIPSE_H_
#define ELLIPSE_H_

#include <iostream>
#include <cmath>

#include <vector2d.h>
//#include <overlap_se2d.h>

class Ellipse {
public:
	Vec2d  r;  /* CofM coordinates */
	Vec2d  a;  /* lengths of the axis */
	Vec2d  u[2]; /* u[i] is the direction (versor) of the i-th axis */ 

	double rmin,rmax;
	Vec2d  a2;  /* lengths squared of the axis */

	Ellipse(){u[0].x=u[1].y=1; rmin=a.x=1; rmax=a.y=3; a2.x=a.x*a.x; a2.y=a.y*a.y;}
	Ellipse(Vec2d const &R): r(R) {rmin=a.x=1; rmax=a.y=3; a2.x=a.x*a.x; a2.y=a.y*a.y;}
	Ellipse(Vec2d const &R, Vec2d const &A): r(R), a(A) {
		u[0].x=u[1].y=1; 
		if(a.x<a.y) {rmin=a.x; rmax=a.y;}
		else {rmin=a.y; rmax=a.x;} 
		a2.x=a.x*a.x; a2.y=a.y*a.y;
		}

//	stream operators
	friend std::ostream& operator<<(std::ostream& pStr, const Ellipse& pE);
	friend std::istream& operator>>(std::istream pStr, Ellipse& pE);

	void in_box(Vec2d const& L);
	
	// prototypes
	double perimeter();
	double area();
	
	void rotate(double const angle);
	
	Vec2d const on_surf_omotopy(Vec2d const &v);
	Vec2d const on_surf(double const angle);
	Vec2d const Don_surf(double const angle);
	
	double const dir2angle(Vec2d const& r);
	double const angle2angle(double const angle);
	
	double const fsurf(Vec2d const& point);
	double const fsurf(Vec2d const& point, Vec2d const& L);
	
	Vec2d const grad(Vec2d const& point);
	Vec2d const grad(double const angle);
	
	Vec2d const Dgrad(double const angle);
	
	double minimize_fsurf(double const start_angle, Ellipse& other_ellipse);
	double overlap(double &start_angle, Ellipse& other_ellipse);

}; // end class Ellipse

// Generic functions

//bool overlap(Ellipse &seI, Ellipse &seJ);
//bool overlap(Ellipse &seI, Ellipse &seJ, Vec2d const& L);



class EllipseMD : public Ellipse {
public:
	double mass;
	Vec2d v; // center of mass velocity
	double I; // inertia tensor
	double omega; // angular velocity
};



#endif //ELLIPSE_H_ 
