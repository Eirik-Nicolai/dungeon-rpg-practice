#include <iostream>
#include <entt/entt.hpp>
#include <ncurses.h>

#include <string>
#include <chrono>

#include "utils/debug.hpp"

#include "systems/logic/logic.hpp"
#include "systems/input/keypress.hpp"
#include "systems/loading/initialize.hpp"
#include "systems/rendering/render.hpp"


bool tick(int *);


auto main(int argc, char *argv[]) -> int
{
    entt::registry reg;

    //TODO
    //init debug
    //auto debugscreen = newterm(getenv("TERM"), nullptr, nullptr);
    //auto mainscreen = newterm(getenv("main"), nullptr, nullptr);
    initscr();

    // init output
    int winsizex, winsizey;
    getmaxyx(stdscr, winsizey, winsizex);

    std::array<WINDOW*, MAX_WINDOWS> windows;

    auto mainwin = newwin(winsizey-2, winsizex-2, 2, 2);
    //wborder(mainwin, 0, 0, 0, 0, 0, 0, 0, 0);
    //nodelay(mainwin, true);
    nodelay(mainwin, true);
    keypad(mainwin, TRUE);

    auto menuwin = newwin(0, 0, 0, 0);
    //nodelay(menuwin, true);
    //keypad(menuwin, TRUE);

    windows[MAINWINDOW] = mainwin;
    windows[MENUWINDOW] = menuwin;
    //start_color();

    noecho();
    cbreak();
    curs_set(0);

    Debug::Setup(mainwin);

    on_init(reg, winsizex, winsizey);

    bool run = true;
    int t = 0;
    while(run)
    {
        int ch =  wgetch(mainwin);
        if(ch != ERR)
        {
            if(ch == KEY_BACKSPACE)
            {
                run = false;
            }
            on_keypress(reg, ch);
        }
        if(tick(&t))
        {
            on_logic(reg);
        }
        on_render(reg, windows);
    }

    endwin();
}

bool tick(int *t)
{
    if(*t == 700)
    {
        (*t) = 0;
        return true;
    }
    (*t) += 1;
    return false;
}
