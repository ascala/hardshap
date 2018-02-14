#include <LLcells.h>



/*
  implementation of metropolis
*/

int ll_mc_sweep( Box *box , LList *llist, Counter *counter){
  
  int Ns=box->Ns,Nc=box->Nc; 
  Sphere* spheres=box->spheres; Sphere newsphere;
  Cap* caps=box->caps; Cap newcap;
  
  double Dmax, L=box->L; 	
  
  int Ncell=llist->Ncell, Nneigh=llist->Nneigh; 
  int *head=llist->head, *next=llist->next, *mycell=llist->mycell;
  int **neigh=llist->neigh;
  int icell;
   
  int           I, K;
  
  Dmax=box->DmaxS;
  for( K = 0; K < Ns; K++){
    
    I = drand48()*Ns; /* displace a sphere at random */
    copyS2S(&spheres[I],&newsphere);
    RandDisplS(&newsphere, Dmax, L);

    if( ll_some_overlapSS(box,llist,I,&newsphere) || some_overlapSC(box,&newsphere) ) {
    	counter->Smoves += 1.0; /* count number of moves */
    }
    else {
    	copyS2S(&newsphere,&spheres[I]);
		counter->Smoves_acc += 1.0; /* count number of accepted moves */
		counter->Smoves += 1.0; /* count number of moves */
		icell=S2ind(&newsphere,llist);
		if(icell!=mycell[I]) 
			reconstruct_llistSS(box,llist,I,icell);
	}

  } /* end Ns moves */

  Dmax=box->DmaxC;
  for( K = 0; K < Nc; K++){
    
    I = drand48()*Nc; /* displace a cap at random */
    copyC2C(&caps[I],&newcap);
    RandDisplC(&newcap, Dmax, L);
    
    if( some_overlapCC(box,I,&newcap) || some_overlapCS(box,&newcap) ) {
    	counter->Cmoves += 1.0; /* count number of moves */
    }
    else {
    	copyC2C(&newcap,&caps[I]);
		counter->Cmoves_acc += 1.0; /* count number of accepted moves */
		counter->Cmoves += 1.0; /* count number of moves */
	}

  } /* end Ns moves */

	return 0;
}

