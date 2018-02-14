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

    void draw_cross(Vec2d P, int col=1);
    void draw_square(Vec2d P, int col=1);
    void draw_x(Vec2d P, int col=1);
    void draw_char(Vec2d P, char c, int col=1);
    void draw_box(Vec2d L, int col=1);

    void draw(Vec2d A, Vec2d B, int col=9);
    void draw(Segment const& S, int col=9);
    void draw(SphericalCap& SC, int col=9);
    void draw(Rectangle& R, int col=9);
    void draw(Circle& C, int col=3);
    void draw(Ellipse& E, int col=3);
    void draw(SEllipse& SE, int col=3);

    void draw_obb(Ellipse& E, int col=5);
    void draw_obb(SEllipse& SE, int col=5);


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
