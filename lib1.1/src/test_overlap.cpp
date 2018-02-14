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
	

	typedef SEllipse Particle;
		
	Particle part[2];
	part[0].e=part[1].e=Vec2d(4,4);	
	cout<<part[0]<<endl;
	
	Vec2d L(4.1*part[0].rmax());
	pl.draw_init(2.0*L);
	
	double rcut(2*part[0].rmax()); 
	if((rcut>=L[0]/2)||(rcut>=L[1]/2))
	{cerr<<"rcut "<<rcut<<" too big for L "<<L<<endl<<flush;exit(0);}
	
    double alpha;
    Vec2d r01,P;                

	int i0=0,i1=1;
    part[i1].r.rnd(L); part[i1].in_box(L); 
    part[i1].rotate(2*M_PI*drand48());

    for (int i = 0; i < 100; ++i) {

    	pl.draw_box(L); pl.draw(part[i0]); 
    	pl.draw(part[i0].r,part[i1].r);
    	
    	r01 = part[i1].r-part[i0].r;  alpha=part[i0].dir2angle(r01);
    	P = part[i0].on_surf(alpha); pl.draw_cross(P);
    	
		sprintf(msg,"start: %d , %g",rad2degree(alpha),part[i1].fsurf(P)); 
		pl.ptex (1, 7, 3, 0, 0, msg);

		part[i0].overlap(alpha,part[i1]);
		P = part[i0].on_surf(alpha); pl.draw_x(P);
		
		sprintf(msg,"ovlp:  %d° , %g",rad2degree(alpha),part[i1].fsurf(P)); 
		pl.ptex (1, 6, 3, 0, 0, msg);

		alpha=part[i0].dir2angle(r01);
		alpha=part[i0].minimize_fsurf(alpha,part[i1]);
		P = part[i0].on_surf(alpha); pl.draw_square(P);

		sprintf(msg,"min:  %d° , %g",rad2degree(alpha),part[i1].fsurf(P)); 
		pl.ptex (1, 5, 3, 0, 0, msg);

		bool OVLP=overlap(part[i0],part[i1]);
		if(OVLP) pl.ptex (-4, 4, 1, 0, 0, "overlap");
		else pl.ptex (-3, 4, 1, 0, 0, "NO overlap");

		Vec2d r1=part[i1].r; 
		for(int i=-2;i<=2;++i) for(int j=-2;j<=2;++j) 
		{ part[i1].r=r1+Vec2d( i*L[0], j*L[1]); pl.draw(part[i1]); }

/*		
		r01.in_box(L); part[i1].r=part[i0].r+r01;
		if(overlap(part[i0],part[i1])&&(!OVLP)) 
			pl.ptex (-4, 2, 1, 0, 0, "BOUNDARY overlap");
*/
		if(overlap(part[i0],part[i1],L)&&(!OVLP)) 
			pl.ptex (-4, 2, 1, 0, 0, "BOUNDARY overlap");

		part[i1].r.rnd(L); part[i1].in_box(L);	
		part[i1].rotate(2*M_PI*drand48());

		i0++; i0%=2; i1++; i1%=2;

		pl.adv(0);
//		pl.eop(); pl.bop();

    }	
	return 0;
}
