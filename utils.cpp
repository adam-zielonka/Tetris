using namespace std;

void setPosition(int* point, int x, int y, int color) {
  point[0] = x;
  point[1] = y;
  point[2] = color;
}

void updatePosition(int* point, int x, int y) {
  point[0] += x;
  point[1] += y;
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