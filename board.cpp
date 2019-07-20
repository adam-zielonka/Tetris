struct Board {
  int xy[20][20];
};

Board drawBoard(int board[22][22], int figure[4][3], int nextFigure[4][3], int menu, int typing) {
  Board printBoard;
  
  for(int j = 1; j < 21; j++) {
    for(int i = 1; i < 21; i++) {
      int color = (i + j) % 2 == 0 ? 8 : 9;
        
      if(board[j][i] != 0)
        color = board[j][i];
      
      if((i + j) % 2 == 0 && i > 10)
        color = 10; 
      else if((i + j) % 2 != 0 && i > 10)
        color = 11;
      
      if(board[j][i] != 0 && i>11) {
        color = board[j][i];
      }
      
      if(j == figure[0][1] && i == figure[0][0])
        color = figure[0][2];
      if(j == figure[1][1] && i == figure[1][0])
        color = figure[1][2];
      if(j == figure[2][1] && i == figure[2][0])
        color = figure[2][2];
      if(j == figure[3][1] && i == figure[3][0])
        color = figure[3][2];

      if(j == nextFigure[0][1] && i == nextFigure[0][0])
        color = nextFigure[0][2];
      if(j == nextFigure[1][1] && i == nextFigure[1][0])
        color = nextFigure[1][2];
      if(j == nextFigure[2][1] && i == nextFigure[2][0])
        color = nextFigure[2][2];
      if(j == nextFigure[3][1] && i == nextFigure[3][0])
        color = nextFigure[3][2];

      if((typing == 1 || menu == 11 || menu == 22) && j == 15 && i > 11 &&  i < 20)
        color = 6;
      
      if(typing == 1 && j == 13 && i > 12 && i < 19)
        color = 1;
        
      printBoard.xy[j-1][i-1] = color;
    }
  }

  return printBoard;
}

Board drawBoard(int board[20][20], int menu, int selectedItem) {
  Board printBoard;

  for(int j = 0; j < 20; j++) {
    for(int i = 0; i < 20; i++) {
      int color = board[j][i] != 0 ? board[j][i] : ((i + j) % 2 == 0 ? 8 : 9);

      if((board[j][i]==7 && selectedItem == 0 && j==9) ||
        (board[j][i]==7 && selectedItem == 1 && j==7) ||
        (board[j][i]==7 && selectedItem == 2 && j==5) ||
        (board[j][i]==7 && selectedItem == 3 && j==3) ||
        (board[j][i]==7 && selectedItem == 4 && j==1))
        color = 0;
        
      if((board[j][i]==7 && menu == 4 && j==9) ||
        (board[j][i]==7 && menu == 4 && j==7) ||
        (board[j][i]==7 && menu == 4 && j==5) ||
        (board[j][i]==7 && menu == 4 && j==3) ||
        (board[j][i]==7 && menu == 4 && j==1))
        color = 3;
      
      printBoard.xy[j][i] = color;
    }
  }

  return printBoard;
}

Board drawBoard(int board[20][20]) {
  Board printBoard;

  for(int j = 0; j < 20; j++)
    for(int i = 0; i < 20; i++)
      printBoard.xy[j][i] = board[j][i] != 0 ? board[j][i] : ((i + j) % 2 == 0 ? 8 : 9);

  return printBoard;
}
