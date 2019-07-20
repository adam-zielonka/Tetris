#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

void renderText(string String, int x, int y) {
  glColor3f(0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, 600, 0, 600, -1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glPushAttrib(GL_DEPTH_TEST);
  glDisable(GL_DEPTH_TEST);
  glRasterPos2i(x,y);
  for (unsigned int i=0; i<String.size(); i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
  }
  glPopAttrib();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

void renderText(int number, int x, int y) {
  char string[64];
  sprintf(string, "%i", number);
  renderText(string, x, y);
}
