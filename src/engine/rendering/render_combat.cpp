#include "render.hpp"

void DungeonThing::on_render_combat()
{
    auto [winx, winy] = GetScreenSize();

    auto winy_main = winy * 0.70;
    auto winy_combat = winy - winy_main;
    int mid_menu_y = winy_main + winy_combat/2;

    DrawRect(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS*2, winy_main-BORDER_OFFS*2);
    DrawRect(BORDER_OFFS, winy_main, winx-BORDER_OFFS*2, winy_combat-BORDER_OFFS);

    //FIXME clean up all of this
    auto enemy_view = m_reg.view<_enemy>();
    auto [play_h, play_m] = m_reg.get<health, mana>(m_player);
    draw_resource_bar<health>(play_h,winx*0.05, winy_main+winy_combat*0.3, 300, 40, olc::DARK_RED);
    draw_resource_bar<mana>(play_m,winx*0.05, winy_main+winy_combat*0.7, 300, 40, olc::CYAN);

    std::string spaces = play_h.max%100==0 ? " " : "  ";
    DrawString(winx*0.05, winy_main+winy_combat*0.15,
               "HEALTH:" +std::to_string(play_h.curr) + "/" + std::to_string(play_h.max),
               olc::WHITE,
               3);

    spaces = play_m.max%100==0 ? "   " : "    ";
    DrawString(winx*0.05, winy_main+winy_combat*0.55,
               "MANA:  " + std::to_string(play_m.curr) + "" + std::to_string(play_m.max),
               olc::WHITE,
               3);

    DrawString(winx*0.3, winy_main+winy_combat*0.15,
               "Buffs",
               olc::WHITE,
               2);

    DrawString(winx*0.42, winy_main+winy_combat*0.15,
               "Debuffs",
               olc::WHITE,
               2);
    DrawLine((winx*0.42)-15, winy_main+winy_combat*0.15, (winx*0.42)-15, winy_main+winy_combat*0.85);

    auto effects = get<affected>(m_player).effects;

    int brow = 1;
    int drow = 1;
    int bcol = 0;
    int dcol = 0;
    for(auto ent : effects)
    {
        if(m_reg.all_of<_buff>(ent))
        {
            int posx = winx*0.3 + GetStringLength("xxxx", 2)*bcol;
            int posy = (winy_main+winy_combat*0.15)+GetStringLength("xx", 2)*brow;

            draw_effect_icon(get<visual>(ent).char_repr, posx, posy,
                             olc::GREEN, olc::VERY_DARK_GREEN);

            ++bcol;
            if(bcol==3)
            {
                bcol = 0;
                brow++;
            }
        }
        else if (m_reg.all_of<_debuff>(ent))
        {
            int posx = winx*0.42 + GetStringLength("xxxx", 2)*dcol;
            int posy = (winy_main+winy_combat*0.15)+GetStringLength("xx", 2)*drow;
            draw_effect_icon(get<visual>(ent).char_repr, posx, posy,
                             olc::RED, olc::VERY_DARK_RED);

            ++dcol;
            if(dcol==3)
            {
                dcol = 0;
                ++drow;
            }
        }
    }

    brow = drow = 1;
    bcol = dcol = 1;

    for(auto [ent]: enemy_view.each())
    {
        auto [pos, app, h] = m_reg.get<combat::pos, combat_appearence, health>(ent);
        DrawString(pos.x, pos.y, app.c, olc::WHITE, 4);
        if(m_targetmenu.GetSelected() == ent && CURR_STATE.type == type::PLAYER_SELECTING_TARGET)
            DrawString(pos.x-GetStringLength("-->", 4),pos.y,"-->",olc::WHITE,4);

        // HEALTH

        draw_resource_bar(h,pos.x+GetStringLength("xx", 4),
                          pos.y-GetStringLength("x", 4)/2,
                          150, 20,
                          olc::RED);

        DrawString(pos.x+GetStringLength("xx", 4)-(GetStringLength(std::to_string(h.curr), 2)/2)+150/2,
                   pos.y-GetStringLength("x", 3)*1/2,
                   std::to_string(h.curr), olc::RED, 2);

        // TODO maybe sort these
        auto affctd = m_reg.get<affected>(ent);
        for(auto dent : affctd.effects)
        {
            olc::Pixel inn = m_reg.all_of<_buff>(ent) ? olc::GREEN : olc::RED;
            olc::Pixel out = m_reg.all_of<_buff>(ent) ? olc::VERY_DARK_GREEN : olc::VERY_DARK_RED;

            int posx = pos.x+GetStringLength("xx", 4)*dcol;
            int posy = pos.y-(GetStringLength("x", 4))/3+(GetStringLength("x", 4))*drow;
            draw_effect_icon(get<visual>(dent).char_repr, posx, posy,
                             olc::RED, olc::VERY_DARK_RED);

            ++dcol;
            if(dcol==4)
            {
                dcol = 1;
                ++drow;
            }

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

        if(ent == m_player)
            continue;

        // std::cout << "buff" << std::endl;
        // auto affctd = m_reg.get<affected>(ent);
        // for(auto dent : affctd.effects)
        // {
        //     auto name = get_name(dent);
        //     std::cout << "buff" << std::endl;
        //     //auto rounds_left = m_reg.get<tick>(dent).rounds;
        //     DrawString(pos.x,
        //                pos.y+GetStringLength("x",2),
        //                name,
        //                olc::RED, 2);
        // }
    }

    switch (CURR_STATE.type)
    {
        case type::PLAYER_SELECTING_ACTION:
        {
            //FIXME move to init menu
            // {
            int mid_menu_x[4];
            mid_menu_x[0] = winx*13/20;
            mid_menu_x[1] = winx*13/20;
            mid_menu_x[2] = winx*8/10;
            mid_menu_x[3] = winx*8/10;
            // }
            //Debugger::instance()+="Currently selected: " + std::to_string(m_combatmenus[m_curr_menu].curr_selected);
            for(int i = 0; i < m_combatmenus[m_curr_menu].ListSize(); ++i)
            {
                auto col = olc::WHITE;
                auto slen = (GetStringLength(m_combatmenus[m_curr_menu].list_items[i].text,4));
                if(m_combatmenus[m_curr_menu].curr_selected == i)
                {
                    col = olc::RED;
                    DrawString(mid_menu_x[i] - GetStringLength("xx", 4) - slen/2, //(GetStringLength(m_combatmenus[m_curr_menu].list_items[i].text,4)),
                               mid_menu_y - (MENU_ITEM_OFFS_Y*1.5/2) + (MENU_ITEM_OFFS_Y*1.5) * (i%2),
                               "->",
                               olc::WHITE,4);
                }
                DrawString(mid_menu_x[i] - slen/2,
                           mid_menu_y - (MENU_ITEM_OFFS_Y*1.5/2) + (MENU_ITEM_OFFS_Y*1.5) * (i%2),
                           m_combatmenus[m_curr_menu].list_items[i].text,
                           col,4);
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
