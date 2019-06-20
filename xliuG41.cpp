/*File name: liu_wang_G4.cpp
 *Name: Xinru Liu
 *Description: this program displays an animation that mimic the roller coaster ride.
            The hills are defined by the points in a data file connected using
            either linear or quadratic piecewise spline lines. The coaster will go up
            and down hills in given speed and stop at the end station. It will start 
            again when requested. The whole scene can also be zoom in and zoom out based
            on user's option.
 *Input: 1) data points stored in a file (integers). There are 3 lines of data points and 
         each line contains the number of points(6) and x and y coordinates of those 6 data points.
       2) the file name(string) when compiling the file (./xliuG3 myInput) 
       3) from the keyboard(char)
            input  Action
         -----------------------------------------------------------------------
         0      Display a linear piecewise spline
         1      Display a quadratic piecewise spline
         2      Display a cubic piecewise spline
         4      Go slower
         6      Go faster
         +      Zoom in
         -      Zoom out
         n      Display the next set of knots in file (message in console when no more data)
         r      Reposition the car at the start of the current track
         s      Start the car running along the track
         q      Quit

 *output: 1) linear, quadratic spline lines using line strip
 *        2) an animation of a "car" (polygon) hanging from and moving along the spline from left to right.
 *        2) The knots (line) hang at each connecting point
 *        3) start and end station (polygons)
 */
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glut.h>
#include <cstring>
#include <string>
#include <math.h>
#include <time.h>


using namespace std;

const int windowHeight = 1000;
const int windowWidth = 1000;
float z = 5;

struct myBoid{
   float Vx, Vy, Vz;
   float Px, Py, Pz;
};

struct Vector{
   float Vx, Vy, Vz;
};


class myClass{
   bool stop;
   bool start;
   myBoid boidArray[40];
   float num_ticks;
   int numBoid;
   float closeness;
   float size;
   float Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
   float view_x;
   float view_y;

public:
   myClass();
   void init();
   void printMenu();
   void initMenu();
   void myMenu(int);
   void size_Menu(int);
   void num_Menu(int);
   void closeness_Menu(int);
   void boundary_Menu(int);
   void myMouse(int, int, int, int);
   void myKeyboard(unsigned char, int, int);
   void myIdle();
   void myDisplay();
   void initial_position();
   void new_position();
   Vector rule1(myBoid, int);
   Vector rule2(myBoid, int);
   Vector rule3(myBoid, int);
   Vector bound_position(myBoid, int);
   Vector pcjCalc(int);
   Vector pvjCalc(int);
   Vector tendency(myBoid);
   void limitVelocity(int);

};

myClass boid;

myClass::myClass(){
    stop = false;
    num_ticks = 150000;
    numBoid = 10;
    closeness = 0.3;
    size = 0.03;
    start = false;
    Xmin = -4; Xmax = 4; Ymin = -4; Ymax = 4; Zmin = -6; Zmax = 6;
    view_x = 0.0;
    view_y = 0.0;
    for (int i = 0; i < numBoid; i++){
      myBoid b;
      float x, y;
      srand(time(NULL));
      x = -4 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(8)));
      b.Px = x;
      y = -4 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(8)));
      b.Py = y;
      b.Pz = -4 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(8)));;
      b.Vx = 0;
      b.Vx = 0;
      b.Vz = 0;
      boidArray[i] = b;
   }
}

void myClass::init(){
/*pre-condition: NA
  This function initializes the window
*/
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable (GL_DEPTH_TEST);
    
}

void size_menu(int value){
 /*pre-condition: int menu operation value
  This function calls myMenu function to show the menu
*/ 

   
  boid.size_Menu(value);
  //cout << "good" << endl;
  //glutPostRedisplay();
}

void myClass::size_Menu(int value){
   switch(value){
      case 6: 
              size = 0.06;
              break;
      case 7: 
              size = 0.04;
              break;
      case 8: 
              size = 0.02;
              break;
   }

   glutPostRedisplay();
}

void num_menu(int value){
   boid.num_Menu(value);
}

void myClass::num_Menu(int value){
   switch(value){
      case 9: //start = false;
              numBoid = 15;
              break;
      case 10: //start = false;
              numBoid = 20;
              break;
      case 11: //start = false;
              numBoid = 25;
              break;
   }

   glutPostRedisplay();
}

void closeness_menu(int value){
   boid.closeness_Menu(value);
}

