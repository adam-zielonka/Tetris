#include <vector>

class Text {
  public:
    string value;
    int x;
    int y;

    Text(string _value, int _x, int _y) {
      value = _value;
      x = _x;
      y = _y;
    }

    Text(int _number, int _x, int _y) {
      char _text[64];
      sprintf(_text, "%i", _number);
      Text(_text, _x, _y);
    }
};

vector<Text> MainMenuTexts() {
  vector<Text> texts;
  texts.push_back(Text("Nowa Gra", 250, 281));
  texts.push_back(Text("Pomoc", 250, 225));
  texts.push_back(Text("Ustawienia", 250, 168));
  texts.push_back(Text("Wyniki", 250, 111));
  texts.push_back(Text("Wyjscie", 250, 55));
  return texts;
}

vector<Text> GameTexts(int menu, char bestName[64], char bestPoints[64], int points) {
  vector<Text> texts;
  texts.push_back(Text("Punkty", 390, 540));
  texts.push_back(Text(points, 460, 540));
  texts.push_back(Text(bestName, 370, 483));
  texts.push_back(Text(bestPoints, 490, 483));
  
  if(menu == 10) 
    texts.push_back(Text("Podaj imie i koncz [ESC]", 332, 426));
  
  if(menu == 11)
    texts.push_back(Text("Przegrales i koncz [ESC]", 332, 426));

  return texts;
}

vector<Text> PauseTexts() {
  vector<Text> texts;
  texts.push_back(Text("Pauza! Kliknij [P] i graj", 332, 426));
  return texts;
}

vector<Text> HelpTexts() {
  vector<Text> texts;
  texts.push_back(Text("Sterowanie:", 90, 280));
  texts.push_back(Text("Strzalki:", 80, 256));
  texts.push_back(Text("W gore - obrot", 80, 232));
  texts.push_back(Text("W dol - opadanie", 80, 209));
  texts.push_back(Text("W prawo", 80, 183));
  texts.push_back(Text("W lewo", 80, 157));
  
  texts.push_back(Text("Inne:", 250, 256));
  texts.push_back(Text("[ESC] Wyjscie/Powrot", 250, 232));
  texts.push_back(Text("[SPACJA] Wybor z Menu", 250, 209));
  texts.push_back(Text("[F1] Pomoc", 250, 183));
  texts.push_back(Text("[P] Pauza", 250, 157));
  return texts;
}

vector<Text> SettingsTexts(int speed) {
  vector<Text> texts;
  texts.push_back(Text("Ustawienia:", 90, 280));
  texts.push_back(Text("Pretkosc [+][-]", 80, 256));
  texts.push_back(Text(speed, 250, 256));
  return texts;
}

vector<Text> BestResultsTexts(char resultNames[6][64], char resultCPoint[6][64]) {
  vector<Text> texts;
  for (int i = 1, y = 0; i < 6; i++, y += 57) {
    texts.push_back(Text(resultNames[i], 220, 281 - y));
    texts.push_back(Text(resultCPoint[i], 340, 281 - y));
  }
  return texts;
}

vector<Text> SaveTexts(char name[64]) {
  vector<Text> texts;
  texts.push_back(Text(name, 390, 369));
  return texts;
}
