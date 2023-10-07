#include "render.hpp"

void on_render(entt::registry &reg, std::array<WINDOW*, 4> windows)
{

    auto clearview = reg.view<window, _isactive>();
    for( auto [ent, w]: clearview.each() )
    {
        werase(windows[w.id]);
    }

    switch (GAME_STATE)
    {
        case state::WALKING:
        {
            Debug::Log("walk", 0, 0);

            on_render_walking(reg, windows[MAINWINDOW]);
            box(windows[MAINWINDOW], 0, 0);
            break;
        }
        case state::PAUSED:
        {
            Debug::Log("pause", 0, 0);
            //on_render_walking(reg, windows[MAINWINDOW]);
            int winy, winx;
            getmaxyx(stdscr, winy, winx);

            wresize(windows[MAINWINDOW], (winy/2)-2, winx-2);
            box(windows[MAINWINDOW], 0, 0);

            wmove(windows[MENUWINDOW], 40, 40);
            wresize(windows[MENUWINDOW], (winy/2)-2, winx-2);
            box(windows[MENUWINDOW], 0, 0);
            break;
        }

        case state::TRANSITION:
        {
            //on_render_transition(reg, windows);
            break;
        }

        default:
            Debug::Log("STATE NOT RECOGNIZED", 0, 0);
            break;
    }

    Debug::Print();

    auto renderview = reg.view<window, _isactive>();
    for( auto [ent, w]: renderview.each() )
    {
        wrefresh(windows[w.id]);
    }
    // wrefresh(windows[0]);
}

void on_render_walking(entt::registry &reg, WINDOW *mainwin)
{
    auto renderview = reg.view<_renderable, pos, simpleappearence>();
    for( auto [ent, p, app]: renderview.each() )
    {
        mvwprintw(mainwin, p.y, p.x, "%c", app.c);
    }
}


void on_render_transition(entt::registry &reg, std::array<WINDOW *, 4> windows)
{
    Debug::Log("RENDER", 0,6);
    auto renderview = reg.view<window, transitioning>();
    for(auto [ent, w, t]: renderview.each())
    {
       wresize(windows[w.id], w.w, w.h);
       wmove(windows[w.id], w.x, w.y);
    }

    Debug::Log("RENDER", 0,7);
}
