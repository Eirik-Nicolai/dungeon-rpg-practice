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

//FIXME Redo all this shit
//probably have pure virtual classes and
//more generic text items
//etc etc

struct TextItemOnSelect
{
  std::string text;
  std::function<void(void)> action;
};

struct TextItemOnScroll
{
  std::string text;
  std::function<int(void)> action;
};
template
<typename T>
class Menu {
  public:
    Menu()
    {
      curr_selected = 0;
    }
    virtual ~Menu() = default;

  public:
    void ScrollDown()
    {
      curr_selected += 1;
      if(curr_selected>=list_items.size()) curr_selected = 0;
    }
    void ScrollUp()
    {
      curr_selected -= 1;
      if(curr_selected<0) curr_selected = list_items.size()-1;
    }
    void Select()
    {
      list_items[curr_selected].action();
    }
    int ListSize(){return list_items.size();}


    void AddItem(T t){list_items.emplace_back(t);}

  public:
    int curr_selected;
    std::vector<T> list_items;
};

class PauseMenu : public Menu<TextItemOnSelect> {
  public:
    PauseMenu() = default;
    PauseMenu(TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&);
    PauseMenu(TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&);
    PauseMenu(TextItemOnSelect&, TextItemOnSelect&);
    PauseMenu(TextItemOnSelect&);

  public:

};

class EquipmentMenu : public Menu<TextItemOnScroll> {
  public:
    EquipmentMenu() = default;
    EquipmentMenu(std::function<void(void)>);

  public:
    int ScrollUp();
    int ScrollDown();
    int ScrollLeft();
    int ScrollRight();

    void Select();

    void AddItemLeft(TextItemOnScroll);
    void AddItemMiddle(TextItemOnScroll);
    void AddItemRight(TextItemOnScroll);
    int curr_menu;
    int CurrentSelected();

  private:
    Menu m_menus[3];
    std::function<void(void)> menu_func;
};

class InventoryMenu : public Menu<TextItemOnSelect> {
  public:
    InventoryMenu() = default;

    void LoadInventoryOfType(std::vector<entt::entity>&);
    void LoadAllInventoryForEntity(entt::registry&, entt::entity&);

};

class CombatMenu : public Menu<TextItemOnSelect> {
  public:
    CombatMenu() = default;
    CombatMenu(TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&);
    CombatMenu(TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&);
    CombatMenu(TextItemOnSelect&, TextItemOnSelect&);
    CombatMenu(TextItemOnSelect&);

  public:
    void ScrollLeft();
    void ScrollRight();

};

class TargetMenu : public Menu<TextItemOnSelect> {
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
