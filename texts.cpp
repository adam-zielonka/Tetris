#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

void drawText(string String, int x, int y)
{
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
  for (unsigned int i=0; i<String.size(); i++)
  {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
  }
  glPopAttrib();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

void MainMenuTexts()
{
  glColor3f(0, 0, 0);
  char string[64];

  sprintf(string, "Nowa Gra");
  drawText(string, 250, 281);

  sprintf(string, "Pomoc");
  drawText(string, 250, 225);
  
  sprintf(string, "Ustawienia");
  drawText(string, 250, 168);
  
  sprintf(string, "Wyniki");
  drawText(string, 250, 111);
  
  sprintf(string, "Wyjscie");
  drawText(string, 250, 55);
}

void GameTexts(int menu, char bestName[64], char bestPoints[64], int points) {
  glColor3f(0, 0, 0);
  char string[64];

  sprintf(string, "Punkty");
  drawText(string, 390, 540);

  sprintf(string, "%i", points);
  drawText(string, 460, 540);
  
  drawText(bestName, 370, 483);
  drawText(bestPoints, 490, 483);
  
  if(menu == 10) {
    sprintf(string, "Podaj imie i koncz [ESC]");
    drawText(string, 332, 426);
  }
  
  if(menu == 11) {
    sprintf(string, "Przegrales i koncz [ESC]");
    drawText(string, 332, 426);
  }
}

void PauseTexts() {
  glColor3f(0, 0, 0);
  char string[64];

  sprintf(string, "Pauza! Kliknij [P] i graj");
  drawText(string, 332, 426);
}

void HelpTexts() {
  glColor3f(0, 0, 0);
  char string[64];

  sprintf(string, "Sterowanie:");
  drawText(string, 90, 280);
  sprintf(string, "Strzalki:");
  drawText(string, 80, 256);
  sprintf(string, "W gore - obrot");
  drawText(string, 80, 232);
  sprintf(string, "W dol - opadanie");
  drawText(string, 80, 209);
  sprintf(string, "W prawo");
  drawText(string, 80, 183);
  sprintf(string, "W lewo");
  drawText(string, 80, 157);
  
  sprintf(string, "Inne:");
  drawText(string, 250, 256);
  sprintf(string, "[ESC] Wyjscie/Powrot");
  drawText(string, 250, 232);
  sprintf(string, "[SPACJA] Wybor z Menu");
  drawText(string, 250, 209);
  sprintf(string, "[F1] Pomoc");
  drawText(string, 250, 183);
  sprintf(string, "[P] Pauza");
  drawText(string, 250, 157);
}

void SettingsTexts(int speed) {
  glColor3f(0, 0, 0);
  char string[64];

  sprintf(string, "Ustawienia:");
  drawText(string, 90, 280);
  sprintf(string, "Pretkosc [+][-]");
  drawText(string, 80, 256);
  sprintf(string, " ");
  drawText(string, 80, 232);
  sprintf(string, " ");
  drawText(string, 80, 209);
  sprintf(string, " ");
  drawText(string, 80, 183);
  sprintf(string, " ");
  drawText(string, 80, 157);
  
  sprintf(string,"%i",speed);
  drawText(string, 250, 256);
  sprintf(string, " ");
  drawText(string, 250, 232);
  sprintf(string, " ");
  drawText(string, 250, 209);
  sprintf(string, " ");
  drawText(string, 250, 183);
  sprintf(string, " ");
  drawText(string, 250, 157);
}

void BestResultsTexts(char resultNames[6][64], char resultCPoint[6][64]) {
  glColor3f(0, 0, 0);

  for (int i = 1, y = 0; i < 6; i++, y += 57) {
      drawText(resultNames[i], 220, 281 - y);
      drawText(resultCPoint[i], 340, 281 - y);
  }    
}

void SaveTexts(char name[64]) {
  drawText(name, 390, 369);
}