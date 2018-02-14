/*
 
Copyright 2007, Antonio Scala
 
This file is part of HardShap, "Simulation of Hard Shaped Particles".
 
HardShaP is free software:
you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
HardShaP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY;
without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with HardShaP.  If not, see <http://www.gnu.org/licenses/>.
 
*/

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>
#include <cmath>

extern "C" {
#include <gaussdev.h>
}


#include <PETE/PETE.h>


template <class T> class vector2d;
typedef vector2d<double> Vec2d ;
typedef vector2d<int> IVec2d ;

template <class T>
class vector2d {
public:
    T vec[2];

    vector2d(){vec[0]=vec[1]=0;}
    vector2d(T const& v){vec[0]=vec[1]=v;}
    vector2d(T const& vx, T const& vy){vec[0]=vx; vec[1]=vy;}
    vector2d(vector2d const& other)
    	{vec[0]=other.vec[0]; vec[1]=other.vec[1];}
    template<class RHS>
    vector2d (const Expression<RHS> &rhs){
    	vec[0] = forEach(rhs, EvalLeaf1(0), OpCombine());
    	vec[1] = forEach(rhs, EvalLeaf1(1), OpCombine());
    }


    ~vector2d() {}

    // assignment (overloading =)
    vector2d &operator=(vector2d const& other) {
        if (this != &other) {  vec[0] = other.vec[0]; vec[1] = other.vec[1]; }
        return *this;
    }

    vector2d &operator=(T const& c) {
    	vec[0] = vec[1] = c; 
        return *this;
    }

  // Assignment operator taking expression:
  //---------------------------------------------------------------------------

  template<class RHS>
  vector2d &operator=(const Expression<RHS> &rhs)
  {
    vec[0] = forEach(rhs, EvalLeaf1(0), OpCombine());
    vec[1] = forEach(rhs, EvalLeaf1(1), OpCombine());
    return *this;
  }

    // dot product (NO * OVERLOADING) and norm
    T dot(const vector2d& rvalue) { return vec[0]*rvalue.vec[0]+vec[1]*rvalue.vec[1]; }

    template<class RHS>     
    T dot(const Expression<RHS>& rhs) { 
    	return vec[0]*forEach(rhs, EvalLeaf1(0), OpCombine())
    	+vec[1]*forEach(rhs, EvalLeaf1(1), OpCombine()); 
    }

    friend T dot(const vector2d& a,const vector2d& b)
    {return a.vec[0]*b.vec[0]+a.vec[1]*b.vec[1]; }

    template<class RHS>     
    friend T dot(const Expression<RHS>& a,const Expression<RHS>& b) { 
    	return forEach(a, EvalLeaf1(0), OpCombine())*forEach(b, EvalLeaf1(0), OpCombine())
    	+forEach(b, EvalLeaf1(1), OpCombine())*forEach(b, EvalLeaf1(1), OpCombine()); 
    }

    // normalization
    T norm(void) { return sqrt(vec[0]*vec[0]+vec[1]*vec[1]); }
    T norm2(void) { return vec[0]*vec[0]+vec[1]*vec[1]; }
    T normalize(void) { T n=sqrt(vec[0]*vec[0]+vec[1]*vec[1]); vec[0]/=n; vec[1]/=n; return n; }


  //---------------------------------------------------------------------------
  // Indexing operators
  //---------------------------------------------------------------------------

  T &operator[](int i)      { return vec[i]; }
  T operator[](int i) const { return vec[i]; }

    //	stream operators
    template<class U> friend std::ostream& 
    operator<<(std::ostream& pStr, const vector2d<U>& pV);

	template<class RHS> friend std::ostream& operator
	<<(std::ostream& pStr, const Expression<RHS> &rhs);


    template<class U> friend std::istream& 
    operator>>(std::istream& pStr, const vector2d<U>& pV);

