#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

//returns a random number
int rand_num()
{
  int fd = open("/dev/random", O_RDONLY);
  int num;
  read(fd, &num, sizeof(num));
  close(fd);
  return abs(num%500);
}

int main() {

  screen s;
  color c;
  struct matrix *edges;
  struct matrix *id;
  struct matrix *m;

  edges = new_matrix(4, 1);
  id = new_matrix(4, 4);
  m = new_matrix(4, 1);

  printf("Adding edges to a matrix:\n");
  add_edge(edges, 100, 100, 0, 110, 300, 0);
  add_edge(edges, 110, 300, 0, 120, 500, 0);
  print_matrix(edges);

  printf("\nAdding points to a matrix:\n");
  add_point(m, 1, 2, 0);
  add_point(m, 2, 0, 0);
  add_point(m, 3, 3, 0);
  add_point(m, 6, 3, 0);
  print_matrix(m);
  
  printf("\nMultiplying two matrixes:\n");
  printf("\nFirst matrix (edges):\n");
  print_matrix(edges);
  printf("\nSecond matrix (m):\n");
  print_matrix(m);
  printf("\nMultiplied together:\n");
  matrix_mult(edges, m);
  print_matrix(m);
  
  printf("\nThe identity matrix:\n");
  ident(id);
  print_matrix(id);

  printf("\nWhen multiplying with identity, matrix stays the same:\n");
  matrix_mult(id, edges);
  print_matrix(edges);

  free(edges);
  edges = new_matrix(4, 1);

  srand(time(NULL));
  c.red = 255;
  /*Ditched the random # generation using system entropy
  int i; 
  for(i = 0; i < 40; i ++){
    int x0, y0, x1, y1;
    x0 = rand_num();
    y0 = rand_num();
    x1 = rand_num();
    y1 = rand_num();
    printf("%d %d %d %d \n", x0, y0, x1, y1);
    add_edge(edges,x0,y0,x1,y1,500,0);
  }
  */

  printf("\nYou have all been very naughty...\n");
  printf("\nExcept for you Dr. Zoidberg..you get a pogo stick!\n");
  printf("\nHoorayyyy, a pogo stick..!\n");
  
  //main shaft
  add_edge(edges, 240, 450, 0,  260, 450, 0);
  add_edge(edges, 260, 450, 0, 260, 100, 0);
  add_edge(edges, 240, 100, 0, 260, 100, 0);
  add_edge(edges, 240, 100, 0, 240, 450, 0);

  //mini stick 
  add_edge(edges, 245, 100, 0,  255, 100, 0);
  add_edge(edges, 255, 100, 0, 255, 80, 0);
  add_edge(edges, 245, 80, 0, 255, 80, 0);
  add_edge(edges, 245, 80, 0, 245, 100, 0);

  //steps
  add_edge(edges, 210, 110, 0,  290, 110, 0);
  add_edge(edges, 290, 110, 0, 290, 100, 0);
  add_edge(edges, 210, 100, 0, 290, 100, 0);
  add_edge(edges, 210, 100, 0, 210, 110, 0);

  //handlebars
  add_edge(edges, 210, 430, 0,  290, 430, 0);
  add_edge(edges, 290, 430, 0, 290, 420, 0);
  add_edge(edges, 210, 420, 0, 290, 420, 0);
  add_edge(edges, 210, 420, 0, 210, 430, 0);

  double theta = 0.0;
  double radius = 10.0;
  int x0, y0, x1, y1;
  x0 = 260;
  y0 = 70;
  while (theta < 360.0){
    x1 = radius*cos(theta) + 250;
    y1 = radius*sin(theta) + 78;

    add_edge(edges, x0, y0, 0, x1, y1, 0);

    x0 = x1;
    y0 = y1;

    theta = theta + .0001;
  }
  
  //triangle (extra test cases)
  //add_edge(edges, 300, 200, 0, 500, 200, 0);
  //add_edge(edges, 500, 200, 0, 350, 400, 0);
  //add_edge(edges, 350, 400, 0, 300, 200, 0);
  
  // print_matrix(edges);
  
  draw_lines(edges, s, c);
  
  save_extension(s, "image.jpg");
  display(s);
  free_matrix(edges);
}
