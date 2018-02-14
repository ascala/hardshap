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

#include <Vec2d.h>
#include <Vec3d.h>
#include <IVec2d.h>
#include <IVec3d.h>

using namespace std;

int main(int argc, char** argv){
  Vec2d v2;
  cout << v2 << endl;
 
  IVec2d iv2;
  cout << iv2 << endl;
  
  Vec3d v3;
  cout << v3 << endl;
  
  IVec3d iv3;
  cout << iv3 << endl;

  return 0;
}
