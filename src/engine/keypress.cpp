#include "game.hpp"
#include "keypress.hpp"
#include <iostream>

void DungeonThing::on_userinput_walking()
{
        //Debug::Log(std::to_string(ISPRESSED_NORTH), 0, 0);

        if (GetKey(olc::Key::W).bHeld)
        {
                //ISPRESSED_NORTH = true;
        }
        if (GetKey(olc::Key::D).bHeld)
        {
                //ISPRESSED_SOUTH = true;
        }
        if (GetKey(olc::Key::A).bHeld)
        {
                //ISPRESSED_WEST = true;
        }
        if (GetKey(olc::Key::D).bHeld)
        {
                //ISPRESSED_EAST = true;
        }

        // OPEN INVENTORY / PAUSE GAME
        if (GetKey(olc::Key::X).bHeld)
        {
                NEXT_STATE = state::PAUSED;
        }


        // if(ISPRESSED_NORTH)
        // {
        //         ISPRESSED_NORTH = false;
        //         if(press_offset_n==0)press_offset_n += 3;
        //         else press_offset_n += 1;
        // }
        // if(ISPRESSED_SOUTH)
        // {
        //         ISPRESSED_SOUTH = false;
        //         if(press_offset_s==0)press_offset_s += 3;
        //         else press_offset_s += 1;
        // }
        // if(ISPRESSED_WEST)
        // {
        //         ISPRESSED_WEST = false;
        //         if(press_offset_w==0)press_offset_w += 3;
        //         else press_offset_w += 1;
        // }
        // if(ISPRESSED_EAST)
        // {
        //         ISPRESSED_EAST = false;
        //         if(press_offset_e==0)press_offset_e += 3;
        //         else press_offset_e += 1;
        // }

        // auto playerent = (*reg.view<_player>().begin());
        // if(press_offset_n > 0)
        // {
        //         --press_offset_n;
        //         reg.get<directionNorth>(playerent).vel = 1;
        // }
        // else
        // {
        //         reg.get<directionNorth>(playerent).vel = 0;
        // }
        // if(press_offset_s > 0)
        // {
        //         --press_offset_s;
        //         reg.get<directionSouth>(playerent).vel = 1;
        // }
        // else
        // {
        //         reg.get<directionSouth>(playerent).vel = 0;
        // }
        // if(press_offset_w > 0)
        // {
        //         --press_offset_w;
        //         reg.get<directionWest>(playerent).vel = 1;
        // }
        // else
        // {
        //         reg.get<directionWest>(playerent).vel = 0;
        // }
        // if(press_offset_e > 0)
        // {
        //         --press_offset_e;
        //         reg.get<directionEast>(playerent).vel = 1;
        // }
        // else
        // {
        //         reg.get<directionEast>(playerent).vel = 0;
        // }
}
