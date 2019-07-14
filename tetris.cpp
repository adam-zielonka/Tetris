//g++ -p -Wall -pedantic -o pro pro.cpp -lGL -lGLU -lglut -lm -std=c++0x
//LIBGL_ALWAYS_INDIRECT=1 ./pro
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <cstring>

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


//Szybkosæ spadania
GLint speed= 1000;
int menu = 0;
int menuwyb = 0;
int punkty = 0;
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
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
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
    
    switch(nastepny)      
    {  
        case 0://Kwadrad
            obiekt2[0]= {15,7,1};
            obiekt2[1]= {15,6,1};
            obiekt2[2]= {16,7,1};
            obiekt2[3]= {16,6,1};
        break; 
        case 1://Linika
            obiekt2[0]= {15,7,2};
            obiekt2[1]= {15,6,2};
            obiekt2[2]= {15,5,2};
            obiekt2[3]= {15,4,2};
        break;  
        case 2://L
            obiekt2[0]= {15,7,3};
            obiekt2[1]= {15,6,3};
            obiekt2[2]= {15,5,3};
            obiekt2[3]= {16,5,3};
        break; 
        case 3://ReversL
            obiekt2[0]= {16,7,4};
            obiekt2[1]= {16,6,4};
            obiekt2[2]= {16,5,4};
            obiekt2[3]= {15,5,4};
        break;
        case 4://Z
            obiekt2[0]= {14,7,5};
            obiekt2[1]= {15,7,5};
            obiekt2[2]= {15,6,5};
            obiekt2[3]= {16,6,5};
        break;
        case 5://ReversZ
            obiekt2[0]= {16,7,6};
            obiekt2[1]= {15,7,6};
            obiekt2[2]= {15,6,6};
            obiekt2[3]= {14,6,6};
        break;
        case 6://Nosek
            obiekt2[0]= {15,7,7};
            obiekt2[1]= {15,6,7};
            obiekt2[2]= {15,5,7};
            obiekt2[3]= {16,6,7};
        break;        

    }
    
}


void GenerujObjekt()
{
    gen = nastepny;

    switch(gen)      
    {  
        case 0://Kwadrad
            obiekt[0]= {5,20,1};
            obiekt[1]= {5,19,1};
            obiekt[2]= {6,20,1};
            obiekt[3]= {6,19,1};
        break; 
        case 1://Linika
            obiekt[0]= {5,20,2};
            obiekt[1]= {5,19,2};
            obiekt[2]= {5,18,2};
            obiekt[3]= {5,17,2};
        break;  
        case 2://L
            obiekt[0]= {5,20,3};
            obiekt[1]= {5,19,3};
            obiekt[2]= {5,18,3};
            obiekt[3]= {6,18,3};
        break; 
        case 3://ReversL
            obiekt[0]= {6,20,4};
            obiekt[1]= {6,19,4};
            obiekt[2]= {6,18,4};
            obiekt[3]= {5,18,4};
        break;
        case 4://Z
            obiekt[0]= {4,20,5};
            obiekt[1]= {5,20,5};
            obiekt[2]= {5,19,5};
            obiekt[3]= {6,19,5};
        break;
        case 5://ReversZ
            obiekt[0]= {6,20,6};
            obiekt[1]= {5,20,6};
            obiekt[2]= {5,19,6};
            obiekt[3]= {4,19,6};
        break;
        case 6://Nosek
            obiekt[0]= {5,20,7};
            obiekt[1]= {5,19,7};
            obiekt[2]= {5,18,7};
            obiekt[3]= {6,19,7};
        break;        

    }
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
                    for(int i=1;i<21;i++)
                    {
                        plan[i][1] = 0;
                        plan[i][2] = 0;
                        plan[i][3] = 0;
                        plan[i][4] = 0;
                        plan[i][5] = 0;
                        plan[i][6] = 0;
                        plan[i][7] = 0;
                        plan[i][8] = 0;
                        plan[i][9] = 0;
                        plan[i][10] = 0;
                        }
                }
}

