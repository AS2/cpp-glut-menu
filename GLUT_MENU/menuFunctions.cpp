#include <iostream>

#include <iterator>

#include "glut.h"
#include "menuFunctions.h"
#include "drawer.h"

static std::string print1() {
  std::cout << "1" << std::endl;
  return "-no msg-";
}

static std::string print2() {
  std::cout << "2" << std::endl;
  return "-no msg-";
}

static std::string print3() {
  std::cout << "3" << std::endl;
  return "-no msg-";
}

static std::string print4() {
  std::cout << "4" << std::endl;
  return "-no msg-";
}

static std::string print42() {
  std::cout << "42" << std::endl;
  return "-no msg-";
}

static std::string printRandomNumber() {
  int rnd = rand();
  std::cout << rnd << std::endl;
  return std::to_string(rnd);
}

static std::string sayHelloWorld() {
  return "HELLO WORLD!";
}

functionsList::functionsList() {
  functions.push_back(functionType("print1", print1));
  functions.push_back(functionType("print2", print2));
  functions.push_back(functionType("print3", print3));
  functions.push_back(functionType("print4", print4));
  functions.push_back(functionType("print42", print42));
  functions.push_back(functionType("printRandomNumber", printRandomNumber));
  functions.push_back(functionType("sayHelloWorld", sayHelloWorld));
}

int functionsList::IsFucntionExist(std::string checkFunc) {
  for (auto listElem : functions)
    if (listElem.GetFuncName() == checkFunc)
      return 1;
  return 0;
}

std::function<std::string()> functionsList::GetFuncByName(std::string checkFunc) {
  for (auto listElem : functions)
    if (listElem.GetFuncName() == checkFunc)
      return listElem.GetFunc();

  return nullptr;
}