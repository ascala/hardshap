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


#include <iostream>

#include <wrap_pl.h>

void wrap_plstream::draw_init(){
//	sdev ("gcw"); 
	sdev ("xwin"); 
	scolbg(255,255,255);
	init ();
	PLFLT xmin(-8),xmax(8),ymin(-8),ymax(8);
	env (xmin, xmax, ymin, ymax, 0, -0);
}

void wrap_plstream::draw_init(Vec2d L){
	//sdev ("gcw"); 
 	sdev ("xwin"); 
    scolbg(255,255,255);
    init ();
    PLFLT side(L.x); if(L.y>side) side=L.y;
    env (-side/2, side/2, -side/2, side/2, 0, -0);
}


void wrap_plstream::draw_cross(Vec2d P){
	PLFLT x0,y0,x1,y1;
	PLFLT eps=0.1;
	x0 = x1 = (PLFLT)P.x; 
	y0=(PLFLT)P.y-eps; y1=(PLFLT)P.y+eps;
	col0 (1); join (x0,y0,x1,y1);
	y0 = y1 = (PLFLT)P.y; 
	x0=(PLFLT)P.x-eps; x1=(PLFLT)P.x+eps;
	col0 (1); join (x0,y0,x1,y1);
}

void wrap_plstream::draw_square(Vec2d P){
	PLFLT x0,y0,x1,y1;
	PLFLT eps=0.1; col0 (1); 
	x0=(PLFLT)P.x-eps; x1=(PLFLT)P.x+eps; 
	y0=(PLFLT)P.y-eps; y1=(PLFLT)P.y-eps;
	join (x0,y0,x1,y1);
	
	y0=(PLFLT)P.y+eps; y1=(PLFLT)P.y+eps;
	join (x0,y0,x1,y1);

	y0=(PLFLT)P.y-eps; y1=(PLFLT)P.y+eps;
	x0=(PLFLT)P.x-eps; x1=(PLFLT)P.x-eps; 
	join (x0,y0,x1,y1);
	
	x0=(PLFLT)P.x+eps; x1=(PLFLT)P.x+eps;
	join (x0,y0,x1,y1);
}

void wrap_plstream::draw_x(Vec2d P){
        PLFLT x0,y0,x1,y1;
        PLFLT eps=0.1; col0 (1);
        x0=(PLFLT)P.x-eps; x1=(PLFLT)P.x+eps; 
        y0=(PLFLT)P.y-eps; y1=(PLFLT)P.y+eps;
        join (x0,y0,x1,y1);
        y0=(PLFLT)P.y+eps; y1=(PLFLT)P.y-eps;
        join (x0,y0,x1,y1);
}

void wrap_plstream::draw_char(Vec2d P, char c){
	PLFLT x[1]={(PLFLT)P.x}, y[1]={(PLFLT)P.y};
	 col0 (1); poin (1, x, y, c);
}

void wrap_plstream::draw_box(Vec2d L){
	PLFLT dx(L.x/2),dy(L.y/2); col0(1);
	join(-dx,dy,dx,dy); join(dx,dy,dx,-dy); 
	join(dx,-dy,-dx,-dy); join(-dx,-dy,-dx,dy); 
}


void wrap_plstream::draw(Vec2d A, Vec2d  B){
	col0 (9); join ((PLFLT)A.x, (PLFLT)A.y, (PLFLT)B.x, (PLFLT)B.y);
}

void wrap_plstream::draw(Segment const &S){
	Vec2d P0(S.r-S.dir), P1(S.r+S.dir);
	col0 (9); join ((PLFLT)P0.x, (PLFLT)P0.y, (PLFLT)P1.x, (PLFLT)P1.y);
}

void wrap_plstream::draw(SphericalCap& SC){
	Vec2d par(SC.radius*SC.dir/SC.halflen), ort(par.y,-par.x);
	Vec2d P0(SC.r-SC.dir),P1(SC.r+SC.dir);
	
	draw(P0+ort, P1+ort);
	draw(P0-ort, P1-ort);

  	PLINT n=51;  PLFLT x0[51], y0[51], x1[51], y1[51]; 
  	Vec2d P;  double alpha;
  	for(int i = 0; i<(int)n; i++){
  		alpha=M_PI*i/(int)(n-1);
  		P=P0+ort*cos(alpha)-par*sin(alpha); 
    	x0[i] = (PLFLT) P.x; y0[i] = (PLFLT) P.y;
  		P=P1+ort*cos(alpha)+par*sin(alpha); 
    	x1[i] = (PLFLT) P.x; y1[i] = (PLFLT) P.y;
  }
  line (n, x0, y0); line (n, x1, y1);
}

