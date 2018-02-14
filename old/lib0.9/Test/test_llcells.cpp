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

#include <se2d.h>
#include <LLcells2d.h>
#include <wrap_pl.h>


using namespace std;

int main(int argc, char **argv)
{	
#ifdef _RSEED
	srand48(_RSEED);
#else
	srand48(time(NULL));
#endif	

	int Nside(4), Npart(Nside*Nside);	
	Ellipse *particles = new Ellipse[Npart];

	double rcut(2*particles[0].rmax);
	Vec2d L(1.01*Nside*rcut);
	for (int i = 0; i < Npart; ++i){
		particles[i].r.rnd(L);
		particles[i].r.in_box(L);
		particles[i].rotate(2*M_PI*drand48());
	}

	LLcells2d<Ellipse> llcell;
	llcell.init(Npart,L,rcut);
	llcell.build(particles);


	wrap_plstream pl;
	pl.draw_init(llcell.L+2*llcell.dL);
	pl.draw(llcell);

	for (int i = 0; i < Npart; ++i) pl.draw(particles[i]);

	cout<<llcell<<endl;

	delete[] particles;

	return 0;
}
