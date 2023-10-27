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
template
<typename Type, typename ret>
class MultiDimMenu : Menu
{
  using multidimlist = std::vector<std::vector<MenuItem<Type, ret>>>;
  using list         = std::vector<MenuItem<Type, ret>>;
  public:
    MultiDimMenu() = default;
    MultiDimMenu(list &);
    MultiDimMenu(list &, list &);
    MultiDimMenu(list &, list &, list &);
    MultiDimMenu(list &, list &, list &, list &);

  public:
    void scroll_up() override;
    void scroll_down() override;
    virtual void scroll_left();
    virtual void scroll_right();

    void select() override;
    int size() override;
    bool is_hovered(int) override;
    virtual bool is_hovered(int c, int r);

    virtual MenuItem<Type, ret> get_hovered();

    virtual list &operator [](int i);

  private:
    multidimlist items;
};

class CombatMenu : public MultiDimMenu<bool, void>
{
  using item = MenuItem<bool, void>;
  using list = std::vector<item>;
  public:
    CombatMenu() = default;
    CombatMenu(list &);
    CombatMenu(list &, list &);
    CombatMenu(list &, list &, list &);
    CombatMenu(list &, list &, list &, list &);
};

class TargetMenu : public MultiDimMenu<entt::entity, void>
{
  using item = MenuItem<entt::entity, void>;
  using list = std::vector<item>;
  public:
    TargetMenu() = default;
    TargetMenu(list &);
    TargetMenu(list &, list &);
    TargetMenu(list &, list &, list &);
    TargetMenu(list &, list &, list &, list &);
};


class EquipmentMenu : public MultiDimMenu<entt::entity, void>
{
  using item = MenuItem<entt::entity, void>;
  using list = std::vector<item>;
  public:
    EquipmentMenu() = default;
    EquipmentMenu(list &, list &, list &);
};

#endif // MENU_H_
