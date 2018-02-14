#ifndef SELLIPSE_H_
#define SELLIPSE_H_

#include <iostream>
#include <cmath>

#include <vector2d.h>

//#include <Ellipse.h>

//lass SEllipse: public Ellipse {
class SEllipse {
public:
	Vec2d  r;  /* CofM coordinates */
	Vec2d  a;  /* lengths of the axis */
	Vec2d  u[2]; /* u[i] is the direction (versor) of the i-th axis */ 

	Vec2d  a2;  /* lengths squared of the axis */

	Vec2d  e;  /* exponents of the SE */


	SEllipse(){
		u[0][0]=u[1][1]=1; 
		a[0]=1; a[1]=2;  
		a2[0]=a[0]*a[0]; a2[1]=a[1]*a[1];
		e[0]=4; e[1]=2;
		}

	SEllipse(Vec2d const &R): r(R) {
		u[0][0]=u[1][1]=1; 
		a[0]=1; a[1]=2;  
		a2[0]=a[0]*a[0]; a2[1]=a[1]*a[1];
		e[0]=4; e[1]=2;
		}

	SEllipse(Vec2d const &R, Vec2d const &A): r(R), a(A) { 
		u[0][0]=u[1][1]=1;   
		a2[0]=a[0]*a[0]; a2[1]=a[1]*a[1];
		e[0]=4; e[1]=2;
	}

	SEllipse(Vec2d const &R, Vec2d const &A, Vec2d const &E): r(R), a(A), e(E) {
		u[0][0]=u[1][1]=1; 
		a2[0]=a[0]*a[0]; a2[1]=a[1]*a[1];
		}
	
//	stream operators
	friend std::ostream& operator<<(std::ostream& pStr, const SEllipse& p)
	{ return (pStr << p.r << ' ' << p.a << ' ' << p.u[0] << ' ' <<p.u[1] << ' ' <<p.e); }
	friend std::istream& operator>>(std::istream& pStr, SEllipse& p)
	{ pStr >> p.r >> p.a >> p.u[0] >> p.u[1] >> p.e; p.a2=p.a*p.a; return pStr;}

	
	// prototypes
	double rmax(){return a.norm();}
	double perimeter();
	double area();

	void rotate(double const angle);
	void in_box(Vec2d const& L){ r.in_box(L);}
	
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
