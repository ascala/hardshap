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


#include <SEllipse.h>

double SEllipse::perimeter(){
	std::cout<<"perimeter of SEllipse not yet implemented\n";
	exit(1);
}

double SEllipse::area(){
	if(e[0]!=e[1]){ 
		std::cerr<<"SuperEllipse: e[0] != e[1] not yet implemented!!!\n"<<std::flush;
		exit(1);
		}
	return pow(4.,1.-1./e[0])*a[0]*a[1]*sqrt(M_PI)*tgamma(1.+1./e[0])/tgamma(0.5+1./e[0]);
}

void SEllipse::rotate(double const angle)
{ //{u[0].rotate(angle); u[1].rotate(angle);}
    double sa=sin(angle), ca=cos(angle);
    u[0]=Vec2d(ca*u[0][0] + sa*u[0][1], -sa*u[0][0] + ca*u[0][1]);
    u[1]=Vec2d(ca*u[1][0] + sa*u[1][1], -sa*u[1][0] + ca*u[1][1]);
}

Vec2d const SEllipse::on_surf_omotopy(Vec2d const v){
	double angle=atan2(u[1].dot(v),u[0].dot(v));
	double sx,sy,x=cos(angle),y=sin(angle); 
	if(x>0) sx=1; else sx=-1; x=fabs(x);
	if(y>0) sy=1; else sy=-1; y=fabs(y);
	return Vec2d(sx*pow(x,2./e[0])*a[0]*u[0] + sy*pow(y,2./e[1])*a[1]*u[1] + r);
}

Vec2d const SEllipse::on_surf(const double angle){
	double sx,sy,x=cos(angle),y=sin(angle); 
	if(x>0) sx=1; else sx=-1; if(y>0) sy=1; else sy=-1; 
	return Vec2d( sx*pow(fabs(x),2./e[0])*a[0]*u[0] + 
				  sy*pow(fabs(y),2./e[1])*a[1]*u[1] + r);
}

Vec2d const SEllipse::Don_surf(double const angle){
	double sx,sy,cosa=cos(angle),sina=sin(angle); 
	if(cosa>0) sx=1; else sx=-1; if(sina>0) sy=1; else sy=-1;
	cosa=fabs(cosa); sina=fabs(sina); 
	double ex=2./e[0], ey=2./e[1];
	return Vec2d(-sy*ex*sina*pow(cosa,ex-1)*a[0]*u[0] + sx*ey*cosa*pow(sina,ey-1)*a[1]*u[1]);
}

double const SEllipse::dir2angle(Vec2d const& r){

	if(e[0]!=e[1]){ 
		std::cerr<<"SuperEllipse: e[0] != e[1] not yet implemented!!!\n"<<std::flush;
		exit(1);
		}
    
	double theta=atan2(u[1].dot(r),u[0].dot(r));
	double x(cos(theta)), y(sin(theta));
	double sx; if(x>0) sx=1; else sx=-1;
	double sy; if(y>0) sy=1; else sy=-1;
	x=sx*pow(fabs(x/a[0]),e[0]/2.);
	y=sy*pow(fabs(y/a[1]),e[1]/2.);
	return atan2(y,x);

}

double const SEllipse::angle2angle(const double theta){
	return atan2( a[0]*sin(theta) , a[1]*cos(theta) );
}

double const SEllipse::fsurf(Vec2d const& P){
	Vec2d dr=P-r, v( u[0].dot(dr)/a[0] , u[1].dot(dr)/a[1] ); 
	return pow(fabs(v[0]),e[0])+pow(fabs(v[1]),e[1])-1;
}

double const SEllipse::fsurf(Vec2d const& P, Vec2d const& L){
	Vec2d dr=P-r; dr.in_box(L);
	Vec2d v( u[0].dot(dr)/a[0] , u[1].dot(dr)/a[1] ); 
	return pow(fabs(v[0]),e[0])+pow(fabs(v[1]),e[1])-1;
}

/*
double const SEllipse::fsurf(double const angle){
	Vec2d v( cos(angle)/a[0] , sin(angle)/a[1] ); 
	return pow(fabs(v[0]),e[0])+pow(fabs(v[1]),e[1])-1;
}
*/

Vec2d const SEllipse::grad(Vec2d const& P)
{
	Vec2d dr=P-r, v( u[0].dot(dr)/a[0] , u[1].dot(dr)/a[1] ), sgnv( (v[0]<0)?-1:1, (v[1]<0)?-1:1 ); 
    return Vec2d( sgnv[0]*e[0]*pow(fabs(v[0]),e[0]-1)*u[0] +  sgnv[1]*e[1]*pow(fabs(v[1]),e[1]-1)*u[1]);
}

Vec2d const SEllipse::grad(double const angle)
{
	Vec2d v( cos(angle)/a[0] , sin(angle)/a[1] ), sgnv( (v[0]<0)?-1:1, (v[1]<0)?-1:1 ); 
    return Vec2d( sgnv[0]*e[0]*pow(fabs(v[0]),e[0]-1)*u[0] +  sgnv[1]*e[1]*pow(fabs(v[1]),e[1]-1)*u[1]);
}

