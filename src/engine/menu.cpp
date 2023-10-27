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

Menu::Menu()
{
  sel_row = 0;
  sel_col = 0;
}

SimpleMenu::SimpleMenu(MenuItem<std::string, void>& a) : Menu()
{
  items.emplace_back(a);
}

SimpleMenu::SimpleMenu(MenuItem<std::string, void> &a, MenuItem<std::string, void> &b) : Menu()
{
  items.emplace_back(a);
  items.emplace_back(b);
}

SimpleMenu::SimpleMenu(MenuItem<std::string, void> &a, MenuItem<std::string, void> &b, MenuItem<std::string, void> &c) : Menu()
{
  items.emplace_back(a);
  items.emplace_back(b);
  items.emplace_back(c);
}

SimpleMenu::SimpleMenu(MenuItem<std::string, void> &a, MenuItem<std::string, void> &b, MenuItem<std::string, void> &c, MenuItem<std::string, void> &d) : Menu()
{
  items.emplace_back(a);
  items.emplace_back(b);
  items.emplace_back(c);
  items.emplace_back(d);
}

void SimpleMenu::select()
{
  items[sel_row].select_cmd();
}

int SimpleMenu::size()
{
  return items.size();
}

bool SimpleMenu::is_hovered(int i)
{
  return i==sel_row;
}

void SimpleMenu::scroll_up()
{
  sel_row -= 1;
  if(sel_row<0) sel_row = items.size()-1;
}

void SimpleMenu::scroll_down()
{
  sel_row += 1;
  if(sel_row>=items.size()) sel_row = 0;
}

MenuItem<std::string, void> &SimpleMenu::operator [](int i){return items[i];}

ScrollableMenu::ScrollableMenu(std::vector<MenuItem<entt::entity, entt::entity>> &_items, int range) : Menu()
{
  inner_sel_row = 0;
  items = _items;
  inner_begin = items.begin();
  inner_size = items.size() > range ? range : items.size();
}

void ScrollableMenu::select()
{
  items[sel_row].select_cmd();
}

int ScrollableMenu::size()
{
  return items.size();
}

bool ScrollableMenu::is_hovered(int i)
{
  return i==inner_sel_row;
}

std::vector<MenuItem<entt::entity, entt::entity>> ScrollableMenu::get_inner()
{
  std::vector<MenuItem<entt::entity, entt::entity>> out;
  out.insert(out.cbegin(), inner_begin, inner_begin+inner_size);
  return out;
}

void ScrollableMenu::scroll_up()
{
  sel_row--;
  if(sel_row == -1)
  {
    sel_row = items.size()-1;
    inner_sel_row = inner_size-1;
    inner_begin = items.end()-inner_size;
  }
  else
  {
    if(inner_sel_row == 0)
    {
      inner_begin--;
    }
    else
    {
      inner_sel_row--;
    }
  }
}

void ScrollableMenu::scroll_down()
{
  sel_row++;
  if(sel_row == items.size())
  {
    sel_row = inner_sel_row = 0;
    inner_begin = items.begin();
  }
  else
  {
    if(inner_sel_row == inner_size-1)
    {
      inner_begin++;
    }
    else
    {
      inner_sel_row++;
    }
  }
}

using singlelist = std::vector<MenuItem<entt::entity, void>>;

MultiDimMenu::MultiDimMenu(singlelist &l1) : Menu()
{
  items.emplace_back(l1);
}

MultiDimMenu::MultiDimMenu(singlelist &l1, singlelist &l2) : Menu()
{
  items.emplace_back(l1);
  items.emplace_back(l2);
}

MultiDimMenu::MultiDimMenu(singlelist &l1, singlelist &l2, singlelist &l3) : Menu()
{
  items.emplace_back(l1);
  items.emplace_back(l2);
  items.emplace_back(l3);
}

MultiDimMenu::MultiDimMenu(singlelist &l1, singlelist &l2, singlelist &l3, singlelist &l4) : Menu()
{
  items.emplace_back(l1);
  items.emplace_back(l2);
  items.emplace_back(l3);
  items.emplace_back(l4);
}

void MultiDimMenu::select()
{
  items[sel_col][sel_row].select_cmd();
}

int MultiDimMenu::size()
{
  return items.size();
}

// TODO figure this out
bool MultiDimMenu::is_hovered(int r)
{
  std::cout << "NOT IMPL" << std::endl;
  return sel_row==r;
}

bool MultiDimMenu::is_hovered(int r, int c)
{
  return sel_row==r && sel_col == c;
}

MenuItem<entt::entity, void> MultiDimMenu::get_hovered()
{
  if(sel_col < items.size())
  {
    if(sel_row < items[sel_col].size())
    {
      return items[sel_col][sel_row];
    }
    else
    {
      std::cout << "MultiDimMenu::get_hovered() row out of bounds" << std::endl;
      return items[sel_col][sel_row];
    }
  }
  std::cout << "MultiDimMenu::get_hovered() row out of bounds" << std::endl;
  return items[sel_col][sel_row];
}

singlelist &MultiDimMenu::operator [](int i)
{
  return items[i];
}

void MultiDimMenu::scroll_up()
{
  sel_row -= 1;
  if(sel_row<0) sel_row = items[sel_col].size()-1;
}

void MultiDimMenu::scroll_down()
{
  sel_row += 1;
  if(sel_row>=items[sel_col].size()) sel_row = 0;
}

void MultiDimMenu::scroll_left()
{
  sel_col -= 1;
  if(sel_col<0) sel_col = items.size()-1;
  if(sel_row > items[sel_col].size()) sel_row = items[sel_col].size()-1;
}

void MultiDimMenu::scroll_right()
{
  sel_col += 1;
  if(sel_col>=items.size()) sel_col = 0;
  if(sel_row > items[sel_col].size()) sel_row = items[sel_col].size()-1;
}






/*
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

CombatMenu::CombatMenu(MenuItem<std::string, void> &a) : Menu()
{
  list_items.emplace_back(a);
}

CombatMenu::CombatMenu(MenuItem<std::string, void> &a, MenuItem<std::string, void> &b) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
}

CombatMenu::CombatMenu(MenuItem<std::string, void> &a, MenuItem<std::string, void> &b, MenuItem<std::string, void> &c) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
  list_items.emplace_back(c);
}

CombatMenu::CombatMenu(MenuItem<std::string, void> &a, MenuItem<std::string, void> &b, MenuItem<std::string, void> &c, MenuItem<std::string, void> &d) : Menu()
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
*/
