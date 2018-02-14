#ifndef _PARAM_H_
#define _PARAM_H_

#include <vector2d.h>

class SimPar {
public:

	Vec2d MaxDisp; /* MC diplacements*/	
	Vec2d MaxRot;  /* MC rotations*/	

	double moves;      // accumulator - counts the # of moves
	double moves_acc;   //      "      - # of accepted moves  ; 
	double ratio;    // fraction of accepted moves in IRATIO steps
	double target_ratio;   

    /* cycles of simulation */

	int Nterm;    // number of thermalization steps
	int Nstep;    // number of simulation steps 

	int Iprint;   // prints info's every IPRINT  steps
	int Isave;    // saves the conf   "  ISAVE     "       
	int Icounter; // checks MaxDisp   "  Icounter  "

	SimPar(): moves(0), moves_acc(0){}

//prototypes
	
	void init(int argc, char** argv);
	void adjust_acceptance();
	
};



#endif //_PARAM_H_