	// ?= with ?=*,/,-,+,...
	vector2d& operator+=(T const& v) 
    { vec[0]+=v; vec[1]+=v; return *this; }
	vector2d& operator-=(T const& v) 
    { vec[0]-=v; vec[1]-=v; return *this; }
	vector2d& operator*=(T const& v) 
    { vec[0]*=v; vec[1]*=v; return *this; }
	vector2d& operator/=(T const& v) 
    { vec[0]/=v; vec[1]/=v; return *this; }
	vector2d<int>& operator%=(int const& v) 
    { vec[0]%=v; vec[1]%=v; return *this; }

	vector2d& operator+=(vector2d const& other) 
    { vec[0]+=other.vec[0]; vec[1]+=other.vec[1]; return *this; }
	vector2d& operator-=(vector2d const& other) 
    { vec[0]-=other.vec[0]; vec[1]-=other.vec[1]; return *this; }
	vector2d& operator*=(vector2d const& other) 
    { vec[0]*=other.vec[0]; vec[1]*=other.vec[1]; return *this; }
	vector2d& operator/=(vector2d const& other) 
    { vec[0]/=other.vec[0]; vec[1]/=other.vec[1]; return *this; }
	vector2d<int>& operator%=(vector2d<int> const& other) 
    { vec[0]%=other.vec[0]; vec[1]%=other.vec[1]; return *this; }


#if 0
    vector2d<int> operator%(vector2d<int> const& other) 
    	const { vector2d<int> out( vec[0]%other.vec[0], vec[1]%other.vec[1] ); return out; }
    vector2d<int>& operator%=(vector2d<int> const& other) 
    	{ vec[0]%=other.vec[0]; vec[1]%=other.vec[1]; return *this; }
#endif

    // mapping to a lattice
    int index(vector2d<int> const &L) { return vec[0] + vec[1] * L.vec[0]; }
    vector2d<int> from_index(int ind, vector2d<int> const &L) { 
    	vector2d<int> other; 
    	other.vec[0] = ind % L.vec[0]; ind /= L.vec[0]; other.vec[1] = ind; 
        return other;
    }


    // periodic boundaries
    void in_box(void) {
        vec[0]-=rint(vec[0]);
        vec[1]-=rint(vec[1]);
    }
    void in_box(T const L) {
        vec[0]-=L*rint(vec[0]/L);
        vec[1]-=L*rint(vec[1]/L);
    }
    void in_box(T const Lx, T const Ly) {
        vec[0]-=Lx*rint(vec[0]/Lx);
        vec[1]-=Ly*rint(vec[1]/Ly);
    }
    void in_box(vector2d const L) {
        vec[0]-=L.vec[0]*rint(vec[0]/L.vec[0]);
        vec[1]-=L.vec[1]*rint(vec[1]/L.vec[1]);
    }
    
#if 0

    // equality & inequality
    bool const operator==(vector2d const &rvalue) {
        return ((vec[0]==rvalue.vec[0])&&(vec[1]==rvalue.vec[1]));
    }
    template <class U>
    friend bool const operator==(vector2d<U> const& l_hand, vector2d<U> const& r_hand);
    bool const operator!=(vector2d const &rvalue) {
        return ((vec[0]!=rvalue.vec[0])||(vec[1]!=rvalue.vec[1]));
    }
    template <class U>
    friend bool const operator!=(vector2d<U> const& l_hand, vector2d <U>const& r_hand);
#endif


    // cross product
    T const cross(vector2d const& other) {
        return vec[0]*other.vec[1]-vec[1]*other.vec[0];
    }

    // "area"
    T const area() {
        return vec[0]*vec[1];
    }

    // 2d rotations
    void rotate(T const angle) {
        T sa,ca; sincos(angle, &sa, &ca);
        T xr(ca*vec[0] + sa*vec[1]), yr(-sa*vec[0] + ca*vec[1]);
        vec[0]=xr; vec[1]=yr;
    }

