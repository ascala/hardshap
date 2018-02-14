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

#include <wrap_plplot.h>

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
    PLFLT side(L[0]); if(L[1]>side) side=L[1];
    env (-side/2, side/2, -side/2, side/2, 0, -0);
}


void wrap_plstream::draw_cross(Vec2d P, int col){
	PLFLT x0,y0,x1,y1;
	PLFLT eps=0.1;
	x0 = x1 = (PLFLT)P[0]; 
	y0=(PLFLT)P[1]-eps; y1=(PLFLT)P[1]+eps;
	col0 (1); join (x0,y0,x1,y1);
	y0 = y1 = (PLFLT)P[1]; 
	x0=(PLFLT)P[0]-eps; x1=(PLFLT)P[0]+eps;
	col0 (col); join (x0,y0,x1,y1);
}

void wrap_plstream::draw_square(Vec2d P, int col){
	PLFLT x0,y0,x1,y1;
	PLFLT eps=0.1; col0 (col); 
	x0=(PLFLT)P[0]-eps; x1=(PLFLT)P[0]+eps; 
	y0=(PLFLT)P[1]-eps; y1=(PLFLT)P[1]-eps;
	join (x0,y0,x1,y1);
	
	y0=(PLFLT)P[1]+eps; y1=(PLFLT)P[1]+eps;
	join (x0,y0,x1,y1);

	y0=(PLFLT)P[1]-eps; y1=(PLFLT)P[1]+eps;
	x0=(PLFLT)P[0]-eps; x1=(PLFLT)P[0]-eps; 
	join (x0,y0,x1,y1);
	
	x0=(PLFLT)P[0]+eps; x1=(PLFLT)P[0]+eps;
	join (x0,y0,x1,y1);
}

void wrap_plstream::draw_x(Vec2d P, int col){
        PLFLT x0,y0,x1,y1;
        PLFLT eps=0.1; col0 (col);
        x0=(PLFLT)P[0]-eps; x1=(PLFLT)P[0]+eps; 
        y0=(PLFLT)P[1]-eps; y1=(PLFLT)P[1]+eps;
        join (x0,y0,x1,y1);
        y0=(PLFLT)P[1]+eps; y1=(PLFLT)P[1]-eps;
        join (x0,y0,x1,y1);
}

void wrap_plstream::draw_char(Vec2d P, char c, int col){
	PLFLT x[1]={(PLFLT)P[0]}, y[1]={(PLFLT)P[1]};
	 col0 (col); poin (1, x, y, c);
}

void wrap_plstream::draw_box(Vec2d L, int col){
	PLFLT dx(L[0]/2),dy(L[1]/2); col0(col);
	join(-dx,dy,dx,dy); join(dx,dy,dx,-dy); 
	join(dx,-dy,-dx,-dy); join(-dx,-dy,-dx,dy); 
}


void wrap_plstream::draw(Vec2d A, Vec2d  B, int col){
	col0(col); join ((PLFLT)A[0], (PLFLT)A[1], (PLFLT)B[0], (PLFLT)B[1]);
}

void wrap_plstream::draw(Segment const &S, int col){
	Vec2d P0(S.r-S.dir), P1(S.r+S.dir);
	col0(col); join ((PLFLT)P0[0], (PLFLT)P0[1], (PLFLT)P1[0], (PLFLT)P1[1]);
}

void wrap_plstream::draw(SphericalCap& SC, int col){
	Vec2d par(SC.radius*SC.dir/SC.halflen), ort(par[1],-par[0]);
	Vec2d P0(SC.r-SC.dir),P1(SC.r+SC.dir);
	
	col0(col);
	
	draw(P0+ort, P1+ort);
	draw(P0-ort, P1-ort);

  	PLINT n=51;  PLFLT x0[51], y0[51], x1[51], y1[51]; 
  	Vec2d P;  double alpha;
  	for(int i = 0; i<(int)n; i++){
  		alpha=M_PI*i/(int)(n-1);
  		P=P0+ort*cos(alpha)-par*sin(alpha); 
    	x0[i] = (PLFLT) P[0]; y0[i] = (PLFLT) P[1];
  		P=P1+ort*cos(alpha)+par*sin(alpha); 
    	x1[i] = (PLFLT) P[0]; y1[i] = (PLFLT) P[1];
  }
  line (n, x0, y0); line (n, x1, y1);
}

void wrap_plstream::draw(Rectangle& R, int col){
	Vec2d A, B, ux(R.a[0]*R.u[0]), uy(R.a[1]*R.u[1]); col0(col);
	A = R.r + ux + uy;
	B = R.r + ux - uy; draw(A,B);		
	B = R.r - ux + uy; draw(A,B);		
	A = R.r - ux - uy;
	B = R.r + ux - uy; draw(A,B);		
	B = R.r - ux + uy; draw(A,B);		
}

