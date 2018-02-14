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

#include <vector2d.h>

using namespace std;

int main(int argc, char** argv){
  Vec2d v1(2.1,1.2); cout << "v1=" << v1 << endl;

  Vec2d v2(3.1,1.3); cout << "v2=" << v2 << endl;

  Vec2d v3(0.75*(v1+v2)); cout << "v3=" << v3 << endl; 
  
  cout<<endl; 
  cout << "ATTENTION: * IS NOT THE DOT PRODUCT !!!\n";
  cout << "v1*v2*v3="<< v1*v2*v3 << endl;
  cout << "(v1*v2)*v3="<< (v1*v2) << "*" << v3 << "=" << (v1*v2)*v3 << endl;
  cout << "v1*(v2*v3)="<< v1 << "*" << (v2*v3) << "=" << v1*(v2*v3) << endl;
  
  cout << endl << endl;
 
  IVec2d iv1(1,1); cout << "iv1=" << iv1 << endl;
  IVec2d iv2(2,2); cout << "iv2=" << iv2 << endl;
  IVec2d iv3; cout << "iv3=iv1+3*iv2=" << (iv3=iv1+3*iv2) << endl;
  
  cout << endl;
  cout << "iv3 % 3 = " << iv3 % 3 << endl;
  cout << "iv3 % (2,4) = " << iv3 % IVec2d(2,4) << endl;
  cout << endl;
  cout << "ATTENTION: * IS NOT THE DOT PRODUCT !!!\n";
  cout << "iv3 * 3 = " << iv3 * 3 << endl;
  cout << "iv3 * (2,4) = " << iv3 * IVec2d(2,4) << endl;
  cout << "iv3.dot( (2,4) ) = " << iv3.dot( IVec2d(2,4) ) << endl;
  cout << endl;
  cout << "iv3 / 3 = " << iv3 / 3 << endl;
  cout << "iv3 / (2,4) = " << iv3 / IVec2d(2,4) << endl;
  cout << endl << endl;
 
  return 0;
}