void myClass::closeness_Menu(int value){
   switch(value){
      case 1: //start = false;
              closeness = 1;
              break;
      case 2: //start = false;
              closeness = 0.5;
              break;
      case 3: //start = false;
              closeness = 0.1;
              break;
   }

   glutPostRedisplay();
}

void boundary_menu(int value){
   boid.boundary_Menu(value);
}

void myClass::boundary_Menu(int value){
   switch(value){
      case 12: //start = false;
              Xmin = -3; Xmax = 3; Ymin = -3; Ymax = 3; Zmin = -3; Zmax = 3;
              break;
      case 13: //start = false;
              Xmin = -6; Xmax = 6; Ymin = -6; Ymax = 6; Zmin = -6; Zmax = 6;
              break;
      case 14: //start = false;
              Xmin = -8; Xmax = 8; Ymin = -8; Ymax = 8; Zmin = -8; Zmax = 8;
              break;
   }

   glutPostRedisplay();
}


void mymenu(int value){
 /*pre-condition: int menu operation value
  This function calls myMenu function to show the menu
*/ 
   
  boid.myMenu(value);
  glutPostRedisplay();
}

void myClass::myMenu(int value){
   
   switch (value) {
         
      case 4: 
            stop = false;
            start = true;
            break;
      case 5: exit(1);
   }
}



void myClass::initMenu (void)
// set up menu
{
   int sub_menu1;
   sub_menu1 = glutCreateMenu (size_menu);
   glutAddMenuEntry("Big", 6);
   glutAddMenuEntry("Median",7);
   glutAddMenuEntry("Small",8);

   
   int sub_menu2;
   sub_menu2 = glutCreateMenu (closeness_menu);
   glutAddMenuEntry("1", 1);
   glutAddMenuEntry("0.5",2);
   glutAddMenuEntry("0.1",3);

   int sub_menu3;
   sub_menu3 = glutCreateMenu (boundary_menu);
   glutAddMenuEntry("small range", 12);
   glutAddMenuEntry("median range",13);
   glutAddMenuEntry("large range",14);

   int sub_menu4;
   sub_menu4 = glutCreateMenu (num_menu);
   glutAddMenuEntry("15", 9);
   glutAddMenuEntry("20",10);
   glutAddMenuEntry("25",11);

   glutCreateMenu (mymenu);       // register callback function
   glutAddSubMenu ("Choose the size of the boid", sub_menu1);
   glutAddSubMenu ("Choose the closeness parameter", sub_menu2);
   glutAddSubMenu ("Choose the boundary movement parameter", sub_menu3);
   glutAddSubMenu ("Choose the number of boids", sub_menu4);
   glutAddMenuEntry ("Start the animation", 4);
   glutAddMenuEntry ("Quit", 5);
   glutAttachMenu (GLUT_RIGHT_BUTTON);
}


Vector myClass::pcjCalc(int j){
   Vector pcj;
   pcj.Vx = 0;
   pcj.Vy = 0;
   pcj.Vz = 0;
   for(int i = 0; i < numBoid; i++){
      if(i!=j){
         pcj.Vx = pcj.Vx + boidArray[i].Px;
         pcj.Vy = pcj.Vy + boidArray[i].Py;
         pcj.Vz = pcj.Vz + boidArray[i].Pz;
      }
   }
   pcj.Vx = pcj.Vx/(numBoid-1);
   pcj.Vy = pcj.Vy/(numBoid-1);
   pcj.Vz = pcj.Vz/(numBoid-1);
   return pcj;
}

Vector myClass::pvjCalc(int j){
   Vector pvj;
   pvj.Vx = 0;
   pvj.Vy = 0;
   pvj.Vz = 0;
   for(int i = 0; i < numBoid; i++){
      if(i!=j){
         pvj.Vx = pvj.Vx + boidArray[i].Vx;
         pvj.Vy = pvj.Vy + boidArray[i].Vy;
         pvj.Vz = pvj.Vz + boidArray[i].Vz;
      }
   }
   pvj.Vx = pvj.Vx/(numBoid-1);
   pvj.Vy = pvj.Vy/(numBoid-1);
   pvj.Vz = pvj.Vz/(numBoid-1);
   return pvj;
}

