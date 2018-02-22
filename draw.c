#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  if (points->lastcol == points->cols) {
    //double size
    grow_matrix(points, 2*points->cols);
  }
  //transcribe new coordinates to matrix
  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;
  points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int line;
  //draw two points at a time
  for (line = 0; line < points->lastcol; line+=2) {
    draw_line(points->m[0][line], points->m[1][line], 
	      points->m[0][line+1], points->m[1][line+1], 
	      s, c);
  }
}

//Bresenham's Line Algorithm
//coded in last HW
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  int dx = x1-x0;
  int dy = y1-y0;
  int octant = -1;

  //change starting points
  if (dy < 0){draw_line(x1, y1, x0, y0, s, c);}
  //|m| <= 1, [+]
  if (dy <= dx && dx*dy >= 0){octant = 1;}
  //|m| > 1, [+]
  else if (dy >= dx && dx*dy >= 0){octant = 2;}
  //|m| >= 1, [-]
  else if (dy >= dx*-1 && dx*dy < 0){octant = 3;}
  //|m| < 1, [-]
  if (dy <= dx*-1 && dx*dy < 0){octant = 4;}

  draw(octant, x0, y0, x1, y1, s, c);
}

//plots the points of the line in a while loop
void draw(int o, int x, int y, int x1, int y1, screen s, color c){
  if (!o){printf("Invalid octant.");return;}
  int A = y1-y;
  int B = -1*(x1-x);
  int d;
  //octants 1 & 5
  if (o == 1){
    d = 2*A + B;
    while (x < x1){
      plot(s, c, x, y);
      if (d>0){y ++; d+= 2*B;}
      x++;
      d += 2*A;
    }
  }
  //octants 2 & 6
  else if (o == 2){
    d = A + 2*B;
    while (y < y1){
      plot(s, c, x, y);
      if (d < 0){x ++; d += 2*A;}
      y++;
      d += 2*B;
    }
  }
  //octants 3 & 7
  else if (o == 3){
    d = 2*B - A;
    while (y < y1){
      plot(s, c, x, y);
      if(d > 0){x--; d -= 2*A;}
      y++;
      d += 2*B;
    }
  }
  //octants 4 & 8
  else{
    d = -2*A + B;
    while(x > x1){
      plot(s, c, x, y);
      if (d < 0){y++; d += 2*B;}
      x --;
      d -= 2*A;
    }
  }
}