void Obruc()
{
    switch(gen)      
    {  
        case 0://Kwadrad

        break; 
        case 1://Linika
            obiekt[0]= {obiekt[0][0]-1,obiekt[0][1]-2,2};
            obiekt[1]= {obiekt[1][0],obiekt[1][1]-1,2};
            obiekt[2]= {obiekt[2][0]+1,obiekt[2][1],2};
            obiekt[3]= {obiekt[3][0]+2,obiekt[3][1]+1,2};
            gen = 11;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
                    obiekt[0]= {obiekt[0][0]+1,obiekt[0][1]+2,2};
                    obiekt[1]= {obiekt[1][0],obiekt[1][1]+1,2};
                    obiekt[2]= {obiekt[2][0]-1,obiekt[2][1],2};
                    obiekt[3]= {obiekt[3][0]-2,obiekt[3][1]-1,2};
                    gen = 1;
                }
        break;  
        case 11://Linika
            obiekt[0]= {obiekt[0][0]+1,obiekt[0][1]+2,2};
            obiekt[1]= {obiekt[1][0],obiekt[1][1]+1,2};
            obiekt[2]= {obiekt[2][0]-1,obiekt[2][1],2};
            obiekt[3]= {obiekt[3][0]-2,obiekt[3][1]-1,2};
            gen = 1;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
                    obiekt[0]= {obiekt[0][0]-1,obiekt[0][1]-2,2};
                    obiekt[1]= {obiekt[1][0],obiekt[1][1]-1,2};
                    obiekt[2]= {obiekt[2][0]+1,obiekt[2][1],2};
                    obiekt[3]= {obiekt[3][0]+2,obiekt[3][1]+1,2};
                    gen = 11;
                }
        break;  
        case 2://L
            obiekt[0]= {obiekt[0][0],obiekt[0][1]-2,3};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]-1,3};
            obiekt[2]= {obiekt[2][0]+2,obiekt[2][1],3};
            obiekt[3]= {obiekt[3][0]+1,obiekt[3][1]+1,3};
            gen = 22;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0],obiekt[0][1]+2,3};
            obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]+1,3};
            obiekt[2]= {obiekt[2][0]-2,obiekt[2][1],3};
            obiekt[3]= {obiekt[3][0]-1,obiekt[3][1]-1,3};
                    gen = 2;
                }
        break; 
        case 22://L
            obiekt[0]= {obiekt[0][0]+2,obiekt[0][1],3};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]+1,3};
            obiekt[2]= {obiekt[2][0],obiekt[2][1]+2,3};
            obiekt[3]= {obiekt[3][0]-1,obiekt[3][1]+1,3};
            gen = 23;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
                    obiekt[0]= {obiekt[0][0]-2,obiekt[0][1],3};
                    obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]-1,3};
                    obiekt[2]= {obiekt[2][0],obiekt[2][1]-2,3};
                    obiekt[3]= {obiekt[3][0]+1,obiekt[3][1]-1,3};
                    gen = 22;
                }
        break;
        case 23://L
            obiekt[0]= {obiekt[0][0],obiekt[0][1]+2,3};
            obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]+1,3};
            obiekt[2]= {obiekt[2][0]-2,obiekt[2][1],3};
            obiekt[3]= {obiekt[3][0]-1,obiekt[3][1]-1,3};
            gen = 24;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0],obiekt[0][1]-2,3};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]-1,3};
            obiekt[2]= {obiekt[2][0]+2,obiekt[2][1],3};
            obiekt[3]= {obiekt[3][0]+1,obiekt[3][1]+1,3};
            gen = 23;
                }
        break;
        case 24://L
            obiekt[0]= {obiekt[0][0]-2,obiekt[0][1],3};
            obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]-1,3};
            obiekt[2]= {obiekt[2][0],obiekt[2][1]-2,3};
            obiekt[3]= {obiekt[3][0]+1,obiekt[3][1]-1,3};
            gen = 2;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0]+2,obiekt[0][1],3};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]+1,3};
            obiekt[2]= {obiekt[2][0],obiekt[2][1]+2,3};
            obiekt[3]= {obiekt[3][0]-1,obiekt[3][1]+1,3};
            gen = 24;
                }
        break;
        case 3://ReversL
            obiekt[0]= {obiekt[0][0]-2,obiekt[0][1],4};
            obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]+1,4};
            obiekt[2]= {obiekt[2][0],obiekt[2][1]+2,4};
            obiekt[3]= {obiekt[3][0]+1,obiekt[3][1]+1,4};
            gen = 32;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0]+2,obiekt[0][1],4};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]-1,4};
            obiekt[2]= {obiekt[2][0],obiekt[2][1]-2,4};
            obiekt[3]= {obiekt[3][0]-1,obiekt[3][1]-1,4};
                    gen = 3;
                }
        break; 
        case 32://RL
            obiekt[0]= {obiekt[0][0],obiekt[0][1]-2,4};
            obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]-1,4};
            obiekt[2]= {obiekt[2][0]-2,obiekt[2][1],4};
            obiekt[3]= {obiekt[3][0]-1,obiekt[3][1]+1,4};
            gen = 33;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0],obiekt[0][1]+2,4};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]+1,4};
            obiekt[2]= {obiekt[2][0]+2,obiekt[2][1],4};
            obiekt[3]= {obiekt[3][0]+1,obiekt[3][1]-1,4};
                    gen = 32;
                }
        break;
        case 33://RL
            obiekt[0]= {obiekt[0][0]+2,obiekt[0][1],4};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]-1,4};
            obiekt[2]= {obiekt[2][0],obiekt[2][1]-2,4};
            obiekt[3]= {obiekt[3][0]-1,obiekt[3][1]-1,4};
            gen = 34;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0]-2,obiekt[0][1],4};
            obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]+1,4};
            obiekt[2]= {obiekt[2][0],obiekt[2][1]+2,4};
            obiekt[3]= {obiekt[3][0]+1,obiekt[3][1]+1,4};
            gen = 33;
                }
        break;
        case 34://RL
            obiekt[0]= {obiekt[0][0],obiekt[0][1]+2,4};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]+1,4};
            obiekt[2]= {obiekt[2][0]+2,obiekt[2][1],4};
            obiekt[3]= {obiekt[3][0]+1,obiekt[3][1]-1,4};
            gen = 3;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0],obiekt[0][1]-2,4};
            obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]-1,4};
            obiekt[2]= {obiekt[2][0]-2,obiekt[2][1],4};
            obiekt[3]= {obiekt[3][0]-1,obiekt[3][1]+1,4};
            
            gen = 34;
                }
        break;
        case 4://Z
            obiekt[0]= {obiekt[0][0]+1,obiekt[0][1]-1,5};
            obiekt[1]= {obiekt[1][0],obiekt[1][1],5};
            obiekt[2]= {obiekt[2][0]+1,obiekt[2][1]+1,5};
            obiekt[3]= {obiekt[3][0],obiekt[3][1]+2,5};
            gen = 41;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0]-1,obiekt[0][1]+1,5};
            obiekt[1]= {obiekt[1][0],obiekt[1][1],5};
            obiekt[2]= {obiekt[2][0]-1,obiekt[2][1]-1,5};
            obiekt[3]= {obiekt[3][0],obiekt[3][1]-2,5};
            gen = 4;
                }
        break;
        case 41://Z
            obiekt[0]= {obiekt[0][0]-1,obiekt[0][1]+1,5};
            obiekt[1]= {obiekt[1][0],obiekt[1][1],5};
            obiekt[2]= {obiekt[2][0]-1,obiekt[2][1]-1,5};
            obiekt[3]= {obiekt[3][0],obiekt[3][1]-2,5};
            gen = 4;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0]+1,obiekt[0][1]-1,5};
            obiekt[1]= {obiekt[1][0],obiekt[1][1],5};
            obiekt[2]= {obiekt[2][0]+1,obiekt[2][1]+1,5};
            obiekt[3]= {obiekt[3][0],obiekt[3][1]+2,5};
            gen = 41;
                }
        break;
        case 5://ReversZ
            obiekt[0]= {obiekt[0][0]-1,obiekt[0][1]+1,6};
            obiekt[1]= {obiekt[1][0],obiekt[1][1],6};
            obiekt[2]= {obiekt[2][0]+1,obiekt[2][1]+1,6};
            obiekt[3]= {obiekt[3][0]+2,obiekt[3][1],6};
            gen = 51;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0]+1,obiekt[0][1]-1,6};
            obiekt[1]= {obiekt[1][0],obiekt[1][1],6};
            obiekt[2]= {obiekt[2][0]-1,obiekt[2][1]-1,6};
            obiekt[3]= {obiekt[3][0]-2,obiekt[3][1],6};
           gen = 5;
                }
        break;
        case 51://ReversZ
            obiekt[0]= {obiekt[0][0]+1,obiekt[0][1]-1,6};
            obiekt[1]= {obiekt[1][0],obiekt[1][1],6};
            obiekt[2]= {obiekt[2][0]-1,obiekt[2][1]-1,6};
            obiekt[3]= {obiekt[3][0]-2,obiekt[3][1],6};
            gen = 5;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0]-1,obiekt[0][1]+1,6};
            obiekt[1]= {obiekt[1][0],obiekt[1][1],6};
            obiekt[2]= {obiekt[2][0]+1,obiekt[2][1]+1,6};
            obiekt[3]= {obiekt[3][0]+2,obiekt[3][1],6};
           gen = 51;
                }
        break;
        case 6://Nosek
            obiekt[0]= {obiekt[0][0],obiekt[0][1]-2,7};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]-1,7};
            obiekt[2]= {obiekt[2][0]+2,obiekt[2][1],7};
            obiekt[3]= {obiekt[3][0],obiekt[3][1],7};
            gen = 62;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0],obiekt[0][1]+2,7};
            obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]+1,7};
            obiekt[2]= {obiekt[2][0]-2,obiekt[2][1],7};
            obiekt[3]= {obiekt[3][0],obiekt[3][1],7};
                    gen = 6;
                }
        break; 
        case 62://L
            obiekt[0]= {obiekt[0][0]+2,obiekt[0][1],7};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]+1,7};
            obiekt[2]= {obiekt[2][0],obiekt[2][1]+2,7};
            obiekt[3]= {obiekt[3][0],obiekt[3][1],7};
            gen = 63;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
                    obiekt[0]= {obiekt[0][0]-2,obiekt[0][1],7};
                    obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]-1,7};
                    obiekt[2]= {obiekt[2][0],obiekt[2][1]-2,7};
                    obiekt[3]= {obiekt[3][0],obiekt[3][1],7};
                    gen = 62;
                }
        break;
        case 63://L
            obiekt[0]= {obiekt[0][0],obiekt[0][1]+2,7};
            obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]+1,7};
            obiekt[2]= {obiekt[2][0]-2,obiekt[2][1],7};
            obiekt[3]= {obiekt[3][0],obiekt[3][1],7};
            gen = 64;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0],obiekt[0][1]-2,7};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]-1,7};
            obiekt[2]= {obiekt[2][0]+2,obiekt[2][1],7};
            obiekt[3]= {obiekt[3][0],obiekt[3][1],7};
            gen = 63;
                }
        break;
        case 64://L
            obiekt[0]= {obiekt[0][0]-2,obiekt[0][1],7};
            obiekt[1]= {obiekt[1][0]-1,obiekt[1][1]-1,7};
            obiekt[2]= {obiekt[2][0],obiekt[2][1]-2,7};
            obiekt[3]= {obiekt[3][0],obiekt[3][1],7};
            gen = 6;
                if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
                (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
                (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
                (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
                {
            obiekt[0]= {obiekt[0][0]+2,obiekt[0][1],7};
            obiekt[1]= {obiekt[1][0]+1,obiekt[1][1]+1,7};
            obiekt[2]= {obiekt[2][0],obiekt[2][1]+2,7};
            obiekt[3]= {obiekt[3][0],obiekt[3][1],7};
            gen = 64;
                }
        break;        

    }
}


void PrzesunObiekt()
{
    obiekt[0][1]--; 
    obiekt[1][1]--;
    obiekt[2][1]--;
    obiekt[3][1]--;
   
    if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
       (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
       (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
       (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
      {
            obiekt[0][1]++; 
            obiekt[1][1]++;
            obiekt[2][1]++;
            obiekt[3][1]++;
            plan[obiekt[0][1]][obiekt[0][0]] = obiekt[0][2];
            plan[obiekt[1][1]][obiekt[1][0]] = obiekt[1][2];
            plan[obiekt[2][1]][obiekt[2][0]] = obiekt[2][2];
            plan[obiekt[3][1]][obiekt[3][0]] = obiekt[3][2];
            GenerujObjekt();   
            GenerujNext();       
      }
    
}

void PrzesunLewo()
{
    obiekt[0][0]--; 
    obiekt[1][0]--;
    obiekt[2][0]--;
    obiekt[3][0]--;
   
    if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
       (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
       (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
       (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
      {
            obiekt[0][0]++; 
            obiekt[1][0]++;
            obiekt[2][0]++;
            obiekt[3][0]++;          
      }
    
}

void PrzesunPrawo()
{
    obiekt[0][0]++; 
    obiekt[1][0]++;
    obiekt[2][0]++;
    obiekt[3][0]++;
   
    if((plan[obiekt[0][1]][obiekt[0][0]] != 0) ||
       (plan[obiekt[1][1]][obiekt[1][0]] != 0) ||
       (plan[obiekt[2][1]][obiekt[2][0]] != 0) ||
       (plan[obiekt[3][1]][obiekt[3][0]] != 0)) 
      {
            obiekt[0][0]--; 
            obiekt[1][0]--;
            obiekt[2][0]--;
            obiekt[3][0]--;          
      }
    
}

void KasujLinie()
{
    int dalej = 0;
    do 
    {
    dalej = 0;
    for(int j=1;j<21;j++)
    {
        if((plan[j][1] >= 1) &&
           (plan[j][2] >= 1) &&
           (plan[j][3] >= 1) &&
           (plan[j][4] >= 1) &&
           (plan[j][5] >= 1) &&
           (plan[j][6] >= 1) &&
           (plan[j][7] >= 1) &&
           (plan[j][8] >= 1) &&
           (plan[j][9] >= 1) &&
           (plan[j][10] >= 1))
           {
                for(int i=j;i<20;i++)
                {
                    for(int n=1;n<11;n++)
                    {
                    plan[i][n]=plan[i+1][n];
                    }
                }
                
                    for(int n=1;n<11;n++)
                    {
                    plan[20][n]=plan[21][n];
                    }
               dalej = 1;
               punkty++;
           }
           
    }
    } while(dalej == 1);
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
    
    
}

// funkcja generuj¹ca scenê 3D
void Display()
{   
    //Generowanie t³a
    glClearColor(1, 1, 1, 1);        
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glEnable(GL_DEPTH_TEST);

    
    
    
    if (menu == 1){
    KasujLinie();
    Wypelni();
    GameTekst();
    }
    
    if (menu == 0){
    Logo();
    MenuG();
    }
    
    if (menu == 2){
    Logo();
    }
    
    if (menu == 3){
    Logo();
    }
    
    if (menu == 4){
    Logo();
    }
    

    // skierowanie poleceñ do wykonania
    glFlush();    
    // zamiana buforów koloru
    glutSwapBuffers();
}

void Timer( int value )
{   if (menu == 1){
    PrzesunObiekt();  
    } 
    // wyœwietlenie sceny
    Display();    
    // nastêpne wywo³anie funkcji timera
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
    if(key == ' ')
    {
    
         switch(menuwyb)      
    {  
        case 0:
        menu = 1;
        GenerujNext();
        break; 
        
        case 1:
        menu = 2;
        break; 
        
        case 2:
        menu = 3;
        break; 
        
        case 3:
        menu = 4;
        break; 
        
        case 4:
        exit(0);
        break;

    };
    }
    
    if(key == 27 && menu == 0)//ESC
    {
        exit( 0 );
    }
    else if(key == 27)
    {
        menu = 0;
    }
    
    Display();
}
void Znaki_Spec(int key, int x, int y)
{ 
    if (menu == 1)
    {
    switch(key)      
    {  
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
            key=0;      
        break; 
    }
    }
    if (menu == 0)
    {
    switch(key)      
    {  
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