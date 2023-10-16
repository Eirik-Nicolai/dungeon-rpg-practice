#include "game.hpp"
#include "render.hpp"

void DungeonThing::on_render_walking()
{
    auto [winx, winy] = GetScreenSize();
    DrawLine(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line

    auto renderview = m_reg.view<_renderable, pos, simpleappearence>();
    for( auto [ent, p, app]: renderview.each() )
    {
        DrawString(p.x, p.y, app.c);
    }
}

void DungeonThing::on_render_combat()
{
    auto [winx, winy] = GetScreenSize();

    auto winy_main = winy * 0.70;

    DrawLine(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy_main-BORDER_OFFS, winx-BORDER_OFFS, winy_main-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy_main-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy_main-BORDER_OFFS); // right line

    DrawLine(BORDER_OFFS, winy_main, winx-BORDER_OFFS, winy_main);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, winy_main, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, winy_main, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line


}


void DungeonThing::on_render_paused()
{
    auto [winx, winy] = GetScreenSize();

    auto winx_main = winx * 0.65;

    DrawLine(BORDER_OFFS, BORDER_OFFS, winx_main-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx_main-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx_main-BORDER_OFFS, BORDER_OFFS, winx_main-BORDER_OFFS, winy-BORDER_OFFS); // right line

    auto winx_pause = winx - winx_main;

    DrawLine(winx_main + BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(winx_main + BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(winx_main + BORDER_OFFS, BORDER_OFFS, winx_main + BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line
}

// void DungeonThing::on_render(entt::registry &reg)
// {

//     //Clear(olc::BLACK);

//     switch (GAME_STATE)
//     {
//         case state::WALKING:
//         {
//             Debug::Log("walk", 0, 0);

//             break;
//         }
//         case state::PAUSED:
//         {
//             Debug::Log("pause", 0, 0);
//             //on_render_walking(reg, windows[MAINWINDOW]);
//             int winy, winx;

//             // wresize(windows[MAINWINDOW], (winy/2)-2, winx-2);
//             // box(windows[MAINWINDOW], 0, 0);

//             // wmove(windows[MENUWINDOW], 40, 40);
//             // wresize(windows[MENUWINDOW], (winy/2)-2, winx-2);
//             // box(windows[MENUWINDOW], 0, 0);
//             break;
//         }

//         case state::TRANSITION:
//         {
//             //on_render_transition(reg, windows);
//             break;
//         }

//         default:
//             Debug::Log("STATE NOT RECOGNIZED", 0, 0);
//             break;
//     }

//     Debug::Print();

//     auto renderview = reg.view<window, _isactive>();
//     for( auto [ent, w]: renderview.each() )
//     {
//         // wrefresh(windows[w.id]);
//     }
//     // wrefresh(windows[0]);
// }


void on_render_transition(entt::registry &reg)
{
    Debug::Log("RENDER", 0,6);
    auto renderview = reg.view<window, transitioning>();
    for(auto [ent, w, t]: renderview.each())
    {
        // wresize(windows[w.id], w.w, w.h);
        // wmove(windows[w.id], w.x, w.y);
    }

    Debug::Log("RENDER", 0,7);
}
