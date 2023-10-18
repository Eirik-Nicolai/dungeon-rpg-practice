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
}
