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

template <class T> class vector2d;
typedef vector2d<double> Vec2d ;
typedef vector2d<int> IVec2d ;

template <class T>
class vector2d {
public:
    T x;
    T y;

    vector2d() :x(0),y(0) {}
    ~vector2d() {}

    //	stream operators
    template<class U>
    friend std::ostream& operator<<(std::ostream& pStr, const vector2d<U>& pV);
    template<class U>
    friend std::istream& operator>>(std::istream& pStr, const vector2d<U>& pV);

    vector2d(T const v) :x(v),y(v) {}

    vector2d(T const vx, T const vy) :x(vx),y(vy) {}

    vector2d(vector2d const & other) : x(other.x) , y(other.y) {}


    // vector product/divisions (* is not the dot product !!!)
    vector2d operator*(vector2d const& vec) const {
        vector2d out( x*vec.x, y*vec.y );
        return out;
    }
    vector2d operator/(vector2d const& vec) const {
        vector2d out( x/vec.x, y/vec.y );
        return out;
    }
    vector2d& operator*=(vector2d const& vec) {
        x*=vec.x;
        y*=vec.y;
        return *this;
    }
    vector2d& operator/=(vector2d const& vec) {
        x/=vec.x;
        y/=vec.y;
        return *this;
    }

    vector2d operator%(vector2d<int> const& vec) const { vector2d<int> out( x%vec.x, y%vec.y ); return out; }
    vector2d& operator%=(vector2d<int> const& vec) { x%=vec.x; y%=vec.y; return *this; }

    // mapping to a lattice
    int index(vector2d<int> const &L) { return x + y * L.x; }
    vector2d from_index(int ind, vector2d<int> const &L) { 
    	vector2d vec; vec.x = ind % L.x; ind /= L.x; vec.y = ind; 
        return vec;
    }


    // assignment (overloading =)
    vector2d &operator=(vector2d const& other) {
        if (this != &other) {  x = other.x; y = other.y; }
        return *this;
    }

    // vector sum
    vector2d &operator+=(vector2d const& other) { x+=other.x; y+=other.y; return *this; }
    vector2d const operator+(void) { return vector2d(x,y); }
    vector2d const operator+(vector2d const& rvalue) { return vector2d(x+rvalue.x,y+rvalue.y); }
    template <class U>
    friend vector2d<U> const operator+(vector2d<U> const &l_hand, vector2d<U> const &r_hand);

    // vector difference
    vector2d &operator-=(vector2d const& other) { x-=other.x; y-=other.y; return *this; }

    vector2d const operator-(void) { return vector2d(-x,-y); }

    vector2d const operator-(vector2d const& rvalue) { return vector2d(x-rvalue.x,y-rvalue.y); }
    template <class U>
    friend vector2d<U> const operator-(vector2d<U> const& l_hand, vector2d<U> const& r_hand);

    // dot product (NO * OVERLOADING) and norm
    T dot(const vector2d& rvalue) { return x*rvalue.x+y*rvalue.y; }

    // normalization
    T norm(void) { return sqrt(x*x+y*y); }
    T norm2(void) { return x*x+y*y; }
    T normalize(void) { T n=sqrt(x*x+y*y); x/=n; y/=n; return n; }

    // multiplication by a scalar
    template <class U> friend vector2d<U> const operator*(U const &l_hand, vector2d<U> const& r_hand);
    template <class U> friend vector2d<U> const operator*(vector2d<U> const& l_hand, U const &r_hand);
    vector2d const operator*=(T const &scalar) { x*=scalar; y*=scalar; return *this; }

    // division by a scalar
    template <class U> friend vector2d<U> const operator/(vector2d<U> const& l_hand, U const &r_hand);
    vector2d const operator/=(T const &scalar) { x/=scalar; y/=scalar; return *this; }

