#include <list>
#include <string>

#include "drawer.h"
#include "dialogWindow.h"
#include "glut.h"

double layer::xToXcoord(int x) {
  return 2.0 * x / width - 1;
}

double layer::YToYcoord(int y) {
  return 1 - 2.0 * y / height;
}

int layer::xCoordsTox(double xCoord) {
  return (xCoord + 1) * width / 2;
}

int layer::yCoordToy(double yCoord) {
  return (yCoord + 1) * height / 2;
}

void layer::beginText() {
  // Save the current projection matrix
  glPushMatrix();

  // Make the current matrix the identity matrix
  glLoadIdentity();

  // Set the projection (to 2D orthographic)
  gluOrtho2D(0, width, 0, height);
}

void layer::drawString(float x, float y, std::string string) {
  glRasterPos2f(x, y);
  int length;

  for (int i = 0; string[i] != '\0'; i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);  // Updates the position
  }
}

void layer::endText() {
  // Restore the original projection matrix
  glPopMatrix();
}

layer::layer(int screenWidth, int screenHeight) {
  width = screenWidth;
  height = screenHeight;
}

void layer::DrawMenu(menuObject& menu, int x, int y) {
  std::list<menuObject*> objects = menu.GetMenuObj();
  int maxLength = 0, currentLength, objectsCount = 0;
  std::string currentName;

  // get menu params 
  for (auto elem : objects) {
    objectsCount++;
    currentName = elem->GetName();

    currentLength = currentName.length();
    if (maxLength < currentLength)
      maxLength = currentLength;
  }

  // draw rectangle with correct size
  glColor3f(0, 0, 0);
  glRectd(xToXcoord(x), YToYcoord(y), xToXcoord(x + maxLength * charWidth + 4), YToYcoord(y + objectsCount * buttonHeight));

  //draw text
  glColor3f(1, 1, 1);
  beginText();

  int currElem = 0, newX, newY;
  for (auto elem : objects) {
    currElem++;
    currentName = elem->GetName();

    newX = x + 2;
    newY = height - (y + buttonHeight * currElem - (buttonHeight - charHeight) / 2);
    drawString(newX, newY, currentName);
  }

  endText();

  // draw submenues
  newX = x + maxLength * 9 + 4;
  currElem = 0;
  for (auto elem : objects) {
    newY = y + 19 * currElem;
    if (elem->GetType() == 1 && elem->isShow() == 1)
      DrawMenu(*elem, newX, newY);
    currElem++;
  }
}

void layer::DrawDW(dialogWindow& dW) {
  double xC1, xC2, yC1, yC2;
  std::string message = dW.GetMessage();
  int dwWidth = message.length() * 9 + 10, dwHeight = 37;

  // draw rectangle with correct size
  xC1 = xToXcoord((width - dwWidth) / 2);
  xC2 = xToXcoord((width + dwWidth) / 2);
  yC1 = YToYcoord((height - dwHeight) / 2);
  yC2 = YToYcoord((height + dwHeight) / 2);
  glColor3f(0.7, 0.7, 0.7);
  glRectd(xC1, yC1, xC2, yC2);

  //draw text
  glColor3f(0.1, 0.1, 0.1);
  beginText();
  drawString((width - dwWidth) / 2 + 5, (height - dwHeight) / 2 + 9, message);
  endText();
}

// RETURNS:
//  - 0 - cursor doesnt cover any menuObject
//  - 1 - cursor cover menu (submenu)
//  - 2 - cursor cover function
int layer::CheckClick(menuObject& menu, dialogWindow& dW, int menuX, int menuY, int mouseX, int mouseY) {
  std::list<menuObject*> objects = menu.GetMenuObj();
  int maxLength = 0, currentLength, objectsCount = 0;
  std::string currentName;

  // get menu params 
  for (auto elem : objects) {
    objectsCount++;
    currentName = elem->GetName();

    currentLength = currentName.length();
    if (maxLength < currentLength)
      maxLength = currentLength;
  }

  // go throw all menu and check click
  int res = 0;

  int newX = menuX + maxLength * charWidth + 4, newY;
  int currElem = 1;
  for (auto elem : objects) {
    newY = menuY + buttonHeight * currElem;
    if (mouseX >= menuX && mouseX < newX && mouseY >= newY - buttonHeight && mouseY < newY) {
      if (elem->GetType() == 0) {
        std::string msg = elem->ClickAction();
        if (msg != "-no msg-") {
          dW.showDW();
          dW.SetMessage(msg);
        }
        menu.CloseAllSubmenues();
        menu.hideMenu();
        return 2;
      }
      else {
        elem->ClickAction();
        return 1;
      }
    }
    else if (elem->GetType() == 1 && elem->isShow() == 1) {
      res = CheckClick(*elem, dW, newX, newY - buttonHeight, mouseX, mouseY);
      if (res == 1)
        return 1;
      else if (res == 2) {  
        menu.CloseAllSubmenues();
        menu.hideMenu();
        return 2;
      }
    }
      
    currElem++;
  }

  return 0;
}
