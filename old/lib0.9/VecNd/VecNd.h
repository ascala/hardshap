#ifndef VECND_H_
#define VECND_H_

#include <iostream>
#include <cmath>

extern "C" {
#include <gaussdev.h>
}

/*	
// rem: redefine % for float and double to get periodic conditions
inline double const operator%(double const &x, double const &L)
{return L*rint(x/L);}
*/

template <int D=2, typename T=double>
class VecNd
{
public:
	T x[D];
	
// constructors / destructors
	VecNd();
	VecNd(T const scalar);
	VecNd(T const array[D]);
	VecNd(VecNd<D,T> const &vector);
	virtual ~VecNd();

// [] 
  	T& operator[](const unsigned int index);
	
//	stream operators
//	friend std::ostream& operator<<(std::ostream& pStr, VecNd<D,T> const& pV);
//	friend std::istream& operator>>(std::istream pStr, VecNd<D,T>& pV);

// assignment (overloading =)
//	VecNd<D,T> &operator=(VecNd<D,T> const &vector);

//unary +,-	
	VecNd<D,T> const operator+(void); 
	VecNd<D,T> const operator-(void); 

// +=,-=,*=,/=,%=
	VecNd<D,T> &operator+=(VecNd<D,T> const &vector);
	VecNd<D,T> &operator-=(VecNd<D,T> const &vector);
	VecNd<D,T> &operator*=(VecNd<D,T> const &vector);
	VecNd<D,T> &operator/=(VecNd<D,T> const &vector);
	VecNd<D,T> &operator%=(VecNd<D,T> const &vector);

// +,-,*,/,%
	VecNd<D,T> const operator+(VecNd<D,T> const &rvalue); // asymmetrical 
	VecNd<D,T> const operator-(VecNd<D,T> const &rvalue); // asymmetrical 
	VecNd<D,T> const operator*(VecNd<D,T> const &rvalue); // asymmetrical 
	VecNd<D,T> const operator/(VecNd<D,T> const &rvalue); // asymmetrical 
	VecNd<D,T> const operator%(VecNd<D,T> const &rvalue); // asymmetrical 

//	template <int D, typename T> friend VecNd<D,T> const operator+(VecNd<D,T> const &lvalue, VecNd<D,T> const &rvalue);
//	friend VecNd<D,T> const operator-(VecNd<D,T> const &lvalue, VecNd<D,T> const &rvalue);
//	friend VecNd<D,T> const operator*(VecNd<D,T> const &lvalue, VecNd<D,T> const &rvalue);
//	friend VecNd<D,T> const operator/(VecNd<D,T> const &lvalue, VecNd<D,T> const &rvalue);
//	friend VecNd<D,T> const operator%(VecNd<D,T> const &lvalue, VecNd<D,T> const &rvalue);
	
// dot product and norm
	T dot(VecNd<D,T> const& rvalue);
	T norm(void);
	T norm2(void);
	void normalize(void);
	
// overloading scalar operations

//	friend VecNd<D,T> const operator*(T const &lvalue, VecNd<D,T> const& rvalue);
//	friend VecNd<D,T> const operator*(VecNd<D,T> const& lvalue, T const &rvalue);
	VecNd<D,T> operator+=(T const scalar);
	VecNd<D,T> operator-=(T const scalar);
	VecNd<D,T> operator*=(T const scalar);
//	friend VecNd<D,T> const operator/(VecNd<D,T> const& lvalue, T const &rvalue);
	VecNd<D,T> operator/=(T const scalar);
	VecNd<D,T> operator%=(T const scalar);


// equality & inequality
	bool const operator==(VecNd<D,T> const& rvalue); // asymmetrical 
//	friend bool const operator==(VecNd<D,T> const& lvalue, VecNd<D,T> const& rvalue);
	bool const operator!=(VecNd<D,T> const& rvalue); // asymmetrical 
//	friend bool const operator!=(VecNd<D,T> const& lvalue, VecNd<D,T> const& rvalue);

		
// random vectors
	void rnd(void);
	void rnd(T const scalar);
	void rnd(T const array[D]);
	void rnd(VecNd<D,T> const &vector);

	void gauss(void);
	void gauss(T const scalar);
	void gauss(T const array[D]);
	void gauss(VecNd<D,T> const &vector);


// periodic boundaries 
	void in_box(void);
	void in_box(T const scalar);
	void in_box(T const array[D]);
	void in_box(VecNd<D,T> const &vector);

};


