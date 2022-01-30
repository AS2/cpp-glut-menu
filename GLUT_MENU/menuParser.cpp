#include <iostream>

#include <fstream>
#include <sstream>
#include <iterator>

#include <functional>

#include "menuFunctions.h"
#include "menuParser.h"

/***********************
 * MENU ELEMENTS TYPES *
 ***********************/

// 'menuObject' functions
menuObject::menuObject() {
  objectType = 0;
  isShowen = 0;
} 
void menuObject::SetName(std::string newName) {
  name = newName;
}

std::string menuObject::GetName(void) {
  return name;
}

int menuObject::GetType(void) {
  return objectType;
}

void menuObject::SetType(int type) {
  objectType = type;
}

void menuObject::showMenu() {
  isShowen = 1;
}

void menuObject::hideMenu() {
  isShowen = 0;
}
char menuObject::isShow() {
  return isShowen;
}

// 'menuFunction' functions
menuFunction::menuFunction(std::string newName, std::function<std::string()> newFunction) {
  SetName(newName);
  function = newFunction;
}

void menuFunction::PrintObject() {
  std::cout << "FUNC: " << GetName() << std::endl;
}

std::string menuFunction::ClickAction(void) {
  return function();
}

// 'menu' functions
menu::menu() {
  parent = NULL; 
}

void menu::PrintObject() {
  std::cout << "MENU: " << GetName() << std::endl;
  for (auto elem : menuObjects)
    elem->PrintObject();
}

void menu::CloseAllSubmenues(void) {
  for (auto elem : menuObjects)
    if (elem->GetType() == 1 && elem->isShow() == 1) {
      elem->CloseAllSubmenues();
      elem->hideMenu();
    }
}

std::string menu::ClickAction(void) {
  parent->CloseAllSubmenues();
  this->showMenu();
  return "-no msg-";
}

/*************
 * MENU TYPE *
 *************/

menu::menu(std::string newName, std::ifstream &fin, menu *newParent) {
  parent = newParent;
  std::string oneStringFromFile;
  functionsList funcList;

  // check '{'
  getline(fin, oneStringFromFile);
  if (oneStringFromFile[0] != '{')
    return;

  SetName(newName);

  // read while don't read '}'
  getline(fin, oneStringFromFile);
  while (oneStringFromFile[0] != '}') {
    std::stringstream sStream(oneStringFromFile);
    std::istream_iterator<std::string> wordsInStream(sStream);

    menuObject *newObject;
    if ((*wordsInStream) == "FUNC") {
      // take func's name
      wordsInStream++;
      std::string funcName = *wordsInStream;
      if (!funcList.IsFucntionExist(funcName))
        return;
      std::function<std::string()> newFunc = funcList.GetFuncByName(funcName);

      // take name for new object
      wordsInStream++;
      std::string newName;
      while (wordsInStream != std::istream_iterator<std::string>())
        newName += (*wordsInStream++) + " ";

      // create new function object
      newObject = new menuFunction(newName, newFunc);
      newObject->SetType(0);
    }
    else {
      // take name for new object
      wordsInStream++;
      std::string newName;
      while (wordsInStream != std::istream_iterator<std::string>())
        newName += (*wordsInStream++) + " ";

      newObject = new menu(newName, fin, this);
      newObject->SetType(1);
    }

    menuObjects.push_back(newObject);
    getline(fin, oneStringFromFile);
  }
}

menu::menu(std::string iFileName) {
  isShowen = 0;
  parent = NULL;

  std::ifstream fin(iFileName);
  std::string oneStringFromFile;
  functionsList funcList;

  while (getline(fin, oneStringFromFile)) {
    std::stringstream sStream(oneStringFromFile);
    std::istream_iterator<std::string> wordsInStream(sStream);

    menuObject *newObject;
    if ((*wordsInStream) == "FUNC") {
      // take func's name
      wordsInStream++;
      std::string funcName = *wordsInStream;
      if (!funcList.IsFucntionExist(funcName))
        return;
      std::function<std::string()> newFunc = funcList.GetFuncByName(funcName);

      // take name for new object
      wordsInStream++;
      std::string newName;
      while (wordsInStream != std::istream_iterator<std::string>())
        newName += (*wordsInStream++) + " ";

      newObject = new menuFunction(newName, newFunc);
      newObject->SetType(0);
    }
    else {
      // take name for new object
      wordsInStream++;
      std::string newName;
      while (wordsInStream != std::istream_iterator<std::string>())
        newName += (*wordsInStream++) + " ";

      newObject = new menu(newName, fin, this);
      newObject->SetType(1);
    }

    menuObjects.push_back(newObject);
  }
}

void menu::MenuConsoleWriter() {
  for (auto elem : menuObjects)
    elem->PrintObject();
}
