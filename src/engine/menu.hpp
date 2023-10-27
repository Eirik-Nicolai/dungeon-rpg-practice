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

template
<typename ret> //TODO add argument to template
using func = std::function<ret(void)>;

template
<typename Type, typename ret>
struct MenuItem
{
  Type content;
  std::string info;
  func<ret> select_cmd;
  func<ret> scroll_cmd;
};

class Menu
{
  public:
    Menu();
    virtual ~Menu() = default;

  public:
    virtual void scroll_up() = 0;
    virtual void scroll_down() = 0;

    virtual void select() = 0;
    virtual int size() = 0;
    virtual bool is_hovered(int) = 0;

  protected:
    int sel_col;
    int sel_row;
};

// "menu within menu", scrolls through more items than fits on screen
class ScrollableMenu : Menu
{
  using list = std::vector<MenuItem<entt::entity, entt::entity>>;
  public:
    ScrollableMenu() = default;
    ScrollableMenu(list&, int);

  public:
    void scroll_up() override;
    void scroll_down() override;

    void select() override;
    int size() override;
    bool is_hovered(int) override;

    MenuItem<entt::entity, entt::entity> &operator [](int i);

    list get_inner();

  private:
    list items;
    int inner_size;
    int inner_sel_row;

    list::iterator inner_begin;
};

// simple, couple text items with a function
class SimpleMenu : Menu
{
  public:
    SimpleMenu() = default;
    SimpleMenu(MenuItem<std::string, void>&);
    SimpleMenu(MenuItem<std::string, void>&,MenuItem<std::string, void>&);
    SimpleMenu(MenuItem<std::string, void>&,MenuItem<std::string, void>&,MenuItem<std::string, void>&);
    SimpleMenu(MenuItem<std::string, void>&,MenuItem<std::string, void>&,MenuItem<std::string, void>&,MenuItem<std::string, void>&);

  public:
    void scroll_up() override;
    void scroll_down() override;

    void select() override;
    int size() override;
    bool is_hovered(int) override;

    MenuItem<std::string, void> &operator [](int i);

  private:
    std::vector<MenuItem<std::string, void>> items;
};


// menu with dimensions in x and y axis
class MultiDimMenu : Menu
{
  using multidimlist = std::vector<std::vector<MenuItem<entt::entity, void>>>;
  using list         = std::vector<MenuItem<entt::entity, void>>;
  public:
    MultiDimMenu() = default;
    MultiDimMenu(list &);
    MultiDimMenu(list &, list &);
    MultiDimMenu(list &, list &, list &);
    MultiDimMenu(list &, list &, list &, list &);

  public:
    void scroll_up() override;
    void scroll_down() override;
    void scroll_left();
    void scroll_right();

    void select() override;
    int size() override;
    bool is_hovered(int) override;
    bool is_hovered(int,int);

    MenuItem<entt::entity, void> get_hovered();

    list &operator [](int i);


  private:
    multidimlist items;
};

// template
// <typename T>
// class Menu {
//   public:
//     Menu()
//     {
//       curr_selected = 0;
//     }
//     virtual ~Menu() = default;

//   public:
//     void ScrollDown()
//     {
//       curr_selected += 1;
//       if(curr_selected>=list_items.size()) curr_selected = 0;
//     }
//     void ScrollUp()
//     {
//       curr_selected -= 1;
//       if(curr_selected<0) curr_selected = list_items.size()-1;
//     }
//     void Select()
//     {
//       list_items[curr_selected].action();
//     }
//     int ListSize(){return list_items.size();}


//     void AddItem(T t){list_items.emplace_back(t);}

//   public:
//     int curr_selected;
//     std::vector<T> list_items;
// };

// class PauseMenu : public Menu<TextItemOnSelect> {
//   public:
//     PauseMenu() = default;
//     PauseMenu(TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&);
//     PauseMenu(TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&);
//     PauseMenu(TextItemOnSelect&, TextItemOnSelect&);
//     PauseMenu(TextItemOnSelect&);

//   public:

// };

// class EquipmentMenu : public Menu<TextItemOnScroll> {
//   public:
//     EquipmentMenu() = default;
//     EquipmentMenu(std::function<void(void)>);

//   public:
//     int ScrollUp();
//     int ScrollDown();
//     int ScrollLeft();
//     int ScrollRight();

//     void Select();

//     void AddItemLeft(TextItemOnScroll);
//     void AddItemMiddle(TextItemOnScroll);
//     void AddItemRight(TextItemOnScroll);
//     int curr_menu;
//     int CurrentSelected();

//   private:
//     Menu m_menus[3];
//     std::function<void(void)> menu_func;
// };

// class InventoryMenu : public Menu<TextItemOnSelect> {
//   public:
//     InventoryMenu() = default;

//     void LoadInventoryOfType(std::vector<entt::entity>&);
//     void LoadAllInventoryForEntity(entt::registry&, entt::entity&);

// };

// class CombatMenu : public Menu<TextItemOnSelect> {
//   public:
//     CombatMenu() = default;
//     CombatMenu(TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&);
//     CombatMenu(TextItemOnSelect&, TextItemOnSelect&, TextItemOnSelect&);
//     CombatMenu(TextItemOnSelect&, TextItemOnSelect&);
//     CombatMenu(TextItemOnSelect&);

//   public:
//     void ScrollLeft();
//     void ScrollRight();

// };

// class TargetMenu : public Menu<TextItemOnSelect> {
//   public:
//     TargetMenu() = default;
//     TargetMenu(std::function<void(void)>);

//     void AddTargets(std::vector<entt::entity> &);

//   public:
//     entt::entity GetSelected();
//   private:
//     std::vector<entt::entity> targets;
// };


#endif // MENU_H_
