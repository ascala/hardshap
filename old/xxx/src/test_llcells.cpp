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


#include <iostream>

#include <wrap_plplot.h>

using namespace std;

int main(int argc, char **argv)
{
#ifdef RSEED
	srand48(RSEED);
#else
	srand48(time(NULL));
#endif

	int Npart(9);
	
	Vec2d r(0,0), axislen(2,1), exponents(3,3);
	SEllipse se(r,axislen,exponents);	
	SEllipse *particles = new SEllipse[Npart];

	Vec2d L(10.0*se.rmax()); 
	for (int i = 0; i < Npart; ++i){
		particles[i]=se;
		particles[i].r.rnd(L);
		particles[i].in_box(L);
		double alpha=2.0*M_PI*drand48(),sa,ca;
		sincos(alpha,&sa,&ca);
		particles[i].u[0]=Vec2d(sa,ca);
		particles[i].u[1]=Vec2d(-ca,sa);
	}

	double sigma(2*se.rmax());
	LLcells2d<SEllipse> llcell;
	llcell.init(Npart,L,sigma);
	llcell.build(particles);


	cout<<llcell<<endl;

	wrap_plstream pl; 
	pl.draw_init(llcell.L);
	pl.draw(llcell);
	for (int i = 0; i < Npart; ++i) {
		pl.draw(particles[i],4);
		pl.draw_char(particles[i].r,'0'+i,5);
	}

	delete[] particles;

	return 0;
}
