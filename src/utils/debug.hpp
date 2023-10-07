#ifndef DEBUG_H_
#define DEBUG_H_

#include <ncurses.h>

#include <iostream>

#include <vector>
#include <string>

struct debugLine{
  std::string s;
  int x,y;
};
extern std::vector<debugLine> debug_lines;
extern WINDOW * currwin;

namespace Debug
{
  void Setup(WINDOW*);

  void Log(std::string, int x, int y);

  void Print();
}

#endif // DEBUG_H_
