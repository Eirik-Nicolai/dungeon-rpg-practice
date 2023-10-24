#include "menu.hpp"

Menu::Menu()
{
  curr_selected = 0;
}

void Menu::ScrollDown()
{
  curr_selected += 1;
  if(curr_selected>=list_items.size()) curr_selected = 0;
}

void Menu::ScrollUp()
{
  curr_selected -= 1;
  if(curr_selected<0) curr_selected = list_items.size()-1;
}


void Menu::Select()
{
  list_items[curr_selected].action();
}

int Menu::ListSize() {return list_items.size();}


PauseMenu::PauseMenu(TextItem &a) : Menu()
{
  list_items.emplace_back(a);
}

PauseMenu::PauseMenu(TextItem &a, TextItem &b) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
}

PauseMenu::PauseMenu(TextItem &a, TextItem &b, TextItem &c) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
  list_items.emplace_back(c);
}

PauseMenu::PauseMenu(TextItem &a, TextItem &b, TextItem &c, TextItem &d) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
  list_items.emplace_back(c);
  list_items.emplace_back(d);
}


CombatMenu::CombatMenu(TextItem &a) : Menu()
{
  list_items.emplace_back(a);
}

CombatMenu::CombatMenu(TextItem &a, TextItem &b) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
}

CombatMenu::CombatMenu(TextItem &a, TextItem &b, TextItem &c) : Menu()
{
  list_items.emplace_back(a);
  list_items.emplace_back(b);
  list_items.emplace_back(c);
}

CombatMenu::CombatMenu(TextItem &a, TextItem &b, TextItem &c, TextItem &d) : Menu()
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
  list_items.emplace_back(TextItem{"", f});
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
