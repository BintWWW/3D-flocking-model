#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;
 
class artObject{
 
  artObject** children;
  int numChildren;
  GLdouble linkLength;
  GLdouble theta;
  GLdouble twist;
  GLdouble displacement;
  GLdouble thetaMax;
  GLdouble thetaMin;
 
  GLdouble thetaInc;
  GLdouble direction; 
 
public:
  artObject(ifstream &fin):thetaInc(0.02),direction(1.0){
    fin >> numChildren;
    fin >> linkLength >> theta >> twist >> displacement >> thetaMax >> thetaMin;
 
    if (numChildren>0){ 
      children = new artObject*[numChildren];
      for(int i=0; i<numChildren; i++)
    children[i] = new artObject(fin);
    }
  };
 
  void traverse(){
    glPushMatrix();
    transform();
    draw();
    for (int i=0; i<numChildren; i++)
      children[i]->traverse();
    glPopMatrix();
  };
 
  void transform(){
    glRotatef(theta,0.0,0.0,1.0);
    glTranslatef(0,0,displacement);
    glTranslatef(linkLength,0.0,0.0);
    glRotatef(twist,1.0,0.0,0.0);
  };
 
  void draw(){
    glBegin(GL_LINES);
    glColor3f(1.0,0,0);
    glVertex3d(-5,0,0);
    glVertex3d(5,0,0);
    glColor3f(0,1.0,0);
    glVertex3d(0,-5,0);
    glVertex3d(0,5,0);
    glColor3f(0,0,1.0);
    glVertex3d(0,0,-5);
    glVertex3d(0,0,5);
    glEnd();
  };
 
  void update(){
    theta = theta + direction*thetaInc;
    if (theta<thetaMin || theta>thetaMax) direction *= -1;
    for (int i=0; i<numChildren; i++)
      children[i]->update();
  };
 
};
 
 
 
 
 
 
 
 
 
 
 
/* OpenGL stuff */
 
GLdouble fov = 35.0;
GLdouble aspect = 4/3.0;
GLdouble dnear = 100.0, dfar = 200.0;
GLint winWidth = 1200, winHeight=(GLint) winWidth/aspect;
 
artObject *ao;
 
void init()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH); 
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.5,0.5,0.5,1.0);
};
 
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslated(0.0,0.0,-190.0);
  ao->traverse();
  glutSwapBuffers();
}
 
void reshape(int w, int h)
{
  glViewport(0,0,w,h);
  aspect = ((GLdouble) w)/h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov,aspect,dnear,dfar);
  glMatrixMode(GL_MODELVIEW);
}
 
void update(void){
  ao->update();
  glutPostRedisplay();
}
 
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(winWidth, winHeight);
  glutCreateWindow("Articlated");
  glutIdleFunc(update);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  ifstream fin(argv[1]);
  ao = new artObject(fin);
  init();
  glutMainLoop();
  return 0;
}