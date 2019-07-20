//sudo add-apt-repository universe
//sudo apt install mesa-common-dev libglu1-mesa-dev freeglut3-dev  -y
//g++ -p -Wall -pedantic -o tetris.out tetris.cpp -lGL -lGLU -lglut -lm -std=c++0x 
//./tetris.out
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include "utils.cpp"
#include "file.cpp"

using namespace std;
 
void printtext(int x, int y, string String)
{
//(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 600, 0, 600, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    for (unsigned int i=0; i<String.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}




//Szybkos� spadania
GLint speed= 1000;
int menu = 0;
int menuwyb = 0;
int punkty = 0;
char imie[64];
int wpisywanie =0;
int imieznkow =0;
int wynikipunkty[6] = {0,0,0,0,0,0};
char wynikiimie[6][64];
char wynikippp[6][64];


const GLfloat Kolory[8][3] =
{
    {1,1,1},
    {0,1,1},//Kwadrad - Turkus
    {1,0,0},//Linika  - Czerwony
    {1,1,0},//L       - Zloty
    {1,0,1},//ReversL - Fiolet
    {0,1,0},//Z       - Niebieski
    {0,0,1},//ReversZ - Zielony
    {0.5,0.5,0.5} //Nosek   - Szary
    
};

//Tablica planszy
int plan[22][22] = 
{
{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,5,5,5,5,5,5,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,3,3,3,3,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0}
};

int logo[20][20] = 
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,0,2,2,2,0,3,0,4,0,4,4,0,5,0,6,6,0},
{0,0,1,0,2,0,0,0,3,0,4,0,4,0,0,5,0,0,6,0},
{0,0,1,0,2,2,0,0,3,0,4,4,4,4,0,5,0,0,6,0},
{0,0,1,0,2,0,0,0,3,0,4,0,0,4,0,5,0,6,6,0},
{0,0,1,0,2,2,2,0,3,0,4,4,4,4,0,5,0,6,0,0},
{0,0,1,0,0,0,0,0,3,0,0,0,0,0,0,5,0,6,0,0},
{0,1,1,1,1,1,0,3,3,3,3,3,3,3,0,5,0,6,6,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


int pop[20][20] = 
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
{0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
{0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
{0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
{0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
{0,0,3,3,3,3,3,3,5,5,5,5,5,5,5,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,0,2,2,2,0,3,0,4,0,4,4,0,5,0,6,6,0},
{0,0,1,0,2,0,0,0,3,0,4,0,4,0,0,5,0,0,6,0},
{0,0,1,0,2,2,0,0,3,0,4,4,4,4,0,5,0,0,6,0},
{0,0,1,0,2,0,0,0,3,0,4,0,0,4,0,5,0,6,6,0},
{0,0,1,0,2,2,2,0,3,0,4,4,4,4,0,5,0,6,0,0},
{0,0,1,0,0,0,0,0,3,0,0,0,0,0,0,5,0,6,0,0},
{0,1,1,1,1,1,0,3,3,3,3,3,3,3,0,5,0,6,6,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void OdczytZPlku()
{
    readResultsFile(wynikiimie, wynikipunkty, wynikippp);
}

void ZapiszDoPliku()
{
    saveResultFile(wynikiimie, wynikipunkty, imie, punkty);
    OdczytZPlku();
    menu=4;
}

void KoniecGry()
{
    if(punkty>wynikipunkty[5]) menu=10;
    else menu=11;
}

//objektu
int obiekt[4][3]=
{
{6,20,1},
{6,19,1},
{5,20,1},
{5,19,1}
};
int obiekt2[4][3]=
{
{6,20,1},
{6,19,1},
{5,20,1},
{5,19,1}
};

int gen = 0;
int nastepny = 0;

void GenerujNext()
{
    nastepny = rand()%(0-7)+0;
    drawNextFigure(obiekt2, nastepny);  
}

void GenerujObjekt()
{
    gen = nastepny;
    drawFigure(obiekt, gen);

    if(isCanNotDraw(plan, obiekt)) KoniecGry();
}

void Obruc()
{
    gen = drawRotate(plan, obiekt, gen);
}


void PrzesunObiekt()
{
    if(moveFigureY(plan, obiekt)) {
        GenerujObjekt();   
        GenerujNext();    
    }    
}

void PrzesunLewo()
{
    moveFigureX(plan, obiekt, -1);
}

void PrzesunPrawo()
{
    moveFigureX(plan, obiekt, +1);
}

void KasujLinie()
{
    punkty += deleteLine(plan);
}

void Wypelni()
{
    //szachownica
    GLfloat Syh=-1.0,Syl=-0.9,Sxl=-1.0,Sxh=-0.9;

    for(int j=1;j<21;j++)
    {
    Sxl=-1.0;
    Sxh=-0.9;
    
    for(int i=1;i<21;i++)
    {
    if((i+j)%2==0)
        glColor3f(0, 0.1, 0); 
    else
        glColor3f(0, 0, 0.1); 
        
      
        
    if(plan[j][i] != 0)
    {
        glColor3fv(Kolory[plan[j][i]]);
    }
    
    if((i+j)%2==0 && i>10)
        glColor3f(0.1, 0.1, 0); 
    else if((i+j)%2!=0 && i>10)
        glColor3f(0.1, 0, 0.1);
    
    if(plan[j][i] != 0 && i>11)
    {
        glColor3fv(Kolory[plan[j][i]]);
    }
    
    if(j == obiekt[0][1] && i == obiekt[0][0])
        glColor3fv(Kolory[obiekt[0][2]]);
    if(j == obiekt[1][1] && i == obiekt[1][0])
        glColor3fv(Kolory[obiekt[1][2]]);
    if(j == obiekt[2][1] && i == obiekt[2][0])
        glColor3fv(Kolory[obiekt[2][2]]);
    if(j == obiekt[3][1] && i == obiekt[3][0])
        glColor3fv(Kolory[obiekt[3][2]]);

    if(j == obiekt2[0][1] && i == obiekt2[0][0])
        glColor3fv(Kolory[obiekt2[0][2]]);
    if(j == obiekt2[1][1] && i == obiekt2[1][0])
        glColor3fv(Kolory[obiekt2[1][2]]);
    if(j == obiekt2[2][1] && i == obiekt2[2][0])
        glColor3fv(Kolory[obiekt2[2][2]]);
    if(j == obiekt2[3][1] && i == obiekt2[3][0])
        glColor3fv(Kolory[obiekt2[3][2]]);

   if( (wpisywanie == 1 || menu ==11 || menu==22)&& j == 15 && i >11 &&  i<20)
    glColor3fv(Kolory[6]);
    
       if( wpisywanie == 1 && j == 13 && i >12 &&  i<19)
    glColor3fv(Kolory[1]);
        
     glBegin( GL_QUADS );
       glVertex3f( Sxl , Syl, 0);
       glVertex3f( Sxh , Syl , 0);
       glVertex3f( Sxh , Syh , 0); 
       glVertex3f( Sxl , Syh , 0); 
     glEnd();
     
     Sxl+=0.1;
     Sxh+=0.1;
     
     }
     Syl+=0.1;
     Syh+=0.1;
     }

}


void Pomoc()
{
  GLfloat Syh=-1.0,Syl=-0.9,Sxl=-1.0,Sxh=-0.9;

    for(int j=0;j<20;j++)
    {
    Sxl=-1.0;
    Sxh=-0.9;
    
    
    
    for(int i=0;i<20;i++)
    {
    if((i+j)%2==0)
        glColor3f(0, 0.1, 0); 
    else
        glColor3f(0, 0, 0.1); 
        
    if(pop[j][i] != 0)
    {
        glColor3fv(Kolory[pop[j][i]]);
    }    

     if((pop[j][i]==7 && menuwyb == 0 && j==9) ||
        (pop[j][i]==7 && menuwyb == 1 && j==7) ||
        (pop[j][i]==7 && menuwyb == 2 && j==5) ||
        (pop[j][i]==7 && menuwyb == 3 && j==3) ||
        (pop[j][i]==7 && menuwyb == 4 && j==1))
        glColor3fv(Kolory[0]);
        
        if((pop[j][i]==7 && menu == 4 && j==9) ||
        (pop[j][i]==7 && menu == 4 && j==7) ||
        (pop[j][i]==7 && menu == 4 && j==5) ||
        (pop[j][i]==7 && menu == 4 && j==3) ||
        (pop[j][i]==7 && menu == 4 && j==1))
        glColor3fv(Kolory[3]);
        
        
     glBegin( GL_QUADS );
       glVertex3f( Sxl , Syl, 0);
       glVertex3f( Sxh , Syl , 0);
       glVertex3f( Sxh , Syh , 0); 
       glVertex3f( Sxl , Syh , 0); 
     glEnd();
     
     Sxl+=0.1;
     Sxh+=0.1;
     
     }
     Syl+=0.1;
     Syh+=0.1;
     }

}

void Logo()
{    

    GLfloat Syh=-1.0,Syl=-0.9,Sxl=-1.0,Sxh=-0.9;

    for(int j=0;j<20;j++)
    {
    Sxl=-1.0;
    Sxh=-0.9;
    
    
    
    for(int i=0;i<20;i++)
    {
    if((i+j)%2==0)
        glColor3f(0, 0.1, 0); 
    else
        glColor3f(0, 0, 0.1); 
        
    if(logo[j][i] != 0)
    {
        glColor3fv(Kolory[logo[j][i]]);
    }    

     if((logo[j][i]==7 && menuwyb == 0 && j==9) ||
        (logo[j][i]==7 && menuwyb == 1 && j==7) ||
        (logo[j][i]==7 && menuwyb == 2 && j==5) ||
        (logo[j][i]==7 && menuwyb == 3 && j==3) ||
        (logo[j][i]==7 && menuwyb == 4 && j==1))
        glColor3fv(Kolory[0]);
        
        if((logo[j][i]==7 && menu == 4 && j==9) ||
        (logo[j][i]==7 && menu == 4 && j==7) ||
        (logo[j][i]==7 && menu == 4 && j==5) ||
        (logo[j][i]==7 && menu == 4 && j==3) ||
        (logo[j][i]==7 && menu == 4 && j==1))
        glColor3fv(Kolory[3]);
        
        
     glBegin( GL_QUADS );
       glVertex3f( Sxl , Syl, 0);
       glVertex3f( Sxh , Syl , 0);
       glVertex3f( Sxh , Syh , 0); 
       glVertex3f( Sxl , Syh , 0); 
     glEnd();
     
     Sxl+=0.1;
     Sxh+=0.1;
     
     }
     Syl+=0.1;
     Syh+=0.1;
     }

}



void MenuG()
{
    glColor3f(0, 0, 0);
    char string[64];

    sprintf(string, "Nowa Gra");
    printtext(250,281,string);

    sprintf(string, "Pomoc");
    printtext(250,225,string);
    
    sprintf(string, "Ustawienia");
    printtext(250,168,string);
    
    sprintf(string, "Wyniki");
    printtext(250,111,string);
    
    sprintf(string, "Wyjscie");
    printtext(250,55,string);
}


void GameTekst()
{
    glColor3f(0, 0, 0);
    char string[64];

    sprintf(string, "Punkty");
    printtext(390,540,string);

    sprintf(string, "%i",punkty);
    printtext(460,540,string);
    
    printtext(370,483,wynikiimie[1]);
    printtext(490,483,wynikippp[1]);
    
    if(menu == 10) {
        sprintf(string, "Podaj imie i koncz [ESC]");
        printtext(332,426,string);
    }
    
    if(menu == 11) {
        sprintf(string, "Przegrales i koncz [ESC]");
        printtext(332,426,string);
    }
}

void Pauza()
{
    glColor3f(0, 0, 0);
    char string[64];
    sprintf(string, "Pauza! Kliknij [P] i graj");
    printtext(332,426,string);
}

void PomocTekst()
{
    glColor3f(0, 0, 0);
    char string[64];

    sprintf(string, "Sterowanie:");
    printtext(90,280,string);
    sprintf(string, "Strzalki:");
    printtext(80,256,string);
    sprintf(string, "W gore - obrot");
    printtext(80,232,string);
    sprintf(string, "W dol - opadanie");
    printtext(80,209,string);
    sprintf(string, "W prawo");
    printtext(80,183,string);
    sprintf(string, "W lewo");
    printtext(80,157,string);
    
    sprintf(string, "Inne:");
    printtext(250,256,string);
    sprintf(string, "[ESC] Wyjscie/Powrot");
    printtext(250,232,string);
    sprintf(string, "[SPACJA] Wybor z Menu");
    printtext(250,209,string);
    sprintf(string, "[F1] Pomoc");
    printtext(250,183,string);
    sprintf(string, "[P] Pauza");
    printtext(250,157,string);
}

void UstawieniaTekst()
{
    glColor3f(0, 0, 0);
    char string[64];

    sprintf(string, "Ustawienia:");
    printtext(90,280,string);
    sprintf(string, "Pretkosc [+][-]");
    printtext(80,256,string);
    sprintf(string, " ");
    printtext(80,232,string);
    sprintf(string, " ");
    printtext(80,209,string);
    sprintf(string, " ");
    printtext(80,183,string);
    sprintf(string, " ");
    printtext(80,157,string);
    
    sprintf(string,"%i" ,speed);
    printtext(250,256,string);
    sprintf(string, " ");
    printtext(250,232,string);
    sprintf(string, " ");
    printtext(250,209,string);
    sprintf(string, " ");
    printtext(250,183,string);
    sprintf(string, " ");
    printtext(250,157,string);
}

void NowaGra()
{
    clearBoard(plan);
    punkty = 0;
    GenerujNext();
    GenerujObjekt();   
    GenerujNext(); 
}

void NajWyniki()
{
    glColor3f(0, 0, 0);

    int nop = 0;
    int liczba = 0;
    while(++liczba < 6) {
        printtext(220,281-nop,wynikiimie[liczba]);
        printtext(340,281-nop,wynikippp[liczba]);
        nop+=57;
    }
}

void Zapisz()
{
    wpisywanie = 1;
    char string[64];
    sprintf(string, imie);
    printtext(390,369,string);
}

// funkcja generuj�ca scen� 3D
void Display()
{   
    //Generowanie t�a
    glClearColor(1, 1, 1, 1);        
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glEnable(GL_DEPTH_TEST);

    if (menu == 1) {
        KasujLinie();
        Wypelni();
        GameTekst();
    }
    
    if (menu == 0) {
        Logo();
        MenuG();
    }
    
    //Pomoc
    if (menu == 2) {
        Pomoc();
        PomocTekst();
    }
    //Ustawieni    
    if (menu == 3) {
        Pomoc();
        UstawieniaTekst();
    }
    
    //Wyniki
    if (menu == 4) {
        Logo();
        NajWyniki();
    }
    
    //KoniecGry
    if (menu == 10) {
        Wypelni();
        GameTekst();
        Zapisz();
    }
    
    if (menu == 11) {
        Wypelni();
        GameTekst();
    }

    if (menu == 22) {
        Wypelni();
        GameTekst();
        Pauza();
    }

    // skierowanie polece� do wykonania
    glFlush();    
    // zamiana bufor�w koloru
    glutSwapBuffers();
}

void Timer( int value )
{   
    if (menu == 1) {
        PrzesunObiekt();  
    } 
    // wy�wietlenie sceny
    Display();    
    // nast�pne wywo�anie funkcji timera
    glutTimerFunc( speed, Timer, 0 );
}

void Reshape(int width, int height)
{ 
    glViewport( 0, 0, width, height );
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1, 1, 100);
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 
	gluLookAt(0, 0, 1.5, 0, 0, 0, 0, 1, 0);
    Display();
}

void Keyboard( unsigned char key, int x, int y )
{   
    OdczytZPlku();

    if((key == 'P' || key == 'p') && menu == 1) {
        menu = 22;
        key=0;
    }

    if((key == 'P' || key == 'p') && menu == 22) {
        menu = 1;
    }
  
    if(key == '+' && speed<2000) {
        speed+=100;
    }

    if(key == '-' && speed>0) {
        speed-=100;
    }  

    if(key == ' ' && menu == 0) {
        switch(menuwyb) {  
            case 0:
                menu = 1;
                NowaGra();
                break; 
            case 1:
                menu = 2;
                break; 
            case 2:
                menu = 3;
                break; 
            //Wyniki
            case 3:
                menu = 4;
                break; 
            case 4:
                exit(0);
                break;
        };
    }
    
    if(wpisywanie == 1 
        && ((key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <=122)) 
        && imieznkow <=10 ) {

        imie[imieznkow] = key;
        imieznkow++;
    }
    
    if(wpisywanie == 1 && key == 8 && imieznkow > 0) {
        imieznkow--;
        imie[imieznkow] = 0;
    }
    
    if(key == 27 && wpisywanie == 1) {
        menu = 0;
        wpisywanie = 0;
        key = 0;
        ZapiszDoPliku();
    }
    else if(key == 27 && menu == 11) {
        menu = 4;
    }
    else if(key == 27 && menu == 0) {
        exit( 0 );
    }
    else if(key == 27) {
        menu = 0;
    }
    
    Display();
}
void Znaki_Spec(int key, int x, int y)
{ 
    if(key == GLUT_KEY_F1 && menu == 1) {
        menu = 2;
        key = 0;
    }
    
    if(key == GLUT_KEY_F1 && menu == 2) {
        menu = 1;
        key = 0;
    }

    if (menu == 1) {
        switch(key) {  
            case GLUT_KEY_UP:
                Obruc();
                break; 
            case GLUT_KEY_DOWN:
                PrzesunObiekt();
                break;  
            case GLUT_KEY_LEFT:
                PrzesunLewo();
                break; 
            case GLUT_KEY_RIGHT:
                PrzesunPrawo();
                break; 
            case GLUT_KEY_END:
                menu = 0;
                key = 0;      
                break; 
        }
    }
    if (menu == 0) {
        switch(key) {  
            case GLUT_KEY_DOWN:
            if(menuwyb == 4) menuwyb = 0;
            else menuwyb++;
            break; 
            case GLUT_KEY_UP:
            if(menuwyb == 0) menuwyb = 4;
            else menuwyb--;
            break;  
            case GLUT_KEY_LEFT:

            break; 
            case GLUT_KEY_RIGHT:

            break; 
            case GLUT_KEY_END:
                exit( 0 );        
            break; 
        }
    }
    
    //narysowanie sceny
    Display();
} 

int main( int argc, char * argv[] )
{   

    OdczytZPlku();
    srand(time(NULL));
    glutInit(& argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Tetris - Zielonka Adam");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Znaki_Spec);    
    glutTimerFunc( speed, Timer, 0 );
    glutMainLoop();
    return 0;
}
