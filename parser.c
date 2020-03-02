#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename
          struct matrix * transform,
          struct matrix * pm,
          screen s
Returns:

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         line: add a line to the edge matrix -
               takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
         ident: set the transform matrix to the identity matrix -
         scale: create a scale matrix,
                then multiply the transform matrix by the scale matrix -
                takes 3 arguments (sx, sy, sz)
         translate: create a translation matrix,
                    then multiply the transform matrix by the translation matrix -
                    takes 3 arguments (tx, ty, tz)
         rotate: create a rotation matrix,
                 then multiply the transform matrix by the rotation matrix -
                 takes 2 arguments (axis, theta) axis should be x y or z
         apply: apply the current transformation matrix to the edge matrix
         display: clear the screen, then
                  draw the lines of the edge matrix to the screen
                  display the screen
         save: clear the screen, then
               draw the lines of the edge matrix to the screen
               save the screen to a file -
               takes 1 argument (file name)
         quit: end parsing

See the file script for an example of the file format

IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename,
                  struct matrix * transform,
                  struct matrix * edges,
                  screen s) {

  FILE *f;
  char line[256];
  clear_screen(s);
  color c; //white
  c.red = 255;
  c.blue = 255;
  c.green = 255;
  double x1,y1,z1,x2,y2,z2,theta; //to hold coordinates and angle
  int r,g,b; //color
  char axis[20]; //axis of rotation
  struct matrix * temp; //temp transform matrix to multiply transform by

  if ( strcmp(filename, "stdin") == 0 )
    f = stdin;
  else
    f = fopen(filename, "r");

  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';
    printf(":%s:\n",line);
    //LINE
    if (strcmp(line,"line")==0) {
      //get dimensions (parse next line)
      fgets(line,255,f);
      sscanf(line, "%lf %lf %lf %lf %lf %lf\n", &x1, &y1, &z1, &x2, &y2, &z2);
      add_edge(edges,x1,y1,z1,x2,y2,z2);
    }
    //IDENTITY MATRIX
    if (strcmp(line,"ident")==0) {
      ident(transform);
    }
    //SCALE
    if (strcmp(line,"scale")==0) {
      //get transformation dimensions (parse next line)
      fgets(line,255,f);
      sscanf(line, "%lf %lf %lf\n", &x1,&y1,&z1);
      temp = make_scale(x1,y1,z1);
      matrix_mult(temp,transform);
    }
    //MOVE
    if (strcmp(line,"move")==0) {
      //get translation dimensions (parse next line)
      fgets(line,255,f);
      sscanf(line, "%lf %lf %lf\n", &x1,&y1,&z1);
      temp = make_translate(x1,y1,z1);
      matrix_mult(temp,transform);
    }
    //ROTATE
    if (strcmp(line,"rotate")==0) {
      //get axis of rotation and theta (parse next line)
      fgets(line,255,f);
      sscanf(line, "%s %lf\n", axis, &theta);
      //find axis
      if (strcmp(axis,"x")==0) {
        temp = make_rotX(theta);
      } else if (strcmp(axis,"y")==0) {
        temp = make_rotY(theta);
      } else if (strcmp(axis,"z")==0) {
        temp = make_rotZ(theta);
      }
      //modify transform
      matrix_mult(temp,transform);
    }
    //APPLY
    if (strcmp(line,"apply")==0) {
      matrix_mult(transform,edges);
    }
    //DISPLAY
    if (strcmp(line,"display")==0) {
      clear_screen(s);
      draw_lines(edges,s,c);
      display(s);
    }
    //COLOR
    //(I added to be able to change color)
    if (strcmp(line,"color")==0) {
      fgets(line,255,f);
      sscanf(line, "%d %d %d\n", &r, &g, &b);
      c.red = r;
      c.green = g;
      c.blue = b;
    }
    //SAVE
    if (strcmp(line,"save")==0) {
      clear_screen(s);
      draw_lines(edges,s,c);
      //get file name (parse next line)
      fgets(line,255,f);
      line[strlen(line)-1]='\0';
      save_extension(s, line);
    }
    if (strcmp(line,"quit")==0) {
      printf("end\n");
    }
  }
}
