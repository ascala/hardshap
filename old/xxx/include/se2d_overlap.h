#ifndef SE2D_OVERLAP_H_
#define SE2D_OVERLAP_H_

#include <se2d.h>

// Oriented Bounding Boxes
template <class ConvexWithAxis>
bool OBBoverlap(ConvexWithAxis const & R1, ConvexWithAxis const & R2){
	Vec2d r12(R2.r-R1.r); 
	
	Vec2d A,B,C,D;
	double proj,left,right,delta;
	
	A = R2.a[0]*R2.u[0]+R2.a[1]*R2.u[1]; B = -R2.a[0]*R2.u[0]+R2.a[1]*R2.u[1];
	C = R2.a[0]*R2.u[0]-R2.a[1]*R2.u[1]; D = -R2.a[0]*R2.u[0]-R2.a[1]*R2.u[1];
	
	proj=left=right=A.dot(R1.u[0]);
	proj=B.dot(R1.u[0]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=C.dot(R1.u[0]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=D.dot(R1.u[0]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	delta=r12.dot(R1.u[0]); left+=delta; right+=delta;
//	if(!intersect(left,right,-R1.a[0],R1.a[0])) return false;
	if( (left>R1.a[0])||(right<-R1.a[0]) ) return false;
	
	proj=left=right=A.dot(R1.u[1]);
	proj=B.dot(R1.u[1]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=C.dot(R1.u[1]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=D.dot(R1.u[1]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	delta=r12.dot(R1.u[1]); left+=delta; right+=delta;
//	if(!intersect(left,right,-R1.a[1],R1.a[1])) return false;
	if( (left>R1.a[1])||(right<-R1.a[1]) ) return false;
	
	A = R1.a[0]*R1.u[0]+R1.a[1]*R1.u[1]; B = -R1.a[0]*R1.u[0]+R1.a[1]*R1.u[1];
	C = R1.a[0]*R1.u[0]-R1.a[1]*R1.u[1]; D = -R1.a[0]*R1.u[0]-R1.a[1]*R1.u[1];
	
	proj=left=right=A.dot(R2.u[0]);
	proj=B.dot(R2.u[0]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=C.dot(R2.u[0]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=D.dot(R2.u[0]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	delta=r12.dot(R2.u[0]); left+=delta; right+=delta;
//	if(!intersect(left,right,-R2.a[0],R2.a[0])) return false;
	if( (left>R2.a[0])||(right<-R2.a[0]) ) return false;
	
	proj=left=right=A.dot(R2.u[1]);
	proj=B.dot(R2.u[1]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=C.dot(R2.u[1]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	proj=D.dot(R2.u[1]); if(proj<left) left=proj; if(proj>right) right=proj; 	
	delta=r12.dot(R2.u[1]); left+=delta; right+=delta;
//	if(!intersect(left,right,-R2.a[1],R2.a[1])) return false;
	if( (left>R2.a[1])||(right<-R2.a[1]) ) return false;
	
	return true;
}

// Circle

bool overlap(Circle &partI, Circle &partJ);
bool overlap(Circle &partI, Circle &partJ, Vec2d const& L);
bool OBBoverlap(Circle &partI, Circle &partJ);
bool OBBoverlap(Circle &partI, Circle &partJ, Vec2d const& L);

// Rectangle
bool overlap(Rectangle &partI, Rectangle &partJ);
bool overlap(Rectangle &partI, Rectangle &partJ, Vec2d const& L);
bool OBBoverlap(Rectangle &partI, Rectangle &partJ);
bool OBBoverlap(Rectangle &partI, Rectangle &partJ, Vec2d const& L);

// Spherical Cap
bool overlap(SphericalCap &partI, SphericalCap &partJ);
bool overlap(SphericalCap &partI, SphericalCap &partJ, Vec2d const& L);
bool OBBoverlap(SphericalCap &partI, SphericalCap &partJ);
bool OBBoverlap(SphericalCap &partI, SphericalCap &partJ, Vec2d const& L);

// Ellipse
bool overlap(Ellipse &partI, Ellipse &partJ);
bool overlap(Ellipse &partI, Ellipse &partJ, Vec2d const& L);
bool OBBoverlap(Ellipse &partI, Ellipse &partJ);
bool OBBoverlap(Ellipse &partI, Ellipse &partJ, Vec2d const& L);

// SEllipse
bool overlap(SEllipse &partI, SEllipse &partJ);
bool overlap(SEllipse &partI, SEllipse &partJ, Vec2d const& L);
bool OBBoverlap(SEllipse &partI, SEllipse &partJ);
bool OBBoverlap(SEllipse &partI, SEllipse &partJ, Vec2d const& L);

/* C I R C L E - P A R T I C L E   O V E R L A P S */

// Circle-Ellipse
double overlap(double &angle, Ellipse &partI, Circle &partJ);
bool overlap(Ellipse &partI, Circle &partJ);
bool overlap(Circle &partI, Ellipse &partJ);
bool overlap(Ellipse &partI, Circle &partJ, Vec2d const& L);
bool overlap(Circle &partI, Ellipse &partJ, Vec2d const& L);

// Circle-SuperEllipse
double overlap(double &angle, SEllipse &partI, Circle &partJ);
bool overlap(SEllipse &partI, Circle &partJ);
bool overlap(Circle &partI, SEllipse &partJ);
bool overlap(SEllipse &partI, Circle &partJ, Vec2d const& L);
bool overlap(Circle &partI, SEllipse &partJ, Vec2d const& L);

// Circle-Rectangle
bool overlap(Rectangle &partI, Circle &partJ);
bool overlap(Circle &partI, Rectangle &partJ);
bool overlap(Rectangle &partI, Circle &partJ, Vec2d const& L);
bool overlap(Circle &partI, Rectangle &partJ, Vec2d const& L);

// Circle-SphericalCap
bool overlap(SphericalCap &partI, Circle &partJ);
bool overlap(Circle &partI, SphericalCap &partJ);
bool overlap(SphericalCap &partI, Circle &partJ, Vec2d const& L);
bool overlap(Circle &partI, SphericalCap &partJ, Vec2d const& L);


/*   C I R C L E - P A R T I C L E   W I T H   O B B's   */

// Circle-Ellipse
double OBBoverlap(double &angle, Ellipse &partI, Circle &partJ);
bool OBBoverlap(Ellipse &partI, Circle &partJ);
bool OBBoverlap(Circle &partI, Ellipse &partJ);
bool OBBoverlap(Ellipse &partI, Circle &partJ, Vec2d const& L);
bool OBBoverlap(Circle &partI, Ellipse &partJ, Vec2d const& L);

// Circle-SuperEllipse
double OBBoverlap(double &angle, SEllipse &partI, Circle &partJ);
bool OBBoverlap(SEllipse &partI, Circle &partJ);
bool OBBoverlap(Circle &partI, SEllipse &partJ);
bool OBBoverlap(SEllipse &partI, Circle &partJ, Vec2d const& L);
bool OBBoverlap(Circle &partI, SEllipse &partJ, Vec2d const& L);

// Circle-Rectangle
bool OBBoverlap(Rectangle &partI, Circle &partJ);
bool OBBoverlap(Circle &partI, Rectangle &partJ);
bool OBBoverlap(Rectangle &partI, Circle &partJ, Vec2d const& L);
bool OBBoverlap(Circle &partI, Rectangle &partJ, Vec2d const& L);

// Circle-SphericalCap
bool OBBoverlap(SphericalCap &partI, Circle &partJ);
bool OBBoverlap(Circle &partI, SphericalCap &partJ);
bool OBBoverlap(SphericalCap &partI, Circle &partJ, Vec2d const& L);
bool OBBoverlap(Circle &partI, SphericalCap &partJ, Vec2d const& L);



#endif /*SE2D_OVERLAP_H_*/