    // random vectors
    void rnd(void) {
        vec[0]=drand48();
        vec[1]=drand48();
    }
    void rnd(T const s) {
        vec[0]=s*(2*drand48()-1);
        vec[1]=s*(2*drand48()-1);
    }
    void rnd(T const sx, T const sy) {
        vec[0]=sx*(2*drand48()-1);
        vec[1]=sy*(2*drand48()-1);
    }
    void rnd(vector2d const s) {
        vec[0]=s.vec[0]*(2*drand48()-1);
        vec[1]=s.vec[1]*(2*drand48()-1);
    }

    void gauss(void) {
        vec[0]=gaussdev();
        vec[1]=gaussdev();
    }
    void gauss(T const W) {
        vec[0]=W*gaussdev();
        vec[1]=W*gaussdev();
    }
    void gauss(vector2d const W) {
        vec[0]=W.vec[0]*gaussdev();
        vec[1]=W.vec[1]*gaussdev();
    }

    // random displacements
    void rnd_displ(void) {
        vec[0]+=drand48();
        vec[1]+=drand48();
    }
    void rnd_displ(T const s) {
        vec[0]+=s*(2*drand48()-1);
        vec[1]+=s*(2*drand48()-1);
    }
    void rnd_displ(T const sx, T const sy) {
        vec[0]+=sx*(2*drand48()-1);
        vec[1]+=sy*(2*drand48()-1);
    }
    void rnd_displ(vector2d const s) {
        vec[0]+=s.vec[0]*(2*drand48()-1);
        vec[1]+=s.vec[1]*(2*drand48()-1);
    }

    void gauss_displ(void) {
        vec[0]+=gaussdev();
        vec[1]+=gaussdev();
    }
    void gauss_displ(T const W) {
        vec[0]+=W*gaussdev();
        vec[1]+=W*gaussdev();
    }
    void gauss_displ(vector2d const W) {
        vec[0]+=W.vec[0]*gaussdev();
        vec[1]+=W.vec[1]*gaussdev();
    }


};



//	friend functions and operators
template<class T>
std::ostream& operator<<(std::ostream& pStr, const vector2d<T>& pV) {
    return (pStr <<  pV.vec[0] <<" "<< pV.vec[1]);
}

template<class RHS>
std::ostream& operator
	<<(std::ostream& pStr, const Expression<RHS> &rhs) {
    return (pStr <<  forEach(rhs, EvalLeaf1(0), OpCombine()) 
    	<<" "<< forEach(rhs, EvalLeaf1(1), OpCombine()) );
}

template<class T>
std::istream& operator>>(std::istream &pStr, vector2d<T>& pV) {
    return (pStr >> pV.vec[0] >> pV.vec[1] );
}

#if 0
template <class T>
bool const operator==(vector2d<T> const& l_hand, vector2d<T> const& r_hand) {
    return vector2d<T>(l_hand)==r_hand;
}

template <class T>
bool const operator!=(vector2d<T> const& l_hand, vector2d<T> const& r_hand) {
    return vector2d<T>(l_hand)!=r_hand;
}
#endif

//-----------------------------------------------------------------------------
// We need to specialize CreateLeaf<T> for our class, so that operators
// know what to stick in the leaves of the expression tree.
//-----------------------------------------------------------------------------

template <class T>
struct CreateLeaf< vector2d<T> >
{
  typedef Reference< vector2d<T> > Leaf_t;
  inline static
  Leaf_t make(const vector2d<T> &a) { return Leaf_t(a); }
};

//-----------------------------------------------------------------------------
// Specialization of LeafFunctor class for applying the EvalLeaf1
// tag to a vector2d. The apply method simply returns the array
// evaluated at the point.
//-----------------------------------------------------------------------------

template<class T>
struct LeafFunctor< vector2d<T>, EvalLeaf1>
{
  typedef T Type_t;
  static Type_t apply(const vector2d<T> &a, const EvalLeaf1 &f)
    { return a[f.val1()]; }
};


// We put this include at the end because
// the operators can't be defined until after vector2d and
// CreateLeaf<vector2d> have been defined.
// (Since vector2d isn't templated the operators aren't just
// templates.)

#include "vector2dOperators.h"


#endif /*VECTOR2D_H_*/
