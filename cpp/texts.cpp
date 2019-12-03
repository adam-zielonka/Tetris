#include <vector>
#include <string>
#include "i18n.cpp"

using namespace std;

namespace Texts {
  class Text {
    public:
      string value;
      int x;
      int y;

      Text(string value, int x, int y) : value{value}, x{x}, y{y} { }
  };

  class Texts {
    private:
      vector<Text> texts;

    public:
      void add(string value, int x, int y) {
        texts.push_back(Text(value, x, y));
      }

      void add(int number, int x, int y) {
        this->add(to_string(number), x, y);
      }

      vector<Text> get() {
        return texts;
      }
  };

  vector<Text> MainMenuTexts() {
    Texts texts;
    texts.add(I18N::i18n.MENU_NEW_GAME, 250, 281);
    texts.add(I18N::i18n.MENU_HELP, 250, 225);
    texts.add(I18N::i18n.MENU_SETTINGS, 250, 168);
    texts.add(I18N::i18n.MENU_RESULT, 250, 111);
    texts.add(I18N::i18n.MENU_EXIT, 250, 55);
    return texts.get();
  }

  vector<Text> GameTexts(int menu, char bestName[64], char bestPoints[64], int points) {
    Texts texts;
    texts.add(I18N::i18n.GAME_POINTS, 390, 540);
    texts.add(points, 460, 540);
    texts.add(bestName, 370, 483);
    texts.add(bestPoints, 490, 483);
    
    if(menu == 10) 
      texts.add(I18N::i18n.GAME_OVER_WRITE_NAME, 332, 426);
    
    if(menu == 11)
      texts.add(I18N::i18n.GAME_OVER, 332, 426);

    return texts.get();
  }

  vector<Text> PauseTexts() {
    Texts texts;
    texts.add(I18N::i18n.GAME_PAUSE, 332, 426);
    return texts.get();
  }

  vector<Text> HelpTexts() {
    Texts texts;
    texts.add(I18N::i18n.HELP_CONTROLS, 90, 280);
    texts.add(I18N::i18n.HELP_ARROWS, 80, 256);
    texts.add(I18N::i18n.HELP_ARROW_UP, 80, 232);
    texts.add(I18N::i18n.HELP_ARROW_DOWN, 80, 209);
    texts.add(I18N::i18n.HELP_ARROW_RIGHT, 80, 183);
    texts.add(I18N::i18n.HELP_ARROW_LEFT, 80, 157);
    
    texts.add(I18N::i18n.HELP_OTHERS, 250, 256);
    texts.add(I18N::i18n.HELP_ESC, 250, 232);
    texts.add(I18N::i18n.HELP_SPACE, 250, 209);
    texts.add(I18N::i18n.HELP_F1, 250, 183);
    texts.add(I18N::i18n.HELP_P, 250, 157);
    return texts.get();
  }

  vector<Text> SettingsTexts(int speed) {
    Texts texts;
    texts.add(I18N::i18n.SETTINGS, 90, 280);
    texts.add(I18N::i18n.SETTINGS_SPEED, 80, 256);
    texts.add(speed, 250, 256);
    texts.add(I18N::i18n.SETTINGS_LANG, 80, 232);
    texts.add(I18N::i18n.SETTINGS_LANG_VALUE, 250, 232);
    return texts.get();
  }

  vector<Text> BestResultsTexts(char resultNames[6][64], char resultCPoint[6][64]) {
    Texts texts;
    for (int i = 1, y = 0; i < 6; i++, y += 57) {
      texts.add(resultNames[i], 220, 281 - y);
      texts.add(resultCPoint[i], 340, 281 - y);
    }
    return texts.get();
  }

  vector<Text> SaveTexts(char name[64]) {
    Texts texts;
    texts.add(name, 390, 369);
    return texts.get();
  }
}
