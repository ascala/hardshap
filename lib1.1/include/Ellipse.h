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

	Vec2d  a2;  /* lengths squared of the axis */

	Ellipse(){u[0][0]=u[1][1]=1; a[0]=1; a[1]=3; a2[0]=a[0]*a[0]; a2[1]=a[1]*a[1];}
	Ellipse(Vec2d const &R): r(R) {a[0]=1; a[1]=3; a2[0]=a[0]*a[0]; a2[1]=a[1]*a[1];}
	Ellipse(Vec2d const &R, Vec2d const &A): r(R), a(A) {
		u[0][0]=u[1][1]=1; 
		a2[0]=a[0]*a[0]; a2[1]=a[1]*a[1];
		}

//	stream operators
	friend std::ostream& operator<<(std::ostream& pStr, const Ellipse& p)
	{ return (pStr << p.r << ' ' << p.a << ' ' << p.u[0] << ' ' <<p.u[1]); }
	friend std::istream& operator>>(std::istream& pStr, Ellipse& p)
	{ pStr >> p.r >> p.a >> p.u[0] >> p.u[1]; p.a2=p.a*p.a; return pStr;}

	void in_box(Vec2d const& L){ r.in_box(L);}
	
	// prototypes
	double rmax(){if(a[0]>=a[1]) return a[0]; else return a[1];}
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
