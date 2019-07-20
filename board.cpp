#include <GL/gl.h>

const GLfloat Colors[8][3] = {
  {1,1,1},
  {0,1,1}, // Square     - Turkus
  {1,0,0}, // Line       - Czerwony
  {1,1,0}, // L          - Zloty
  {1,0,1}, // Mirrored L - Fiolet
  {0,1,0}, // Z          - Niebieski
  {0,0,1}, // Mirrored Z - Zielony
  {0.5,0.5,0.5} // Nose  - Szary
};

void drawBoard(int board[22][22], int figure[4][3], int nextFigure[4][3], int menu, int typing) {
  GLfloat Syh=-1.0, Syl=-0.9, Sxl=-1.0, Sxh=-0.9;

  for(int j = 1; j < 21; j++) {
    Sxl=-1.0;
    Sxh=-0.9;
    
    for(int i = 1; i < 21; i++) {
      if((i + j) % 2 == 0)
        glColor3f(0, 0.1, 0); 
      else
        glColor3f(0, 0, 0.1); 
        
      if(board[j][i] != 0)
        glColor3fv(Colors[board[j][i]]);
      
      if((i + j) % 2 == 0 && i > 10)
        glColor3f(0.1, 0.1, 0); 
      else if((i + j) % 2 != 0 && i > 10)
        glColor3f(0.1, 0, 0.1);
      
      if(board[j][i] != 0 && i>11) {
        glColor3fv(Colors[board[j][i]]);
      }
      
      if(j == figure[0][1] && i == figure[0][0])
        glColor3fv(Colors[figure[0][2]]);
      if(j == figure[1][1] && i == figure[1][0])
        glColor3fv(Colors[figure[1][2]]);
      if(j == figure[2][1] && i == figure[2][0])
        glColor3fv(Colors[figure[2][2]]);
      if(j == figure[3][1] && i == figure[3][0])
        glColor3fv(Colors[figure[3][2]]);

      if(j == nextFigure[0][1] && i == nextFigure[0][0])
        glColor3fv(Colors[nextFigure[0][2]]);
      if(j == nextFigure[1][1] && i == nextFigure[1][0])
        glColor3fv(Colors[nextFigure[1][2]]);
      if(j == nextFigure[2][1] && i == nextFigure[2][0])
        glColor3fv(Colors[nextFigure[2][2]]);
      if(j == nextFigure[3][1] && i == nextFigure[3][0])
        glColor3fv(Colors[nextFigure[3][2]]);

      if((typing == 1 || menu == 11 || menu == 22) && j == 15 && i > 11 &&  i < 20)
        glColor3fv(Colors[6]);
      
      if(typing == 1 && j == 13 && i > 12 && i < 19)
        glColor3fv(Colors[1]);
        
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

void drawBoard(int board[20][20], int menu, int selectedItem)
{
  GLfloat Syh=-1.0, Syl=-0.9, Sxl=-1.0, Sxh=-0.9;

  for(int j=0;j<20;j++) {
    Sxl=-1.0;
    Sxh=-0.9;
    
    for(int i=0;i<20;i++) {
      if((i+j)%2==0)
        glColor3f(0, 0.1, 0); 
      else
        glColor3f(0, 0, 0.1); 
          
      if(board[j][i] != 0)
        glColor3fv(Colors[board[j][i]]);

      if((board[j][i]==7 && selectedItem == 0 && j==9) ||
        (board[j][i]==7 && selectedItem == 1 && j==7) ||
        (board[j][i]==7 && selectedItem == 2 && j==5) ||
        (board[j][i]==7 && selectedItem == 3 && j==3) ||
        (board[j][i]==7 && selectedItem == 4 && j==1))
        glColor3fv(Colors[0]);
        
      if((board[j][i]==7 && menu == 4 && j==9) ||
        (board[j][i]==7 && menu == 4 && j==7) ||
        (board[j][i]==7 && menu == 4 && j==5) ||
        (board[j][i]==7 && menu == 4 && j==3) ||
        (board[j][i]==7 && menu == 4 && j==1))
        glColor3fv(Colors[3]);
        
      glBegin( GL_QUADS );
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
