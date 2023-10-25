#include "render.hpp"

void DungeonThing::on_render_paused()
{
    auto [winx, winy] = GetScreenSize();

    auto winx_main = winx * PAUSED::OVERVIEW::EQUIPMENT_SIZE_X;
    auto winx_menu = winx - winx_main;

    int equipment_win_y = winy*PAUSED::OVERVIEW::EQUIPMENT_SIZE_Y;
    int stat_win_y = winy*(1-PAUSED::OVERVIEW::EQUIPMENT_SIZE_Y);

    // equipment and stats
    DrawRect(BORDER_OFFS, BORDER_OFFS, winx_main-BORDER_OFFS, equipment_win_y-BORDER_OFFS*2);
    DrawRect(BORDER_OFFS, equipment_win_y, winx_main-BORDER_OFFS, stat_win_y-BORDER_OFFS);

    // menu
    DrawRect(winx_main + BORDER_OFFS, BORDER_OFFS, winx_menu-BORDER_OFFS*2, winy-BORDER_OFFS*2);


    //FIXME move to init menu
    int mid_menu_x = winx_main + winx_menu/2;
    int mid_menu_y = winy/2;

    //menu text items
    for(int i = 0; i < m_pausemenus[m_curr_menu].ListSize(); ++i)
    {
        DrawString(mid_menu_x - GetStringLength(m_pausemenus[m_curr_menu].list_items[i].text,4)/2,
                   mid_menu_y + (MENU_ITEM_OFFS_Y*i) - (MENU_ITEM_OFFS_Y*m_pausemenus[m_curr_menu].ListSize()/2),
                   m_pausemenus[m_curr_menu].list_items[i].text,
                   m_pausemenus[m_curr_menu].curr_selected==i ? olc::RED : olc::WHITE,
                   4);
    }

    on_render_paused_stats();

    switch(CURR_STATE.type)
    {
        case type::OVERVIEW:
            on_render_paused_overview();
            break;
        case type::EQUIPMENT:
            on_render_paused_overview();
            on_render_paused_equipment();
            break;
        case type::INVENTORY:
            on_render_paused_inventory();
            break;
        default:
            std::cout << "NOT IMPL" << std::endl;
    }
}

void DungeonThing::on_render_paused_stats()
{
    auto [winx, winy] = GetScreenSize();

    auto winx_main = winx * PAUSED::OVERVIEW::EQUIPMENT_SIZE_X;
    auto winx_menu = winx - winx_main;

    int equipment_win_y = winy*PAUSED::OVERVIEW::EQUIPMENT_SIZE_Y;
    int stat_win_y = winy*(1-PAUSED::OVERVIEW::EQUIPMENT_SIZE_Y);

    //FIXME move to init menu
    int mid_menu_x = winx_main + winx_menu/2;
    int mid_menu_y = winy/2;

    //FIXME all this initializing and finding w/e can be done once on state change
    //now we're doing it every frame

    auto [frce, mnd, armr, wllpwr] = m_reg.get<force, mind, armour, willpower>(m_player);
    auto [currhealth, currmana] = m_reg.get<health, mana>(m_player);

    // STATS

    DrawRect(winx_main*0.79,winy*0.79, 300+20, 40, olc::WHITE);
    FillRect(winx_main*0.80,winy*0.80,
             get_percentage(currhealth.curr, currhealth.max)*3, 30, olc::WHITE);

    DrawString(winx_main*0.80, winy*0.85,
               std::to_string(currmana.curr) + "/" + std::to_string(currmana.max),
               olc::WHITE,
               3);
}

