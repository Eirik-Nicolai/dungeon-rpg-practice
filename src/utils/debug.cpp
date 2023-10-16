#include "debug.hpp"

std::vector<debugLine> debug_lines;


void Debug::Setup()
{
  debug_lines = std::vector<debugLine>();

}


void Debug::Log(std::string s, int x, int y)
{
  debug_lines.push_back(debugLine{"[log] " + s, x, y});
}

void Debug::Print()
{
  for(auto line: debug_lines)
  {
  }
}
