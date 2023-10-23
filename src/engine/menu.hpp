#ifndef MENU_H_
#define MENU_H_

#include <vector>
#include <string>
#include <iostream>
#include <functional>

#include <entt/entt.hpp>

#include "utils/debug.hpp"

#include "components/combat.hpp"

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
    int ListSize();
    void Select();

  public:
    int curr_selected;
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
    CombatMenu(TextItem&, TextItem&);
    CombatMenu(TextItem&);

  public:
    void ScrollLeft();
    void ScrollRight();

};

class TargetMenu : public Menu {
  public:
    TargetMenu() = default;
    TargetMenu(std::function<void(void)>);

    void AddTargets(std::vector<entt::entity> &);

  public:
    entt::entity GetSelected();
  private:
    std::vector<entt::entity> targets;
};


#endif // MENU_H_
