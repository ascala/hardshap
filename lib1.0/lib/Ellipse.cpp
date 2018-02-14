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


#include <Ellipse.h>

//	stream operators
std::ostream& operator<<(std::ostream& pStr, const Ellipse& pE)
{ return (pStr << pE.r << ';' << pE.a << ';' << pE.u[0] << ';' <<pE.u[1]); }

//
void Ellipse::in_box(Vec2d const& L){ r.in_box(L);}

double Ellipse::perimeter(){return M_PI*(1.5*(a.x+a.y)-sqrt(a.x*a.y));}

double Ellipse::area(){return M_PI*a.x*a.y;}

void Ellipse::rotate(double const angle)
{ //{u[0].rotate(angle); u[1].rotate(angle);}
    double sa=sin(angle), ca=cos(angle);
    u[0]=Vec2d(ca*u[0].x + sa*u[0].y, -sa*u[0].x + ca*u[0].y);
    u[1]=Vec2d(ca*u[1].x + sa*u[1].y, -sa*u[1].x + ca*u[1].y);
}

Vec2d const Ellipse::on_surf_omotopy(Vec2d const &dir)
{
    double angle=atan2(u[1].dot(dir),u[0].dot(dir));
    return Vec2d( cos(angle)*a.x*u[0] + sin(angle)*a.y*u[1] + r);
}

Vec2d const Ellipse::on_surf(double const angle)
{
    return Vec2d( cos(angle)*a.x*u[0] + sin(angle)*a.y*u[1] + r);
}

Vec2d const Ellipse::Don_surf(double const angle){
    return Vec2d( -sin(angle)*a.x*u[0] + cos(angle)*a.y* u[1] );
}

double const Ellipse::dir2angle(Vec2d const& dir)
{
    double angle=atan2(u[1].dot(dir),u[0].dot(dir));
    return atan2( a.x*sin(angle) , a.y*cos(angle) );
}

double const Ellipse::angle2angle(double const angle)
{
    return atan2( a.x*sin(angle) , a.y*cos(angle) );
}

double const Ellipse::fsurf(Vec2d const& P)
{
    Vec2d dr=P-r, v(dr.dot(u[0])/a.x,dr.dot(u[1])/a.y);
    return v.dot(v)-1;
}

double const Ellipse::fsurf(Vec2d const& P, Vec2d const& L)
{
    Vec2d dr=P-r; dr.in_box(L); 
    Vec2d v(dr.dot(u[0])/a.x,dr.dot(u[1])/a.y);
    return v.dot(v)-1;
}

/*
double const Ellipse::fsurf(double const angle)
{
    Vec2d v(cos(angle)*u[0]+sin(angle)*u[1]);
    return v*v-1;
}
*/

Vec2d const Ellipse::grad(Vec2d const& P)
{
    Vec2d dr=P-r;
    return Vec2d( 2*u[0].dot(dr)*u[0]/a2.x + 2*u[1].dot(dr)*u[1]/a2.y );
}

Vec2d const Ellipse::grad(double const angle)
{
    return Vec2d( 2*cos(angle)*u[0]/a.x + 2*sin(angle)*u[1]/a.y );
}

Vec2d const Ellipse::Dgrad(double const angle)
{
    return Vec2d( -2*sin(angle)*u[0]/a.x + 2*cos(angle)*u[1]/a.y );
}


double Ellipse::minimize_fsurf(double const angle, Ellipse& e1)
{
    static double tol=1.0e-4;
    double dangle=M_PI/10;
	
	// start from three points a<b<c
    double a=angle-dangle,b=angle,c=angle+dangle;
    Vec2d P;
    P=on_surf(b); double fb=e1.fsurf(P);
    P=on_surf(a); double fa=e1.fsurf(P);
    P=on_surf(c); double fc=e1.fsurf(P);
 
 	
 	if((fa<fb)&&(fc<fb)){ // I am bracketing a maximum!!
		c=b; fc=fb;
 		b=a; fb=fa;
		a-=dangle; P=on_surf(a); fa=e1.fsurf(P);
 	}

    // for convex shapes & potentials, if fa>fb<fc then [a,c] brackets a minimum 
 	while(!((fa>fb)&&(fc>fb))) {   
    	if((fa>fb)&&(fb>fc)) { // potential decreases from a to c
        	do { // therefore walk toward c 
            	a=b; fa=fb;
            	b=c; fb=fc;
            	c+=dangle; P=on_surf(c); fc=e1.fsurf(P);
        	} while(fb>fc);
    	}
    	else if((fa<fb)&&(fb<fc)) { // potential increases from a to c
        	do { // therefore walk toward a 
            	c=b; fc=fb;
            	b=a; fb=fa;
            	a-=dangle; P=on_surf(a); fa=e1.fsurf(P);
        	} while(fa<fc);
    	}
 	dangle/=2; // refine search
 	} // now I am bracketing a minimum
	
    double y,fy;
    while((c-b)>tol) {
        y=b+(c-b)/2.618; P=on_surf(y); fy=e1.fsurf(P);
        if(fy>fb) { c=y; fc=fy; }
        else { a=b; fa=fb;   b=y; fb=fy; }
    }
	
    return b;
}

double Ellipse::overlap(double &angle, Ellipse& e1)
{
    static double tol=1.0e-4;
    double dangle=M_PI/10;
	
	// start from three points a<b<c
    double a=angle-dangle,b=angle,c=angle+dangle;
    Vec2d P;
    P=on_surf(b); double fb=e1.fsurf(P);
    if(fb<0) {angle=b; return fb;}
    P=on_surf(a); double fa=e1.fsurf(P);
    if(fa<0) {angle=a; return fa;}
    P=on_surf(c); double fc=e1.fsurf(P);
    if(fc<0) {angle=c; return fc;}
 
 	
 	if((fa<fb)&&(fc<fb)){ // I am bracketing a maximum!!
		c=b; fc=fb;
 		b=a; fb=fa;
		a-=dangle; P=on_surf(a); fa=e1.fsurf(P);
     	if(fa<0) {angle=a; return fa;}
 	}

    // for convex shapes & potentials, if fa>fb<fc then [a,c] brackets a minimum 
 	while(!((fa>fb)&&(fc>fb))) {   
    	if((fa>fb)&&(fb>fc)) { // potential decreases from a to c
        	do { // therefore walk toward c 
            	a=b; fa=fb;
            	b=c; fb=fc;
            	c+=dangle; P=on_surf(c); fc=e1.fsurf(P);
     			if(fc<0) {angle=c; return fc;}
        	} while(fb>fc);
    	}
    	else if((fa<fb)&&(fb<fc)) { // potential increases from a to c
        	do { // therefore walk toward a 
            	c=b; fc=fb;
            	b=a; fb=fa;
            	a-=dangle; P=on_surf(a); fa=e1.fsurf(P);
    			if(fa<0) {angle=a; return fa;}
        	} while(fa<fc);
    	}
 	dangle/=2; // refine search
 	} // now I am bracketing a minimum
	
    double y,fy;
    while((c-b)>tol) {
        y=b+(c-b)/2.618; P=on_surf(y); fy=e1.fsurf(P);
     	if(fy<0) {angle=y; return fy;}
        if(fy>fb) { c=y; fc=fy; }
        else { a=b; fa=fb;   b=y; fb=fy; }
    }
	
    angle=b; return fb;
}



