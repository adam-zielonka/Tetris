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

void rotateFigure(const int pattern[4][2], int figure[4][3], int sign = 1) {
  for (int i = 0; i < 4; i++) {
    updatePosition(figure[i], sign * pattern[i][0], sign * pattern[i][1]);
  }
}

bool rotateFigure(int board[22][22], const int pattern[4][2], int figure[4][3], int sign = 1) {
  rotateFigure(pattern, figure, sign);
  if(isCanNotDraw(board, figure)) {
    rotateFigure(pattern, figure, -1 * sign);
    return false;
  } else {
    return true;
  }
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

int drawRotate(int board[22][22], int figure[4][3], int oldId) {
  int newId = oldId;
  switch(oldId)      
  {  
    case 0: break; //Square
    case 1: newId = rotateFigure(board, ROTATE_LINE, figure) ? 11 : 1; break;  
    case 11: newId = rotateFigure(board, ROTATE_LINE, figure, -1) ? 1 : 11; break;  
    case 2: newId = rotateFigure(board, ROTATE_L_0, figure) ? 22 : 2; break;  
    case 22: newId = rotateFigure(board, ROTATE_L_1, figure) ? 23 : 22; break; 
    case 23: newId = rotateFigure(board, ROTATE_L_0, figure, -1) ? 24 : 23; break;  
    case 24: newId = rotateFigure(board, ROTATE_L_1, figure, -1) ? 2 : 24; break; 
    case 3: newId = rotateFigure(board, ROTATE_MIRRORED_L_0, figure) ? 32 : 3; break; 
    case 32: newId = rotateFigure(board, ROTATE_MIRRORED_L_1, figure) ? 33 : 32; break; 
    case 33: newId = rotateFigure(board, ROTATE_MIRRORED_L_0, figure, -1) ? 34 : 33; break; 
    case 34: newId = rotateFigure(board, ROTATE_MIRRORED_L_1, figure, -1) ? 3 : 34; break; 
    case 4: newId = rotateFigure(board, ROTATE_Z, figure) ? 41 : 4; break; 
    case 41: newId = rotateFigure(board, ROTATE_Z, figure, -1) ? 4 : 41; break; 
    case 5: newId = rotateFigure(board, ROTATE_MIRRORED_Z, figure) ? 51 : 5; break; 
    case 51: newId = rotateFigure(board, ROTATE_MIRRORED_Z, figure, -1) ? 5 : 51; break; 
    case 6: newId = rotateFigure(board, ROTATE_NOSE_0, figure) ? 62 : 6; break; 
    case 62: newId = rotateFigure(board, ROTATE_NOSE_1, figure) ? 63 : 62; break; 
    case 63: newId = rotateFigure(board, ROTATE_NOSE_0, figure, -1) ? 64 : 63; break; 
    case 64: newId = rotateFigure(board, ROTATE_NOSE_1, figure, -1) ? 6 : 64; break;
  }
  return newId;
}
