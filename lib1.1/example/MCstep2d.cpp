#include <MCstep2d.h>

void NVT_MCstep(SimBox2d &box){
  
  int Npart(box.Npart); 
  Particle *particles=box.particles, newparticle;  
  BigParticle *bigparticles=box.bigparticles, newbigparticle;  
  Vec2d MaxDisp(box.MaxDisp), BigMaxDisp(box.BigMaxDisp), L(box.L); 	
  int Ipart;
  
  // displace small particles
  for( int K = 0; K < Npart; K++){
    
// 	Ipart=K;
    Ipart = (int)(drand48()*Npart); // choose a particle at random 
 	Ipart=K;
    newparticle=particles[Ipart]; 
    newparticle.r.rnd_displ(MaxDisp); newparticle.r.in_box(L);
#if 0
    newparticle.rotate(M_PI*(drand48()-0.5));
#endif    
    if( !box.some_overlap(Ipart,newparticle) ){ // move is accepted
    	particles[Ipart]=newparticle;
		box.moves_acc += 1.0; // count number of accepted moves 
	}
	box.moves += 1.0; // count number of moves 

  } // end Ns moves 

  // displace small particles
  for( int K = 0; K < 2; K++){
    
// 	Ipart=K;
    Ipart = (int)(drand48()*2); // choose a particle at random 
 	Ipart=K;
    newbigparticle=bigparticles[Ipart]; 
    newbigparticle.r.rnd_displ(BigMaxDisp); newbigparticle.r.in_box(L);
#if 0
    newbigparticle.rotate(0.1*M_PI*(drand48()-0.5));
#endif    
    if( !box.some_big_overlap(Ipart,newbigparticle) ){ // move is accepted
    	bigparticles[Ipart]=newbigparticle;
		box.big_moves_acc += 1.0; // count number of accepted moves 
	}
	box.big_moves += 1.0; // count number of moves 

  } // end Ns moves 
  

}

template <class Particle>
void NVT_MCstep(SimBox2d &box, LLcells2d<Particle> &cells){
  int Npart(box.Npart); 
  Particle *particles=box.particles;  
  Vec2d MaxDisp(box.MaxDisp), L(box.L); 	
  
  int Nneigh(cells.Nneigh); 
  
  int *head=cells.head, *next=cells.next, *mycell=cells.mycell;
  int **neigh=cells.neigh;
   
  Particle newparticle=box.particles[0]; // valid only if all particles are the same  
  int Ipart,Icell;
  for(int K = 0; K < Npart; K++){
    
    Ipart = (int)(drand48()*Npart); // displace a particle at random 
    newparticle.r=particles[Ipart].r;
    newparticle.r.rnd_displ(MaxDisp); newparticle.r.in_box(L);

    if( !cells.overlap(particles, Ipart, newparticle) ) { // move is accepted
    	particles[Ipart].r=newparticle.r;
		box.moves_acc += 1.0; // count number of accepted moves 
		Icell=cells.index(newparticle.r);
		if(Icell!=mycell[Ipart]) cells.rebuild(Ipart,Icell);
	}
	box.moves += 1.0; // count number of moves 

  } // end Ns moves 

}

