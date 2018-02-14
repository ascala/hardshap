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
	
	Vec2d L(8,6);
	pl.draw_init(2.2*L);
	
	Vec2d r1(-1,-1), dir1(1.0,1.5); 
	Vec2d r2(1,0), dir2(1.2,0.8);
	Vec2d ax[2];
	ax[0]=Vec2d(1,0); ax[1]=Vec2d(0,1);
	 
	Rectangle rec1(r1,dir1,ax),rec2(r2,dir2,ax),rec;
	double angle;
	
	for (int i = 0; i > -100; ++i) {
    	pl.draw_box(L); pl.draw(rec1); pl.draw_cross(rec2.r);
    	for (int x = -4; x < 4; ++x) for (int y = -4; y < 4; ++y){
    		rec=rec2;  rec.r.x+=x*L.x; rec.r.y+=y*L.y; pl.draw(rec);
		}

   		if(overlap(rec1,rec2,L))
   			{sprintf(msg,"OVERLAP !!");  pl.ptex (1, 6, 3, 0, 0, msg);}
		else
   			{sprintf(msg,"NO OVERLAP");  pl.ptex (1, 6, 3, 0, 0, msg);}

		if(overlap(rec1,rec2,L)!=overlap(rec1,rec2))
   			{sprintf(msg,"(periodic image)");  pl.ptex (1, 5, 3, 0, 0, msg);}

		pl.adv(0);
		
		rec1.r.rnd_displ(0.1); rec2.r.rnd_displ(1.0);  
		angle=2*M_PI*(drand48()-0.5); rec1.rotate(angle);
		angle=2*M_PI*(drand48()-0.5); rec2.rotate(angle); 
	}
	return 0;
}