void wrap_plstream::draw(Rectangle& R){
	Vec2d A, B, ux(R.a.x*R.u[0]), uy(R.a.y*R.u[1]);
	A = R.r + ux + uy;
	B = R.r + ux - uy; draw(A,B);		
	B = R.r - ux + uy; draw(A,B);		
	A = R.r - ux - uy;
	B = R.r + ux - uy; draw(A,B);		
	B = R.r - ux + uy; draw(A,B);		
}

void wrap_plstream::draw(Circle& C){
  PLINT n=101;  PLFLT x[101], y[101]; 
  Vec2d P;  double alpha;
  for(int i = 0; i<(int)n-1;i++){
  	alpha=2*M_PI*i/(int)(n-1);
	//P=C.on_surf(alpha); 
	P=C.r+C.rmax*Vec2d(cos(alpha),sin(alpha)); 
    x[i] = (PLFLT) P.x;
    y[i] = (PLFLT) P.y;
  }
  x[n-1] = x[0]; y[n-1] = y[0];
  col0 (3); line (n, x, y);
}

void wrap_plstream::draw(Ellipse& E){
  PLINT n=101;  PLFLT x[101], y[101]; 
  Vec2d P;  double alpha;
  for(int i = 0; i<(int)n-1;i++){
  	alpha=2*M_PI*i/(int)(n-1);
  	P=E.on_surf(alpha); 
    x[i] = (PLFLT) P.x;
    y[i] = (PLFLT) P.y;
  }
  x[n-1] = x[0]; y[n-1] = y[0];
  col0 (3); line (n, x, y);
//  draw_obb(E,pl);
}

void wrap_plstream::draw(SEllipse& SE){
  PLINT n=101;  PLFLT x[101], y[101]; 
  Vec2d P;  double alpha;
  for(int i = 0; i<(int)n-1;i++){
  	alpha=2*M_PI*i/(int)(n-1);
  	P=SE.on_surf(alpha); 
    x[i] = (PLFLT) P.x;
    y[i] = (PLFLT) P.y;
  }
  x[n-1] = x[0]; y[n-1] = y[0];
  col0 (3); line (n, x, y);
//  draw_obb(E,pl);
}

void wrap_plstream::draw_obb(Ellipse& E){
	Vec2d A,B;
	col0 (5); 
	A = E.r+E.a.x*E.u[0]+E.a.y*E.u[1]; B = E.r+E.a.x*E.u[0]-E.a.y*E.u[1]; 
	join ((PLFLT)A.x, (PLFLT)A.y, (PLFLT)B.x, (PLFLT)B.y);
	A = E.r-E.a.x*E.u[0]+E.a.y*E.u[1]; B = E.r-E.a.x*E.u[0]-E.a.y*E.u[1]; 
	join ((PLFLT)A.x, (PLFLT)A.y, (PLFLT)B.x, (PLFLT)B.y);
	A = E.r+E.a.x*E.u[0]+E.a.y*E.u[1]; B = E.r-E.a.x*E.u[0]+E.a.y*E.u[1]; 
	join ((PLFLT)A.x, (PLFLT)A.y, (PLFLT)B.x, (PLFLT)B.y);
	A = E.r+E.a.x*E.u[0]-E.a.y*E.u[1]; B = E.r-E.a.x*E.u[0]-E.a.y*E.u[1]; 
	join ((PLFLT)A.x, (PLFLT)A.y, (PLFLT)B.x, (PLFLT)B.y);
}

void wrap_plstream::draw_obb(SEllipse& SE){
	Vec2d A,B;
	col0 (5); 
	A = SE.r+SE.a.x*SE.u[0]+SE.a.y*SE.u[1]; B = SE.r+SE.a.x*SE.u[0]-SE.a.y*SE.u[1]; 
	join ((PLFLT)A.x, (PLFLT)A.y, (PLFLT)B.x, (PLFLT)B.y);
	A = SE.r-SE.a.x*SE.u[0]+SE.a.y*SE.u[1]; B = SE.r-SE.a.x*SE.u[0]-SE.a.y*SE.u[1]; 
	join ((PLFLT)A.x, (PLFLT)A.y, (PLFLT)B.x, (PLFLT)B.y);
	A = SE.r+SE.a.x*SE.u[0]+SE.a.y*SE.u[1]; B = SE.r-SE.a.x*SE.u[0]+SE.a.y*SE.u[1]; 
	join ((PLFLT)A.x, (PLFLT)A.y, (PLFLT)B.x, (PLFLT)B.y);
	A = SE.r+SE.a.x*SE.u[0]-SE.a.y*SE.u[1]; B = SE.r-SE.a.x*SE.u[0]-SE.a.y*SE.u[1]; 
	join ((PLFLT)A.x, (PLFLT)A.y, (PLFLT)B.x, (PLFLT)B.y);
}



