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


#include <Rectangle.h>

Rectangle::Rectangle(): a(1,1) {u[0].x=u[1].y=1;}
	
Rectangle::Rectangle(const Vec2d& center, const Vec2d& lengths, const Vec2d dir[2])
: r(center), a(lengths)  {u[0]=dir[0]; u[1]=dir[1];}

Rectangle::Rectangle(Rectangle const &other): 
r(other.r), a(other.a) { u[0]=other.u[0]; u[1]=other.u[1];}

double Rectangle::perimeter(){return 4*(a.x+a.y);}

double Rectangle::area(){return 4*a.x*a.y;}

void Rectangle::rotate(double const angle)
{ //{u[0].rotate(angle); u[1].rotate(angle);}
    double sa=sin(angle), ca=cos(angle);
    u[0]=Vec2d(ca*u[0].x + sa*u[0].y, -sa*u[0].x + ca*u[0].y);
    u[1]=Vec2d(ca*u[1].x + sa*u[1].y, -sa*u[1].x + ca*u[1].y);
}


//	stream operators
std::ostream& operator<<(std::ostream& pStr, const Rectangle& pS)
{ return ( pStr << pS.r << ';' << pS.a << ";["<<pS.u[0]<<','<<pS.u[1]<<']' ); }


//===================================================================

