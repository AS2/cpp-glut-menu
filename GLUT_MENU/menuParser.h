#ifndef __MENU_PARSER_H__
#define __MENU_PARSER_H__

#include <iostream>

#include <string>
#include <functional>
#include <list>

/***********************
 * MENU ELEMENTS TYPES *
 ***********************/

// PARENT CLASS
class menuObject {
private:
  std::string name;
  char objectType;    // 0 - is function, 1 - is menu
protected:
  char isShowen;      // parameter for menus
public:
  menuObject();

  void SetName(std::string newName);
  void SetType(int type);

  std::string GetName(void);
  int GetType(void);

  void showMenu();
  void hideMenu();
  char isShow();

  /*** VIRTUAL FUNCS ***/
  virtual void PrintObject() { std::cout << "???" << std::endl; };
  virtual std::string ClickAction() { return "???"; };

  virtual void CloseAllSubmenues(void) { std::cout << "???" << std::endl; };
  virtual void CloseAllSubmenuesInParent(void) { std::cout << "???" << std::endl; };

  virtual std::list<menuObject*> GetMenuObj(void) { return std::list<menuObject*>(1); };
};

class menuFunction : public menuObject {
private:
  std::function<std::string()> function;

public:
  menuFunction(std::string newName, std::function<std::string()> newFunction);

  virtual void PrintObject();
  virtual std::string ClickAction();
};

class menu : public menuObject {
private:
  std::list<menuObject*> menuObjects;
  menu* parent;

  menu(std::string newName, std::ifstream& fin, menu* newParent);
public:
  menu();
  menu(std::string iFileName);

  void MenuConsoleWriter();

  virtual std::list<menuObject*> GetMenuObj(void) { return menuObjects; }

  virtual void PrintObject();
  virtual std::string ClickAction();

  virtual void CloseAllSubmenues(void);
};

#endif