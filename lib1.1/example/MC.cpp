#include <SimBox2d.h>

#include <MCstep2d.h>

#include <Histogram.h>

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

	char namefile[1000];
	char* inprefix; if(argc>1) inprefix=argv[1]; else inprefix="start";
	char* outprefix; if(argc>2) outprefix=argv[2]; else outprefix="run";
	double trun=10; if(argc>3) trun=atof(argv[3]);
	
    SimBox2d box;
	sprintf(namefile,"%s%04d.cnf",inprefix,rank);
	box.read_conf(namefile);	                
                
	double rmax=box.particles[0].radius,Rmax;
#if defined(_CIRCLE)
   	Rmax=box.bigparticles[0].radius;
//#elif defined(_SPHERICALCAP)
#else
	Rmax=box.bigparticles[0].a[0];
#endif 	

	int nbin=100; double minbin=2*Rmax, maxbin=box.L[0]/2;
	Histogram his(nbin,minbin,maxbin);   
	
	Vec2d dist; int step;
	for (step = 0; difftime(time(NULL),tstart)<trun; ++step) { 
		NVT_MCstep(box);
		dist=box.bigparticles[0].r-box.bigparticles[1].r; 
		dist.in_box(box.L);
		his.add_value(dist.norm());
	}

	sprintf(namefile,"%s%04d.cnf",outprefix,rank);
	box.write_conf(namefile);
	if(step>0){//write pdf's only if they are some steps
		sprintf(namefile,"%s%04d.his",outprefix,rank);
		his.write(namefile);
		sprintf(namefile,"%s%04d.pdf",outprefix,rank);
		his.print_pdf(namefile);
	}

    return 0;
}
