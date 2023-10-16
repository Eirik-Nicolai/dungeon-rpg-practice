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
                NEXT_STATE = state::COMBAT;
        }
}
