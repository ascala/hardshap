/*

    Copyright 2007, Antonio Scala

    This file is part of HardShap, "Simulation of Hard Shaped Particles".

    HardShaP is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HardShaP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HardShaP.  If not, see <http://www.gnu.org/licenses/>.

*/


#include <Vec3d.h>

void Vec3d::InBox(const double L)
	{ x -= L*rint(x/L); y -= L*rint(y/L); z -= L*rint(z/L); }

void Vec3d::InBox(const Vec3d &L)
	{ x -= L.x*rint(x/L.x); y -= L.y*rint(y/L.y); z -= L.z*rint(z/L.z); }

void Vec3d::RandDispl(const double Dmax)
	{x += (drand48() - 0.5 )*Dmax; y += (drand48() - 0.5 )*Dmax; z += (drand48() - 0.5 )*Dmax;}

void Vec3d::RandDispl(const Vec3d &Dmax)
	{x += (drand48() - 0.5 )*Dmax.x; y += (drand48() - 0.5 )*Dmax.y; z += (drand48() - 0.5 )*Dmax.z;}

void Vec3d::Randomize(const double L)
	{ x = (2*drand48()-1)*L; y = (2*drand48()-1)*L; z = (2*drand48()-1)*L; }

void Vec3d::Randomize(const Vec3d &L)
	{ x = (2*drand48()-1)*L.x; y = (2*drand48()-1)*L.y; z = (2*drand48()-1)*L.z; }

void Vec3d::Gaussian(const double sigma) { x = gaussdev()*sigma; y = gaussdev()*sigma; z = gaussdev()*sigma; }

void Vec3d::Gaussian(const Vec3d &sigma) { x = gaussdev()*sigma.x; y = gaussdev()*sigma.y; z = gaussdev()*sigma.z; }


