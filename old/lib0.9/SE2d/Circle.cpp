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

double Circle::perimeter(){return 2*M_PI*rmax;}

double Circle::area(){return M_PI*rmax*rmax;}


Vec2d const Circle::on_surf(const double angle)
{
    return Vec2d( rmax*cos(angle) +r.x , rmax*sin(angle) + r.y);
}

Vec2d const Circle::Don_surf(double const angle){
    return Vec2d( -rmax*sin(angle) , rmax*cos(angle) );
}

double const Circle::dir2angle(const Vec2d& dir)
{
    return atan2( dir.y , dir.x );
}


double const Circle::fsurf(const Vec2d& P)
{
    Vec2d dr = (P-r)/rmax;
    return dr*dr-1;
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
    Vec2d dr = (P-r)/rmax;
    return 2*dr;
}

Vec2d const Circle::grad(double const angle)
{
    return Vec2d( 2*cos(angle)/rmax , 2*sin(angle)/rmax );
}

Vec2d const Circle::Dgrad(double const angle)
{
    return Vec2d( -2*sin(angle)/rmax , 2*cos(angle)/rmax );
}


void Circle::copy(Circle &B){
	r=B.r;
	rmax=B.rmax; rmax2=B.rmax2; 
}
	
void Circle::in_box(Vec2d &L){ r.in_box(L); }
	
bool Circle::overlap(Circle &B, double sigmaAB2, Vec2d &L){
	Vec2d dr;
	dr.x=r.x-B.r.x; dr.y=r.y-B.r.y; 
	dr.in_box(L);
	return (dr.norm2()<sigmaAB2);
}

bool Circle::overlap(Circle &B, Vec2d &L){
	double sigmaAB2=rmax+B.rmax; sigmaAB2*=sigmaAB2;
	Vec2d dr;
	dr.x=r.x-B.r.x; dr.y=r.y-B.r.y;
	dr.in_box(L);
	return (dr.norm2()<sigmaAB2);
}