Vec2d const SEllipse::Dgrad(double const angle)
{
	Vec2d v( -sin(angle)/a[0] , cos(angle)/a[1] ), sgnv( (v[0]<0)?-1:1, (v[1]<0)?-1:1 ); 
    return Vec2d( sgnv[0]*e[0]*pow(fabs(v[0]),e[0]-1)*u[0] +  sgnv[1]*e[1]*pow(fabs(v[1]),e[1]-1)*u[1]);
}


double SEllipse::minimize_fsurf(double const angle, SEllipse& se1)
{
    static double tol=1.0e-6;
    double dangle=M_PI/10;
	
	// start from three points a<b<c
    double a=angle-dangle,b=angle,c=angle+dangle;
    Vec2d P;
    P=on_surf(b); double fb=se1.fsurf(P);
    P=on_surf(a); double fa=se1.fsurf(P);
    P=on_surf(c); double fc=se1.fsurf(P);
 
 	
 	if((fa<fb)&&(fc<fb)){ // I am bracketing a maximum!!
		c=b; fc=fb;
 		b=a; fb=fa;
		a-=dangle; P=on_surf(a); fa=se1.fsurf(P);
 	}

    // for convex shapes & potentials, if fa>fb<fc then [a,c] brackets a minimum 
 	while(!((fa>fb)&&(fc>fb))) {   
    	if((fa>fb)&&(fb>fc)) { // potential decreases from a to c
        	do { // therefore walk toward c 
            	a=b; fa=fb;
            	b=c; fb=fc;
            	c+=dangle; P=on_surf(c); fc=se1.fsurf(P);
        	} while(fb>fc);
    	}
    	else if((fa<fb)&&(fb<fc)) { // potential increases from a to c
        	do { // therefore walk toward a 
            	c=b; fc=fb;
            	b=a; fb=fa;
            	a-=dangle; P=on_surf(a); fa=se1.fsurf(P);
        	} while(fa<fc);
    	}
 	dangle/=2; // refine search
 	} // now I am bracketing a minimum
	
    double y,fy;
    while((c-b)>tol) {
        y=b+(c-b)/2.618; P=on_surf(y); fy=se1.fsurf(P);
        if(fy>fb) { c=y; fc=fy; }
        else { a=b; fa=fb;   b=y; fb=fy; }
    }
	
    return b;
}

double SEllipse::overlap(double &angle, SEllipse& se1)
{
    static double tol=1.0e-8;
    double dangle=M_PI/10;
	
	// start from three points a<b<c
    double a=angle-dangle,b=angle,c=angle+dangle;
    Vec2d P;
    P=on_surf(b); double fb=se1.fsurf(P);
    if(fb<0) {angle=b; return fb;}
    P=on_surf(a); double fa=se1.fsurf(P);
    if(fa<0) {angle=a; return fa;}
    P=on_surf(c); double fc=se1.fsurf(P);
    if(fc<0) {angle=c; return fc;}
 
 	
 	if((fa<fb)&&(fc<fb)){ // I am bracketing a maximum!!
		c=b; fc=fb;
 		b=a; fb=fa;
		a-=dangle; P=on_surf(a); fa=se1.fsurf(P);
     	if(fa<0) {angle=a; return fa;}
 	}

    // for convex shapes & potentials, if fa>fb<fc then [a,c] brackets a minimum 
 	while(!((fa>fb)&&(fc>fb))) {   
    	if((fa>fb)&&(fb>fc)) { // potential decreases from a to c
        	do { // therefore walk toward c 
            	a=b; fa=fb;
            	b=c; fb=fc;
            	c+=dangle; P=on_surf(c); fc=se1.fsurf(P);
     			if(fc<0) {angle=c; return fc;}
        	} while(fb>fc);
    	}
    	else if((fa<fb)&&(fb<fc)) { // potential increases from a to c
        	do { // therefore walk toward a 
            	c=b; fc=fb;
            	b=a; fb=fa;
            	a-=dangle; P=on_surf(a); fa=se1.fsurf(P);
    			if(fa<0) {angle=a; return fa;}
        	} while(fa<fc);
    	}
 	dangle/=2; // refine search
 	} // now I am bracketing a minimum
	
    double y,fy;
    while((c-b)>1.0e-3) {
        y=b+(c-b)/2.618; P=on_surf(y); fy=se1.fsurf(P);
     	if(fy<0) {angle=y; return fy;}
        if(fy>fb) { c=y; fc=fy; }
        else { a=b; fa=fb;   b=y; fb=fy; }
    }
    while((c-b)>tol) {
        y=b+(c-b)/2.618; P=on_surf(y); fy=se1.fsurf(P);
     	if(fy<0) {angle=y; return fy;}
     	if(fy>0.1) {angle=y; return fy;}
        if(fy>fb) { c=y; fc=fy; }
        else { a=b; fa=fb;   b=y; fb=fy; }
    }
	
    angle=b; return fb;
}



