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


#include<math.h>
#include<stdio.h>
#include<stdlib.h>
//#include<assert.h>

#include <gaussdev.h>

/* Generates gaussian distributed rnd numbers with zero mean and unit variance */
/* using Box-Muller method with drand48() as the uniform rnd numbers generator */

double gaussdev(void)  {  
  static int have_oldg=0; static double oldg; 
  double BoxMuller,r2,x,y; 

  if (have_oldg == 0) { /* No gaussian rnd number is in memory */ 

    do { 
      x=2.0*drand48()-1.0; // two uniform rnd numbers in [-1,1]x[-1,1] 
      y=2.0*drand48()-1.0; 
      r2=x*x+y*y;     
    } 
    while (r2 >= 1.0 || r2 == 0.0); // force x,y in the unit circle
 
    // Box-Muller transform factor
    BoxMuller=sqrt(-2.0*log(r2)/r2); 
    
    oldg=x*BoxMuller; have_oldg=1; // store one gaussian rnd number
    return y*BoxMuller; // return the other gaussian rnd number

  } 
  else {// Gaussian rnd number already in memory 

    have_oldg=0; // will not have gaussian rnd number in memory 
    return oldg; // return old gaussian rnd 
  } 

}
