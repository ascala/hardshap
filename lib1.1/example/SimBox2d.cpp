/* creator/distructor for the structure box */
#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<iostream>

#include <SimBox2d.h>

bool SimBox2d::create_RND(double phi, const Vec2d& side, BigParticle bigparticle, Particle particle, double angle){
	
	int Nsmall=phi*(side[0]*side[1]-2*bigparticle.area());
	double l=sqrt(2*bigparticle.area()+Nsmall*particle.area()/phi);
	L=Vec2d(l,l);
	
	double rcut=2*particle.rmax();
	if(2*rcut>=l) return false;
#if 0
	if(2*(2*bigparticle.rmax())>=l) return false;
#else
	if(2*(2*bigparticle.a[0])>=l) return false;
#endif 

	
#if 0
	bigparticle.r.rnd(L); bigparticle.r.in_box(L);
	bigparticle.rotate(2*drand48()*M_PI);
	bigparticles[0]=bigparticle;
	do{
		bigparticle.r.rnd(L); bigparticle.r.in_box(L);
		bigparticle.rotate(2*drand48()*M_PI);
	}while( overlap(bigparticles[0],bigparticle,L) );
	bigparticles[1]=bigparticle;
#else	
	bigparticle.r[0]=-bigparticle.rmax()-particle.rmax();
	bigparticle.r.in_box(L);
	bigparticles[0]=bigparticle;
	
	bigparticle.r[0]=bigparticle.rmax()+particle.rmax();
	bigparticle.r.in_box(L); bigparticle.rotate(angle);
	bigparticles[1]=bigparticle;	
#endif	
	
	if(Npart>0) delete[] particles;	
	particles = new Particle[Nsmall];

	for(Npart=0; Npart<Nsmall; Npart++){
		bool anyovlp;
		do{
			anyovlp=false;
			particle.r.rnd(L); particle.r.in_box(L); 
			particle.rotate(2*drand48()*M_PI);
			anyovlp=anyovlp||overlap(particle,bigparticles[0],L);
			anyovlp=anyovlp||overlap(particle,bigparticles[1],L);
			for(int i=0;i<Npart;++i)
			anyovlp=anyovlp||overlap(particle,particles[i],L);
		} while(anyovlp);
		particles[Npart]=particle;
	}
	
	MaxDisp=Vec2d(particle.rmax());
	BigMaxDisp=Vec2d( sqrt(particle.rmax()/bigparticle.rmax())*MaxDisp );
#if 1
	BigMaxDisp[1]=0;
#endif
//MaxDisp=Vec2d(L);
//BigMaxDisp=Vec2d(particle.rmax());
	

	return true;
}


bool SimBox2d::create_RND(double phi, BigParticle bigparticle, Particle particle, int Nsmall, double angle){
	
	double side=sqrt(2*bigparticle.area()+Nsmall*particle.area()/phi);
	double scalfactor=1.2;
	
	L=Vec2d(scalfactor*side,side/scalfactor);
	double rcut=2*particle.rmax();
	if(2*rcut>=scalfactor*side) return false;
	if(2*rcut>=side/scalfactor) return false;
	if(2*(2*bigparticle.rmax())>=side) return false;
	
#if 0
	bigparticle.r.rnd(L); bigparticle.r.in_box(L);
	bigparticle.rotate(2*drand48()*M_PI);
	bigparticles[0]=bigparticle;
	do{
		bigparticle.r.rnd(L); bigparticle.r.in_box(L);
		bigparticle.rotate(2*drand48()*M_PI);
	}while( overlap(bigparticles[0],bigparticle,L) );
	bigparticles[1]=bigparticle;
#else	
	bigparticle.r[0]=-bigparticle.rmax()-particle.rmax();
	bigparticle.r.in_box(L);
	bigparticles[0]=bigparticle;
	
	bigparticle.r[0]=bigparticle.rmax()+particle.rmax();
	bigparticle.r.in_box(L); bigparticle.rotate(angle);
	bigparticles[1]=bigparticle;	
#endif	
	
	if(Npart>0) delete[] particles;	
	particles = new Particle[Nsmall];

	for(Npart=0; Npart<Nsmall; Npart++){
		bool anyovlp;
		do{
			anyovlp=false;
			particle.r.rnd(L); particle.r.in_box(L); 
			particle.rotate(2*drand48()*M_PI);
			anyovlp=anyovlp||overlap(particle,bigparticles[0],L);
			anyovlp=anyovlp||overlap(particle,bigparticles[1],L);
			for(int i=0;i<Npart;++i)
			anyovlp=anyovlp||overlap(particle,particles[i],L);
		} while(anyovlp);
		particles[Npart]=particle;
	}
	
	MaxDisp=Vec2d(particle.rmax());
	BigMaxDisp=Vec2d( sqrt(particle.rmax()/bigparticle.rmax())*MaxDisp );
#if 1
	BigMaxDisp[1]=0;
#endif
//MaxDisp=Vec2d(L);
//BigMaxDisp=Vec2d(particle.rmax());
	

	return true;
}

void SimBox2d::enforce_periodic(){
	for (int i = 0; i < Npart; ++i) particles[i].r.in_box(L); 
}

bool SimBox2d::any_overlap(){
  // LOOP OVER ALL SPHERES EXCEPT I    
  for( int J = 1; J < Npart; J++) for( int I = 0; I < J; I++) 
  		if ( OBBoverlap(particles[I],particles[J],L) ) return true;

  for( int J = 1; J < 2; J++) for( int I = 0; I < J; I++) 
  		if ( OBBoverlap(bigparticles[I],bigparticles[J],L) ) return true;

  for( int J = 0; J < Npart; J++) for( int I = 0; I < 2; I++) 
  		if ( OBBoverlap(particles[I],bigparticles[J],L) ) return true;
  // NO OVERLAP 
  return false;	
}

int SimBox2d::count_overlaps(){
	int count(0);
  // LOOP OVER ALL SPHERES EXCEPT I    
  for( int J = 1; J < Npart; J++) for( int I = 0; I < J; I++) 
  		if ( OBBoverlap(particles[I],particles[J],L) ) count++;
  return count;	
}


bool SimBox2d::some_overlap(int I, Particle &particle){
  // LOOP OVER ALL SPHERES EXCEPT I    
  for( int J = 0; J < Npart; J++) if ( I != J ) 
  	if ( OBBoverlap(particle,particles[J],L) ) return true;
  for( int J = 0; J < 2; J++) 
  	if ( OBBoverlap(particle,bigparticles[J],L) ) return true;
  // NO OVERLAP 
  return false;	
}

bool SimBox2d::some_big_overlap(int I, BigParticle &bigparticle){
  // LOOP OVER ALL SPHERES EXCEPT I    
  for( int J = 0; J < Npart; J++) 
  	if ( OBBoverlap(bigparticle,particles[J],L) ) return true;
  for( int J = 0; J < 2; J++) if ( I != J )  
  	if ( OBBoverlap(bigparticle,bigparticles[J],L) ) return true;
  // NO OVERLAP 
  return false;	
}

