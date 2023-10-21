#include "movement.hpp"
#include <iostream>

void on_move_tick(entt::registry &reg)
{
    auto dir_tick = reg.view<const movespeed, const dirVertical, const dirHorisontal, moveTick>();

    for (auto [ent, speed, dirV, dirH, tick]: dir_tick.each())
    {
        if(dirV.up || dirV.down || dirH.left || dirH.right)
        {
            tick.tick += 0.15;
        }
    }
}

void on_move(entt::registry &reg)
{
    auto movement = reg.view<const movespeed, moveTick>();
    for (auto [ent, speed, tick]: movement.each())
    {
        if(tick.tick >= speed.speed)
        {
            auto [p, dirV, dirH] = reg.get<pos, dirVertical, dirHorisontal>(ent);
            if(dirV.up)
            {
                p.y -= 10;
            }
            if(dirV.down)
            {
                p.y += 10;
            }
            if(dirH.left)
            {
                p.x -= 10;
            }
            if(dirH.right)
            {
                p.x += 10;
            }
            tick.tick = 0;
        }
    }
}