// constructors

template <int D,typename T> 
VecNd<D,T>::VecNd() 
{for(int k=0;k<D;k++) x[k]=0;}

template <int D,typename T> 
VecNd<D,T>::VecNd(T const scalar) 
{for(int k=0;k<D;k++) x[k]=scalar;}

template <int D,typename T> 
VecNd<D,T>::VecNd(const T vector[D])
{for(int k=0;k<D;k++) x[k]=vector[k];}

template <int D,typename T> 
VecNd<D,T>::VecNd(VecNd<D,T> const &vector)
{for(int k=0;k<D;k++) x[k]=vector.x[k];}

template <int D,typename T> 
VecNd<D,T>::~VecNd() {}


// []
template <int D,typename T>
inline T& VecNd<D,T>::operator[](const unsigned int index){return x[index];}


//	stream operators

template <int D,typename T> 
std::ostream& operator<<(std::ostream& pStr, VecNd<D,T> const& pV)
{ 
	pStr << '('; 
	for(int k=0;k<D-1;k++) pStr << pV.x[k] << ',';
	return (pStr << pV.x[D-1] << ')'); 
}

template <int D,typename T> 
std::istream& operator>>(std::istream pStr, VecNd<D,T>& pV)
{ 
	for(int k=0;k<D;k++) pStr >> pV.x[k];
	return pStr; 
}


// assignment (overloading =)	VecNd(T const[D]);

/*
template <int D,typename T>
inline VecNd<D,T> & VecNd<D,T>::operator=(VecNd<D,T> const &vector)
{
	if (this != &vector) for(int k=0;k<D;k++) x[k]=vector.x[k];
	return *this;
}
*/


// unary + , - operator

template <int D,typename T>
inline VecNd<D,T> const VecNd<D,T>::operator+(void)
{return VecNd<D,T>(x);}

template <int D,typename T>
inline VecNd<D,T> const VecNd<D,T>::operator-(void)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = -x[k];
	return res; 
}

// += , -= , *= , /= , %=

template <int D,typename T>
inline VecNd<D,T> & VecNd<D,T>::operator+=(VecNd<D,T> const &vector)
{for(int k=0;k<D;k++) x[k] += vector.x[k]; return *this;}

template <int D,typename T>
inline VecNd<D,T> & VecNd<D,T>::operator-=(VecNd<D,T> const &vector)
{for(int k=0;k<D;k++) x[k] -= vector.x[k]; return *this;}

template <int D,typename T>
inline VecNd<D,T> & VecNd<D,T>::operator*=(VecNd<D,T> const &vector)
{for(int k=0;k<D;k++) x[k] *= vector.x[k]; return *this;}

template <int D,typename T>
inline VecNd<D,T> & VecNd<D,T>::operator/=(VecNd<D,T> const &vector)
{for(int k=0;k<D;k++) x[k] /= vector.x[k]; return *this;}

template <int D,typename T>
inline VecNd<D,T> & VecNd<D,T>::operator%=(VecNd<D,T> const &vector)
{for(int k=0;k<D;k++) x[k] %= vector.x[k]; return *this;}


// + , - , *, /, %
template <int D,typename T>
inline VecNd<D,T> const VecNd<D,T>::operator+(VecNd<D,T> const& rvalue)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = x[k]+rvalue.x[k];
	return res; 
}

template <int D,typename T>
inline VecNd<D,T> const VecNd<D,T>::operator-(VecNd<D,T> const& rvalue)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = x[k]-rvalue.x[k];
	return res; 
}

template <int D,typename T>
inline VecNd<D,T> const VecNd<D,T>::operator*(VecNd<D,T> const& rvalue)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = x[k]*rvalue.x[k];
	return res; 
}

template <int D,typename T>
inline VecNd<D,T> const VecNd<D,T>::operator/(VecNd<D,T> const& rvalue)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = x[k]/rvalue.x[k];
	return res; 
}

template <int D,typename T>
inline VecNd<D,T> const VecNd<D,T>::operator%(VecNd<D,T> const& rvalue)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = x[k]%rvalue.x[k];
	return res; 
}

// friend + , - , *, /, % (left hand operators)

template <int D,typename T>
inline VecNd<D,T> const operator+(VecNd<D,T> const &lvalue, VecNd<D,T> const &rvalue)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = lvalue.x[k]+rvalue.x[k];
	return res; 
}

