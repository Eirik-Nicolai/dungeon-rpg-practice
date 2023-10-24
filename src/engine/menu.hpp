#ifndef MENU_H_
#define MENU_H_

#include <vector>
#include <string>
#include <iostream>
#include <functional>

#include <entt/entt.hpp>

#include "utils/debug.hpp"

#include "components/combat.hpp"
#include "components/globals.hpp"
#include "components/equipment.hpp"

struct TextItem
{
  std::string text;
  std::function<void(void)> action;
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
    PauseMenu(TextItem&, TextItem&, TextItem&, TextItem&);
    PauseMenu(TextItem&, TextItem&, TextItem&);
    PauseMenu(TextItem&, TextItem&);
    PauseMenu(TextItem&);

  public:

};

class EquipmentMenu : public Menu {
  public:
    EquipmentMenu() = default;
    EquipmentMenu(std::function<void(void)>);

  public:
    void LoadEquipment(entt::registry&, EquipmentState&);
    entt::entity ScrollLeft();
    entt::entity ScrollRight();

  private:
    int curr_menu;

    Menu m_menus[3];
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
