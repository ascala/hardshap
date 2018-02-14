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
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{

#ifdef _RSEED
    srand48(_RSEED);
#else

    srand48(time(NULL));
#endif

    double radius(1);
    Circle c(radius);
    cout << c << " Area: " << c.area() <<endl;
    cout <<endl;

    Vec2d r(0,0),a(0.5,1);

    Ellipse e(r,a);
    cout << e << " Area: " << e.area() <<endl;
    cout <<endl;

	SEllipse se(r,a);
	cout << se << endl;
    for (double expon = 2; expon <= 128; expon*=2)
    {
        se.e=Vec2d(expon);
        cout << "Exponent: " << e << " Area: " << se.area() <<endl;
    }
    cout <<endl;

    SphericalCap sc;
    cout << sc << " Area: " << sc.area() <<endl;
    cout <<endl;


    Segment s;
    cout << s <<endl;
    cout <<endl;

    return 0;
}
