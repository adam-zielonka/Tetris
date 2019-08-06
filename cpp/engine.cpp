#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

namespace Engine {
  const GLfloat Colors[12][3] = {
    {1,1,1},
    {0,1,1}, // Square     - Turkus
    {1,0,0}, // Line       - Czerwony
    {1,1,0}, // L          - Zloty
    {1,0,1}, // Mirrored L - Fiolet
    {0,1,0}, // Z          - Niebieski
    {0,0,1}, // Mirrored Z - Zielony
    {0.5,0.5,0.5}, // Nose - Szary
    {0, 0.1, 0}, // Background 1A //8
    {0, 0, 0.1}, // Background 1B //9
    {0.1, 0.1, 0}, // Background 2A //10
    {0.1, 0, 0.1} // Background 2B //11
  };

  void renderBoard(int board[20][20]) {
    GLfloat Syh=-1.0, Syl=-0.9, Sxl=-1.0, Sxh=-0.9;

    for(int j = 0; j < 20; j++) {
      Sxl=-1.0;
      Sxh=-0.9;
      
      for(int i = 0; i < 20; i++) {
        glColor3fv(Colors[board[j][i]]);
          
        glBegin(GL_QUADS);
          glVertex3f(Sxl, Syl, 0);
          glVertex3f(Sxh, Syl, 0);
          glVertex3f(Sxh, Syh, 0); 
          glVertex3f(Sxl, Syh, 0); 
        glEnd();
        
        Sxl+=0.1;
        Sxh+=0.1;
      }
      Syl+=0.1;
      Syh+=0.1;
    }
  }

  void renderText(string String, int x, int y) {
    glColor3f(0, 0, 0);
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
    for (unsigned int i=0; i<String.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  }

  void Reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 1.5, 0, 0, 0, 0, 1, 0);
  }

  void Init(int argc, char * argv[], GLint * speed, void (* MainLoop)(void), void (* Timer)(void),
    void (* Keyboard)(unsigned char, int, int),  void (* SpecialKeys)(int, int, int)) {

    static function<void()> mainLoop = [&]() { MainLoop(); };
    static function<void(unsigned char, int , int)> keyboard_bounce = [&](unsigned char key, int x, int y) { Keyboard(key, x, y); };
    static function<void(int, int , int)> special_keys_bounce = [&](int key, int x, int y) { SpecialKeys(key, x, y); };
    
    auto display = []() {   
      glClearColor(1, 1, 1, 1);        
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glEnable(GL_DEPTH_TEST);

      mainLoop();

      glFlush();
      glutSwapBuffers();
    };
    static std::function<void()> display_bounce = [&]() { display(); };

    auto reshape = [](int width, int height) { Engine::Reshape(width, height); display_bounce(); };
    auto specialKeys = [](int key, int x, int y) { special_keys_bounce(key, x, y); display_bounce(); };
    auto keyboard = [](unsigned char key, int x, int y) { keyboard_bounce(key, x, y); display_bounce(); };

    static std::function<void()> timer_bounce;
    auto timer = [](int ms) { timer_bounce(); };
    timer_bounce = [&]() {
      Timer();
      display();
      glutTimerFunc(*speed, timer, 0);
    };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Tetris");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);    
    glutTimerFunc(*speed, timer, 0);
    glutMainLoop();
  }
}
