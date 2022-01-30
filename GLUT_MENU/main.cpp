#include <iostream>

#include "glut.h"
#include "menuParser.h"
#include "drawer.h"

#pragma warning(disable: 4996)

#define width 1280
#define height 720

menu testMenu("testMenu.txt");
dialogWindow dW;
layer menuLayer(width, height);

int lastX, lastY;

void DisplayFunc() {
  glClearColor(0.3, 0.5, 0.7, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  if (testMenu.isShow())
    menuLayer.DrawMenu(testMenu, lastX, lastY);
  if(dW.isShowDW())
    menuLayer.DrawDW(dW);

  glFinish();
  glutSwapBuffers();
}

void KeyboardFunc(unsigned char key, int x, int y) {
  if (dW.isShowDW()) {
    dW.hideDW();
    glutPostRedisplay();
  }

  if (key == 27)
    exit(0);
}

void MouseFunc(int button, int state, int x, int y) {
  if (dW.isShowDW()) {
    dW.hideDW();
    glutPostRedisplay();
  }

  if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    testMenu.CloseAllSubmenues();
    testMenu.showMenu();
    lastX = x, lastY = y;

    glutPostRedisplay();
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    if (menuLayer.CheckClick(testMenu, dW, lastX, lastY, x, y) == 0) {
      testMenu.CloseAllSubmenues();
      testMenu.hideMenu();
    }

    glutPostRedisplay();
  }
}

int main(int argc, char* argv[]) {
  testMenu.MenuConsoleWriter();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(width, height);
  glutCreateWindow("GLUT init try!");

  glutDisplayFunc(DisplayFunc);
  glutMouseFunc(MouseFunc);
  glutKeyboardFunc(KeyboardFunc);

  glutMainLoop();
}