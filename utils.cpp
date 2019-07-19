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

void drawFigure(int figure[4][3], int code) {
  int color = code + 1;

  switch(code) {
    case 0://Square
      setPosition(figure[0], 5, 20, color);
      setPosition(figure[1], 5, 19, color);
      setPosition(figure[2], 6, 20, color);
      setPosition(figure[3], 6, 19, color);
      break; 
    case 1://Line
      setPosition(figure[0], 5, 20, color);
      setPosition(figure[1], 5, 19, color);
      setPosition(figure[2], 5, 18, color);
      setPosition(figure[3], 5, 17, color);
      break;  
    case 2://L
      setPosition(figure[0], 5, 20, color);
      setPosition(figure[1], 5, 19, color);
      setPosition(figure[2], 5, 18, color);
      setPosition(figure[3], 6, 18, color);
      break; 
    case 3://Mirrored L
      setPosition(figure[0], 6, 20, color);
      setPosition(figure[1], 6, 19, color);
      setPosition(figure[2], 6, 18, color);
      setPosition(figure[3], 5, 18, color);
      break;
    case 4://Z
      setPosition(figure[0], 4, 20, color);
      setPosition(figure[1], 5, 20, color);
      setPosition(figure[2], 5, 19, color);
      setPosition(figure[3], 6, 19, color);
      break;
    case 5://Mirrored Z
      setPosition(figure[0], 6, 20, color);
      setPosition(figure[1], 5, 20, color);
      setPosition(figure[2], 5, 19, color);
      setPosition(figure[3], 4, 19, color);
      break;
    case 6://Nose
      setPosition(figure[0], 5, 20, color);
      setPosition(figure[1], 5, 19, color);
      setPosition(figure[2], 5, 18, color);
      setPosition(figure[3], 6, 19, color);
      break;
  }
}

void drawNextFigure(int figure[4][3], int code) {
  int color = code + 1;

  switch(code) {
    case 0://Square
      setPosition(figure[0], 15, 7, color);
      setPosition(figure[1], 15, 6, color);
      setPosition(figure[2], 16, 7, color);
      setPosition(figure[3], 16, 6, color);
      break; 
    case 1://Line
      setPosition(figure[0], 15, 7, color);
      setPosition(figure[1], 15, 6, color);
      setPosition(figure[2], 15, 5, color);
      setPosition(figure[3], 15, 4, color);
      break;  
    case 2://L
      setPosition(figure[0], 15, 7, color);
      setPosition(figure[1], 15, 6, color);
      setPosition(figure[2], 15, 5, color);
      setPosition(figure[3], 16, 5, color);
      break;
    case 3://Mirrored L
      setPosition(figure[0], 16, 7, color);
      setPosition(figure[1], 16, 6, color);
      setPosition(figure[2], 16, 5, color);
      setPosition(figure[3], 15, 5, color);
      break;
    case 4://Z
      setPosition(figure[0], 14, 7, color);
      setPosition(figure[1], 15, 7, color);
      setPosition(figure[2], 15, 6, color);
      setPosition(figure[3], 16, 6, color);
      break;
    case 5://Mirrored Z
      setPosition(figure[0], 16, 7, color);
      setPosition(figure[1], 15, 7, color);
      setPosition(figure[2], 15, 6, color);
      setPosition(figure[3], 14, 6, color);
      break;
    case 6://Nose
      setPosition(figure[0], 15, 7, color);
      setPosition(figure[1], 15, 6, color);
      setPosition(figure[2], 15, 5, color);
      setPosition(figure[3], 16, 6, color);
      break;        
  }
}
