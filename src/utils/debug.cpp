#include "debug.hpp"

std::vector<debugLine> debug_lines;
WINDOW * currwin;


void Debug::Setup(WINDOW* win)
{
  debug_lines = std::vector<debugLine>();
  currwin = win;
}


void Debug::Log(std::string s, int x, int y)
{
  debug_lines.push_back(debugLine{"[log] " + s, x, y});
}

void Debug::Print()
{
  for(auto line: debug_lines)
  {
      mvwprintw(currwin, line.y, line.x, "%s",line.s.c_str());
  }
}
