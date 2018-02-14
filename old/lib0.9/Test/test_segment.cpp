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


#include "wrap_pl.h"

#include <iostream>

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

int rad2degree(double rad){int deg=(int)(180.*rad/M_PI); return ((deg+360)%360);}

int main(int argc, char **argv) {
#ifdef _RSEED
        srand48(_RSEED);
#else
        srand48(time(NULL));
#endif

	char msg[100];

	wrap_plstream pl; 
	
	Vec2d L(10,10);
	pl.draw_init(1.2*L);
	
	Vec2d r1(-1,-1), r2(2,0), dir(0,1);
	Segment s1(r1,dir,2),s2(r2,dir,1);

	double sc,tc,len2; Vec2d P1,P2;
	for (int i = 0; i > -100; ++i) {
    	pl.draw_box(L); pl.draw(s1); pl.draw(s2); 
		len2=s1.dist2(s2,sc,tc); 
		P1 = s1.r + sc*s1.dir; pl.draw_x(P1);  
		P2 = s2.r + tc*s2.dir; pl.draw_x(P2);
   		pl.draw(P1,P2);
   		
   		sprintf(msg,"distance: %g",sqrt(len2)); 
   		pl.ptex (1, 7, 3, 0, 0, msg);

		pl.adv(0);
		s1.r.rnd_displ(0.5);  s1.dir.rotate(0.1*M_PI*(drand48()-0.5));
		s2.r.rnd_displ(0.5);  s2.dir.rotate(0.1*M_PI*(drand48()-0.5));
	}
	return 0;
}