void wrap_plstream::draw(Circle& C, int col){
  PLINT n=101;  PLFLT x[101], y[101]; 
  Vec2d P;  double alpha; col0(col);
  for(int i = 0; i<(int)n-1;i++){
  	alpha=2*M_PI*i/(int)(n-1);
	//P=C.on_surf(alpha); 
	P=C.r+C.radius*Vec2d(cos(alpha),sin(alpha)); 
    x[i] = (PLFLT) P[0];
    y[i] = (PLFLT) P[1];
  }
  x[n-1] = x[0]; y[n-1] = y[0];
  col0(col); line (n, x, y);
}

void wrap_plstream::draw(Ellipse& E, int col){
  PLINT n=101;  PLFLT x[101], y[101]; 
  Vec2d P;  double alpha; 
  for(int i = 0; i<(int)n-1;i++){
  	alpha=2*M_PI*i/(int)(n-1);
  	P=E.on_surf(alpha); 
    x[i] = (PLFLT) P[0];
    y[i] = (PLFLT) P[1];
  }
  x[n-1] = x[0]; y[n-1] = y[0];
  col0(col); line (n, x, y);
//  draw_obb(E,pl);
}

void wrap_plstream::draw(SEllipse& SE, int col){
  PLINT n=101;  PLFLT x[101], y[101]; 
  Vec2d P;  double alpha; col0(col);
  for(int i = 0; i<(int)n-1;i++){
  	alpha=2*M_PI*i/(int)(n-1);
  	P=SE.on_surf(alpha); 
    x[i] = (PLFLT) P[0];
    y[i] = (PLFLT) P[1];
  }
  x[n-1] = x[0]; y[n-1] = y[0];
  col0(col); line (n, x, y);
//  draw_obb(E,pl);
}

void wrap_plstream::draw_obb(Ellipse& E, int col){
	Vec2d A,B;
	col0(col); 
	A = E.r+E.a[0]*E.u[0]+E.a[1]*E.u[1]; B = E.r+E.a[0]*E.u[0]-E.a[1]*E.u[1]; 
	join ((PLFLT)A[0], (PLFLT)A[1], (PLFLT)B[0], (PLFLT)B[1]);
	A = E.r-E.a[0]*E.u[0]+E.a[1]*E.u[1]; B = E.r-E.a[0]*E.u[0]-E.a[1]*E.u[1]; 
	join ((PLFLT)A[0], (PLFLT)A[1], (PLFLT)B[0], (PLFLT)B[1]);
	A = E.r+E.a[0]*E.u[0]+E.a[1]*E.u[1]; B = E.r-E.a[0]*E.u[0]+E.a[1]*E.u[1]; 
	join ((PLFLT)A[0], (PLFLT)A[1], (PLFLT)B[0], (PLFLT)B[1]);
	A = E.r+E.a[0]*E.u[0]-E.a[1]*E.u[1]; B = E.r-E.a[0]*E.u[0]-E.a[1]*E.u[1]; 
	join ((PLFLT)A[0], (PLFLT)A[1], (PLFLT)B[0], (PLFLT)B[1]);
}

void wrap_plstream::draw_obb(SEllipse& SE, int col){
	Vec2d A,B;
	col0(col); 
	A = SE.r+SE.a[0]*SE.u[0]+SE.a[1]*SE.u[1]; B = SE.r+SE.a[0]*SE.u[0]-SE.a[1]*SE.u[1]; 
	join ((PLFLT)A[0], (PLFLT)A[1], (PLFLT)B[0], (PLFLT)B[1]);
	A = SE.r-SE.a[0]*SE.u[0]+SE.a[1]*SE.u[1]; B = SE.r-SE.a[0]*SE.u[0]-SE.a[1]*SE.u[1]; 
	join ((PLFLT)A[0], (PLFLT)A[1], (PLFLT)B[0], (PLFLT)B[1]);
	A = SE.r+SE.a[0]*SE.u[0]+SE.a[1]*SE.u[1]; B = SE.r-SE.a[0]*SE.u[0]+SE.a[1]*SE.u[1]; 
	join ((PLFLT)A[0], (PLFLT)A[1], (PLFLT)B[0], (PLFLT)B[1]);
	A = SE.r+SE.a[0]*SE.u[0]-SE.a[1]*SE.u[1]; B = SE.r-SE.a[0]*SE.u[0]-SE.a[1]*SE.u[1]; 
	join ((PLFLT)A[0], (PLFLT)A[1], (PLFLT)B[0], (PLFLT)B[1]);
}



