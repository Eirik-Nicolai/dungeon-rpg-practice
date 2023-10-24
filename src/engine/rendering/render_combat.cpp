#include "render.hpp"

void DungeonThing::on_render_combat()
{
    auto [winx, winy] = GetScreenSize();

    auto winy_main = winy * 0.70;
    auto winy_combat = winy - winy_main;
    int mid_menu_y = winy_main + winy_combat/2;

    // FIXME use rects instead of raw lines
    DrawRect(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS*2, winy_main-BORDER_OFFS*2);
    // DrawLine(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    // DrawLine(BORDER_OFFS, winy_main-BORDER_OFFS, winx-BORDER_OFFS, winy_main-BORDER_OFFS); // bottom line
    // DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy_main-BORDER_OFFS);     // left line
    // DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy_main-BORDER_OFFS); // right line

    DrawRect(BORDER_OFFS, winy_main, winx-BORDER_OFFS*2, winy_combat-BORDER_OFFS);

    // DrawLine(BORDER_OFFS, winy_main, winx-BORDER_OFFS, winy_main);     // top line
    // DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    // DrawLine(BORDER_OFFS, winy_main, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    // DrawLine(winx-BORDER_OFFS, winy_main, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line

    //FIXME clean up all of this
    auto enemy_view = m_reg.view<_enemy>();

    for(auto [ent]: enemy_view.each())
    {
        auto [pos, app, h, f] = m_reg.get<combat::pos, combat_appearence, health, force>(ent);
        DrawString(pos.x, pos.y, app.c, olc::WHITE, 4);
        DrawString(pos.x+GetStringLength("100", 4),
                   pos.y, std::to_string(h.curr), olc::RED, 4);
        DrawString(pos.x-GetStringLength("1000", 4),
                   pos.y, std::to_string(f.curr), olc::BLUE, 4);
        if(m_targetmenu.GetSelected() == ent && CURR_STATE.type == type::PLAYER_SELECTING_TARGET)
            DrawString(pos.x-GetStringLength("-->", 4),pos.y,"-->",olc::WHITE,4);
        auto affctd = m_reg.get<affected>(ent);
        for(auto dent : affctd.effects)
        {
            auto name = get_name(dent);
            auto rounds_left = m_reg.get<tick>(dent).rounds;
            DrawString(pos.x,
                       pos.y+GetStringLength("x", 2),
                       name + " " + std::to_string(rounds_left),
                       olc::RED, 2);
        }
    }

    auto ally_view = m_reg.view<_ally>();

    for(auto [ent]: ally_view.each())
    {
        auto [pos, app, h] = m_reg.get<combat::pos, combat_appearence, health>(ent);
        DrawString(pos.x, pos.y, app.c, olc::WHITE, 4);
        DrawString(pos.x+GetStringLength("100",4),
                   pos.y, std::to_string(h.curr), olc::RED, 4);
        if(m_targetmenu.GetSelected() == ent && CURR_STATE.type == type::PLAYER_SELECTING_TARGET)
            DrawString(pos.x,pos.y,"<--",olc::WHITE,4);

        auto affctd = m_reg.get<affected>(ent);
        for(auto dent : affctd.effects)
        {
            auto name = get_name(dent);
            auto rounds_left = m_reg.get<tick>(dent).rounds;
            DrawString(pos.x,
                       pos.y+GetStringLength("x",2),
                       name + " " + std::to_string(rounds_left),
                       olc::RED, 2);
        }
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
            for(int i = 0; i < m_combatmenus[m_curr_menu].ListSize(); ++i)
            {
                DrawString(mid_menu_x[i] - GetStringLength(m_combatmenus[m_curr_menu].list_items[i].text,4)/2,
                           mid_menu_y - (MENU_ITEM_OFFS_Y*1.5/2) + (MENU_ITEM_OFFS_Y*1.5) * (i%2),
                           m_combatmenus[m_curr_menu].list_items[i].text,
                           olc::WHITE,4);
                if(m_combatmenus[m_curr_menu].curr_selected == i)
                {
                    DrawString(mid_menu_x[i] - (GetStringLength(m_combatmenus[m_curr_menu].list_items[i].text,4)) - GetStringLength("-->",4),
                               mid_menu_y - (MENU_ITEM_OFFS_Y*1.5/2) + (MENU_ITEM_OFFS_Y*1.5) * (i%2),
                               "-->",
                               olc::WHITE,4);
                }
            }

        }
        break;
        case type::PLAYER_SELECTING_TARGET:
        {
            auto name = get_name(m_intended_action);
            DrawString((winx/2) - GetStringLength(name,4)/2, mid_menu_y,
                       name,
                       olc::WHITE,4);
        }
        break;
        //default:
            //std::cout << "NOT IMPL" << std::endl;
    }

}
