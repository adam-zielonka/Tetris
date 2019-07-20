#include <GL/gl.h>

const GLfloat Colors[12][3] = {
  {1,1,1},
  {0,1,1}, // Square     - Turkus
  {1,0,0}, // Line       - Czerwony
  {1,1,0}, // L          - Zloty
  {1,0,1}, // Mirrored L - Fiolet
  {0,1,0}, // Z          - Niebieski
  {0,0,1}, // Mirrored Z - Zielony
  {0.5,0.5,0.5}, // Nose - Szary
  {0, 0.1, 0}, // Background 1A //8
  {0, 0, 0.1}, // Background 1B //9
  {0.1, 0.1, 0}, // Background 2A //10
  {0.1, 0, 0.1} // Background 2B //11
};

void renderBoard(int board[20][20]) {
  GLfloat Syh=-1.0, Syl=-0.9, Sxl=-1.0, Sxh=-0.9;

  for(int j = 0; j < 20; j++) {
    Sxl=-1.0;
    Sxh=-0.9;
    
    for(int i = 0; i < 20; i++) {
      glColor3fv(Colors[board[j][i]]);
        
      glBegin(GL_QUADS);
        glVertex3f(Sxl, Syl, 0);
        glVertex3f(Sxh, Syl, 0);
        glVertex3f(Sxh, Syh, 0); 
        glVertex3f(Sxl, Syh, 0); 
      glEnd();
      
      Sxl+=0.1;
      Sxh+=0.1;
    }
    Syl+=0.1;
    Syh+=0.1;
  }
}
