#include "render.hpp"

void DungeonThing::on_render_combat()
{
    auto [winx, winy] = GetScreenSize();

    auto winy_main = winy * 0.70;
    auto winy_combat = winy - winy_main;
    int mid_menu_y = winy_main + winy_combat/2;

    DrawLine(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy_main-BORDER_OFFS, winx-BORDER_OFFS, winy_main-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy_main-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy_main-BORDER_OFFS); // right line

    DrawLine(BORDER_OFFS, winy_main, winx-BORDER_OFFS, winy_main);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, winy_main, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, winy_main, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line

    auto enemy_view = m_reg.view<_enemy>();
    auto debuff_view = m_reg.view<_debuff, affects>();

    for(auto [ent]: enemy_view.each())
    {
        auto [pos, app, h] = m_reg.get<combat::pos, combat_appearence, health>(ent);
        DrawString(pos.x, pos.y, app.c, olc::WHITE, 4);
        DrawString(pos.x+GetStringLength("100"),
                   pos.y, std::to_string(h.curr), olc::RED, 4);
        if(m_targetmenu.GetSelected() == ent && CURR_STATE.type == type::PLAYER_SELECTING_TARGET)
            DrawString(pos.x-GetStringLength("-->"),pos.y,"-->",olc::WHITE,4);
        for(auto [dent, aff] : debuff_view.each())
        {
            for (auto t : aff.targets)
            {
                if (t == ent)
                {
                    auto name = m_reg.get<visual>(dent).name;
                    DrawString(pos.x,
                               pos.y+GetStringLength("x"),
                               name, olc::RED, 4);
                }
            }
        }
    }

    auto ally_view = m_reg.view<_ally>();

    for(auto [ent]: ally_view.each())
    {
        auto [pos, app, h] = m_reg.get<combat::pos, combat_appearence, health>(ent);
        DrawString(pos.x, pos.y, app.c, olc::WHITE, 4);
        DrawString(pos.x+GetStringLength("100"),
                   pos.y, std::to_string(h.curr), olc::RED, 4);
        if(m_targetmenu.GetSelected() == ent && CURR_STATE.type == type::PLAYER_SELECTING_TARGET)
            DrawString(pos.x,pos.y,"<--",olc::WHITE,4);
    }

    switch (CURR_STATE.type)
    {
        case type::PLAYER_SELECTING_ACTION:
        {
            //FIXME move to init menu
            // {
            int mid_menu_x[4];
            mid_menu_x[0] = winx/3;
            mid_menu_x[1] = winx/3;
            mid_menu_x[2] = winx*2/3;
            mid_menu_x[3] = winx*2/3;

            // }
            Debugger::instance()+="Currently selected: " + std::to_string(m_combatmenus[m_curr_menu].curr_selected);
            for(int i = 0; i < m_combatmenus[m_curr_menu].list_size; ++i)
            {
                DrawString(mid_menu_x[i] - GetStringLength(m_combatmenus[m_curr_menu].list_items[i].text)/2,
                           mid_menu_y - (MENU_ITEM_OFFS_Y*1.5/2) + (MENU_ITEM_OFFS_Y*1.5) * (i%2),
                           m_combatmenus[m_curr_menu].list_items[i].text,
                           olc::WHITE,4);
                if(m_combatmenus[m_curr_menu].curr_selected == i)
                {
                    DrawString(mid_menu_x[i] - (GetStringLength(m_combatmenus[m_curr_menu].list_items[i].text)/2) - GetStringLength("-->"),
                               mid_menu_y - (MENU_ITEM_OFFS_Y*1.5/2) + (MENU_ITEM_OFFS_Y*1.5) * (i%2),
                               "-->",
                               olc::WHITE,4);
                }
            }

        }
        break;
        case type::PLAYER_SELECTING_TARGET:
        {
            auto name = m_reg.get<visual>(m_intended_action).name;
            DrawString((winx/2) - GetStringLength(name)/2, mid_menu_y,
                       name,
                       olc::WHITE,4);
        }
        break;
        //default:
            //std::cout << "NOT IMPL" << std::endl;
    }

}
