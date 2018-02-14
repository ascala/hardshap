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

//#include <Vec2d.h>
//#include <SEllipse.h>
#include <Circle.h>
#include <SphericalCap.h>

#include <Segment.h>


using namespace std;

int main(int argc, char** argv){

  
  double radius(1);
  Circle c(radius);
  cout << c << " Area: " << c.area() <<endl;
  
  Vec2d r(0,0),a(0.5,1);

  Ellipse e(r,a);
  cout << e << " Area: " << e.area() <<endl;
  
  Vec2d expon(4,4);
  SEllipse se(r,a,expon);
  cout << se << " Area: " << se.area() <<endl;

  
  SphericalCap sc;
  cout << sc <<endl;
  

  Segment s;
  cout << s <<endl;  
 

  return 0;
}
