#include "ai.hpp"

void on_follow(entt::registry &reg)
{
  auto ai_view = reg.view<_follow, pos, dirVertical, dirHorisontal>();

  for(auto [ent, follow, p, dirV, dirH]: ai_view.each())
  {
    auto targetpos = reg.get<const pos>(follow.target);
    dirV.up = targetpos.y < p.y;
    dirV.down = targetpos.y > p.y;
    dirH.left = targetpos.x < p.x;
    dirH.right = targetpos.x > p.x;
  }
}

void on_ai(entt::registry &reg)
{
  on_follow(reg);
}
