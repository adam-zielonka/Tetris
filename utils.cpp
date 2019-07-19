#include "constants.cpp"

using namespace std;

bool isCanNotDraw(int board[22][22], int figure[4][3]) {
  return (
    (board[figure[0][1]][figure[0][0]] != 0) ||
    (board[figure[1][1]][figure[1][0]] != 0) ||
    (board[figure[2][1]][figure[2][0]] != 0) ||
    (board[figure[3][1]][figure[3][0]] != 0)
  );
}

void setPosition(int point[3], int x, int y, int color) {
  point[0] = x;
  point[1] = y;
  point[2] = color;
}

void updatePosition(int point[3], int x, int y) {
  point[0] += x;
  point[1] += y;
}

void setFigurePosition(const int pattern[4][2], int figure[4][3], int color) {
  for (int i = 0; i < 4; i++) {
    setPosition(figure[i], pattern[i][0], pattern[i][1], color);
  }
}

void drawFigure(int figure[4][3], int code) {
  int color = code + 1;

  switch(code) {
    case 0: setFigurePosition(SQUARE, figure, color); break;
    case 1: setFigurePosition(LINE, figure, color); break;
    case 2: setFigurePosition(L, figure, color); break;
    case 3: setFigurePosition(MIRRORED_L, figure, color); break;
    case 4: setFigurePosition(Z, figure, color); break;
    case 5: setFigurePosition(MIRRORED_Z, figure, color); break;
    case 6: setFigurePosition(NOSE, figure, color); break;
  }
}

void drawNextFigure(int figure[4][3], int code) {
  int color = code + 1;

  switch(code) {
    case 0: setFigurePosition(NEXT_SQUARE, figure, color); break;
    case 1: setFigurePosition(NEXT_LINE, figure, color); break;
    case 2: setFigurePosition(NEXT_L, figure, color); break;
    case 3: setFigurePosition(NEXT_MIRRORED_L, figure, color); break;
    case 4: setFigurePosition(NEXT_Z, figure, color); break;
    case 5: setFigurePosition(NEXT_MIRRORED_Z, figure, color); break;
    case 6: setFigurePosition(NEXT_NOSE, figure, color); break;
  }
}
