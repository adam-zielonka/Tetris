//sudo add-apt-repository universe
//sudo apt install mesa-common-dev libglu1-mesa-dev freeglut3-dev  -y
//g++ -p -Wall -pedantic -o tetris.out tetris.cpp -lGL -lGLU -lglut -lm
//./tetris.out
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include "utils.cpp"
#include "file.cpp"
#include "texts.cpp"
#include "board.cpp"
#include "engine.cpp"

using namespace std;
 
GLint speed = 1000;

int menu = 0;
int selectedMenuItem = 0;

int points = 0;

char playerName[64];
int playerNameLength = 0;
int typing = 0;

int resultPoints[6] = {0,0,0,0,0,0};
char resultNames[6][64];
char resultCPoints[6][64];

int figure[4][3];
int nextFigure[4][3];

int figureCode = 0;
int nextFigureCode = 0;

int board[22][22] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,5,5,5,5,5,5,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,3,3,3,3,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0}
};

int list[20][20] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,1,0,2,2,2,0,3,0,4,0,4,4,0,5,0,6,6,0},
  {0,0,1,0,2,0,0,0,3,0,4,0,4,0,0,5,0,0,6,0},
  {0,0,1,0,2,2,0,0,3,0,4,4,4,4,0,5,0,0,6,0},
  {0,0,1,0,2,0,0,0,3,0,4,0,0,4,0,5,0,6,6,0},
  {0,0,1,0,2,2,2,0,3,0,4,4,4,4,0,5,0,6,0,0},
  {0,0,1,0,0,0,0,0,3,0,0,0,0,0,0,5,0,6,0,0},
  {0,1,1,1,1,1,0,3,3,3,3,3,3,3,0,5,0,6,6,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int popover[20][20] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
  {0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
  {0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
  {0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
  {0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
  {0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,1,0,2,2,2,0,3,0,4,0,4,4,0,5,0,6,6,0},
  {0,0,1,0,2,0,0,0,3,0,4,0,4,0,0,5,0,0,6,0},
  {0,0,1,0,2,2,0,0,3,0,4,4,4,4,0,5,0,0,6,0},
  {0,0,1,0,2,0,0,0,3,0,4,0,0,4,0,5,0,6,6,0},
  {0,0,1,0,2,2,2,0,3,0,4,4,4,4,0,5,0,6,0,0},
  {0,0,1,0,0,0,0,0,3,0,0,0,0,0,0,5,0,6,0,0},
  {0,1,1,1,1,1,0,3,3,3,3,3,3,3,0,5,0,6,6,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void renderBoard(Board board) {
  renderBoard(board.xy);
}

void renderTexts(vector<Text> texts) {
  for (size_t i = 0; i < texts.size(); i++)
    renderText(texts[i].value, texts[i].x, texts[i].y);
}

void ReadResults() {
  readResultsFile(resultNames, resultPoints, resultCPoints);
}

void SaveResults() {
  saveResultFile(resultNames, resultPoints, playerName, points);
  ReadResults();
  menu = 4;
}

void GameOver() {
  if(points>resultPoints[5]) menu = 10;
  else menu = 11;
}

void SetNextFigure() {
  nextFigureCode = rand()%(0-7)+0;
  drawNextFigure(nextFigure, nextFigureCode);  
}

void SetFigure() {
  figureCode = nextFigureCode;
  drawFigure(figure, figureCode);

  if(isCanNotDraw(board, figure)) GameOver();
}

void RotateFigure() {
  figureCode = drawRotate(board, figure, figureCode);
}

void MoveFigureDown() {
  if(moveFigureY(board, figure)) {
    SetFigure();
    SetNextFigure();
  }    
}

void MoveFigureLeft() {
  moveFigureX(board, figure, -1);
}

void MoveFigureRight() {
  moveFigureX(board, figure, +1);
}

void DeleteLines() {
  points += deleteLine(board);
}

void RenderBoard() {
  renderBoard(drawBoard(board, figure, nextFigure, menu, typing));
}

void RenderPopover() {
  renderBoard(drawBoard(popover));
}

void RenderList() {    
  renderBoard(drawBoard(list, menu, selectedMenuItem));
}

void RenderGameTexts() {
  renderTexts(GameTexts(menu, resultNames[1], resultCPoints[1], points));
}

void NewGame() {
  clearBoard(board);
  points = 0;
  SetNextFigure();
  SetFigure();   
  SetNextFigure(); 
}

void RenderSaveTexts() {
  typing = 1;
  renderTexts(SaveTexts(playerName));
}

void Display() {   
  glClearColor(1, 1, 1, 1);        
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);

  if(menu == 0) { // Main Menu
    RenderList();
    renderTexts(MainMenuTexts());
  }

  if(menu == 1) { // Game
    DeleteLines();
    RenderBoard();
    RenderGameTexts();
  }
  
  if(menu == 2) { // Help
    RenderPopover();
    renderTexts(HelpTexts());
  }
  
  if(menu == 3) { // Settings
    RenderPopover();
    renderTexts(SettingsTexts(speed));
  }
  
  if(menu == 4) { // Best Results
    RenderList();
    renderTexts(BestResultsTexts(resultNames, resultCPoints));
  }
  
  if(menu == 10) { // Game Over with result save 
    RenderBoard();
    RenderGameTexts();
    RenderSaveTexts();
  }
  
  if(menu == 11) { // Game Over
    RenderBoard();
    RenderGameTexts();
  }

  if(menu == 22) { // Pause
    RenderBoard();
    RenderGameTexts();
    renderTexts(PauseTexts());
  }

  glFlush();
  glutSwapBuffers();
}

void Timer(int value) {   
  if(menu == 1) MoveFigureDown();
  Display();
  glutTimerFunc(speed, Timer, 0);
}

void Reshape(int width, int height)
{ 
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, 1, 1, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0, 0, 1.5, 0, 0, 0, 0, 1, 0);
  Display();
}

void Keyboard(unsigned char key, int x, int y) {   
  ReadResults();

  if((key == 'P' || key == 'p') && menu == 1) {
    menu = 22;
    key=0;
  }

  if((key == 'P' || key == 'p') && menu == 22) {
    menu = 1;
  }

  if(key == '+' && speed<2000) {
    speed+=100;
  }

  if(key == '-' && speed>0) {
    speed-=100;
  }  

  if(key == ' ' && menu == 0) {
    switch(selectedMenuItem) {  
      case 0:
        menu = 1;
        NewGame();
        break; 
      case 1:
        menu = 2;
        break; 
      case 2:
        menu = 3;
        break; 
      case 3:
        menu = 4;
        break; 
      case 4:
        exit(0);
        break;
    }
  }
  
  if(typing == 1 
      && ((key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <=122)) 
      && playerNameLength <=10 ) {

      playerName[playerNameLength] = key;
      playerNameLength++;
  }
  
  if(typing == 1 && key == 8 && playerNameLength > 0) {
      playerNameLength--;
      playerName[playerNameLength] = 0;
  }
  
  if(key == 27 && typing == 1) {
      menu = 0;
      typing = 0;
      key = 0;
      SaveResults();
  }
  else if(key == 27 && menu == 11) {
      menu = 4;
  }
  else if(key == 27 && menu == 0) {
      exit( 0 );
  }
  else if(key == 27) {
      menu = 0;
  }
  
  Display();
}

void SpecialChars(int key, int x, int y) { 
  if(key == GLUT_KEY_F1 && menu == 1) {
    menu = 2;
    key = 0;
  }
  
  if(key == GLUT_KEY_F1 && menu == 2) {
    menu = 1;
    key = 0;
  }

  if(menu == 1) {
    switch(key) {  
      case GLUT_KEY_UP:
        RotateFigure();
        break; 
      case GLUT_KEY_DOWN:
        MoveFigureDown();
        break;  
      case GLUT_KEY_LEFT:
        MoveFigureLeft();
        break; 
      case GLUT_KEY_RIGHT:
        MoveFigureRight();
        break; 
      case GLUT_KEY_END:
        menu = 0;
        key = 0;      
        break; 
    }
  }
  if(menu == 0) {
    switch(key) {  
      case GLUT_KEY_DOWN:
        if(selectedMenuItem == 4) selectedMenuItem = 0;
        else selectedMenuItem++;
        break; 
      case GLUT_KEY_UP:
        if(selectedMenuItem == 0) selectedMenuItem = 4;
        else selectedMenuItem--;
        break;  
      case GLUT_KEY_LEFT:

        break; 
      case GLUT_KEY_RIGHT:

        break; 
      case GLUT_KEY_END:
        exit(0);        
        break; 
    }
  }
  
  Display();
} 

int main(int argc, char * argv[]) {   
  ReadResults();
  srand(time(NULL));
  glutInit(& argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Tetris");
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(SpecialChars);    
  glutTimerFunc(speed, Timer, 0);
  glutMainLoop();
  return 0;
}
