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


#include <Segment.h>

Segment::Segment(): dir(0,1),halflen(1) {}
	
Segment::Segment(const Vec2d& center, const Vec2d& direction, const double half)
: r(center), dir(direction), halflen(half) 
{dir.normalize(); dir*=halflen;}

Segment::Segment(const Vec2d& P0, const Vec2d& P1)
:r(0.5*(P1+P0)),dir(0.5*(P1-P0)),halflen(dir.norm()){}

Segment::Segment(Segment const &other): 
r(other.r), dir(other.dir), halflen(other.halflen) {}

//	stream operators
std::ostream& operator<<(std::ostream& pStr, const Segment& pS)
{ return (pStr << pS.r - pS.dir << ';' << pS.r + pS.dir); }

//
	
// distance squared between two Segments: negative if caps overlap !!!inline	

double Segment::dist2( Segment const &S){double u1,u2; return this->dist2(S,u1,u2);}

double Segment::dist2(Segment const &S, double &sc, double &tc)
{
	const double eps(1.0e-6);
	
	Vec2d     PQ(r-S.r);
    double    a = dir*dir;        // always > 0
    double    b = dir*S.dir;
    double    c = S.dir*S.dir;    // always > 0
    double    d = dir*PQ;
    double    e = S.dir*PQ;
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

    return dr*dr;   // return the closest distance
}
//===================================================================



