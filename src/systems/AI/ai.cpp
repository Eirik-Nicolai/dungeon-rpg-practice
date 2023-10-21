#include "ai.hpp"

void on_follow(entt::registry &reg)
{
    auto ai_view = reg.view<ai::_follow, pos, dirVertical, dirHorisontal>();

    for(auto [ent, follow, p, dirV, dirH]: ai_view.each())
    {
        auto targetpos = reg.get<const pos>(follow.target);
        dirV.up = targetpos.y < p.y;
        dirV.down = targetpos.y > p.y;
        dirH.left = targetpos.x < p.x;
        dirH.right = targetpos.x > p.x;
    }
}

void on_strolling(entt::registry &reg)
{
    auto ai_view = reg.view<ai::_strolling, const pos, dirVertical, dirHorisontal>();

    for(auto [ent, follow, p, dirV, dirH]: ai_view.each())
    {
        pos targetpos = {0,0};
        if(!follow.reverse)
        {
            targetpos = {follow.init_pos.x+follow.dirX, follow.init_pos.y+follow.dirY};
            int progx = follow.dirX==0 ? 0 : abs((p.x-follow.init_pos.x)*100/follow.dirX);
            int progy = follow.dirY==0 ? 0 : abs((p.y-follow.init_pos.y)*100/follow.dirY);

            follow.strolling_progress =  (progx+progy) / (progx==0||progy==0?1:2);
            if (follow.strolling_progress >= 100)
            {
                follow.reverse = true;
                follow.strolling_progress = 0;
            }
        }
        else
        {
            targetpos = {follow.init_pos.x-follow.dirX, follow.init_pos.y-follow.dirY};
            int progx = follow.dirX==0 ? 0 : abs((p.x-follow.init_pos.x)*100/follow.dirX);
            int progy = follow.dirY==0 ? 0 : abs((p.y-follow.init_pos.y)*100/follow.dirY);

            follow.strolling_progress = (progx+progy)/ 2;
            if (follow.strolling_progress <= 100)
            {
                follow.reverse = false;
                follow.strolling_progress = 0;
            }
        }
        dirV.up = targetpos.y < p.y;
        dirV.down = targetpos.y > p.y;
        dirH.left = targetpos.x < p.x;
        dirH.right = targetpos.x > p.x;
    }
}

void on_ai(entt::registry &reg)
{
    on_follow(reg);
    on_strolling(reg);
}
