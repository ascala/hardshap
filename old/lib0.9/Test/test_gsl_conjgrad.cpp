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
#include <wrap_pl.h>

#include <iostream>

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multimin.h>

#include "gsl_fmin.h"

using namespace std;

int rad2degree(double rad){int deg=(int)(180.*rad/M_PI); return ((deg+360)%360);}


int
     main (void)
     {
#ifdef _RSEED
        srand48(_RSEED);
#else
        srand48(time(NULL));
#endif

	char msg[100];

	wrap_plstream pl; 
	

	typedef SEllipse Particle;
		
	Particle part[2];
	part[0].e=part[1].e=Vec2d(2,2);	
    	part[0].r-=Vec2d(1.2,0);
    	part[1].r+=Vec2d(1.2,0);
	cout<<part[0]<<endl;
	cout<<part[1]<<endl;
	
	Vec2d L(4.1*part[0].rmax);
	pl.draw_init(2*L);
	

	double rcut(2*part[0].rmax); 
	if((rcut>=L.x/2)||(rcut>=L.y/2))
	{cerr<<"rcut "<<rcut<<" too big for L "<<L<<endl<<flush;exit(0);}


       size_t iter = 0;
       int status;
     
       const gsl_multimin_fdfminimizer_type *T;
       gsl_multimin_fdfminimizer *s;
     
       /* Position of the minimum (1,2). */
       double par[2] = { 1.0, 2.0 };
     
       gsl_vector *x;
       gsl_multimin_function_fdf my_func;
     
       my_func.f = &my_f;
       my_func.df = &my_df;
       my_func.fdf = &my_fdf;
       my_func.n = 2;
       my_func.params = &par;
     
       /* Starting point, x = (5,7) */
       x = gsl_vector_alloc (2);
       double a=2*drand48()*M_PI,b=2*drand48()*M_PI;
       gsl_vector_set (x, 0, a);
       gsl_vector_set (x, 1, b);
     
       T = gsl_multimin_fdfminimizer_conjugate_fr;
       s = gsl_multimin_fdfminimizer_alloc (T, 2);
     
       gsl_multimin_fdfminimizer_set (s, &my_func, x, 0.01, 1e-4);
     
    	pl.draw_box(L); 
	pl.draw(part[0]); pl.draw(part[1]); 
	pl.draw(part[0].on_surf(a),part[1].on_surf(b));
	pl.adv(0);

       do
         {
           iter++;
           status = gsl_multimin_fdfminimizer_iterate (s);
     
    	pl.draw_box(L); 
	pl.draw(part[0]); pl.draw(part[1]); 
//    	pl.draw(part[0].r,part[1].r);
   	a=gsl_vector_get(s->x,0); b=gsl_vector_get(s->x,1);
	pl.draw(part[0].on_surf(a),part[1].on_surf(b));
	pl.adv(0);

           if (status)
             break;
     
           status = gsl_multimin_test_gradient (s->gradient, 1e-3);
     
           if (status == GSL_SUCCESS)
             printf ("Minimum found at:\n");
     
           printf ("%5d %.5f %.5f %10.5f\n", iter,
                   gsl_vector_get (s->x, 0),
                   gsl_vector_get (s->x, 1),
                   s->f);
     
         }
       while (status == GSL_CONTINUE && iter < 100);
     
    	pl.draw_box(L); 
	pl.draw(part[0]); pl.draw(part[1]); 
   	a=gsl_vector_get(s->x,0); b=gsl_vector_get(s->x,1);
	pl.draw(part[0].on_surf(a),part[1].on_surf(b));
	pl.adv(0);
     
       gsl_multimin_fdfminimizer_free (s);
       gsl_vector_free (x);
     
       return 0;
     }
