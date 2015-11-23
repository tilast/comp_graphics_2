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

GLint Width = 512, Height = 512;
const int CubeSize = 200;

void displayCube() {
  GLint left = (Width - CubeSize) / 2;
  GLint right = left + CubeSize;
  GLint top = (Height - CubeSize) / 2;
  GLint bottom = top + CubeSize;

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(255, 0, 0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(left, top);
    glVertex2f(right, top);
    glVertex2f(right, bottom);
    glVertex2f(left, bottom);
  glEnd();

  glFinish();
}

void reshapeCube(GLint w, GLint h) {
  Width = w;
  Height = h;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, w, 0, h, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyboardCube(unsigned char key, int x, int y) {
  if(key == ESCAPE) {
    exit(0);
  }
}

int main(int argc, char ** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(Width, Height);
  glutCreateWindow("Red square example");

  glutDisplayFunc(displayCube);
  glutReshapeFunc(reshapeCube);
  glutKeyboardFunc(keyboardCube);

  glutMainLoop();

  return 0;
}