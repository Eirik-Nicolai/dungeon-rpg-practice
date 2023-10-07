#include "keypress.hpp"
#include <iostream>

int press_offset_n = 0;
int press_offset_s = 0;
int press_offset_w = 0;
int press_offset_e = 0;


void on_keypress(entt::registry &reg, int &ch)
{
        // WALKING
        if (ch == KEY_UP || ch == 'w')
        {
                ISPRESSED_NORTH = true;
        }
        if (ch == KEY_DOWN || ch == 's')
        {
                ISPRESSED_SOUTH = true;
        }
        if (ch == KEY_LEFT || ch == 'a')
        {
                ISPRESSED_WEST = true;
        }
        if (ch == KEY_RIGHT || ch == 'd')
        {
                ISPRESSED_EAST = true;
        }

        // OPEN INVENTORY / PAUSE GAME
        if (ch == 'i' || ch == 'z')
        {
                NEW_GAME_STATE = state::PAUSED;
        }
}

void on_input_menu(entt::registry &reg)
{

}

void on_input_walking(entt::registry &reg)
{
        //Debug::Log(std::to_string(ISPRESSED_NORTH), 0, 0);
        if(ISPRESSED_NORTH)
        {
                ISPRESSED_NORTH = false;
                if(press_offset_n==0)press_offset_n += 3;
                else press_offset_n += 1;
        }
        if(ISPRESSED_SOUTH)
        {
                ISPRESSED_SOUTH = false;
                if(press_offset_s==0)press_offset_s += 3;
                else press_offset_s += 1;
        }
        if(ISPRESSED_WEST)
        {
                ISPRESSED_WEST = false;
                if(press_offset_w==0)press_offset_w += 3;
                else press_offset_w += 1;
        }
        if(ISPRESSED_EAST)
        {
                ISPRESSED_EAST = false;
                if(press_offset_e==0)press_offset_e += 3;
                else press_offset_e += 1;
        }

        auto playerent = (*reg.view<_player>().begin());
        if(press_offset_n > 0)
        {
                --press_offset_n;
                reg.get<directionNorth>(playerent).vel = 1;
        }
        else
        {
                reg.get<directionNorth>(playerent).vel = 0;
        }
        if(press_offset_s > 0)
        {
                --press_offset_s;
                reg.get<directionSouth>(playerent).vel = 1;
        }
        else
        {
                reg.get<directionSouth>(playerent).vel = 0;
        }
        if(press_offset_w > 0)
        {
                --press_offset_w;
                reg.get<directionWest>(playerent).vel = 1;
        }
        else
        {
                reg.get<directionWest>(playerent).vel = 0;
        }
        if(press_offset_e > 0)
        {
                --press_offset_e;
                reg.get<directionEast>(playerent).vel = 1;
        }
        else
        {
                reg.get<directionEast>(playerent).vel = 0;
        }
}
