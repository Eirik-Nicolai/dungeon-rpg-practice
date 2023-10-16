#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>

#include <vector>
#include <string>

struct debugLine{
  std::string s;
  int x,y;
};
extern std::vector<debugLine> debug_lines;

namespace Debug
{
  void Setup();

  void Log(std::string, int x, int y);

  void Print();
}

#endif // DEBUG_H_
