/* moveTeapot.cpp
 *
 * Starting code for in-class exercise to animate the teapot.
 *
 */

#include <iostream>
#include <GL/glut.h>

using namespace std;

float z = 5.0;  // distance of eye (center of projection) from frustum
float x = 1.0;
float x_min = -5;
float x_max = 5;
float y_min = -5;
float y_max = 5;
float z_min = -5;
float z_max = 5;

void display ()
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity ();
   gluLookAt (0.0, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glScalef (1.0, 1.0, 1.0);

   /* draw a red cube in center of volume */
   glColor3f (0.0, 0.0, 0.0);
   glBegin(GL_LINE_STRIP);
      glVertex3f(x-1.5,0.5,0.0);
      glVertex3f(x-1.0,1.0,0.0);
      glVertex3f(x,0.0,0.0);
      glVertex3f(x+1,1.0,0.0);
      glVertex3f(x+1.5,0.5,0.0);
    glEnd();

   glFlush ();
}

void init ()
{
   glClearColor (0.8, 0.8, 0.8, 0.0);
   glShadeModel (GL_FLAT);
   glEnable (GL_DEPTH_TEST);
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   /* set up matrices for projection coordinate system */
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-10, 10, -10, 10, 1.5, 20.0);

   /* reset matrices to user's coordinate system */
   glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case '8': x = x + 1;
                glutPostRedisplay ();
                glFlush ();
                break;
      case '2': x = x - 1;
                glutPostRedisplay ();
                glFlush ();
                break;
      case 'q': exit (1);
   }
}

int main (int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Spinning Teapot");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc (reshape);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0; 
}










void initmenu ()            // set up menu
{
   glutCreateMenu (mymenu);         // register callback function
   glutAddMenuEntry ("Menu", 0);
   glutAddMenuEntry ("", 0);
   glutAddMenuEntry ("Choose the size of boid", 1);
   glutAddMenuEntry ("Choose the closeness", 2);
   glutAddMenuEntry ("Choose boundary movement parameter", 3);
   glutAddMenuEntry ("Choose the number of boids", 4);
   glutAddMenuEntry ("Start/Restart with chosen parameter", 5);
   glutAddMenuEntry ("Quit", 6);
   glutAttachMenu (GLUT_RIGHT_BUTTON);
}



