#ifndef FMIN_H
#define FMIN_H

#include <gsl/gsl_vector.h>

     double
     my_f (const gsl_vector *v, void *params);

     void
     my_df (const gsl_vector *v, void *params,
            gsl_vector *df);

     void
     my_fdf (const gsl_vector *x, void *params,
             double *f, gsl_vector *df);


#endif
