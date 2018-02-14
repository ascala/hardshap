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

#ifdef _HAVE_PETE_
#include <vector2dPETE.h>
#else

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>
#include <cmath>

extern "C" {
#include <gaussdev.h>
}

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
    vector2d(vector2d const& vv){vec[0]=vv.vec[0]; vec[1]=vv.vec[1];}
    ~vector2d() {}

  	T &operator[](int i)      { return vec[i]; }
  	T operator[](int i) const { return vec[i]; }

    //	stream operators
    template<class U> friend std::ostream& 
    operator<<(std::ostream& pStr, const vector2d<U>& pV);

    template<class U> friend std::istream& 
    operator>>(std::istream& pStr, const vector2d<U>& pV);


    // vector product/divisions (* is not the dot product !!!)
    vector2d operator*(vector2d const& vv) const {
        vector2d out( vec[0]*vv.vec[0], vec[1]*vv.vec[1] );
        return out;
    }
    vector2d operator/(vector2d const& vv) const {
        vector2d out( vec[0]/vv.vec[0], vec[1]/vv.vec[1] );
        return out;
    }
    vector2d& operator*=(vector2d const& vv) {
        vec[0]*=vv.vec[0];
        vec[1]*=vv.vec[1];
        return *this;
    }
    vector2d& operator/=(vector2d const& vv) {
        vec[0]/=vv.vec[0];
        vec[1]/=vv.vec[1];
        return *this;
    }

    vector2d operator%(vector2d<int> const& vv) const { vector2d<int> out( vec[0]%vv.vec[0], vec[1]%vv.vec[1] ); return out; }
    vector2d& operator%=(vector2d<int> const& vv) { vec[0]%=vv.vec[0]; vec[1]%=vv.vec[1]; return *this; }

    // mapping to a lattice
    int index(vector2d<int> const &L) { return vec[0] + vec[1] * L.vec[0]; }
    vector2d from_index(int ind, vector2d<int> const &L) { 
    	vector2d vv; vv.vec[0] = ind % L.vec[0]; ind /= L.vec[0]; vv.vec[1] = ind; 
        return vv;
    }


    // assignment (overloading =)
    vector2d &operator=(vector2d const& other) {
        if (this != &other) {  vec[0] = other.vec[0]; vec[1] = other.vec[1]; }
        return *this;
    }

    // vector sum
    vector2d &operator+=(vector2d const& other) { vec[0]+=other.vec[0]; vec[1]+=other.vec[1]; return *this; }
    vector2d const operator+(void) { return vector2d(vec[0],vec[1]); }
    vector2d const operator+(vector2d const& rvalue) { return vector2d(vec[0]+rvalue.vec[0],vec[1]+rvalue.vec[1]); }
    template <class U>
    friend vector2d<U> const operator+(vector2d<U> const &l_hand, vector2d<U> const &r_hand);

    // vector difference
    vector2d &operator-=(vector2d const& other) { vec[0]-=other.vec[0]; vec[1]-=other.vec[1]; return *this; }

    vector2d const operator-(void) { return vector2d(-vec[0],-vec[1]); }

    vector2d const operator-(vector2d const& rvalue) { return vector2d(vec[0]-rvalue.vec[0],vec[1]-rvalue.vec[1]); }
    template <class U>
    friend vector2d<U> const operator-(vector2d<U> const& l_hand, vector2d<U> const& r_hand);

    // dot product (NO * OVERLOADING) and norm
    T dot(const vector2d& rvalue) { return vec[0]*rvalue.vec[0]+vec[1]*rvalue.vec[1]; }
    friend T dot(const vector2d& a,const vector2d& b) { return a.vec[0]*b.vec[0]+a.vec[1]*b.vec[1]; }

	// cross product
    T cross(const vector2d& rvalue) { return vec[0]*rvalue.vec[1]-vec[1]*rvalue.vec[0]; }
    friend T cross(const vector2d& a,const vector2d& b) { return a.vec[0]*b.vec[1]-a.vec[1]*b.vec[0]; }

    // normalization
    T norm(void) { return sqrt(vec[0]*vec[0]+vec[1]*vec[1]); }
    T norm2(void) { return vec[0]*vec[0]+vec[1]*vec[1]; }
    T normalize(void) { T n=sqrt(vec[0]*vec[0]+vec[1]*vec[1]); vec[0]/=n; vec[1]/=n; return n; }
    T norm(const vector2d& a) { return sqrt(a.vec[0]*a.vec[0]+a.vec[1]*a.vec[1]); }

    // multiplication by a scalar
    template <class U> friend vector2d<U> const operator*(U const &l_hand, vector2d<U> const& r_hand);
    template <class U> friend vector2d<U> const operator*(vector2d<U> const& l_hand, U const &r_hand);
    vector2d const operator*=(T const &scalar) { vec[0]*=scalar; vec[1]*=scalar; return *this; }

    // division by a scalar
    template <class U> friend vector2d<U> const operator/(vector2d<U> const& l_hand, U const &r_hand);
    vector2d const operator/=(T const &scalar) { vec[0]/=scalar; vec[1]/=scalar; return *this; }

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


    // "area"
    T const area() {
        return vec[0]*vec[1];
    }


    // 2d rotations
    void rotate(T const angle) {
        T sa=sin(angle), ca=cos(angle);
        T xr(ca*vec[0] + sa*vec[1]), yr(-sa*vec[0] + ca*vec[1]);
        vec[0]=xr;
        vec[1]=yr;
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
};

//	friend functions and operators
template<class T>
std::ostream& operator<<(std::ostream& pStr, const vector2d<T>& pV) {
    return (pStr <<  pV.vec[0] <<" "<< pV.vec[1]);
}

template<class T>
std::istream& operator>>(std::istream &pStr, vector2d<T>& pV) {
    return (pStr >> pV.vec[0] >> pV.vec[1] );
}


template <class T>
vector2d<T> const operator*(T const &l_hand, vector2d<T> const& r_hand) {
    return vector2d<T>(l_hand*r_hand.vec[0],l_hand*r_hand.vec[1]);
}

template <class T>
vector2d<T> const operator*(vector2d<T> const& l_hand, T const &r_hand) {
    return vector2d<T>(l_hand.vec[0]*r_hand,l_hand.vec[1]*r_hand);
}

template <class T>
vector2d<T> const operator/(vector2d<T> const& l_hand, T const &r_hand) {
    return vector2d<T>(l_hand.vec[0]/r_hand,l_hand.vec[1]/r_hand);
}

template <class T>
vector2d<T> const operator+(vector2d<T> const &l_hand, vector2d<T> const &r_hand) {
    return vector2d<T>(l_hand) += r_hand;
}

template <class T>
vector2d<T> const operator-(vector2d<T> const& l_hand, vector2d<T> const& r_hand) {
    return vector2d<T>(l_hand) -= r_hand;
}

template <class T>
bool const operator==(vector2d<T> const& l_hand, vector2d<T> const& r_hand) {
    return vector2d<T>(l_hand)==r_hand;
}

template <class T>
bool const operator!=(vector2d<T> const& l_hand, vector2d<T> const& r_hand) {
    return vector2d<T>(l_hand)!=r_hand;
}

#endif /*VECTOR2D_H_*/


#endif // _HAVE_PETE_
