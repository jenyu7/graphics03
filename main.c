#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

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
  return num%500;
}

int main() {

  screen s;
  color c;
  struct matrix *edges;
  
  c.red = 255;
  edges = new_matrix(4, 4);
  int i; 
  for(i = 0; i < 40; i ++){
    int y0, x1, y1;
    y0 = rand_num();
    x1 = rand_num();
    y1 = rand_num();
    add_edge(edges,0,y0,x1,y1,500,0);
  }
  print_matrix(edges);

  draw_lines(edges, s, c);
  display(s);
  free_matrix( edges );
}
