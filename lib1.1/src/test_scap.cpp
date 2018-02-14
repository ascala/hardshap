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
	
	Vec2d r1(-1,-1), dir1(0,1.5);   double radius1(0.7);
	Vec2d r2(1,0),   dir2(0,0.7); double radius2(1.2);
	SphericalCap sc1(r1,dir1,radius1),sc2(r2,dir2,radius2);

	double sc,tc,len2; Vec2d P1,P2;
	for (int i = 0; i > -100; ++i) {
    	pl.draw_box(L); pl.draw(sc1); pl.draw(sc2); 
		len2=sc1.dist2(sc2,sc,tc); 
		P1 = sc1.r + sc*sc1.dir; pl.draw_x(P1);  
		P2 = sc2.r + tc*sc2.dir; pl.draw_x(P2);
   		pl.draw(P1,P2);
   		
   		sprintf(msg,"distance^2: %g",len2); 
   		pl.ptex (1, 7, 3, 0, 0, msg);
   		if(len2<0){
   			sprintf(msg,"OVERLAP !!!"); 
   			pl.ptex (1, 6, 3, 0, 0, msg);
   		}

		pl.adv(0);
		sc1.r.rnd_displ(0.5);  sc1.dir.rotate(0.1*M_PI*(drand48()-0.5));
		sc2.r.rnd_displ(0.5);  sc2.dir.rotate(0.1*M_PI*(drand48()-0.5));
	}
	return 0;
}
