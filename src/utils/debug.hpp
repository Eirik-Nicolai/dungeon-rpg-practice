#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>

#include <vector>
#include <string>

#include "olcPixelGameEngine.h"
#include "globals.hpp"

class Debugger
{
    public:
        static Debugger& instance()
        {
            static Debugger instance;
            return instance;
        }
        void Print(olc::PixelGameEngine *pge)
        {
            auto [winx, winy] = pge->GetWindowSize();
            winx *= 0.80;
            winy *= 0.80;
            int offs = 0;
            for (auto &s: debug_lines)
            {
                pge->DrawString(
                    winx,
                    winy + offs*PIXEL_OFFS,
                    s,
                    olc::WHITE
                );
                offs++;
            }
        }
        void Clear()
        {
            debug_lines.clear();
        }

    public:
        Debugger operator+=(const std::string &rhs)
        {
            debug_lines.emplace_back(debug_line(debug_lines.size(), rhs));
            return *this;
        }

    private:
        Debugger() = default;
        //~Debugger() = default;
        std::string debug_line(int i, const std::string &s)
        {
            return std::string("[ "+ std::to_string(i) + " ] " + s);
        }
        std::vector<std::string> debug_lines;
};



#endif // DEBUG_H_
