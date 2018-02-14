#include <SimBox2d.h>

#include <MCstep2d.h>

#include <wrap_plplot.h>

#include <ctime>

#include <iostream>
using namespace std;

void draw(wrap_plstream &pl, SimBox2d &box){
	Vec2d r;
	for (int i = 0; i < box.Npart; ++i) {
		r=box.particles[i].r;
		for (int x = -1; x <= 1; ++x) for (int y = -1; y <= 1; ++y) {
			box.particles[i].r=r+Vec2d(x*box.L[0],y*box.L[1]);
			pl.draw(box.particles[i],3);
		}
		box.particles[i].r=r;
	}
	for (int i = 0; i < 2; ++i) {
		r=box.bigparticles[i].r;
		for (int x = -1; x <= 1; ++x) for (int y = -1; y <= 1; ++y) {
			box.bigparticles[i].r=r+Vec2d(x*box.L[0],y*box.L[1]);
			pl.draw(box.bigparticles[i],9);
		}
		box.bigparticles[i].r=r;
	}
}


int main(int argc, char **argv) {

#ifdef _RSEED
    srand48(_RSEED);
#else
    srand48(time(NULL));
#endif


    SimBox2d box;
 	char* namefile; 
 	if(argc>1) namefile=argv[1]; 
 	else {cerr<<"Need nae of the file to view!!!\n"<<flush;exit(1);}
    box.read_conf(namefile);	
      
wrap_plstream pl;

	double rmax=box.particles[0].radius,Rmax;
#if defined(_CIRCLE)
   	Rmax=box.bigparticles[0].radius;
//#elif defined(_SPHERICALCAP)
#else
	Rmax=box.bigparticles[0].a[0];
#endif 	
	
pl.draw_init(box.L+Vec2d(Rmax));
draw(pl,box); draw(pl,box);
pl.draw_box(box.L); pl.draw_box(box.L); 
pl.adv(0);
pl.clear(); 

    return 0;
}