void DungeonThing::on_render_paused_overview()
{
    auto [winx, winy] = GetScreenSize();

    auto winx_main = winx * PAUSED::OVERVIEW::EQUIPMENT_SIZE_X;
    auto winx_menu = winx - winx_main;

    int equipment_win_y = winy*PAUSED::OVERVIEW::EQUIPMENT_SIZE_Y;
    int stat_win_y = winy*(1-PAUSED::OVERVIEW::EQUIPMENT_SIZE_Y);

    //FIXME move to init menu
    int mid_menu_x = winx_main + winx_menu/2;
    int mid_menu_y = winy/2;

    //FIXME all this initializing and finding w/e can be done once on state change
    //now we're doing it every frame

    // EQUIPMENT
    auto equipmentstate = m_reg.ctx().get<EquipmentState>();

    PAUSED::OVERVIEW::draw_equipment(this, equipmentstate.head,
                   winx_main*PAUSED::OVERVIEW::EQUIPMENT_X_POS,
                   equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_TOP_POS);

    PAUSED::OVERVIEW::draw_equipment(this, equipmentstate.torso,
                   winx_main*PAUSED::OVERVIEW::EQUIPMENT_X_POS,
                   equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_MID_POS);

    PAUSED::OVERVIEW::draw_equipment(this, equipmentstate.legs,
                   winx_main*PAUSED::OVERVIEW::EQUIPMENT_X_POS,
                   equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_BOT_POS);

    PAUSED::OVERVIEW::draw_equipment(this, equipmentstate.main_hand,
                   winx_main*PAUSED::OVERVIEW::EQUIPMENT_LEFTLEAN_X_POS,
                   equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_MID_POS);

    PAUSED::OVERVIEW::draw_equipment(this, equipmentstate.off_hand,
                   winx_main*PAUSED::OVERVIEW::EQUIPMENT_RIGHTLEAN_X_POS,
                   equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_MID_POS);

    PAUSED::OVERVIEW::draw_equipment(this, equipmentstate.jewellery_finger_left,
                   winx_main*PAUSED::OVERVIEW::EQUIPMENT_LEFTLEAN_X_POS,
                                     equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_BOT_POS);

    PAUSED::OVERVIEW::draw_equipment(this, equipmentstate.jewellery_finger_right,
                   winx_main*PAUSED::OVERVIEW::EQUIPMENT_RIGHTLEAN_X_POS,
                   equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_BOT_POS);

    PAUSED::OVERVIEW::draw_equipment(this, equipmentstate.jewellery_ears,
                   winx_main*PAUSED::OVERVIEW::EQUIPMENT_RIGHTLEAN_X_POS,
                                     equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_TOP_POS);

    PAUSED::OVERVIEW::draw_equipment(this, equipmentstate.jewellery_necklace,
                   winx_main*PAUSED::OVERVIEW::EQUIPMENT_LEFTLEAN_X_POS,
                                     equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_TOP_POS);
}

void DungeonThing::on_render_paused_equipment()
{
    auto [winx, winy] = GetScreenSize();

    auto winx_main = winx * PAUSED::OVERVIEW::EQUIPMENT_SIZE_X;
    int equipment_win_y = winy*PAUSED::OVERVIEW::EQUIPMENT_SIZE_Y;

    //TODO use some time to do this in a cleaner way
    //there's some method using the index 0-8 along with the dice-face position
    auto equip = m_reg.ctx().get<EquipmentState>();;
    entt::entity curr_selected;
    int x, y;

    //TODO remember to change
    switch(m_current_selected_equipment_type)
    {
        case INV_INDEX_HEAD:
            curr_selected = equip.head;
            x = winx_main*PAUSED::OVERVIEW::EQUIPMENT_X_POS;
            y = equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_TOP_POS;
            break;
        case INV_INDEX_TORSO:
            curr_selected = equip.torso;
            x = winx_main*PAUSED::OVERVIEW::EQUIPMENT_X_POS;
            y = equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_MID_POS;
            break;
        case INV_INDEX_LEGS:
            curr_selected = equip.legs;
            x = winx_main*PAUSED::OVERVIEW::EQUIPMENT_X_POS;
            y = equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_BOT_POS;
            break;
        case INV_INDEX_MAINHAND:
            curr_selected = equip.main_hand;
            x = winx_main*PAUSED::OVERVIEW::EQUIPMENT_LEFTLEAN_X_POS;
            y = equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_MID_POS;
            break;
        case INV_INDEX_OFFHAND:
            curr_selected = equip.off_hand;
            x = winx_main*PAUSED::OVERVIEW::EQUIPMENT_RIGHTLEAN_X_POS;
            y = equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_MID_POS;
            break;
        case INV_INDEX_EARS:
            curr_selected = equip.jewellery_ears;
            x = winx_main*PAUSED::OVERVIEW::EQUIPMENT_RIGHTLEAN_X_POS;
            y = equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_TOP_POS;
            break;
        case INV_INDEX_NECKLACE:
            curr_selected = equip.jewellery_necklace;
            x = winx_main*PAUSED::OVERVIEW::EQUIPMENT_LEFTLEAN_X_POS;
            y = equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_TOP_POS;
            break;
        case INV_INDEX_FINGERLEFT:
            curr_selected = equip.jewellery_finger_left;
            x = winx_main*PAUSED::OVERVIEW::EQUIPMENT_LEFTLEAN_X_POS;
            y = equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_BOT_POS;
            break;
        case INV_INDEX_FINGERRIGHT:
            curr_selected = equip.jewellery_finger_right;
            x = winx_main*PAUSED::OVERVIEW::EQUIPMENT_RIGHTLEAN_X_POS;
            y = equipment_win_y*PAUSED::OVERVIEW::EQUIPMENT_Y_BOT_POS;
            break;
        default:
            throw std::runtime_error("equipment index not recognized");
    }
    
    DrawString(x-GetStringLength(get_name(curr_selected),2)-GetStringLength("--", 3),y,">", olc::WHITE, 3);
    DrawString(x+GetStringLength(get_name(curr_selected),2)+GetStringLength("-", 3),y,"<", olc::WHITE, 3);
}

