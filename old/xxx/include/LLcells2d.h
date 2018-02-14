#ifndef LLCELLS2D_H_
#define LLCELLS2D_H_

#include <vector2d.h>
#include <se2d.h>

template <class Particle>
class LLcells2d {
public:
	int Npart; // number of particles
	IVec2d Nside; // number of cells on side x,y
	int Ncell, Nneigh; // total number of cells, number of neighb. per cell
	Vec2d L, dL, Lhalf; // sides of the box, sides of the cell, half sides
	int* mycell; // mycell[IP] is the cell index of the IP-th particle
	int* next; // if>0, IP1=next[IP] is a particle in the same cell of IP 
	int* head; // if>0, head[IC] is the first particle in the IC-th cell
	int** neigh; // neigh[IC][0..Nneigh-1] are the neighbour cells of IC

	LLcells2d():Npart(0), Ncell(0) {}
	
	~LLcells2d(){
		if(Ncell>0){
			for (int IC = 0; IC < Ncell; ++IC) if(Nneigh>0) delete[] neigh[IC];
			delete[] neigh; delete[] head;
		}
		if(Npart>0) {delete[] mycell;  delete[] next;}
	}
	
	friend std::ostream& operator<<(std::ostream& pStr, const LLcells2d& ll)
	{ 	char c;
		pStr << "Linked list:\n";
		for (int Icell = 0; Icell < ll.Ncell; ++Icell) {
			if(Icell<10) c='0'+Icell; else c='A'+Icell-10; 
			pStr << "Cell " << c <<": ";
			int Ipart=ll.head[Icell];
			while(Ipart>=0) {
				if(Ipart<10) c='0'+Ipart; else c='A'+Ipart-10; 
				pStr << c << " "; Ipart=ll.next[Ipart];
				}
			pStr << std::endl;
		}
		pStr << "\nNeighbour list:\n"; int Jcell;
		for (int Icell = 0; Icell < ll.Ncell; ++Icell){
			if(Icell<10) c='0'+Icell; else c='A'+Icell-10;
			pStr << "Cell " << c <<": ";
			for (int nn = 0; nn < ll.Nneigh; ++nn) {
				Jcell=ll.neigh[Icell][nn];
				if(Jcell<10) c='0'+Jcell; else c='A'+Jcell-10;
				pStr << c << " ";
			}
			pStr<<std::endl;
		}
		return pStr; 
	}

// returns the index of the cell where the the point "r" lies
int index(Vec2d &r){
	IVec2d ivr;
	ivr[0]=((int)((r[0]+Lhalf[0])/dL[0]))%Nside[0];
	ivr[1]=((int)((r[1]+Lhalf[1])/dL[1]))%Nside[1];
	return ivr.index(Nside);
}

// initializes a linked-list cell structure; each cell is a box of side at least rcut
void init(int npart, Vec2d side, double rcut){

	Npart=npart;
	mycell=new int[Npart];
	next=new int[Npart];
	
	L = side; Lhalf=L/2.0;
	Nneigh=3*3;

	rcut*=(1+1.0e-8); 
	Nside[0] = (int)(side[0]/rcut);
	Nside[1] = (int)(side[1]/rcut);
	
	dL[0] = L[0]/Nside[0]; 
	dL[1] = L[1]/Nside[1]; 
	
	Ncell=Nside.area();
	head=new int[Ncell];
	neigh=new int*[Ncell];
	for (int Icell = 0; Icell < Ncell; ++Icell) neigh[Icell]=new int[Nneigh];
		
	int Icell, Jcell, NN;
	for (int ix = 0; ix < Nside[0]; ++ix) 
	for (int iy = 0; iy < Nside[1]; ++iy)   {
		
		IVec2d ivec(ix,iy);
		Icell=ivec.index(Nside);

		NN=0;  
		for (int dy = -1; dy <= 1; ++dy) 
		for (int dx = -1; dx <= 1; ++dx) {
			IVec2d jvec(ix+dx,iy+dy);
			jvec+=Nside; jvec%=Nside;
			Jcell=jvec.index(Nside);
			neigh[Icell][NN]=Jcell;
			NN++;
		} // neigbours
		
	} // cells
	
}

// assign cells to the particles
void build(Particle *particles){

	// cells contain no particles
	for (int Icell = 0; Icell < Ncell; ++Icell) head[Icell]=-1;
	// put particles in cell
	int Icell;
	for (int Ipart = 0; Ipart < Npart; ++Ipart){
		Icell = this->index(particles[Ipart].r); // cell of particles[Ipart]
		mycell[Ipart]=Icell; // assign cell to the particle
		next[Ipart]=head[Icell]; // next[particle] are in the cell
		head[Icell]=Ipart; // assign first particle in the cell
	}

}

void rebuild(Particle *particles){ build(particles); }

// takes particle Ipart away from its old cell and puts it in its new cell 
void rebuild(int Ipart, int NewCell){
	int OldCell=mycell[Ipart], Jpart=head[OldCell];
	// Jpart is the first particle in OldCell
	
	if(Jpart==Ipart) // if Ipart is be the first element
		head[OldCell]=next[Ipart]; // take away Ipart from the cell OldCell
	else{ 
		while(next[Jpart]!=Ipart) Jpart=next[Jpart]; // otherwhise find Ipart
		next[Jpart]=next[Ipart]; // and take away Ipart from the cell OldCell
	}	
	// to finish, put Ipart in the cell NewCell
	next[Ipart]=head[NewCell]; head[NewCell]=Ipart; mycell[Ipart]=NewCell;	
}

// check if particle Ipart has any overlap
bool overlap(Particle* particles, int Ipart, Particle &particle) {      
  int Jpart, Icell=this->index(particle.r);
  // LOOP OVER ALL MOLECULES EXCEPT I  
  for (int nn = 0; nn < Nneigh; ++nn) {
  	Jpart = head[neigh[Icell][nn]];
  	while(Jpart>=0){ // check linked list is not empty
  		if(Jpart!=Ipart)
  			if ( overlap(particle,particles[Jpart], L) ) return true;
  		Jpart=next[Jpart];
  	}// particles in the neigbours of Icell
  }// neighbours of Icell
  
  return false;
}


}; // end class LLcells2d


#endif /*LLCELLS2D_H_*/