template <int D,typename T>
inline VecNd<D,T> const operator-(VecNd<D,T> const &lvalue, VecNd<D,T> const &rvalue)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = lvalue.x[k]-rvalue.x[k];
	return res; 
}

template <int D,typename T>
inline VecNd<D,T> const operator*(VecNd<D,T> const &lvalue, VecNd<D,T> const &rvalue)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = lvalue.x[k]*rvalue.x[k];
	return res; 
}

template <int D,typename T>
inline VecNd<D,T> const operator/(VecNd<D,T> const &lvalue, VecNd<D,T> const &rvalue)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = lvalue.x[k]/rvalue.x[k];
	return res; 
}

template <int D,typename T>
inline VecNd<D,T> const operator%(VecNd<D,T> const &lvalue, VecNd<D,T> const &rvalue)
{ 
	VecNd<D,T> res; 
	for(int k=0;k<D;k++) res.x[k] = lvalue.x[k]%rvalue.x[k];
	return res; 
}


// dot product and norm

template <int D,typename T> 
inline T VecNd<D,T>::dot(VecNd<D,T> const& rvalue)
{ T d=0; for(int k=0;k<D;k++) d+=x[k]*rvalue.x[k]; return d;}

template <int D,typename T> 
inline T VecNd<D,T>::norm2(void)
{ T d=0; for(int k=0;k<D;k++) d+=x[k]*x[k]; return d; }

template <int D,typename T> 
inline T VecNd<D,T>::norm(void)
{ T d=0; for(int k=0;k<D;k++) d+=x[k]*x[k]; return sqrt(d); }

template <int D,typename T>
inline void VecNd<D,T>::normalize(void) 
{ 
	T d=0; 
	for(int k=0;k<D;k++) d+=x[k]*x[k];
	d=sqrt(d); 
	for(int k=0;k<D;k++) x[k]/=d;
}

// overloading scalar operations

//+,+=
template <int D,typename T>
inline VecNd<D,T> const operator+(T const &lvalue, VecNd<D,T> const& rvalue) // friend *
{ 
	VecNd<D,T> res;
	for(int k=0;k<D;k++) res.x[k]= lvalue+rvalue.x[k];
	return res;
} 
template <int D,typename T>
inline VecNd<D,T> const operator+(VecNd<D,T> const& lvalue, T const &rvalue) // friend *
{ 
	VecNd<D,T> res;
	for(int k=0;k<D;k++) res.x[k]= lvalue.x[k]+rvalue;
	return res;
}  
template <int D,typename T>
inline VecNd<D,T> VecNd<D,T>::operator+=(T const scalar) 
{ for(int k=0;k<D;k++) x[k]+=scalar; return *this; } 

// -,-=
template <int D,typename T>
inline VecNd<D,T> const operator-(T const &lvalue, VecNd<D,T> const& rvalue) // friend *
{ 
	VecNd<D,T> res;
	for(int k=0;k<D;k++) res.x[k]= lvalue-rvalue.x[k];
	return res;
} 
template <int D,typename T>
inline VecNd<D,T> const operator-(VecNd<D,T> const& lvalue, T const &rvalue) // friend *
{ 
	VecNd<D,T> res;
	for(int k=0;k<D;k++) res.x[k]= lvalue.x[k]-rvalue;
	return res;
} 
template <int D,typename T>
inline VecNd<D,T> VecNd<D,T>::operator-=(T const scalar) 
{ for(int k=0;k<D;k++) x[k]-=scalar; return *this; } 

//*,*=
template <int D,typename T>
inline VecNd<D,T> const operator*(T const &lvalue, VecNd<D,T> const& rvalue) // friend *
{ 
	VecNd<D,T> res;
	for(int k=0;k<D;k++) res.x[k]= lvalue*rvalue.x[k];
	return res;
} 

template <int D,typename T>
inline VecNd<D,T> const operator*(VecNd<D,T> const& lvalue, T const &rvalue) // friend *
{ 
	VecNd<D,T> res;
	for(int k=0;k<D;k++) res.x[k]= lvalue.x[k]*rvalue;
	return res;
} 
 
template <int D,typename T>
inline VecNd<D,T> VecNd<D,T>::operator*=(T const scalar) 
{ for(int k=0;k<D;k++) x[k]*=scalar; return *this; } 

