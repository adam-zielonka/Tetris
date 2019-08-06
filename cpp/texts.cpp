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

      Text(string _value, int _x, int _y) {
        value = _value;
        x = _x;
        y = _y;
      }

      Text(int _number, int _x, int _y) : Text(to_string(_number), _x, _y) {}
  };

  vector<Text> MainMenuTexts() {
    vector<Text> texts;
    texts.push_back(Text(I18N::i18n.MENU_NEW_GAME, 250, 281));
    texts.push_back(Text(I18N::i18n.MENU_HELP, 250, 225));
    texts.push_back(Text(I18N::i18n.MENU_SETTINGS, 250, 168));
    texts.push_back(Text(I18N::i18n.MENU_RESULT, 250, 111));
    texts.push_back(Text(I18N::i18n.MENU_EXIT, 250, 55));
    return texts;
  }

  vector<Text> GameTexts(int menu, char bestName[64], char bestPoints[64], int points) {
    vector<Text> texts;
    texts.push_back(Text(I18N::i18n.GAME_POINTS, 390, 540));
    texts.push_back(Text(points, 460, 540));
    texts.push_back(Text(bestName, 370, 483));
    texts.push_back(Text(bestPoints, 490, 483));
    
    if(menu == 10) 
      texts.push_back(Text(I18N::i18n.GAME_OVER_WRITE_NAME, 332, 426));
    
    if(menu == 11)
      texts.push_back(Text(I18N::i18n.GAME_OVER, 332, 426));

    return texts;
  }

  vector<Text> PauseTexts() {
    vector<Text> texts;
    texts.push_back(Text(I18N::i18n.GAME_PAUSE, 332, 426));
    return texts;
  }

  vector<Text> HelpTexts() {
    vector<Text> texts;
    texts.push_back(Text(I18N::i18n.HELP_CONTROLS, 90, 280));
    texts.push_back(Text(I18N::i18n.HELP_ARROWS, 80, 256));
    texts.push_back(Text(I18N::i18n.HELP_ARROW_UP, 80, 232));
    texts.push_back(Text(I18N::i18n.HELP_ARROW_DOWN, 80, 209));
    texts.push_back(Text(I18N::i18n.HELP_ARROW_RIGHT, 80, 183));
    texts.push_back(Text(I18N::i18n.HELP_ARROW_LEFT, 80, 157));
    
    texts.push_back(Text(I18N::i18n.HELP_OTHERS, 250, 256));
    texts.push_back(Text(I18N::i18n.HELP_ESC, 250, 232));
    texts.push_back(Text(I18N::i18n.HELP_SPACE, 250, 209));
    texts.push_back(Text(I18N::i18n.HELP_F1, 250, 183));
    texts.push_back(Text(I18N::i18n.HELP_P, 250, 157));
    return texts;
  }

  vector<Text> SettingsTexts(int speed) {
    vector<Text> texts;
    texts.push_back(Text(I18N::i18n.SETTINGS, 90, 280));
    texts.push_back(Text(I18N::i18n.SETTINGS_SPEED, 80, 256));
    texts.push_back(Text(speed, 250, 256));
    texts.push_back(Text(I18N::i18n.SETTINGS_LANG, 80, 232));
    texts.push_back(Text(I18N::i18n.SETTINGS_LANG_VALUE, 250, 232));
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
}
