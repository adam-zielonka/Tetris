#include "./engine/texts.cpp"

void MainMenuTexts() {
  renderText("Nowa Gra", 250, 281);
  renderText("Pomoc", 250, 225);
  renderText("Ustawienia", 250, 168);
  renderText("Wyniki", 250, 111);
  renderText("Wyjscie", 250, 55);
}

void GameTexts(int menu, char bestName[64], char bestPoints[64], int points) {
  renderText("Punkty", 390, 540);
  renderText(points, 460, 540);
  renderText(bestName, 370, 483);
  renderText(bestPoints, 490, 483);
  
  if(menu == 10) 
    renderText("Podaj imie i koncz [ESC]", 332, 426);
  
  if(menu == 11)
    renderText("Przegrales i koncz [ESC]", 332, 426);
}

void PauseTexts() {
  renderText("Pauza! Kliknij [P] i graj", 332, 426);
}

void HelpTexts() {
  renderText("Sterowanie:", 90, 280);
  renderText("Strzalki:", 80, 256);
  renderText("W gore - obrot", 80, 232);
  renderText("W dol - opadanie", 80, 209);
  renderText("W prawo", 80, 183);
  renderText("W lewo", 80, 157);
  
  renderText("Inne:", 250, 256);
  renderText("[ESC] Wyjscie/Powrot", 250, 232);
  renderText("[SPACJA] Wybor z Menu", 250, 209);
  renderText("[F1] Pomoc", 250, 183);
  renderText("[P] Pauza", 250, 157);
}

void SettingsTexts(int speed) {
  renderText("Ustawienia:", 90, 280);
  renderText("Pretkosc [+][-]", 80, 256);
  renderText(speed, 250, 256);
}

void BestResultsTexts(char resultNames[6][64], char resultCPoint[6][64]) {
  for (int i = 1, y = 0; i < 6; i++, y += 57) {
    renderText(resultNames[i], 220, 281 - y);
    renderText(resultCPoint[i], 340, 281 - y);
  }    
}

void SaveTexts(char name[64]) {
  renderText(name, 390, 369);
}
