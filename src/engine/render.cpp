#include "render.hpp"

void DungeonThing::on_render_walking()
{
    auto [winx, winy] = GetScreenSize();
    DrawLine(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line

    auto walls = m_reg.view<_renderable, pos, size, _wall>();
    for( auto [ent, p, s]: walls.each() )
    {
        for(int y = 0; y < s.height; y+=10)
        {
            for(int x = 0; x < s.width; x+=10)
            {
                DrawString(p.x+x, p.y+y, "H");
            }
        }
    }

    auto simple = m_reg.view<_renderable, pos, simpleappearence>();
    for( auto [ent, p, app]: simple.each() )
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

    auto winy_combat = winy - winy_main;
     //FIXME move to init menu
    int mid_menu_x[4];
    mid_menu_x[0] = winx/3;
    mid_menu_x[1] = winx/3;
    mid_menu_x[2] = winx*2/3;
    mid_menu_x[3] = winx*2/3;

    int mid_menu_y = winy_main + winy_combat/2;

    //debug line
    // DrawLine(mid_menu_x[0], 0, mid_menu_x[0], winy);
    // DrawLine(0, mid_menu_y, winx, mid_menu_y);

    for(int i = 0; i < m_combatmenus[m_curr_menu].list_size; ++i)
    {
        DrawString(mid_menu_x[i] - GetStringLength(m_combatmenus[m_curr_menu].list_items[i].text)/2,
                   mid_menu_y - (MENU_ITEM_OFFS_Y*1.5/2) + (MENU_ITEM_OFFS_Y*1.5) * (i%2),
                   m_combatmenus[m_curr_menu].list_items[i].text,
                   olc::WHITE,
                   2);
        if(m_combatmenus[m_curr_menu].curr_selected == i)
        {
            DrawString(mid_menu_x[i] - (GetStringLength(m_combatmenus[m_curr_menu].list_items[i].text)/2) - 3*8*2,
                       mid_menu_y - (MENU_ITEM_OFFS_Y*1.5/2) + (MENU_ITEM_OFFS_Y*1.5) * (i%2),
                       "-->",
                       olc::WHITE,
                       2);

        }
    }
}


void DungeonThing::on_render_paused()
{
    auto [winx, winy] = GetScreenSize();

    auto winx_main = winx * 0.65;

    DrawLine(BORDER_OFFS, BORDER_OFFS, winx_main-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx_main-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx_main-BORDER_OFFS, BORDER_OFFS, winx_main-BORDER_OFFS, winy-BORDER_OFFS); // right line

    DrawLine(winx_main + BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(winx_main + BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(winx_main + BORDER_OFFS, BORDER_OFFS, winx_main + BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line

    auto winx_pause = winx - winx_main;

    //FIXME move to init menu
    int mid_menu_x = winx_main + winx_pause/2;
    int mid_menu_y = winy/2;

    //debug line
    // DrawLine(mid_menu_x, 0, mid_menu_x, winy);
    // DrawLine(0, mid_menu_y, winx, mid_menu_y);

    for(int i = 0; i < m_pausemenus[m_curr_menu].list_size; ++i)
    {
        DrawString(mid_menu_x - GetStringLength(m_pausemenus[m_curr_menu].list_items[i].text)/2,
                   mid_menu_y + (MENU_ITEM_OFFS_Y*i) - (MENU_ITEM_OFFS_Y*m_pausemenus[m_curr_menu].list_size/2),
                   m_pausemenus[m_curr_menu].list_items[i].text,
                   m_pausemenus[m_curr_menu].curr_selected==i ? olc::RED : olc::WHITE,
                   2);
    }
}



void DungeonThing::on_render_transition_combat()
{
    auto [winx, winy] = GetScreenSize();

    auto winy_main = winy * 0.7;
    auto winy_combat = winy - winy_main;

    // FIXME what the fuck
    auto v = winy_combat/m_transition_time;
    m_elapsed_transition_time += GetElapsedTime();
    auto transition_coeff = 60*(m_transition_time/(m_elapsed_transition_time*m_elapsed_transition_time*m_elapsed_transition_time*m_elapsed_transition_time));
    if(transition_coeff < 10) transition_coeff = 10;
    m_transition_progress = 100-transition_coeff+10;// * GetElapsedTime();
    auto winy_transition = winy - (winy_combat * (m_transition_progress/100));

    auto col = olc::WHITE;
    if(m_transition_progress > 20) col = olc::GREY;
    if(m_transition_progress > 40) col = olc::DARK_GREY;
    if(m_transition_progress > 60) col = olc::VERY_DARK_GREY;
    if(m_transition_progress < 80)
    {
        auto walls = m_reg.view<_renderable, pos, size, _wall>();
        for( auto [ent, p, s]: walls.each() )
        {
            for(int y = 0; y < s.height; y+=10)
            {
                for(int x = 0; x < s.width; x+=10)
                {
                    DrawString(p.x+x, p.y+y, "H", col);
                }
            }
        }

        auto simple = m_reg.view<_renderable, pos, simpleappearence>();
        for( auto [ent, p, app]: simple.each() )
        {
            DrawString(p.x, p.y, app.c, col);
        }
    }
    DrawLine(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy_transition-BORDER_OFFS, winx-BORDER_OFFS, winy_transition-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy_transition-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy_transition-BORDER_OFFS); // right line

    DrawLine(BORDER_OFFS, winy_transition, winx-BORDER_OFFS, winy_transition);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, winy_transition, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, winy_transition, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line
}
