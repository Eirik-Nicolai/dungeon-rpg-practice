#include "ai.hpp"

void on_follow_player(entt::registry &reg, entt::entity &player)
{
  auto playerpos = reg.get<const pos>(player);

  auto ai_view = reg.view<_follow_player, pos, dirVertical, dirHorisontal>();

  for(auto [ent, p, dirV, dirH]: ai_view.each())
  {
    dirV.up = playerpos.y < p.y;
    dirV.down = playerpos.y > p.y;
    dirH.left = playerpos.x < p.x;
    dirH.right = playerpos.x > p.x;
  }
}

void on_ai(entt::registry &reg, entt::entity &player)
{
  on_follow_player(reg, player);
}
