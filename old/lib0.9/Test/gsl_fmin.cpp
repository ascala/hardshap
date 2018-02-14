#include "gsl_fmin.h"
#include <se2d.h>

typedef SEllipse Particle;

     /* distance between two points on the particles */
     
     double
     my_f (const gsl_vector *v, void *params)
     {
       double a,b;
       Particle *ps = (Particle *)params;
     
       a = gsl_vector_get(v, 0);
       b = gsl_vector_get(v, 1);
       
       Vec2d d(ps[0].on_surf(a)-ps[1].on_surf(b));
       return d.norm2();
     }
     
     /* The gradient of f, df = (df/dx, df/dy). */
     void
     my_df (const gsl_vector *v, void *params,
            gsl_vector *df)
     {
       double x, y;
       Particle *dp = (Particle *)params;
     
       x = gsl_vector_get(v, 0);
       y = gsl_vector_get(v, 1);
     
       Vec2d d, p0(dp[0].on_surf(x)),p1(dp[1].on_surf(x));
       double eps=0.5e-2,dfx,dfy;
       
       d=dp[0].on_surf(x+eps)-p1; dfx =d.norm2();
       d=dp[0].on_surf(x-eps)-p1; dfx-=d.norm2();
       
       d=p0-dp[1].on_surf(y+eps); dfy =d.norm2();
       d=p0-dp[1].on_surf(y-eps); dfy-=d.norm2();
       
       eps=1;//eps*=2;
       gsl_vector_set(df, 0, dfx/eps);
       gsl_vector_set(df, 1, dfy/eps);
     }
     
     /* Compute both f and df together. */
     void
     my_fdf (const gsl_vector *x, void *params,
             double *f, gsl_vector *df)
     {
       *f = my_f(x, params);
       my_df(x, params, df);
     }

