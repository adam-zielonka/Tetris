#include "engine.cpp"

void MainMenuTexts() {
  drawText("Nowa Gra", 250, 281);
  drawText("Pomoc", 250, 225);
  drawText("Ustawienia", 250, 168);
  drawText("Wyniki", 250, 111);
  drawText("Wyjscie", 250, 55);
}

void GameTexts(int menu, char bestName[64], char bestPoints[64], int points) {
  drawText("Punkty", 390, 540);
  drawText(points, 460, 540);
  drawText(bestName, 370, 483);
  drawText(bestPoints, 490, 483);
  
  if(menu == 10) 
    drawText("Podaj imie i koncz [ESC]", 332, 426);
  
  if(menu == 11)
    drawText("Przegrales i koncz [ESC]", 332, 426);
}

void PauseTexts() {
  drawText("Pauza! Kliknij [P] i graj", 332, 426);
}

void HelpTexts() {
  drawText("Sterowanie:", 90, 280);
  drawText("Strzalki:", 80, 256);
  drawText("W gore - obrot", 80, 232);
  drawText("W dol - opadanie", 80, 209);
  drawText("W prawo", 80, 183);
  drawText("W lewo", 80, 157);
  
  drawText("Inne:", 250, 256);
  drawText("[ESC] Wyjscie/Powrot", 250, 232);
  drawText("[SPACJA] Wybor z Menu", 250, 209);
  drawText("[F1] Pomoc", 250, 183);
  drawText("[P] Pauza", 250, 157);
}

void SettingsTexts(int speed) {
  drawText("Ustawienia:", 90, 280);
  drawText("Pretkosc [+][-]", 80, 256);
  drawText(speed, 250, 256);
}

void BestResultsTexts(char resultNames[6][64], char resultCPoint[6][64]) {
  for (int i = 1, y = 0; i < 6; i++, y += 57) {
    drawText(resultNames[i], 220, 281 - y);
    drawText(resultCPoint[i], 340, 281 - y);
  }    
}

void SaveTexts(char name[64]) {
  drawText(name, 390, 369);
}
