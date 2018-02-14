#include <SimPar.h>

void SimPar::init(int argc, char** argv){
	if(argc>2) Nterm=atoi(argv[2]); else Nterm=1000;
	if(argc>3) Nstep=atoi(argv[3]); else Nstep=1000;
	if(argc>4) Iprint=atoi(argv[4]); else Iprint=100;
	if(argc>5) Isave=atoi(argv[5]); else Isave=10000;
	if(argc>6) Icounter=atoi(argv[6]); else Icounter=100;
	target_ratio=0.4;
}

void SimPar::adjust_acceptance() {

    ratio = moves_acc / moves;
    if ( ratio > target_ratio) MaxDisp *= 1.05;
    else MaxDisp *= 0.95;
//    if(Dmax>L/2) Dmax=L/2;
    moves_acc = moves = 0.0;

    big_ratio = big_moves_acc / big_moves;
    if ( big_ratio > big_target_ratio) BigMaxDisp *= 1.05;
    else BigMaxDisp *= 0.95;
//    if(Dmax>L/2) Dmax=L/2;
    big_moves_acc = big_moves = 0.0;

}
