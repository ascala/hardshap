#ifndef SE2D_OVERLAP_H_
#define SE2D_OVERLAP_H_

#include <se2d.h>

// Oriented Bounding Boxes
template <class ConvexWithAxis>
bool OBBoverlap(ConvexWithAxis const & R1, ConvexWithAxis const & R2){
	Vec2d r12(R2.r-R1.r); 
	
	Vec2d A,B,C,D;
	double proj,left,right,delta;
	
	A = R2.a.x*R2.u[0]+R2.a.y*R2.u[1]; B = -R2.a.x*R2.u[0]+R2.a.y*R2.u[1];
	C = R2.a.x*R2.u[0]-R2.a.y*R2.u[1]; D = -R2.a.x*R2.u[0]-R2.a.y*R2.u[1];
	
	proj=left=right=A*R1.u[0];
	proj=B*R1.u[0]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=C*R1.u[0]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=D*R1.u[0]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	delta=r12*R1.u[0]; left+=delta; right+=delta;
//	if(!intersect(left,right,-R1.a.x,R1.a.x)) return false;
	if( (left>R1.a.x)||(right<-R1.a.x) ) return false;
	
	proj=left=right=A*R1.u[1];
	proj=B*R1.u[1]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=C*R1.u[1]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=D*R1.u[1]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	delta=r12*R1.u[1]; left+=delta; right+=delta;
//	if(!intersect(left,right,-R1.a.y,R1.a.y)) return false;
	if( (left>R1.a.y)||(right<-R1.a.y) ) return false;
	
	A = R1.a.x*R1.u[0]+R1.a.y*R1.u[1]; B = -R1.a.x*R1.u[0]+R1.a.y*R1.u[1];
	C = R1.a.x*R1.u[0]-R1.a.y*R1.u[1]; D = -R1.a.x*R1.u[0]-R1.a.y*R1.u[1];
	
	proj=left=right=A*R2.u[0];
	proj=B*R2.u[0]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=C*R2.u[0]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=D*R2.u[0]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	delta=r12*R2.u[0]; left+=delta; right+=delta;
//	if(!intersect(left,right,-R2.a.x,R2.a.x)) return false;
	if( (left>R2.a.x)||(right<-R2.a.x) ) return false;
	
	proj=left=right=A*R2.u[1];
	proj=B*R2.u[1]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=C*R2.u[1]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=D*R2.u[1]; if(proj<left) left=proj; if(proj>right) right=proj; 	
	delta=r12*R2.u[1]; left+=delta; right+=delta;
//	if(!intersect(left,right,-R2.a.y,R2.a.y)) return false;
	if( (left>R2.a.y)||(right<-R2.a.y) ) return false;
	
	return true;
}

// Circle

bool overlap(Circle &partI, Circle &partJ);

bool overlap(Circle &partI, Circle &partJ, Vec2d const& L);

// Rectangle
bool overlap(Rectangle &partI, Rectangle &partJ);

bool overlap(Rectangle &partI, Rectangle &partJ, Vec2d const& L);

// Spherical Cap
bool overlap(SphericalCap &partI, SphericalCap &partJ);

bool overlap(SphericalCap &partI, SphericalCap &partJ, Vec2d const& L);

// Ellipse
bool overlap(Ellipse &partI, Ellipse &partJ);

bool overlap(Ellipse &partI, Ellipse &partJ, Vec2d const& L);

// SEllipse
bool overlap(SEllipse &partI, SEllipse &partJ);

bool overlap(SEllipse &partI, SEllipse &partJ, Vec2d const& L);



#endif /*SE2D_OVERLAP_H_*/
