#include "movement.hpp"
#include <iostream>

void on_move(entt::registry &reg)
{
    auto dir_tick = reg.view<const movespeed, const dirVertical, const dirHorisontal, moveTick>();

    for (auto [ent, speed, dirV, dirH, tick]: dir_tick.each())
    {
        if(dirV.up || dirV.down || dirH.left || dirH.right)
        {
            tick.tick += 0.15;
        }
    }

    auto movement = reg.view<const movespeed, const dirVertical, const dirHorisontal, moveTick, pos>();
    for (auto [ent, speed, dirV, dirH, tick, p]: movement.each())
    {
        if(tick.tick >= speed.speed)
        {
            auto &p = reg.get<pos>(ent);
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
