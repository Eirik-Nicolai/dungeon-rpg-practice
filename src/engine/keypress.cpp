#include "game.hpp"
#include "keypress.hpp"
#include <iostream>

void DungeonThing::on_userinput_walking()
{
    if (GetKey(olc::Key::W).bHeld)
    {
        m_reg.get<dirVertical>(m_player).up = true;
    }
    if (GetKey(olc::Key::W).bReleased)
    {
        m_reg.get<dirVertical>(m_player).up = false;
    }

    if (GetKey(olc::Key::S).bHeld)
    {
        m_reg.get<dirVertical>(m_player).down = true;
    }
    if (GetKey(olc::Key::S).bReleased)
    {
        m_reg.get<dirVertical>(m_player).down = false;
    }

    if (GetKey(olc::Key::A).bHeld)
    {
        m_reg.get<dirHorisontal>(m_player).left = true;
    }
    if (GetKey(olc::Key::A).bReleased)
    {
        m_reg.get<dirHorisontal>(m_player).left = false;
    }

    if (GetKey(olc::Key::D).bHeld)
    {
        m_reg.get<dirHorisontal>(m_player).right = true;
    }
    if (GetKey(olc::Key::D).bReleased)
    {
        m_reg.get<dirHorisontal>(m_player).right = false;
    }


    // OPEN INVENTORY / PAUSE GAME
    if (GetKey(olc::Key::I).bReleased)
    {
        NEXT_STATE.state = state::PAUSED;
        NEXT_STATE.type = type::INIT_PAUSED;
    }

    // DEBUGGING
    if (GetKey(olc::Key::X).bReleased)
    {
        NEXT_STATE.state = state::COMBAT;
        NEXT_STATE.type = type::INIT;
    }
}

void DungeonThing::on_userinput_paused()
{
    switch(CURR_STATE.type)
    {
        case type::OVERVIEW:
        {
            if (GetKey(olc::Key::W).bReleased)
            {
                m_pausemenus[m_curr_menu].ScrollUp();
            }
            if (GetKey(olc::Key::S).bReleased)
            {
                m_pausemenus[m_curr_menu].ScrollDown();
            }
            if(GetKey(olc::Key::ENTER).bReleased)
            {
                m_pausemenus[m_curr_menu].Select();
            }
        }
        break;
        case type::EQUIPMENT:
        {
            if (GetKey(olc::Key::W).bReleased)
            {
                m_current_selected_equipment_type = m_equipment_menu.ScrollUp();
            }
            if (GetKey(olc::Key::S).bReleased)
            {
                m_current_selected_equipment_type = m_equipment_menu.ScrollDown();
            }
            if (GetKey(olc::Key::A).bReleased)
            {
                m_current_selected_equipment_type = m_equipment_menu.ScrollLeft();
            }
            if (GetKey(olc::Key::D).bReleased)
            {
                m_current_selected_equipment_type = m_equipment_menu.ScrollRight();
            }
            if(GetKey(olc::Key::ENTER).bReleased)
            {
                m_equipment_menu.Select();
            }
        }
        break;
        case ::type::INVENTORY:
        case type::CHANGING_EQUIPMENT:
        {
            if (GetKey(olc::Key::W).bReleased)
            {
                m_inventory_menu.ScrollUp();
            }
            if (GetKey(olc::Key::S).bReleased)
            {
                m_inventory_menu.ScrollDown();
            }
            // TODO use to see special effects
            // if (GetKey(olc::Key::A).bReleased)
            // {
            //     m_current_selected_equipment_type = m_equipment_menu.ScrollLeft();
            // }
            // if (GetKey(olc::Key::D).bReleased)
            // {
            //     m_current_selected_equipment_type = m_equipment_menu.ScrollRight();
            // }
            if(GetKey(olc::Key::ENTER).bReleased)
            {
                m_inventory_menu.Select();
            }
        }
        break;
        default:
            std::cout << "PAUSE TYPE NOT RECOGNISED" << std::endl;
    }


    // DEBUG

    // if(GetKey(olc::Key::Z).bReleased)
    // {
    //     m_reg.patch<health>(m_player, [](auto &h){
    //         h.curr -= 15;
    //     });
    // }

    // if(GetKey(olc::Key::X).bReleased)
    // {
    //     m_reg.patch<health>(m_player, [](auto &h){
    //        h.curr += 15;
    //     });
    // }
}


void DungeonThing::on_userinput_combat()
{
    if (CURR_STATE.type == type::PLAYER_SELECTING_ACTION)
    {
        if (GetKey(olc::Key::W).bReleased || GetKey(olc::Key::UP).bReleased)
        {
            m_combatmenus[m_curr_menu].ScrollUp();
        }
        if (GetKey(olc::Key::S).bReleased || GetKey(olc::Key::DOWN).bReleased)
        {
            m_combatmenus[m_curr_menu].ScrollDown();
        }
        if (GetKey(olc::Key::A).bReleased || GetKey(olc::Key::LEFT).bReleased)
        {
            m_combatmenus[m_curr_menu].ScrollLeft();
        }
        if (GetKey(olc::Key::D).bReleased || GetKey(olc::Key::RIGHT).bReleased)
        {
            m_combatmenus[m_curr_menu].ScrollRight();
        }
        if(GetKey(olc::Key::ENTER).bReleased || GetKey(olc::Key::SPACE).bReleased)
        {
            m_combatmenus[m_curr_menu].Select();
        }
    }
    else
    {
        if (GetKey(olc::Key::W).bReleased || GetKey(olc::Key::UP).bReleased)
        {
            m_targetmenu.ScrollDown();
        }
        if (GetKey(olc::Key::S).bReleased || GetKey(olc::Key::DOWN).bReleased)
        {
            m_targetmenu.ScrollDown();
        }
        if(GetKey(olc::Key::ENTER).bReleased || GetKey(olc::Key::SPACE).bReleased)
        {
            m_targetmenu.Select();
        }
    }
}
