//#include <Vec2d.h>
//#include <Sphere.h>
#include <SimBox2d.h>
#include <LLcells2d.h>

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
			pl.draw(box.particles[i]);
		}
		box.particles[i].r=r;
	}
}
int main(int argc, char **argv) {

#ifdef _RSEED
    srand48(_RSEED);
#else
    srand48(time(NULL));
#endif


    IVec2d Ncell(12,6);
//    IVec2d Ncell(6,6);
    SimBox2d box;
        
wrap_plstream pl;
        
    box.init(argc,argv);

	double rmax=0.5; Vec2d r(0), a(rmax/2,rmax), e(4,4);
//    Circle particle(r,rmax);
    Ellipse particle(r,a);
//    SEllipse particle(r,a,e);
 
	// phimax for sigma=1 sphereres is ~ 0.785397
    if (!box.create_SQ(0.170,particle,Ncell)) exit(0); // Ellipses
//    if (!box.create_SQ(0.225,particle,Ncell)) exit(0); // Superellipses
    
    double side=box.L[0]; if(box.L[1]>side) side=box.L[1];
	double rcut=2*particle.rmax();
	
	if(side/2<=rcut)
		{cerr<<"rcut "<< rcut<<"to big for L "<<box.L<<flush<<endl;exit(0);}

pl.draw_init(box.L+Vec2d(rcut));
cout << "\n\n\tPress <Enter> to make an MC step\n\n\n";
//pl.draw(cells); 
draw(pl,box); draw(pl,box);
pl.draw_box(box.L); pl.draw_box(box.L); pl.adv(0);


box.Nstep*=100;
    for (int iterm = 1; iterm <= box.Nterm; ++iterm) {
#ifdef _LL_MC
        NVT_MCstep(box,cells);
#else
    	NVT_MCstep(box);
#endif
        if((iterm%box.Icounter)==0) {
            box.adjust_acceptance();
cerr << "Step: "<< iterm << " , Displacement: "<< box.MaxDisp << " , Acceptance: "<< box.ratio << endl;


draw(pl,box); draw(pl,box);
pl.draw_box(box.L); pl.draw_box(box.L); pl.adv(0);
        }
    }

//    box.write(stdout); cout<<"\n\n\n";

    for (int irun = 1; irun <= box.Nstep; ++irun) {
#ifdef _LL_MC
        NVT_MCstep(box,cells);
#else
    	NVT_MCstep(box);
#endif
        if((irun%box.Iprint)==0) {
            cout << "Step: "<< irun << endl;

pl.clear(); 
draw(pl,box); draw(pl,box);
pl.draw_box(box.L); pl.draw_box(box.L); 
//pl.adv(0);


        }
    }
pl.adv(0);
draw(pl,box); draw(pl,box);
pl.draw_box(box.L); pl.draw_box(box.L); 
pl.adv(0);
//pl.clear();

draw(pl,box); draw(pl,box);
pl.draw_box(box.L); pl.draw_box(box.L); pl.adv(0);
//    box.write(stdout); cout<<"\n\n\n";


    return 0;
}
