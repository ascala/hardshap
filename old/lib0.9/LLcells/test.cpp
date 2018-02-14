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

#ifdef _USE_PL
#include <se2d_pl.h>
#else
#include <se2d.h>
#endif

#include <LLcells2d.h>

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

#ifdef _USE_PL
	llcell.draw();
#else
	cout<<llcell<<endl;
#endif

	delete[] circles;

	return 0;
}