// /,/=
template <int D,typename T>
inline VecNd<D,T> const operator/(VecNd<D,T> const& lvalue, T const &rvalue) // friend *
{ 
	VecNd<D,T> res;
	for(int k=0;k<D;k++) res.x[k]= lvalue[k]/rvalue;
	return res;
} 
template <int D,typename T>
inline VecNd<D,T> VecNd<D,T>::operator/=(T const scalar) 
{ for(int k=0;k<D;k++) x[k]/=scalar; return *this; } 

// %,%=
template <int D,typename T>
inline VecNd<D,T> const operator%(VecNd<D,T> const& lvalue, T const &rvalue) // friend *
{ 
	VecNd<D,T> res;
	for(int k=0;k<D;k++) res.x[k]= lvalue[k]%rvalue;
	return res;
} 
template <int D,typename T>
inline VecNd<D,T> VecNd<D,T>::operator%=(T const scalar) 
{ for(int k=0;k<D;k++) x[k]%=scalar; return *this; } 

// equality & inequality
template <int D,typename T>
inline bool const VecNd<D,T>::operator==(VecNd<D,T> const &rvalue)
{ for(int k=0;k<D;k++) if (x[k]!=rvalue.x[k]) return false; return true;}

template <int D,typename T>
inline bool const operator==(VecNd<D,T> const& lvalue, VecNd<D,T> const& rvalue)
{ for(int k=0;k<D;k++) if (lvalue.x[k]!=rvalue.x[k]) return false; return true; }

template <int D,typename T>
inline bool const VecNd<D,T>::operator!=(VecNd<D,T> const &rvalue)
{ for(int k=0;k<D;k++) if (x[k]!=rvalue.x[k]) return true; return false;}

template <int D,typename T>
inline bool const operator!=(VecNd<D,T> const& lvalue, VecNd<D,T> const& rvalue)
{ for(int k=0;k<D;k++) if (lvalue.x[k]!=rvalue.x[k]) return true; return false; }


// random vectors

template <int D,typename T>
inline void  VecNd<D,T>::rnd(void)
{for(int k=0;k<D;k++) x[k]=drand48();}

template <int D,typename T>
inline void VecNd<D,T>::rnd(T const scalar)
{for(int k=0;k<D;k++) x[k]=scalar*(2*drand48()-1);}

template <int D,typename T>
inline void VecNd<D,T>::rnd(T const array[D])
{for(int k=0;k<D;k++) x[k]=array[k]*(2*drand48()-1);}

template <int D,typename T>
inline void VecNd<D,T>::rnd(VecNd<D,T> const &vector)
{for(int k=0;k<D;k++) x[k]=vector.x[k]*(2*drand48()-1);}
	
	

template <int D,typename T>
inline void VecNd<D,T>::gauss(void)
{for(int k=0;k<D;k++) x[k]=gaussdev();}

template <int D,typename T>
inline void VecNd<D,T>::gauss(T const scalar)
{for(int k=0;k<D;k++) x[k]=scalar*gaussdev();}

template <int D,typename T>
inline void VecNd<D,T>::gauss(T const array[D])
{for(int k=0;k<D;k++) x[k]=array[k]*gaussdev();}
		
template <int D,typename T>
inline void VecNd<D,T>::gauss(VecNd<D,T> const &vector)
{for(int k=0;k<D;k++) x[k]=vector.x[k]*gaussdev();}
		
// periodic boundaries

template <int D,typename T>
inline void VecNd<D,T>::in_box(void)
{for(int k=0;k<D;k++) x[k]-=rint(x[k]);}

template <int D,typename T>
inline void VecNd<D,T>::in_box(T const L)
{for(int k=0;k<D;k++) x[k]-=L*rint(x[k]/L);}

template <int D,typename T>
inline void VecNd<D,T>::in_box(T const L[D])
{for(int k=0;k<D;k++) x[k]-=L[k]*rint(x[k]/L[k]);}

template <int D,typename T>
inline void VecNd<D,T>::in_box(VecNd<D,T> const &L)
{for(int k=0;k<D;k++) x[k]-=L.x[k]*rint(x[k]/L.x[k]);}

// bynary norm,dot

template <int D,typename T>
inline T const norm(VecNd<D,T> const& v)
{return v.norm();}

template <int D,typename T>
inline T const norm2(VecNd<D,T> const& v)
{return v.norm2();}

template <int D,typename T>
inline T const dot(VecNd<D,T> const& v,VecNd<D,T> const& u)
{return v.dot(u);}




#endif /*VECND_H_*/
