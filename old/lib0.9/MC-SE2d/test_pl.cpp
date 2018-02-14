//#include "Ellipse.hpp"
#include "se2d_pl.h"

//#include "Vec2d.h"

#include <iostream>

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

int main(int argc, char **argv) {
#ifdef _RSEED
        srand48(_RSEED);
#else
        srand48(time(NULL));
#endif

	char msg[100];

	se2d_plstream pl; 
	
	pl.draw_init();
	
	Segment s;
	s.P0=Vec2d(3,3); s.P1=Vec2d(2,1);
	pl.draw(s);
	pl.ptex (1, 5, 5, 0, 0, "Segment");
	pl.adv(0);

	SphericalCap sc(s.P0,s.P1,1);
	pl.draw(sc);
	pl.ptex (1, 5, 5, 0, 0, "Spherical cap");
	pl.adv(0);

	Circle c;
	c.r=Vec2d(3,3);
	pl.draw(c);
	pl.ptex (1, 5, 5, 0, 0, "Circle");
	pl.adv(0);

	Ellipse e;
	e.r=Vec2d(1,0);
	pl.draw(e);
	pl.ptex (1, 5, 5, 0, 0, "Ellipse");
	pl.adv(0);

	SEllipse se;
	se.r=Vec2d(1,0);
	pl.draw(se);
	pl.ptex (1, 5, 5, 0, 0, "Super Ellipse");
	pl.adv(0);


	
	SEllipse e1,e2;
    double alpha;
    Vec2d r,P;                
	double rmin=1, rmin2=1;

	SphericalCap sc1,sc2;

    e2.r.rnd(6.,6.); 
    e2.rotate(2*M_PI*drand48());
//	e2.r=Vec2d(2.1,0.); e2.rotate(0.3);
    for (int i = 0; i < 30; ++i) {
    	pl.draw(e1); sc1=SphericalCap(e1); pl.draw(sc1);
    	pl.draw(e2); sc2=SphericalCap(e2); pl.draw(sc2);
    	pl.draw_line(e1.r,e2.r);
    	r = e1.r-e2.r;  
//    	P = e2.on_surf_omotopy(r); pl.draw_x(P);
//    	r=P-e2.r; alpha=e2.dir2angle(r);
    	alpha=e2.dir2angle(r);
    	P = e2.on_surf(alpha);
    	pl.draw_cross(P);
sprintf(msg,"%g , %g",e2.fsurf(P),e1.fsurf(P)); pl.ptex (1, 7, 3, 0, 0, msg);

		if(r*r<rmin2)
pl.ptex (-4, 4, 1, 0, 0, "S-S overlap");
		else{
			alpha=e2.minimize_fsurf(alpha,e1);
			P = e2.on_surf(alpha);
			pl.draw_x(P);
sprintf(msg,"%g , %g",e2.fsurf(P),e1.fsurf(P)); pl.ptex (1, 6, 3, 0, 0, msg);
if(e1.fsurf(P)<0) pl.ptex (-4, 4, 1, 0, 0, "overlap");
else pl.ptex (-3, 4, 1, 0, 0, "NO overlap");
		}

		e2.r.rnd(6.,6.); 		
//		e2.r.RandDispl(1);
		e2.rotate(2*M_PI*drand48());
		pl.adv(0);
//		pl.eop(); pl.bop();
    }	
	return 0;
}
