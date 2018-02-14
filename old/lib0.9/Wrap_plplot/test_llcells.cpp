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

#include <wrap_pl.h>

using namespace std;

int main(int argc, char **argv)
{
	int Npart(9);	
	Circle *circles = new Circle[Npart];
	Vec2d L(3.3);
	for (int i = 0; i < Npart; ++i){
		circles[i].r.rnd(L);
		circles[i].in_box(L);
	}

	double rcut(circles[0].radius);
	LLcells2d<Circle> llcell;
	llcell.init(Npart,L,rcut);
	llcell.build(circles);


	cout<<llcell<<endl;

	wrap_plstream pl; 
	pl.draw_init(llcell.L);
	pl.draw(llcell);

	Ellipse E; cout<<E<<endl; pl.draw(E);
//	SEllipse SE; cout<<SE<<endl; pl.draw(SE);
	Vec2d P;
/*
	for (int i = 0; i < 1000; ++i){
		P=E.on_surf(M_PI*2*drand48());
		pl.draw_x(P);
	}
*/

	delete[] circles;

	return 0;
}
