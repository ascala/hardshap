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


#include <IVec3d.h>


IVec3d IVec3d::from_index(int ind, IVec3d &L){
	IVec3d vec;
	vec.x = ind % L.x; ind /= L.x;
	vec.y = ind % L.y; ind /= L.y;
	vec.z = ind; //vec.z = ind % L.z;
	return vec;
}

