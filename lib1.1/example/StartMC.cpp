#include <SimBox2d.h>
#include <LLcells2d.h>

#include <MCstep2d.h>

#include <ctime>

#include <iostream>
using namespace std;

int main(int argc, char **argv) {
time_t tstart=time(NULL);
int rank = 0;

long int rseed;
#ifdef _RSEED
        rseed=_RSEED+rank;
#else
        rseed=(long int)(tstart)+rank;
#endif
srand48(rseed);


 	double packing_fraction=0.10; if(argc>1) packing_fraction=atof(argv[1]);
	int nsigma=10; if(argc>2) nsigma=atoi(argv[2]);
	double trun=10; if(argc>3) trun=atof(argv[3]);
	char* prefix; if(argc>4) prefix=argv[4]; else prefix="start";
	char namefile[1000]; sprintf(namefile,"%s%04d.cnf",prefix,rank);
	int sexpon=3; if(argc>5) sexpon=atoi(argv[5]);

    SimBox2d box;
                
                                
	double rmax=0.5; Vec2d r(0);
    Circle particle(r,rmax);
    
    double Rmax(10*rmax); Vec2d a(Rmax,Rmax), e(sexpon,sexpon);
#if defined(_CIRCLE)
   	Circle bigparticle(Rmax);
#elif defined(_ELLIPSE)
    Ellipse bigparticle(r,a);
#elif defined(_SELLIPSE)
    SEllipse bigparticle(r,a,e);
#elif defined(_RECTANGLE)
 	Rectangle bigparticle(r,a);
#else
	Circle bigparticle;
	cerr<<"You should compile defining which is the kind of big particle!!!\n"<<flush;
	exit(1);
#endif 	
 	double l=4*Rmax+nsigma*2*rmax; Vec2d side(l,l);
    if ( !box.create_RND(packing_fraction,side,bigparticle,particle) ) exit(0); 
    
	for (int step = 0; difftime(time(NULL),tstart)<trun; ++step) 
		NVT_MCstep(box);
		
	box.write_conf(namefile);

    return 0;
}
