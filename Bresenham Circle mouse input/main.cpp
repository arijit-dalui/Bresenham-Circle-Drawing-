#include<windows.h>
#include <stdio.h>
#include <math.h>
#include<bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
int radius,xc,yc,i=0;

void setcircle(int button,int state,int x,int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && i==0){
        xc = x;
        yc = y;
        i++;
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && i==1)
    {
        radius = sqrt((x-xc)*(x-xc)+(y-yc)*(y-yc));
        i++;
    }
    glutPostRedisplay();
}

void setradius(int button,int state,int x,int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        radius = sqrt((x-xc)*(x-xc)+(y-yc)*(y-yc));
    }
}

void plot_point(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc+x, yc-y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc+y, yc-x);
  glVertex2i(xc-x, yc-y);
  glVertex2i(xc-y, yc-x);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc-y, yc+x);
  glEnd();
}


void bresenham_circle(int r)
{
  int x=0,y=r;
  float pk=(5.0/4.0)-r;


  plot_point(x,y);
  int k;

  while(x < y)
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 2*x+1;
    else
    {
      y = y - 1;
      pk = pk + 2*(x - y) + 1;
    }
    plot_point(x,y);
  }
  glFlush();
}


void circles(void)
{

  glClear(GL_COLOR_BUFFER_BIT);

  bresenham_circle(radius);
}

void Init()
{

  glClearColor(1.0,1.0,1.0,0);

  glColor3f(0.0,0.0,0.0);

  gluOrtho2D(0 , 640 , 0 , 480);

}

int main(int argc, char **argv)
{

  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);

  glutCreateWindow("bresenham_circle");


  Init();
  glutDisplayFunc(circles);
  glutMouseFunc(setcircle);


  glutMainLoop();

  return 0;
}
