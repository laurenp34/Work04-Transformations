#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main(int argc, char **argv) {

  screen s;
  clear_screen(s);
  color c;
  struct matrix * edges;
  struct matrix * transform;
  struct matrix * temp;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  c.red = 255;
  c.green = 255;
  c.blue = 255;

//behind square
  //add_edge(edges,100,100,0,200,100,0);
//   add_edge(edges,200,100,0,200,200,0);
//   add_edge(edges,200,200,0,100,200,0);
//   add_edge(edges,100,200,0,100,100,0);
// //front square
//   add_edge(edges,100,100,100,200,100,100);
//   add_edge(edges,200,100,100,200,200,100);
//   add_edge(edges,200,200,100,100,200,100);
//   add_edge(edges,100,200,100,100,100,010);
// //connections
//   add_edge(edges,100,100,100,100,100,0);
//   add_edge(edges,200,100,0,200,100,100);
//   add_edge(edges,200,200,0,200,200,100);
//   add_edge(edges,100,200,0,100,200,100);
//
//   transform = make_rotX(30);
//   matrix_mult(transform,edges);
//   transform = make_rotY(30);
//   matrix_mult(transform,edges);

  // draw_lines(edges,s,c);
  // display(s);
  //  print_matrix(edges);
  // int i;
  // for (i=0;i<12;i++) {
  //   transform = make_rotZ(30);
  //   matrix_mult(transform,edges);
  //   print_matrix(edges);
  //   // draw_lines(edges,s,c);
  //   // display(s);
  //   // print_matrix(edges);
  // }

  // add_edge(edges,0,0,0,50,0,0);
  // add_edge(edges,0,0,0,50,50,0);
  // ident(transform);
  // temp = make_rotZ(30);
  // matrix_mult(temp,transform);
  // temp = make_translate(100,100,0);
  // matrix_mult(temp,transform);
  // matrix_mult(transform,edges);
  // draw_lines(edges,s,c);

  // transform = make_translate(50,0,0);
  // matrix_mult(transform,edges);
  // print_matrix(edges);
  // draw_lines(edges,s,c);
  //
  // transform = make_translate(0,50,0);
  // matrix_mult(transform,edges);
  // print_matrix(edges);
  // draw_lines(edges,s,c);
  //
  // transform = make_translate(0,0,50);
  // matrix_mult(transform,edges);
  // print_matrix(edges);
  // draw_lines(edges,s,c);

  // transform = make_translate(0,70,0);
  // matrix_mult(transform,edges);
  // print_matrix(edges);
  // draw_lines(edges,s,c);

  // display(s);
  // save_extension(s, "lines.png");
  //save_ppm(s, "binary.ppm");




  if ( argc == 2 )
    parse_file( argv[1], transform, edges, s );
  else
    parse_file( "stdin", transform, edges, s );

  free_matrix( edges );
  free_matrix( transform );
}
