#ifndef MY_PL_H_
#define MY_PL_H_


#include <cmath>

#include <plstream.h>

#include <se2d.h>

#include <LLcells2d.h>

class wrap_plstream :  public plstream {
public:
    void draw_init();
    void draw_init(Vec2d L);

    void draw_cross(Vec2d P);
    void draw_square(Vec2d P);
    void draw_x(Vec2d P);
    void draw_char(Vec2d P, char c);
    void draw_box(Vec2d L);

    void draw(Vec2d A, Vec2d B);
    void draw(Segment const& S);
    void draw(SphericalCap& SC);
    void draw(Rectangle& R);
    void draw(Circle& C);
    void draw(Ellipse& E);
    void draw(SEllipse& SE);

    void draw_obb(Ellipse& E);
    void draw_obb(SEllipse& SE);


// template for LLcells2d
	template <class Particle>
	void draw(LLcells2d<Particle>& ll){
		PLFLT x0,y0,dx,dy, x[1],y[1];
    	dx = ll.dL.x; dy = ll.dL.y;
    	double side(ll.L.x); if(ll.L.y>side) side=ll.L.y;
    	x0 = (dx-side)/2; y0 = (dy-side)/2;
    	col0 (9);
    	char c; int ind;
    	for (int ix = 0; ix < ll.Nside.x; ++ix) 
    	for (int iy = 0; iy < ll.Nside.y; ++iy) {
    		x[0] = x0 + ix*dx; y[0] = y0 + iy*dy;
        	Vec2d v((double)x[0],(double)y[0]); ind=ll.index(v);
        	if(ind<10) c='0'+ind; else c='A'+ind-10;
        	poin (1, x, y, c);
        	join (x[0]-dx/2, y[0]-dx/2, x[0]+dx/2, y[0]-dx/2);        
        	join (x[0]-dx/2, y[0]+dx/2, x[0]+dx/2, y[0]+dx/2);        
        	join (x[0]-dx/2, y[0]-dx/2, x[0]-dx/2, y[0]+dx/2);        
        	join (x[0]+dx/2, y[0]-dx/2, x[0]+dx/2, y[0]+dx/2);
    	}
	}


private:
};


#endif /*MY_PL_H_*/
