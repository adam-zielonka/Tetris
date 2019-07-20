#include <fstream>

using namespace std;

void saveResultFile(char resultNames[6][64], int resultPoints[6], char name[64], int points) {
  fstream file;
  file.open("wyniki.txt", ios::out);
  if(file.good()) {
    int addedResult = false;
    int counter = 0;
    while(++counter < 5) {
      if(resultPoints[counter] < points && addedResult == false) {
        addedResult = true;
        counter--;
        file<<name<<endl;
        file<<points<<endl;
      } else {
        file<<resultNames[counter]<<endl;
        file<<resultPoints[counter]<<endl;
      }
    }
    file.close();
  }
}

void saveResultFile(char resultNames[6][64], int resultPoints[6]) {
  fstream file;
  file.open("wyniki.txt", ios::out);
  if(file.good()) {
    int counter = 0;
    while(++counter < 6) {
      file<<resultNames[counter]<<endl;
      file<<resultPoints[counter]<<endl;
    }
    file.close();
  }
}

void readResultsFile(char resultNames[6][64], int resultPoints[6], char resultCPoint[6][64]) {
  fstream file;
  file.open("wyniki.txt", ios::in);
  if(file.good()) {
    string line;
    int counter = 0;
    while(!file.eof() && ++counter < 6) {
      getline(file, line);
      for(int i = 0; i < 11; i++) {
        resultNames[counter][i] = line[i];
      }
      resultNames[counter][11] = 0;
      if(resultNames[counter][0] == 0) {
        sprintf(resultNames[counter], "Anonim");
      }
      resultPoints[counter] = 0;
      getline(file, line);
      for(int i=0;i<11;i++) {
        resultCPoint[counter][i] = line[i];
        if (line[i]==0) break;
        resultPoints[counter] += line[i] - 48;
        resultPoints[counter] *= 10;
      }
      resultPoints[counter] /= 10;
    }
    file.close();
  } else {
    saveResultFile(resultNames, resultPoints);
    readResultsFile(resultNames, resultPoints, resultCPoint);
  }
}
