#include "logic.hpp"

void on_collision(entt::registry &reg)
{
    auto movement = reg.view<const pos, dirVertical, dirHorisontal>();
    for (auto [ent, p, dirV, dirH]: movement.each())
    {
        if(dirV.up || dirV.down || dirH.left || dirH.right)
        {
            pos potensialpos = p;
            if(dirV.down) potensialpos.y+=PIXEL_OFFS;
            if(dirV.up)   potensialpos.y-=PIXEL_OFFS;
            if(dirH.right)potensialpos.x+=PIXEL_OFFS;
            if(dirH.left) potensialpos.x-=PIXEL_OFFS;

            // solid blocks
            auto block = reg.view<pos, _solid>();
            for(auto [blockent, blockp]: block.each())
            {
                if(reg.all_of<size>(blockent))
                {
                    auto s = reg.get<size>(blockent);
                    // std::cout << potensialpos.y << std::endl;
                    // std::cout << blockp.y << " - " << blockp.y+s.height << std::endl;
                    if(potensialpos.x >= blockp.x
                       && potensialpos.x < blockp.x + s.width
                       && potensialpos.y >= blockp.y
                       && potensialpos.y < blockp.y + s.height)
                    {
                        dirV.up = false;
                        dirV.down = false;
                        dirH.right = false;
                        dirH.left = false;
                    }
                }
            }
        }
    }
}

void on_logic(entt::registry &reg)
{

}


void on_gamestate_change(entt::registry &reg)
{

}
