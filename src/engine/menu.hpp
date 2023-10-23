#ifndef MENU_H_
#define MENU_H_

#include <vector>
#include <string>
#include <iostream>
#include <functional>

#include <entt/entt.hpp>

#include "utils/debug.hpp"

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

class TargetMenu : public Menu {
  public:
    TargetMenu() = default;
    TargetMenu(std::function<void(void)>, entt::entity&);
    TargetMenu(std::function<void(void)>, entt::entity&, entt::entity&);
    TargetMenu(std::function<void(void)>, entt::entity&, entt::entity&, entt::entity&);
    TargetMenu(std::function<void(void)>, entt::entity&, entt::entity&, entt::entity&, entt::entity&);

  public:
    entt::entity GetSelected();
  private:
    std::vector<entt::entity> targets;
};


#endif // MENU_H_
