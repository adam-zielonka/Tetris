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