Vector myClass::rule1(myBoid b, int j){
   Vector pcj;
   pcj = boid.pcjCalc(j);
   for(int i = 0; i < numBoid; i++){
      if(i!=j){
         pcj.Vx = pcj.Vx + boidArray[i].Px;
         pcj.Vy = pcj.Vy + boidArray[i].Py;
         pcj.Vz = pcj.Vz + boidArray[i].Pz;
      }
   }
   pcj.Vx = pcj.Vx/(numBoid-1);
   pcj.Vy = pcj.Vy/(numBoid-1);
   pcj.Vz = pcj.Vz/(numBoid-1);
   pcj.Vx = (pcj.Vx - b.Px)/100;
   pcj.Vy = (pcj.Vy - b.Py)/100;
   pcj.Vz = (pcj.Vz - b.Pz)/100;
   return pcj;
}

Vector myClass::rule2(myBoid b, int j){
   Vector c;
   c.Vx = 0; c.Vy = 0; c.Vz = 0;
   for (int i = 0; i < numBoid; i++){
      if(i!=j){
         if (pow(pow(boidArray[i].Px - b.Px, 2)+ pow(boidArray[i].Py - b.Py, 2) + pow(boidArray[i].Pz - b.Pz, 2),0.5)< closeness){
            c.Vx = c.Vx - (boidArray[i].Px - b.Px);
            c.Vy = c.Vy - (boidArray[i].Py - b.Py);
            c.Vz = c.Vz - (boidArray[i].Pz - b.Pz);
         }
      }
   }
   return c;
}

Vector myClass::rule3(myBoid b, int j){
   Vector pvj;
   pvj = boid.pvjCalc(j);
   for(int i = 0; i < numBoid; i++){
      if(i!=j){
         pvj.Vx = pvj.Vx + boidArray[i].Vx;
         pvj.Vy = pvj.Vy + boidArray[i].Vy;
         pvj.Vz = pvj.Vz + boidArray[i].Vz;
      }
   }

   pvj.Vx = pvj.Vx/(numBoid-1);
   pvj.Vy = pvj.Vy/(numBoid-1);
   pvj.Vz = pvj.Vz/(numBoid-1);
   pvj.Vx = (pvj.Vx - b.Vx)/8;
   pvj.Vy = (pvj.Vy - b.Vy)/8;
   pvj.Vz = (pvj.Vz - b.Vz)/8;

   return pvj;
}

Vector myClass::bound_position(myBoid b, int j){
   Vector v;
   if(b.Px < Xmin){
      v.Vx = 1;
   }
   else if(b.Px > Xmax){
      v.Vx = -1;
   }
   if(b.Py < Ymin){
      v.Vy = 1;
   }
   else if(b.Py > Ymax){
      v.Vy = -1;
   }

   if(b.Pz < Zmin){
      v.Vz = 1;
   }
   else if(b.Pz > Zmax){
      v.Vz = -1;
   }
   return v;
}

Vector myClass::tendency(myBoid b){
   Vector place;
   place.Vx = (0-b.Px)/100;
   place.Vy = (0-b.Py)/100;
   place.Vz = (0-b.Pz)/100;
   return place;
}

void myClass::limitVelocity(int j){
   int vlim = 5;
   Vector v;
   float bVelocity;
   bVelocity = pow(pow(boidArray[j].Vy,2)+pow(boidArray[j].Vx,2)+pow(boidArray[j].Vz,2),2);
   if(bVelocity > vlim){
      boidArray[j].Vx = (boidArray[j].Vx/bVelocity)*vlim;
      boidArray[j].Vy = (boidArray[j].Vy/bVelocity)*vlim;
      boidArray[j].Vz = (boidArray[j].Vz/bVelocity)*vlim;
   }
}

void myClass::new_position(){
   Vector v1, v2, v3, v4, v5;
   for(int j = 0; j < numBoid; j++){
      v1 = boid.rule1(boidArray[j], j);
      v2 = boid.rule2(boidArray[j], j);
      v3 = boid.rule3(boidArray[j], j);
      v4 = boid.bound_position(boidArray[j], j);
      v5 = boid.tendency(boidArray[j]);
      boidArray[j].Vx = boidArray[j].Vx + v1.Vx + v2.Vx + v3.Vx + v4.Vx + v5.Vx;
      boidArray[j].Vy = boidArray[j].Vy + v1.Vy + v2.Vy + v3.Vy + v4.Vy + v5.Vy;
      boidArray[j].Vz = boidArray[j].Vz + v1.Vz + v2.Vz + v3.Vz + v4.Vz + v5.Vz;
      boid.limitVelocity(j);
      boidArray[j].Px = boidArray[j].Px + boidArray[j].Vx;
      boidArray[j].Py = boidArray[j].Py + boidArray[j].Vy;
      boidArray[j].Pz = boidArray[j].Pz + boidArray[j].Vz;
      //cout << boidArray[j].Px << endl;
      //cout << boidArray[j].Py << endl;
   }
}

