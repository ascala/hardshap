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


#include <wrap_plplot.h>

#include <iostream>

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

int main(int argc, char **argv) {
#ifdef _RSEED
        srand48(_RSEED);
#else
        srand48(time(NULL));
#endif

	char msg[100];

	wrap_plstream pl; 
	
	pl.draw_init();
	
	Segment s;
	s.r=Vec2d(2,2); s.dir=Vec2d(2,1); s.dir.normalize(); s.halflen=2;
	pl.draw(s);
	pl.ptex (1, 5, 5, 0, 0, "Segment");
	pl.adv(0);

	SphericalCap sc(s.r,s.halflen*s.dir,1);
	pl.draw(sc);
	pl.ptex (1, 5, 5, 0, 0, "Spherical cap");
	pl.adv(0);

	Circle c;
	c.r=Vec2d(3,3);
	pl.draw(c);
	pl.ptex (1, 5, 5, 0, 0, "Circle");
	pl.adv(0);

	for (int i = 0; i < 5; ++i)	
	{
	Ellipse e;
	e.r=Vec2d(1,0);
	pl.draw(e);
	pl.ptex (1, 5, 5, 0, 0, "Ellipse");

	Vec2d r,P; double angle;
	r.rnd(1); r.normalize(); r*=4; pl.draw(e.r,e.r+r);
	angle=e.dir2angle(r); P=e.on_surf(angle); pl.draw_x(P);	
	
	pl.adv(0);	
	}
	
	for (int i = 0; i < 5; ++i)	
	{
	SEllipse se;
	se.r=Vec2d(1,0); se.e=Vec2d(4,4);
	pl.draw(se);
	pl.ptex (1, 5, 5, 0, 0, "Super Ellipse");

	Vec2d r,P; double angle;
	r.rnd(1); r.normalize(); r*=4; pl.draw(se.r,se.r+r);
	angle=se.dir2angle(r); P=se.on_surf(angle); pl.draw_x(P);	
	
	pl.adv(0);
	}
	

	
	return 0;
}
