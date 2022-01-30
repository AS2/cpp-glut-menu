#include "dialogWindow.h"

dialogWindow::dialogWindow() {
  message = "-no msg-";
  isShowen = 0;
}

dialogWindow::dialogWindow(std::string newMessage) {
  message = newMessage;
  isShowen = 0;
}

void dialogWindow::SetMessage(std::string newMessage) {
  message = newMessage;
}

std::string dialogWindow::GetMessage(void) {
  return message;
}

void dialogWindow::showDW() {
  isShowen = 1;
}

void dialogWindow::hideDW() {
  isShowen = 0;
}

char dialogWindow::isShowDW() {
  return isShowen;
}