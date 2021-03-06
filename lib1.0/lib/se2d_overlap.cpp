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


#include <se2d_overlap.h>

// Circle

bool overlap(Circle &partI, Circle &partJ){
	Vec2d rIJ(partJ.r-partI.r); 
	double sigma=partI.rmax+partJ.rmax;
	return ( rIJ.norm2()<=sigma*sigma ) ;
}

bool overlap(Circle &partI, Circle &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	double sigma=partI.rmax+partJ.rmax;
	return ( rIJ.norm2()<=sigma*sigma );
}

// Rectangle
bool overlap(Rectangle &partI, Rectangle &partJ){
	return ( OBBoverlap(partI,partJ) ) ;
}

bool overlap(Rectangle &partI, Rectangle &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	Vec2d rJold(partJ.r); partJ.r=partI.r+rIJ;
	bool ovlp( OBBoverlap(partI,partJ) ) ;
	partJ.r=rJold; return ovlp;
}

// Spherical Cap
bool overlap(SphericalCap &partI, SphericalCap &partJ) { 
	double sigma=partI.rmax+partJ.rmax;
	return ( partI.dist2(partJ)<=sigma*sigma ); 
}

bool overlap(SphericalCap &partI, SphericalCap &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	Vec2d rJold(partJ.r); partJ.r=partI.r+rIJ;
	double sigma=partI.rmax+partJ.rmax;
	bool ovlp = ( partI.dist2(partJ)<sigma*sigma ) ;
	partJ.r=rJold; return ovlp;
}

// Ellipse
bool overlap(Ellipse &partI, Ellipse &partJ){
	Vec2d rIJ(partJ.r-partI.r);
	double angle= partI.dir2angle(rIJ);
	return ( partI.overlap(angle,partJ)<0 );
}

bool overlap(Ellipse &partI, Ellipse &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	Vec2d rJold(partJ.r); partJ.r=partI.r+rIJ;
	double angle= partI.dir2angle(rIJ);
	bool ovlp = ( partI.overlap(angle,partJ)<0 ) ;
	partJ.r=rJold; return ovlp;
}

// SEllipse
bool overlap(SEllipse &partI, SEllipse &partJ){
	Vec2d rIJ(partJ.r-partI.r);
	double angle= partI.dir2angle(rIJ);
	return ( partI.overlap(angle,partJ)<0 );
}

bool overlap(SEllipse &partI, SEllipse &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	Vec2d rJold(partJ.r); partJ.r=partI.r+rIJ;
	double angle= partI.dir2angle(rIJ);
	bool ovlp = ( partI.overlap(angle,partJ)<0 ) ;
	partJ.r=rJold; return ovlp;
}


// ************* M I X E D ************* 

// Circle-Ellipse
double overlap(double &angle, Ellipse &partI, Circle &partJ){
    static double tol=1.0e-4;
    double dangle=M_PI/10;
	
	// start from three points a<b<c
    double a=angle-dangle,b=angle,c=angle+dangle;
    Vec2d P;
    P=partJ.on_surf(b); double fb=partI.fsurf(P);
    if(fb<0) {angle=b; return fb;}
    P=partJ.on_surf(a); double fa=partI.fsurf(P);
    if(fa<0) {angle=a; return fa;}
    P=partJ.on_surf(c); double fc=partI.fsurf(P);
    if(fc<0) {angle=c; return fc;}
 
 	
 	if((fa<fb)&&(fc<fb)){ // I am bracketing a maximum!!
		c=b; fc=fb;
 		b=a; fb=fa;
		a-=dangle; P=partJ.on_surf(a); fa=partI.fsurf(P);
     	if(fa<0) {angle=a; return fa;}
 	}

    // for convex shapes & potentials, if fa>fb<fc then [a,c] brackets a minimum 
 	while(!((fa>fb)&&(fc>fb))) {   
    	if((fa>fb)&&(fb>fc)) { // potential decreases from a to c
        	do { // therefore walk toward c 
            	a=b; fa=fb;
            	b=c; fb=fc;
            	c+=dangle; P=partJ.on_surf(c); fc=partI.fsurf(P);
     			if(fc<0) {angle=c; return fc;}
        	} while(fb>fc);
    	}
    	else if((fa<fb)&&(fb<fc)) { // potential increases from a to c
        	do { // therefore walk toward a 
            	c=b; fc=fb;
            	b=a; fb=fa;
            	a-=dangle; P=partJ.on_surf(a); fa=partI.fsurf(P);
    			if(fa<0) {angle=a; return fa;}
        	} while(fa<fc);
    	}
 	dangle/=2; // refine search
 	} // now I am bracketing a minimum
	
    double y,fy;
    while((c-b)>tol) {
        y=b+(c-b)/2.618; P=partJ.on_surf(y); fy=partI.fsurf(P);
     	if(fy<0) {angle=y; return fy;}
        if(fy>fb) { c=y; fc=fy; }
        else { a=b; fa=fb;   b=y; fb=fy; }
    }
	
    angle=b; return fb;
}
bool overlap(Ellipse &partI, Circle &partJ){
	double angle=partI.dir2angle(partJ.r-partI.r);
	return (overlap(angle,partI,partJ)<0);
}
bool overlap(Circle &partI, Ellipse &partJ){return overlap(partJ,partI);}
bool overlap(Ellipse &partI, Circle &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	Vec2d rJold(partJ.r); partJ.r=partI.r+rIJ;
	double angle= partI.dir2angle(rIJ);
	bool ovlp = (overlap(angle,partI,partJ)<0);
	partJ.r=rJold; return ovlp;
}
bool overlap(Circle &partI, Ellipse &partJ, Vec2d const& L)
{return overlap(partJ,partI, L);}

