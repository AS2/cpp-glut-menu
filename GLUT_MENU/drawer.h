#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <vector>
#include "menuParser.h"
#include "dialogWindow.h"

/*********************
 * Screen layer type *
 *********************/

class layer {
private:
  int width, height;
  const int buttonHeight = 19, charWidth = 9, charHeight = 15;

  // transform coords funcs
  double xToXcoord(int x);
  double YToYcoord(int y);
  int xCoordsTox(double xCoord);
  int yCoordToy(double yCoord);

  // draw text functions
  void beginText();
  void drawString(float x, float y, std::string string);
  void endText();

public:
  layer(int screenWidth, int screenHeight);

  void DrawMenu(menuObject& menu, int x, int y);
  void DrawDW(dialogWindow& dW);

  int CheckClick(menuObject& menu, dialogWindow& dW, int menuX, int menuY, int mouseX, int mouseY);
};

#endif