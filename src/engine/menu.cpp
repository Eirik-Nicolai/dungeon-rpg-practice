#include "menu.hpp"

// template <typename T>
// Menu<T>::Menu()
// {
//   curr_selected = 0;
// }

// template <typename T>
// void Menu<T>::ScrollDown()
// {
//   curr_selected += 1;
//   if(curr_selected>=list_items.size()) curr_selected = 0;
// }

// template <typename T>
// void Menu<T>::ScrollUp()
// {
//   curr_selected -= 1;
//   if(curr_selected<0) curr_selected = list_items.size()-1;
// }

// template <typename T>
// void Menu<T>::Select()
// {
//   list_items[curr_selected].action();
// }

// template <typename T>
// int Menu<T>::ListSize() {return list_items.size();}

// template <typename T>
// void Menu<T>::AddItem(T t) {list_items.emplace_back(t);}

PauseMenu::PauseMenu(TextItemOnSelect &a) : Menu()
{
  list_items.emplace_back(a);
}

PauseMenu::PauseMenu(TextItemOnSelect &a, TextItemOnSelect &b) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
}

PauseMenu::PauseMenu(TextItemOnSelect &a, TextItemOnSelect &b, TextItemOnSelect &c) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
  list_items.emplace_back(c);
}

PauseMenu::PauseMenu(TextItemOnSelect &a, TextItemOnSelect &b, TextItemOnSelect &c, TextItemOnSelect &d) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
  list_items.emplace_back(c);
  list_items.emplace_back(d);
}

EquipmentMenu::EquipmentMenu(std::function<void(void)> f)
{
    curr_menu = 1;
    m_menus[0] = Menu();
    m_menus[1] = Menu();
    m_menus[2] = Menu();
    menu_func = f;
}

void EquipmentMenu::AddItemLeft(TextItemOnScroll ti)
{
    m_menus[0].AddItem(ti);
}

void EquipmentMenu::AddItemMiddle(TextItemOnScroll ti)
{
    m_menus[1].AddItem(ti);
}

void EquipmentMenu::AddItemRight(TextItemOnScroll ti)
{
    m_menus[2].AddItem(ti);
}
// TODO menus need to be cleaned up
int EquipmentMenu::ScrollUp()
{
    curr_selected -= 1;
    if(curr_selected<0) curr_selected = m_menus[curr_menu].ListSize()-1;
    return m_menus[curr_menu].list_items[curr_selected].action();
}

int EquipmentMenu::ScrollDown()
{
    curr_selected += 1;
    if(curr_selected>=m_menus[curr_menu].ListSize()) curr_selected = 0;
    return m_menus[curr_menu].list_items[curr_selected].action();
}

int EquipmentMenu::ScrollLeft()
{
    curr_menu -= 1;
    if(curr_menu<0) curr_menu=2;
    if(m_menus[curr_menu].ListSize() <= curr_selected) curr_selected = m_menus[curr_menu].ListSize()-1;
    return m_menus[curr_menu].list_items[curr_selected].action();
}

int EquipmentMenu::ScrollRight()
{
    curr_menu = (curr_menu + 1) % 3;
    if(m_menus[curr_menu].ListSize() <= curr_selected) curr_selected = m_menus[curr_menu].ListSize()-1;
    return m_menus[curr_menu].list_items[curr_selected].action();
}

void EquipmentMenu::Select()
{
    menu_func();
}

int EquipmentMenu::CurrentSelected()
{
    return m_menus[curr_menu].curr_selected;
}

CombatMenu::CombatMenu(TextItemOnSelect &a) : Menu()
{
  list_items.emplace_back(a);
}

CombatMenu::CombatMenu(TextItemOnSelect &a, TextItemOnSelect &b) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
}

CombatMenu::CombatMenu(TextItemOnSelect &a, TextItemOnSelect &b, TextItemOnSelect &c) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
  list_items.emplace_back(c);
}

CombatMenu::CombatMenu(TextItemOnSelect &a, TextItemOnSelect &b, TextItemOnSelect &c, TextItemOnSelect &d) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
  list_items.emplace_back(c);
  list_items.emplace_back(d);
}

void CombatMenu::ScrollLeft()
{
  curr_selected -= 2;
  if(curr_selected<0) curr_selected = list_items.size()+curr_selected;
}

void CombatMenu::ScrollRight()
{
  curr_selected += 2;
  if(curr_selected>=list_items.size()) curr_selected = curr_selected-list_items.size();
}

TargetMenu::TargetMenu(std::function<void(void)> f)
{
  list_items.emplace_back(TextItemOnSelect{"", f});
}

//TODO clean up
void TargetMenu::AddTargets(std::vector<entt::entity> &target_view)
{
  for(auto ent : target_view)
  {
    targets.emplace_back(ent);
    list_items.emplace_back(list_items[0]);
  }
  //BUG need to remove first element due to this being stupid
  //or clean up and make better
}

entt::entity TargetMenu::GetSelected()
{
  return targets[curr_selected];
}
