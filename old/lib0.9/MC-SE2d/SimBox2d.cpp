/* creator/distructor for the structure box */
#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<iostream>

#include <SimBox2d.h>

/*
int SimBox2d::read(char *name) {

  FILE *fp=fopen(name,"r");
  this->read(fp);
  fclose(fp);

  return 0;
}

int SimBox2d::read(FILE *fp) {

  fscanf(fp,"%d",&Npart); 
  particles = new Particle[Npart];
  
  fscanf(fp,"%lf %lf",&L.x,&L.y); 
  
  fscanf(fp,"%lf %f",&a.x,&a.y);
   
  fscanf(fp,"%lf %lf",&MaxDisp.x,&MaxDisp.y);

  Particle particle; particle.a=a; 
  for(int i=0;i<Npart;i++){ 
  	fscanf(fp,"%lf %lf",&particle.r.x,&particle.r.y);
  	particles[i]=particle;
  	}  

  return 0;
}


int SimBox2d::write(char *name) {
	
  FILE* fp=fopen(name,"w");
  this->write(fp);
  fclose(fp);  

  return 0;
}

int SimBox2d::write(FILE *fp) {

  fprintf(fp,"%d\n",Npart); 
  fprintf(fp,"%20.18lf %20.18lf\n",L.x,L.y);
  fprintf(fp,"%20.18lf %20.18lf\n",a.x,a.y);
  fprintf(fp,"%20.18lf %20.18lf\n",MaxDisp.x,MaxDisp.y);

  for(int i=0;i<Npart;i++) 
  	fprintf(fp,"%20.18lf %20.18lf\n",particles[i].r.x,particles[i].r.y);

  return 0;
}
*/

bool SimBox2d::create_SQ(double phi, Particle particle, IVec2d Ncell){
	double phimax = particle.area()/(4*particle.a.x*particle.a.y);
std::cerr<<"particle: "<<particle<<"  area:"<<particle.area()<<std::endl;	
std::cerr<<"phimax: "<<phimax<<std::endl;	
	if(phi>phimax) return false;
	
	int pointXcell=1;
	Vec2d a(particle.a);
	// phi = pointXcell*particle.area/a.vol 
	a *= sqrt(phimax/phi);
	
	MaxDisp=Vec2d(0.1*a);
//	MaxDisp=Vec2d(0.01*a);
	
	L=Vec2d(a.x*Ncell.x,a.y*Ncell.y);
	
	double rcut=2*particle.rmax;
std::cerr<<"a "<<a<<", Ncell "<< Ncell << std::endl;
std::cerr<<"L "<<L<<", rcut "<< rcut << std::endl;
	double Lmin=L.x; if(L.y<L.x) Lmin=L.y;
	if(2*rcut>=Lmin) return false;
	
	if(Npart>0) delete[] particles;	
	Npart=pointXcell*Ncell.volume();
	
	particles = new Particle[Npart];
	Vec2d ex(a.x,0), ey(0,a.y), r;
	int count=0;
	for (int ix = 0; ix < Ncell.x; ++ix)
	for (int iy = 0; iy < Ncell.y; ++iy){
		particle.r=ix*ex+iy*ey+a/2; //std::cout<<r<<std::endl;
		particle.r.in_box(L); //std::cout<<r<<std::endl<<std::endl;
		particles[count] = particle;
		count++;
	}

	return true;
}

/*
bool SimBox2d::create_HEX(double phi, double sigma, IVec2d Ncell){
	static double phimax=0.90689968;
	double s3=sigma*sigma*sigma; if(phi*s3>phimax) return false;
	
	this->sigma=sigma;
	MaxDisp=Vec2d(0.1*sigma,0.1*sigma);
	
	double radius=sigma/2, rho = phi / ( M_PI*radius*radius);
	int pointXcell=2;
	double vol = (pointXcell/rho), a=sqrt(2*vol/sin(2.*M_PI/3.));
	L=a*Ncell;
	
	if(Npart>0) delete[] particles;	
	Npart=pointXcell*Ncell.volume();
	
	particles = new Particle[Npart];
	Vec2d ex(a,0,0), ey(0,a,0), ez(0,0,a), r;
	Vec2d e1(a/2,a/2,a/2), r1;
	int count=0;
	for (int ix = 0; ix < Ncell.x; ++ix)
	for (int iy = 0; iy < Ncell.y; ++iy)
	for (int iz = 0; iz < Ncell.z; ++iz){
		r=ix*ex+iy*ey+iz*ez; r.in_box(L);
		particles[count] = Particle(r,sigma);
		count++;
		r1=r+e1; r1.in_box(L);
		particles[count] = Particle(r1,sigma);
		count++;
	}

	return true;
}
*/

void SimBox2d::enforce_periodic(){
	for (int i = 0; i < Npart; ++i) particles[i].r.in_box(L); 
}

bool SimBox2d::any_overlap(){
  // LOOP OVER ALL SPHERES EXCEPT I    
  for( int J = 1; J < Npart; J++) for( int I = 0; I < J; I++) 
  	if ( overlap(particles[I],particles[J],L) ) return true;
  // NO OVERLAP 
  return false;	
}

int SimBox2d::count_overlaps(){
	int count(0);
  // LOOP OVER ALL SPHERES EXCEPT I    
  for( int J = 1; J < Npart; J++) for( int I = 0; I < J; I++) 
  	if ( overlap(particles[I],particles[J],L) ) count++;
  return count;	
}


bool SimBox2d::some_overlap(int I, Particle &particle){
  // LOOP OVER ALL SPHERES EXCEPT I    
  for( int J = 0; J < Npart; J++) if ( I != J ) 
  	if ( overlap(particle,particles[J],L) ) return true;
//  	if ( overlap(particle,particles[J]) ) return true;
  // NO OVERLAP 
  return false;	
}
