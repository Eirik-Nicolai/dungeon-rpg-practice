#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>
#include <functional>
#include <vector>

struct TextItem
{
  std::string text;
  std::function<void(void)> action;
};

class MenuMenu {

};

class Menu {
  public:
    Menu();
    virtual ~Menu() = default;

  public:
    void ScrollDown();
    void ScrollUp();
    void Select();

  public:
    int curr_selected;
    int list_size;
    std::vector<TextItem> list_items;
};

class PauseMenu : public Menu {
  public:
    PauseMenu() = default;
    PauseMenu(TextItem&, TextItem&, TextItem&);

  public:

};

class CombatMenu : public Menu {
  public:
    CombatMenu() = default;
    CombatMenu(TextItem&, TextItem&, TextItem&, TextItem&);
    CombatMenu(TextItem&, TextItem&, TextItem&);

  public:
    void ScrollLeft();
    void ScrollRight();

};


#endif // MENU_H_