    // equality & inequality
    bool const operator==(vector2d const &rvalue) {
        return ((x==rvalue.x)&&(y==rvalue.y));
    }
    template <class U>
    friend bool const operator==(vector2d<U> const& l_hand, vector2d<U> const& r_hand);
    bool const operator!=(vector2d const &rvalue) {
        return ((x!=rvalue.x)||(y!=rvalue.y));
    }
    template <class U>
    friend bool const operator!=(vector2d<U> const& l_hand, vector2d <U>const& r_hand);

    // cross product
    T const cross(vector2d const& other) {
        return x*other.y-y*other.x;
    }

    // "area"
    T const area() {
        return x*y;
    }


    // 2d rotations
    void rotate(T const angle) {
        T sa=sin(angle), ca=cos(angle);
        T xr(ca*x + sa*y), yr(-sa*x + ca*y);
        x=xr;
        y=yr;
    }

    // random vectors
    void rnd(void) {
        x=drand48();
        y=drand48();
    }
    void rnd(T const s) {
        x=s*(2*drand48()-1);
        y=s*(2*drand48()-1);
    }
    void rnd(T const sx, T const sy) {
        x=sx*(2*drand48()-1);
        y=sy*(2*drand48()-1);
    }
    void rnd(vector2d const s) {
        x=s.x*(2*drand48()-1);
        y=s.y*(2*drand48()-1);
    }

    void gauss(void) {
        x=gaussdev();
        y=gaussdev();
    }
    void gauss(T const W) {
        x=W*gaussdev();
        y=W*gaussdev();
    }
    void gauss(vector2d const W) {
        x=W.x*gaussdev();
        y=W.y*gaussdev();
    }

    // random displacements
    void rnd_displ(void) {
        x+=drand48();
        y+=drand48();
    }
    void rnd_displ(T const s) {
        x+=s*(2*drand48()-1);
        y+=s*(2*drand48()-1);
    }
    void rnd_displ(T const sx, T const sy) {
        x+=sx*(2*drand48()-1);
        y+=sy*(2*drand48()-1);
    }
    void rnd_displ(vector2d const s) {
        x+=s.x*(2*drand48()-1);
        y+=s.y*(2*drand48()-1);
    }

    void gauss_displ(void) {
        x+=gaussdev();
        y+=gaussdev();
    }
    void gauss_displ(T const W) {
        x+=W*gaussdev();
        y+=W*gaussdev();
    }
    void gauss_displ(vector2d const W) {
        x+=W.x*gaussdev();
        y+=W.y*gaussdev();
    }

    // periodic boundaries
    void in_box(void) {
        x-=rint(x);
        y-=rint(y);
    }
    void in_box(T const L) {
        x-=L*rint(x/L);
        y-=L*rint(y/L);
    }
    void in_box(T const Lx, T const Ly) {
        x-=Lx*rint(x/Lx);
        y-=Ly*rint(y/Ly);
    }
    void in_box(vector2d const L) {
        x-=L.x*rint(x/L.x);
        y-=L.y*rint(y/L.y);
    }
};

//	friend functions and operators
template<class T>
std::ostream& operator<<(std::ostream& pStr, const vector2d<T>& pV) {
    return (pStr <<  pV.x <<" "<< pV.y);
}

template<class T>
std::istream& operator>>(std::istream pStr, vector2d<T>& pV) {
    return (pStr >> pV.x >> pV.y );
}

template <class T>
vector2d<T> const operator*(T const &l_hand, vector2d<T> const& r_hand) {
    return vector2d<T>(l_hand*r_hand.x,l_hand*r_hand.y);
}

template <class T>
vector2d<T> const operator*(vector2d<T> const& l_hand, T const &r_hand) {
    return vector2d<T>(l_hand.x*r_hand,l_hand.y*r_hand);
}

template <class T>
vector2d<T> const operator/(vector2d<T> const& l_hand, T const &r_hand) {
    return vector2d<T>(l_hand.x/r_hand,l_hand.y/r_hand);
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
