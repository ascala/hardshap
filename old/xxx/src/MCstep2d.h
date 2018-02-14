#ifndef MCSTEP2D_H_
#define MCSTEP2D_H_

#include <SimBox2d.h>
#include <LLcells2d.h>

void NVT_MCstep(SimBox2d &box);

template <class Particle>
void NVT_MCstep(SimBox2d &box, LLcells2d<Particle> &cells);

#endif /*MCSTEP2D_H_*/
