#ifndef __DIALOG_WINDOW_H__
#define __DIALOG_WINDOW_H__

#include <iostream>

#include <string>
#include <functional>
#include <list>

/**********************
 * Dialog window type *
 **********************/

class dialogWindow {
private:
  std::string message;
  char isShowen;
public:
  dialogWindow();
  dialogWindow(std::string newMessage);

  void SetMessage(std::string newMessage);
  std::string GetMessage(void);

  void showDW();
  void hideDW();
  char isShowDW();
};

#endif
