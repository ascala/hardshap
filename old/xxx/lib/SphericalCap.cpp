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


#include <SphericalCap.h>

SphericalCap::SphericalCap()
: dir(0,1), halflen(2), radius(0.5), radius2(0.25) {}
	
SphericalCap::SphericalCap(const Vec2d& center, const Vec2d& half, const double rad)
: r(center), dir(half), halflen(dir.norm()), radius(rad), radius2(radius*radius) {}

SphericalCap::SphericalCap(SphericalCap const &other)
: r(other.r), dir(other.dir), halflen(other.halflen), radius(other.radius), radius2(radius*radius) {}

/*
SphericalCap::SphericalCap(Ellipse const &e){
	if(e.a[0]>e.a[1]){
		r=e.a[1]; 
		P0=e.r - (e.a[0]-r)*e.u[0];
		P1=e.r + (e.a[0]-r)*e.u[0];
	}
	else{
		r=e.a[0]; 
		P0=e.r - (e.a[1]-r)*e.u[1];
		P1=e.r + (e.a[1]-r)*e.u[1];
	}
	r2=r*r; sig=2*r; sig2=sig*sig;
}

SphericalCap::SphericalCap(SEllipse const &se){
	if(se.a[0]>se.a[1]){
		r=se.a[1]; 
		P0=se.r - se.a[0]*se.u[0];
		P1=se.r + se.a[0]*se.u[0];
	}
	else{
		r=se.a[0]; 
		P0 = se.r - se.a[1]*se.u[1];
		P1 = se.r + se.a[1]*se.u[1];
	}
	r2=r*r; sig=2*r; sig2=sig*sig;
}
*/


//

// prototypes 

double SphericalCap::perimeter()
{return 2*( M_PI*radius+4*halflen );}

double SphericalCap::area()
{return radius*(M_PI*radius + 4*halflen);}
	
void SphericalCap::rotate(double const angle)
{ 
    double sa=sin(angle), ca=cos(angle);
    dir=Vec2d(ca*dir[0] + sa*dir[1], -sa*dir[0] + ca*dir[1]);
}

	
// distance squared between two SphericalCaps: negative if caps overlap !!!inline	
double SphericalCap::dist2( SphericalCap const &SC2){double u1,u2; return this->dist2(SC2,u1,u2);}

double SphericalCap::dist2(SphericalCap const &S, double &sc, double &tc)
{
	const double eps(1.0e-6);
	
	Vec2d     PQ(r-S.r), Sdir(S.dir);
    double    a = dir.dot(dir);        // always > 0
    double    b = dir.dot(Sdir);
    double    c = Sdir.dot(S.dir);    // always > 0
    double    d = dir.dot(PQ);
    double    e = Sdir.dot(PQ);
    double    D = a*c - b*b;      // always >= 0

    // compute the line parameters of the two closest points
    if (D < eps) { // the lines are almost parallel
    	if( d<0 ) sc = -1.0;  else sc = 1.0;
        tc = (e+sc*b)/c;
   }
    else {                // get the closest points on the infinite lines
    	sc = (b*e-c*d) / D;
    	if(sc<-1.0 ) { sc = -1.0; tc = (e+sc*b)/c;} 
    	else if( sc>1.0 ) { sc = 1.0; tc = (e+sc*b)/c;}
    	else tc = (a*e-b*d) / D;
    }
 	
 	if(tc<-1.0) { 
 		tc=-1.0; sc=(tc*b-d)/a; 
 		if(sc<-1.0) sc=-1.0; else if(sc>1.0) sc=1.0;
 	}
 	else if(tc>1.0) { 
 		tc=1.0; sc=(tc*b-d)/a; 
 		if(sc<-1.0) sc=-1.0; else if(sc>1.0) sc=1.0;
 	} 
 

    // get the difference of the two closest points
    Vec2d dr = PQ + (sc * dir) - (tc * S.dir);  // = SC1(sc) - SC2(tc)
	
    return dr.dot(dr);   // return the closest distance
}
//===================================================================

double SphericalCap::dist2(Vec2d const &point)
{double u; return this->dist2(point,u);}
	
double SphericalCap::dist2(Vec2d const &point, double &u){
	Vec2d rij=point-r;
	double proj=rij.dot(dir)/halflen;
	if(proj>halflen) {rij-=dir; u=1; return rij.dot(rij);}
	if(proj<-halflen) {rij+=dir; u=-1; return rij.dot(rij);}
	u=proj/halflen; return rij.dot(rij)-proj*proj;
}
