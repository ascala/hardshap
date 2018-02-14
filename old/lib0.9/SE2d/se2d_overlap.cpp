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
	double sigmaIJ=partI.rmax+partJ.rmax;
	return ( rIJ.norm2()<sigmaIJ*sigmaIJ ) ;
}

bool overlap(Circle &partI, Circle &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	double sigmaIJ=partI.rmax+partJ.rmax;
	return ( rIJ.norm2()<sigmaIJ*sigmaIJ );
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
bool overlap(SphericalCap &partI, SphericalCap &partJ) { return ( partI.dist2(partJ)<0 ); }

bool overlap(SphericalCap &partI, SphericalCap &partJ, Vec2d const& L){
	Vec2d rIJ(partJ.r-partI.r); rIJ.in_box(L);
	Vec2d rJold(partJ.r); partJ.r=partI.r+rIJ;
	bool ovlp = ( partI.dist2(partJ)<0 ) ;
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