void myClass::myIdle(){
   if(!stop){
      clock_t endWait;
      boid.new_position();
      /*wait*/
      endWait = clock () + num_ticks;

      /* please wait...*/
      while (clock () < endWait);

      glutPostRedisplay();       /* call Display function again */
   }
}

void Idle(void)
{
   boid.myIdle();  
}

void myClass::myDisplay(){
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   int color1, color2, color3;
   color1 = 1.0;
   color2 = 1.0;
   color3 = 0.0;
   glLoadIdentity ();
   gluLookAt (view_x,view_y , z,0.0 , 0.0, 0.0, 0.0, 1.0, 0.0);
  
   if(start){
      for (int i = 0; i < numBoid; i++){
         glColor3f(1.0, 0.0, 0.0);
         glBegin(GL_POLYGON);                       //1
            glVertex3f( boidArray[i].Px, boidArray[i].Py-0.6*size , boidArray[i].Pz+2*size);
            glVertex3f( boidArray[i].Px, boidArray[i].Py-0.6*size , boidArray[i].Pz-2*size);
            glVertex3f( boidArray[i].Px, boidArray[i].Py, boidArray[i].Pz-2*size);
            glVertex3f( boidArray[i].Px, boidArray[i].Py, boidArray[i].Pz+2*size);
         glEnd();
         glColor3f(0.8, 0.5, 0.0);
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
      }
   }
   
}

void display(){
    boid.myDisplay();
    glFlush();
}



void myClass::myKeyboard(unsigned char key, int x, int y){
/*pre-condition: key(unsigned char, IN), x(int, IN), y(int, IN)
  This function changes the boolean variables based on corresponding key
*/
    switch (key){
      case '2': if(view_y > -10.0)
                  view_y -= 0.2;
                else
                  cout << "Hitting limit(Y min)" << endl;
        break;
      case '4': if(view_x > -10.0)
                  view_x -= 0.2;
                else
                  cout << "Hitting limit(X min)" << endl;
        break;
      case '6': if(view_x < 10.0)
                  view_x += 0.2;
                else
                  cout << "Hitting limit(X max)" << endl;
        break;
      case '8': if(view_y < 10.0)
                  view_y += 0.2;
                else
                  cout << "Hitting limit(Y max)" << endl;
        break;
      case '5': stop = true;
        break;
      case '7':
            num_ticks = num_ticks +10000;
            cout << " Slowing down" << endl;
        break;
      case '9':
            num_ticks = num_ticks -10000;
            cout << " Speeding up" << endl;
        break;
      }
    glutPostRedisplay();
}




void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   /* set up matrices for projection coordinate system */
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1, 1, -1, 1, 1.5, 20.0);

   /* reset matrices to user's coordinate system */
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
    boid.myKeyboard(key, x, y);
}

void hint ()
{
  cout << "Hint:" << endl;
  cout << "Press '2' to move camera down" << endl;
  cout << "Press '4' to move camera left" << endl;
  cout << "Press '6' to move camera right" << endl;
  cout << "Press '8' to move camera up" << endl;
  cout << "Press '7' to make the animation slower" << endl;
  cout << "Press '9' to make the animation faster" << endl;
  cout << "Press '5' to stop the animation" << endl;
  cout << "Right click for more options" << endl;
}
int main (int argc, char** argv)
{
   hint();
   
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   /* set up the window size, in pixels */
   glutInitWindowSize (windowHeight, windowWidth);

   /* put the window at 100, 100 on user's screen */
   glutInitWindowPosition (100, 100);

   /* make a title for window */
   glutCreateWindow ("Boids");

   /* set up some GL stuff */
   boid.init ();
   

   /*display the menu*/
   //boid.printMenu();


   /* check the keyboard continuously by calling keyboard function */
   glutKeyboardFunc(keyboard);

   glutReshapeFunc (reshape);

   /*initialize the menu*/
   boid.initMenu ();

   /* call display function */
   glutDisplayFunc(display);

   /* initilize mouse function*/
   //glutMouseFunc (mymouse);

   /*animation*/
   
      glutIdleFunc( Idle );
   
   

   /* repeat these things indefinitely */
   glutMainLoop();

   /* we're done! */
   return 0;
}