// Circle-SuperEllipse
double overlap(double &angle, SEllipse &partI, Circle &partJ){
    static double tol=1.0e-4;
    double dangle=M_PI/10;
	
	// start from three points a<b<c
    double a=angle-dangle,b=angle,c=angle+dangle;
    Vec2d P;
    P=partJ.on_surf(b); double fb=partI.fsurf(P);
    if(fb<0) {angle=b; return fb;}
    P=partJ.on_surf(a); double fa=partI.fsurf(P);
    if(fa<0) {angle=a; return fa;}
    P=partJ.on_surf(c); double fc=partI.fsurf(P);
    if(fc<0) {angle=c; return fc;}
 
 	
 	if((fa<fb)&&(fc<fb)){ // I am bracketing a maximum!!
		c=b; fc=fb;
 		b=a; fb=fa;
		a-=dangle; P=partJ.on_surf(a); fa=partI.fsurf(P);
     	if(fa<0) {angle=a; return fa;}
 	}

    // for convex shapes & potentials, if fa>fb<fc then [a,c] brackets a minimum 
 	while(!((fa>fb)&&(fc>fb))) {   
    	if((fa>fb)&&(fb>fc)) { // potential decreases from a to c
        	do { // therefore walk toward c 
            	a=b; fa=fb;
            	b=c; fb=fc;
            	c+=dangle; P=partJ.on_surf(c); fc=partI.fsurf(P);
     			if(fc<0) {angle=c; return fc;}
        	} while(fb>fc);
    	}
    	else if((fa<fb)&&(fb<fc)) { // potential increases from a to c
        	do { // therefore walk toward a 
            	c=b; fc=fb;
            	b=a; fb=fa;
            	a-=dangle; P=partJ.on_surf(a); fa=partI.fsurf(P);
    			if(fa<0) {angle=a; return fa;}
        	} while(fa<fc);
    	}
 	dangle/=2; // refine search
 	} // now I am bracketing a minimum
	
    double y,fy;
    while((c-b)>tol) {
        y=b+(c-b)/2.618; P=partJ.on_surf(y); fy=partI.fsurf(P);
     	if(fy<0) {angle=y; return fy;}
        if(fy>fb) { c=y; fc=fy; }
        else { a=b; fa=fb;   b=y; fb=fy; }
    }
	
    angle=b; return fb;
}
bool overlap(SEllipse &partI, Circle &partJ){
	double angle=partI.dir2angle(partJ.r-partI.r);
	return (overlap(angle,partI,partJ)<0);
}
bool overlap(Circle &partI, SEllipse &partJ){return overlap(partJ,partI);}
bool overlap(SEllipse &partI, Circle &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	Vec2d rJold(partJ.r); partJ.r=partI.r+rIJ;
	double angle= partI.dir2angle(rIJ);
	bool ovlp = (overlap(angle,partI,partJ)<0);
	partJ.r=rJold; return ovlp;
}
bool overlap(Circle &partI, SEllipse &partJ, Vec2d const& L)
{return overlap(partJ,partI, L);}

// Circle-Rectangle
bool overlap(Rectangle &partI, Circle &partJ){
	Vec2d rij=partJ.r-partI.r;
	double x=fabs(rij.dot(partI.u[0])),y=fabs(rij.dot(partI.u[1]));
	double dx=x-partI.a.x, dy=y-partI.a.y;
	if((dx>partJ.rmax)||(dy>partJ.rmax)) return false;
	if((dx<=0)||(dy<=0)) return true;
	if((dx*dx+dy*dy)<=partJ.rmax2) return true;
	return false;
}
bool overlap(Circle &partI, Rectangle &partJ){return overlap(partJ,partI);}
bool overlap(Rectangle &partI, Circle &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	Vec2d rJold(partJ.r); partJ.r=partI.r+rIJ;
	bool ovlp = overlap(partI,partJ);
	partJ.r=rJold; return ovlp;
}
bool overlap(Circle &partI, Rectangle &partJ, Vec2d const& L)
{return overlap(partJ,partI, L);}

// Circle-SphericalCap
bool overlap(SphericalCap &partI, Circle &partJ){
	double sigma=partI.rmax+partJ.rmax; 
	return (partI.dist2(partJ.r)<=sigma*sigma);
}
bool overlap(Circle &partI, SphericalCap &partJ){return overlap(partJ,partI);}
bool overlap(SphericalCap &partI, Circle &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	Vec2d rJold(partJ.r); partJ.r=partI.r+rIJ;
	bool ovlp = overlap(partI,partJ);
	partJ.r=rJold; return ovlp;
}
bool overlap(Circle &partI, SphericalCap &partJ, Vec2d const& L)
{return overlap(partJ,partI, L);}
