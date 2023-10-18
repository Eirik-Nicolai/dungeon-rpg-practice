#include "menu.hpp"

Menu::Menu()
{
  curr_selected = 0;
}

void Menu::ScrollDown()
{
  curr_selected += 1;
  if(curr_selected>=list_size) curr_selected = 0;
}

void Menu::ScrollUp()
{
  curr_selected -= 1;
  if(curr_selected<0) curr_selected = list_size-1;
}


void Menu::Select()
{
  list_items[curr_selected].action();
}

PauseMenu::PauseMenu(TextItem &resume, TextItem &option, TextItem &exit) : Menu()
{
  list_items.emplace_back(resume);
  list_items.emplace_back(option);
  list_items.emplace_back(exit);
  list_size = list_items.size();
}


CombatMenu::CombatMenu(TextItem &a, TextItem &b, TextItem &c) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
  list_items.emplace_back(c);
  list_size = list_items.size();
}

CombatMenu::CombatMenu(TextItem &a, TextItem &b, TextItem &c, TextItem &d) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
  list_items.emplace_back(c);
  list_items.emplace_back(d);
  list_size = list_items.size();
}

void CombatMenu::ScrollLeft()
{
  curr_selected -= 2;
  if(curr_selected<0) curr_selected = list_size+curr_selected;
}

void CombatMenu::ScrollRight()
{
  curr_selected += 2;
  if(curr_selected>=list_size) curr_selected = curr_selected-list_size;// + (curr_selected-list_size);
}
