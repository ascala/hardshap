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

#include <VecNd.h>

using namespace std;

int main(int argc, char** argv){
  srand48(time(NULL));
  
  
{
  double size(10);

  VecNd<2,double> v,u,L(size);
  v.rnd(L); u.rnd(L); 
  
  cout << v << " , " << u<< " v + u  = "<<v+u<<endl;
  v+=u; v.in_box(L); cout << v <<endl;
  
  v[1]=0; cout << v << endl;
  v.x[1]=100; cout << v << endl;

}

#if 1
{
  int size(3);

  VecNd<2,int> v,u,t,L(size);
    
  for (int i = -2*L[0]; i <= 2*L[0]; ++i)  {
		v[0]=i; cout << v << " "<< v%L << " " << (v+2*L)%L <<endl;
	}

}
#endif
	
  return 0;
}
