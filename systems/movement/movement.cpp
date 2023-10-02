#include "movement.hpp"
#include <iostream>

void on_move(entt::registry &reg)
{
    auto north_view = reg.view<movespeed, directionNorth>();
    auto south_view = reg.view<movespeed, directionSouth>();
    auto west_view =  reg.view<movespeed, directionWest>();
    auto east_view =  reg.view<movespeed, directionEast>();

    for (auto [ent, speed, dir]: north_view.each())
    {
        if(dir.tick >= 1.0)
        {
            auto p = reg.get<pos>(ent);
            reg.replace<pos>(ent, p.x, p.y-1);
            dir.tick = dir.tick-1;
        }
        else if (dir.vel > 0)
        {
            dir.tick += speed.speed;
        }
    }

    for (auto [ent, speed, dir]: south_view.each())
    {
        if(dir.tick >= 1.0)
        {
            auto p = reg.get<pos>(ent);
            reg.replace<pos>(ent, p.x, p.y+1);
            dir.tick = dir.tick-1;
        }
        else if (dir.vel > 0)
        {
            dir.tick += speed.speed;
        }
    }

    for (auto [ent, speed, dir]: west_view.each())
    {
        if(dir.tick >= 1.0)
        {
            auto p = reg.get<pos>(ent);
            reg.replace<pos>(ent, p.x-1, p.y);
            dir.tick = dir.tick-1;
        }
        else if (dir.vel > 0)
        {
            dir.tick += speed.speed;
        }
    }

    for (auto [ent, speed, dir]: east_view.each())
    {
        if(dir.tick >= 1.0)
        {
            auto p = reg.get<pos>(ent);
            reg.replace<pos>(ent, p.x+1, p.y);
            dir.tick = dir.tick-1;
        }
        else if (dir.vel > 0)
        {
            dir.tick += speed.speed;
        }
    }
}