void top_menu(int id)
{
   if (id==17) exit(0);
}
void size_menu(int id)
{
   if (id==2)

}
void closeness_menu(int id)
{

}
void boundary_menu(int id)
{

}
void number_menu(int id)
{

}
void start_menu(int id)
{
  
}
void makeMenu(void)
{
   // The sub-menu is created first (because it should be visible when the top
   // menu is created): its callback function is registered and menu entries added.
   int size;
   size = glutCreateMenu(size_menu);
   glutAddMenuEntry("Big", 1);
   glutAddMenuEntry("Median",2);
   glutAddMenuEntry("Small",3);
   int closeness;
   closeness = glutCreateMenu(closeness_menu);
   glutAddMenuEntry("closer", 4);
   glutAddMenuEntry("close", 5);
   glutAddMenuEntry("far", 6);
   glutAddMenuEntry("further", 7);
   int boundary;
   boundary = glutCreateMenu(boundary_menu);
   glutAddMenuEntry("Bigger boundary", 8);
   glutAddMenuEntry("Unit boundary", 9);
   glutAddMenuEntry("Smaller boundary", 10);
   int num_boids;
   num_boids = glutCreateMenu(number_menu);
   glutAddMenuEntry("2", 11);
   glutAddMenuEntry("3", 12);
   glutAddMenuEntry("4", 13);
   glutAddMenuEntry("5", 14);
   glutAddMenuEntry("6", 15);
   int start;
   start = glutCreateMenu(start_menu);
   glutAddMenuEntry("Start", 16);
   glutAddMenuEntry("Restart", 17);
   // The top menu is created: its callback function is registered and menu entries,
   // including a submenu, added.
   glutCreateMenu(top_menu);
   glutAddSubMenu("Choose the size of boid", size);
   glutAddMenuEntry ("Choose the closeness", closeness);
   glutAddMenuEntry ("Choose boundary movement parameter", boundary);
   glutAddMenuEntry ("Choose the number of boids", num_boids);
   glutAddMenuEntry ("Start/Restart with chosen parameter", start);
   glutAddMenuEntry("Quit",17);
   // The menu is attached to a mouse button.
   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mymenu (int value)         // Define actions for the menu based on values given in initmenu()
{
   switch (value) { 
    case 1: cout << "Don't wanna repeat that again in the console." << endl;
          break;
    case 2: cout << "Well, I want to have an option that allows you using mouse click input, but I couldn't." <<endl;
          break;
    case 3: 
          break;
    case 4: 
          break;
    case 5: 
          break;
    case 6: cout << "Goodbye!" << endl;
          exit (1);
   }
}







float Move = 1;
float x = y = z = 0;

gluLookAt (0.0, 0.0, 0.0, x, y, z, 0.0, 1.0, 0.0);



void myClass::mykeyboard (unsigned char key, int x, int y)
{
   switch (key){
      case '2': if(x > -5.0)
                  x -= 0.2;
                else
                  cout << "Hitting limit(X min)" << endl;
        break;
      case '4': if(x < 5.0)
                  x += 0.2;
                else
                  cout << "Hitting limit(X max)" << endl;
        break;
      case '6': if(y > -5.0)
                  y -= 0.2;
                else
                  cout << "Hitting limit(Y min)" << endl;
        break;
      case '8': if(y < 5.0)
                  y += 0.2;
                else
                  cout << "Hitting limit(Y max)" << endl;
        break;
      case '5': if(Move == 1){
                     Move = 0;
                     cout << "Paused" << endl;
                   }
                else{
                  Move = 1;
                  ct << "Restarted" << endl;
                }
        break;
      case '7': 
            NUM_TICKS = NUM_TICKS +10000;
            cout << " Slowing down" << endl;
        break;
      case '9': 
            NUM_TICKS = NUM_TICKS -10000;
            cout << " Speeding up" << endl;
        break;
      }
   glutPostRedisplay();
}












         glColor3f(1.0, 0.0, 0.0);
         glBegin(GL_POLYGON);                       //1
            glVertex3f( boidArray[i].Px, boidArray[i].Py-0.6*size , boidArray[i].Pz+2*size);
            glVertex3f( boidArray[i].Px, boidArray[i].Py-0.6*size , boidArray[i].Pz-2*size);
            glVertex3f( boidArray[i].Px, boidArray[i].Py, boidArray[i].Pz-2*size);
            glVertex3f( boidArray[i].Px, boidArray[i].Py, boidArray[i].Pz+2*size);
         glEnd();
         glColor3f(0.0, 1.0, 1.0);
         glBegin(GL_POLYGON);                       //2
             glVertex3f( boidArray[i].Px, boidArray[i].Py, boidArray[i].Pz+2*size);
             glVertex3f( boidArray[i].Px, boidArray[i].Py, boidArray[i].Pz-2*size);
             glVertex3f( boidArray[i].Px-1.5*size, boidArray[i].Py+size , boidArray[i].Pz-0.2*size);
             glVertex3f( boidArray[i].Px-1.5*size, boidArray[i].Py+size , boidArray[i].Pz+size);
         glEnd();
         glBegin(GL_POLYGON);                       //3
             glVertex3f( boidArray[i].Px, boidArray[i].Py, boidArray[i].Pz-2*size);
             glVertex3f( boidArray[i].Px, boidArray[i].Py, boidArray[i].Pz+2*size);
             glVertex3f( boidArray[i].Px+1.5*size, boidArray[i].Py+size , boidArray[i].Pz+size);
             glVertex3f( boidArray[i].Px+1.5*size, boidArray[i].Py+size , boidArray[i].Pz-0.2*size);
         glEnd();
         glBegin(GL_POLYGON);                       //4
             glVertex3f( boidArray[i].Px-1.5*size, boidArray[i].Py+size , boidArray[i].Pz+size);
             glVertex3f( boidArray[i].Px-1.5*size, boidArray[i].Py+size , boidArray[i].Pz-0.2*size);
             glVertex3f( boidArray[i].Px- 2*size , boidArray[i].Py+0.5*size , boidArray[i].Pz);
         glEnd();
         glBegin(GL_POLYGON);                       //5
             glVertex3f( boidArray[i].Px+1.5*size, boidArray[i].Py+size , boidArray[i].Pz-0.2*size);
             glVertex3f( boidArray[i].Px+1.5*size, boidArray[i].Py+size , boidArray[i].Pz+size);
             glVertex3f( boidArray[i].Px+ 2*size , boidArray[i].Py+0.5*size , boidArray[i].Pz);
         glEnd();