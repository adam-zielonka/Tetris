//sudo add-apt-repository universe
//sudo apt install mesa-common-dev libglu1-mesa-dev freeglut3-dev  -y
//g++ -p -Wall -pedantic -o tetris.out tetris.cpp -lGL -lGLU -lglut -lm -std=c++0x 
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

using namespace std;
 
//Szybkos� spadania
GLint speed= 1000;
int menu = 0;
int menuwyb = 0;
int punkty = 0;
char imie[64];
int wpisywanie =0;
int imieznkow =0;
int wynikipunkty[6] = {0,0,0,0,0,0};
char wynikiimie[6][64];
char wynikippp[6][64];

int plan[22][22] = {
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

int logo[20][20] = {
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


int pop[20][20] = {
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

int obiekt[4][3] = {
  {6,20,1},
  {6,19,1},
  {5,20,1},
  {5,19,1}
};
int obiekt2[4][3] = {
  {6,20,1},
  {6,19,1},
  {5,20,1},
  {5,19,1}
};

int gen = 0;
int nastepny = 0;

void OdczytZPlku() {
  readResultsFile(wynikiimie, wynikipunkty, wynikippp);
}

void ZapiszDoPliku() {
  saveResultFile(wynikiimie, wynikipunkty, imie, punkty);
  OdczytZPlku();
  menu = 4;
}

void KoniecGry() {
  if(punkty>wynikipunkty[5]) menu = 10;
  else menu = 11;
}

void GenerujNext() {
  nastepny = rand()%(0-7)+0;
  drawNextFigure(obiekt2, nastepny);  
}

void GenerujObjekt() {
  gen = nastepny;
  drawFigure(obiekt, gen);

  if(isCanNotDraw(plan, obiekt)) KoniecGry();
}

void Obruc() {
  gen = drawRotate(plan, obiekt, gen);
}

void PrzesunObiekt() {
  if(moveFigureY(plan, obiekt)) {
    GenerujObjekt();
    GenerujNext();
  }    
}

void PrzesunLewo() {
  moveFigureX(plan, obiekt, -1);
}

void PrzesunPrawo() {
  moveFigureX(plan, obiekt, +1);
}

void KasujLinie() {
  punkty += deleteLine(plan);
}

void Wypelni() {
  drawBoard(plan, obiekt, obiekt2, menu, wpisywanie);
}

void Pomoc() {
  drawBoard(pop);
}

void Logo() {    
  drawBoard(logo, menu, menuwyb);
}

void GameTekst() {
  GameTexts(menu, wynikiimie[1], wynikippp[1], punkty);
}

void NowaGra() {
  clearBoard(plan);
  punkty = 0;
  GenerujNext();
  GenerujObjekt();   
  GenerujNext(); 
}

void Zapisz() {
  wpisywanie = 1;
  SaveTexts(imie);
}

// funkcja generuj�ca scen� 3D
void Display() {   
  //Generowanie t�a
  glClearColor(1, 1, 1, 1);        
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);

  if(menu == 1) {
    KasujLinie();
    Wypelni();
    GameTekst();
  }
  
  if(menu == 0) {
    Logo();
    MainMenuTexts();
  }
  
  //Pomoc
  if(menu == 2) {
    Pomoc();
    HelpTexts();
  }
  //Ustawieni    
  if(menu == 3) {
    Pomoc();
    SettingsTexts(speed);
  }
  
  //Wyniki
  if(menu == 4) {
    Logo();
    BestResultsTexts(wynikiimie, wynikippp);
  }
  
  //KoniecGry
  if(menu == 10) {
    Wypelni();
    GameTekst();
    Zapisz();
  }
  
  if(menu == 11) {
    Wypelni();
    GameTekst();
  }

  if(menu == 22) {
    Wypelni();
    GameTekst();
    PauseTexts();
  }

  // skierowanie polece� do wykonania
  glFlush();    
  // zamiana bufor�w koloru
  glutSwapBuffers();
}

void Timer(int value) {   
  if(menu == 1) {
      PrzesunObiekt();  
  } 
  // wy�wietlenie sceny
  Display();    
  // nast�pne wywo�anie funkcji timera
  glutTimerFunc( speed, Timer, 0 );
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
  OdczytZPlku();

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
    switch(menuwyb) {  
      case 0:
        menu = 1;
        NowaGra();
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
  
  if(wpisywanie == 1 
      && ((key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <=122)) 
      && imieznkow <=10 ) {

      imie[imieznkow] = key;
      imieznkow++;
  }
  
  if(wpisywanie == 1 && key == 8 && imieznkow > 0) {
      imieznkow--;
      imie[imieznkow] = 0;
  }
  
  if(key == 27 && wpisywanie == 1) {
      menu = 0;
      wpisywanie = 0;
      key = 0;
      ZapiszDoPliku();
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

void Znaki_Spec(int key, int x, int y) { 
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
        Obruc();
        break; 
      case GLUT_KEY_DOWN:
        PrzesunObiekt();
        break;  
      case GLUT_KEY_LEFT:
        PrzesunLewo();
        break; 
      case GLUT_KEY_RIGHT:
        PrzesunPrawo();
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
        if(menuwyb == 4) menuwyb = 0;
        else menuwyb++;
        break; 
      case GLUT_KEY_UP:
        if(menuwyb == 0) menuwyb = 4;
        else menuwyb--;
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
  
  //narysowanie sceny
  Display();
} 

int main(int argc, char * argv[]) {   
  OdczytZPlku();
  srand(time(NULL));
  glutInit(& argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Tetris");
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(Znaki_Spec);    
  glutTimerFunc( speed, Timer, 0 );
  glutMainLoop();
  return 0;
}