//TODO bigger task
//make the stats change dynamically when hovering an inv for equipment
void DungeonThing::on_render_paused_inventory()
{
    auto [winx, winy] = GetScreenSize();

    auto winx_main = winx * PAUSED::OVERVIEW::EQUIPMENT_SIZE_X;
    int equipment_win_y = winy*PAUSED::OVERVIEW::EQUIPMENT_SIZE_Y;


    DrawString(winx_main*0.1,equipment_win_y*0.1,"INVENTORY:", olc::WHITE, 3);
    DrawString(winx_main*0.6,equipment_win_y*0.1,"F   M   A   W", olc::WHITE, 3);
    DrawLine(winx_main*0.1,
             (equipment_win_y*0.1)+GetStringLength("x", 3),
             (winx_main*0.9),
             (equipment_win_y*0.1)+GetStringLength("x", 3));
    auto offs = 40;
    auto i = 0;
    //TODO figure out a better way to get
    //current selected inv
    for(auto e : m_inventory_list)
    {
        auto name = get_name(e);
        DrawString(winx_main*0.6,(equipment_win_y*0.2)+offs*i,
                   PAUSED::OVERVIEW::get_inv_stats_drawn(this, e),
                   olc::WHITE, 3);
        if(m_inventory_menu.curr_selected == i)
        {
            DrawString(winx_main*0.1,(equipment_win_y*0.2)+offs*i,
                       name, olc::RED, 3);
            DrawString(winx_main*0.1-GetStringLength("-> ", 3),(equipment_win_y*0.2)+offs*i,
                       "->", olc::WHITE, 3);

        }
        else
        {
            DrawString(winx_main*0.1,(equipment_win_y*0.2)+offs*i,
                       name, olc::WHITE, 3);
        }
        ++i;
    }
}

void PAUSED::OVERVIEW::draw_equipment(DungeonThing *olc, entt::entity &ent, int x, int y)
{
    int val_offs = GetStringLength("Willpower: ", 2);
    int init_offs = 10;
    int offs = 20;
    auto equip = olc->get_name(ent, "---");
    olc->DrawString(x-GetStringLength(equip, 3)/2, y,
               equip,
               olc::WHITE,3);

    x = x-PAUSED::OVERVIEW::EQUIPMENT_MAX_STR_LEN;
    force frce;
    if(!olc->tryget_component(ent, frce))
    {
        frce.curr = 0;
    }
    olc->DrawString(x,y+init_offs+offs,
                    "Force: ",
                    olc::WHITE,2);
    olc->DrawString(x+val_offs,y+init_offs+offs,
                    (frce.curr ? std::to_string(frce.curr) : "-"),
                    olc::RED,2);

    mind mnd;
    if(!olc->tryget_component(ent, mnd))
    {
        mnd.curr=0;
    }
    olc->DrawString(x,y+init_offs+offs*2,
                    "Mind: ",
                    olc::WHITE,2);
    olc->DrawString(x+val_offs,y+init_offs+offs*2,
                    (mnd.curr ? std::to_string(mnd.curr) : "-"),
                    olc::RED,2);
    armour arm;
    if(!olc->tryget_component(ent, arm))
    {
        arm.curr = 0;
    }
    olc->DrawString(x,y+init_offs+offs*3,
                    "Armour: ",
                    olc::WHITE,2);
    olc->DrawString(x+val_offs,y+init_offs+offs*3,
                    (arm.curr ? std::to_string(arm.curr) : "-"),
                    olc::RED,2);

    willpower wlpwr;
    if(!olc->tryget_component(ent, wlpwr))
    {
        wlpwr.curr = 0;
    }
    olc->DrawString(x,y+init_offs+offs*4,
                    "Willpower: ",
                    olc::WHITE,2);
    olc->DrawString(x+val_offs,y+init_offs+offs*4,
                    (wlpwr.curr ? std::to_string(wlpwr.curr) : "-"),
                    olc::RED,2);
}


std::string PAUSED::OVERVIEW::get_inv_stats_drawn(DungeonThing *olc, entt::entity &ent)
{
    std::string o[4];
    force frce;
    if(olc->tryget_component(ent, frce))
    {
        o[0] = std::to_string(frce.curr);
    }
    else
        o[0] = "-";

    mind mnd;
    if(olc->tryget_component(ent, mnd))
    {
        o[1] = std::to_string(mnd.curr);
    }
    else
        o[1] = "-";

    armour arm;
    if(olc->tryget_component(ent, arm))
    {
        o[2] = std::to_string(arm.curr);
    }
    else
        o[2] = "-";

    willpower wlpwr;
    if(olc->tryget_component(ent, wlpwr))
    {
        o[3] = std::to_string(wlpwr.curr);
    }
    else
        o[3] = "-";

    std::string out;
    for(int i = 0; i < 4; ++i)
    {
        out += o[i] ;
        for(int j = o[i].length(); j < 4; ++j)
            out += " ";
    }
    return out;
}
