#ifdef USEGLEW
  #include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include <math.h>
#define PI 3.14159265f
#include <stdlib.h>
#include <stdio.h>

#define ESCAPE '\033'

GLint Width = 1000, Height = 800;
double dim = 3.0;
int th = 80;  /* azimuth of view angle */
int ph = 20;  /* elevation of view angle */

// torus
GLdouble innerRaidus = 0.5;
GLdouble outterRaidus = 1;
GLint sides = 50;
GLint rings = 50;
GLfloat xRotated = 30.0;
GLfloat yRotated = 33.0;
GLfloat zRotated = 40.0;

void drawAxes() {
  glBegin(GL_LINES);
  // X - red
  glColor3f(1,0,0);
  glVertex3d(-dim,0,0);
  glVertex3d(dim,0,0);

  // Y - green
  glColor3f(0,1,0);
  glVertex3d(0,-dim,0);
  glVertex3d(0,dim,0);

  // Z - blue
  glColor3f(0,0,1);
  glVertex3d(0,0,-dim);
  glVertex3d(0,0,dim);

  glEnd();

  glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(dim,0,0);
    glRotated(90,0,1,0);
    glutSolidCone(0.1,0.1,10,10);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0,1,0);
    glTranslatef(0,dim,0);
    glRotated(-90,1,0,0);
    glutSolidCone(0.1,0.1,10,10);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(0,0,dim);
    glutSolidCone(0.1,0.1,10,10);
  glPopMatrix();
}

void display() {
  /*  Clear the image */
  glClear(GL_COLOR_BUFFER_BIT);
  /*  Reset previous transforms */
  glLoadIdentity();

  glRotated(ph,1,0,0);
  glRotated(th,0,1,0);

  drawAxes();

  glColor3f(0, 1, 0); 
  glTranslatef(-1.5,0.5,-1.5);
  glScalef(0.3, 0.3, 0.3);
  glutSolidTorus(innerRaidus, outterRaidus, sides, rings);

  glutSolidTorus(innerRaidus, outterRaidus, sides, rings);

  /*  Flush and swap */
  glFlush();
  glutSwapBuffers();

  // glLoadIdentity();
  // glTranslatef(-0.5,1.0,-4.5);
  // glScalef(0.5, 0.5, 0.5);
  // glutSolidTorus(innerRaidus, outterRaidus, sides, rings);

  // glFlush();
}

void reshape(GLint width, GLint height) {
  double w2h = (height>0) ? (double)width/height : 1;
  glViewport(0,0, width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* orthogonal projection */
  glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
  if(key == ESCAPE) {
    exit(0);
  }
}

void windowSpecial(int key,int x,int y)
{
  /*  Right arrow key - increase azimuth by 5 degrees */
  if (key == GLUT_KEY_RIGHT) th += 5;
  /*  Left arrow key - decrease azimuth by 5 degrees */
  else if (key == GLUT_KEY_LEFT) th -= 5;
  /*  Up arrow key - increase elevation by 5 degrees */
  else if (key == GLUT_KEY_UP) ph += 5;
  /*  Down arrow key - decrease elevation by 5 degrees */
  else if (key == GLUT_KEY_DOWN) ph -= 5;

  /*  Keep angles to +/-360 degrees */
  th %= 360;
  ph %= 360;

  glutPostRedisplay();
}

int main(int argc, char ** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(Width, Height);
  glutCreateWindow("Red square example");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(windowSpecial);

  glutMainLoop();

  return 0;
}
