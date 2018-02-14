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


#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <Circle.h>

double Circle::perimeter(){return 2*M_PI*radius;}

double Circle::area(){return M_PI*radius*radius;}


Vec2d const Circle::on_surf(const double angle)
{
    return Vec2d( radius*cos(angle) +r[0] , radius*sin(angle) + r[1]);
}

Vec2d const Circle::Don_surf(double const angle){
    return Vec2d( -radius*sin(angle) , radius*cos(angle) );
}

double const Circle::dir2angle(const Vec2d& dir)
{
    return atan2( dir[1] , dir[0] );
}


double const Circle::fsurf(const Vec2d& P)
{
    Vec2d dr = (P-r)/radius;
    return dr.dot(dr)-1;
}

/*
double const Circle::fsurf(double const angle)
{
    Vec2d v(cos(angle)*u[0]+sin(angle)*u[1]);
    return v*v-1;
}
*/

Vec2d const Circle::grad(Vec2d const& P)
{
    Vec2d dr = (P-r)/radius;
    return 2.0*dr;
}

Vec2d const Circle::grad(double const angle)
{
    return Vec2d( 2*cos(angle)/radius , 2*sin(angle)/radius );
}

Vec2d const Circle::Dgrad(double const angle)
{
    return Vec2d( -2*sin(angle)/radius , 2*cos(angle)/radius );
}


void Circle::copy(Circle &B){
	r=B.r;
	radius=B.radius; radius2=B.radius2; 
}
	
void Circle::in_box(Vec2d &L){ r.in_box(L); }
	
bool Circle::overlap(Circle &B, double sigmaAB2, Vec2d &L){
	Vec2d dr;
	dr[0]=r[0]-B.r[0]; dr[1]=r[1]-B.r[1]; 
	dr.in_box(L);
	return (dr.norm2()<sigmaAB2);
}

bool Circle::overlap(Circle &B, Vec2d &L){
	double sigmaAB2=radius+B.radius; sigmaAB2*=sigmaAB2;
	Vec2d dr;
	dr[0]=r[0]-B.r[0]; dr[1]=r[1]-B.r[1];
	dr.in_box(L);
	return (dr.norm2()<sigmaAB2);
}


