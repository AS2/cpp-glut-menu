#ifndef __MENU_FUNCTIONS_H__
#define __MENU_FUNCTIONS_H__

#include <list>
#include <string>
#include <functional>

class functionType {
private:
  std::string functionName;
  std::function<std::string()> function;
  
public:
  functionType() {
  }

  functionType(std::string newFuncName, std::function<std::string()> newFunc) {
    functionName = newFuncName;
    function = newFunc;
  }

  std::string GetFuncName() {
    return functionName;
  }

  std::function<std::string()> GetFunc() {
    return function;
  }
};

class functionsList {
private:
  std::list<functionType> functions;
public:
  functionsList();
  int IsFucntionExist(std::string checkFunc);
  std::function<std::string()> GetFuncByName(std::string checkFunc);
};

#endif
