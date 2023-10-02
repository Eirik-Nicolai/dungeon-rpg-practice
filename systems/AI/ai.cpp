#include "ai.hpp"

void on_follow_player(entt::registry &reg)
{
  auto player = (*reg.view<const _player>().begin());
  auto playerpos = reg.get<const pos>(player);

  auto ai_view = reg.view<_follow_player, pos, directionNorth, directionSouth, directionWest, directionEast>();

  for(auto [ent, p, north, south, west, east]: ai_view.each())
  {
    if(playerpos.x > p.x)
    {
      if (east.vel < 1) east.vel += 1;
    }
    else
    {
      if (east.vel > 0 )east.vel -= 1;
    }
    if (playerpos.x < p.x)
    {
      if (west.vel < 1) west.vel += 1;
    }
    else
    {
      if (west.vel > 0 )west.vel -= 1;
    }
    if(playerpos.y > p.y)
    {
      if (south.vel < 1) south.vel += 1;
    }
    else
    {
      if (south.vel > 0 )south.vel -= 1;
    }
    if (playerpos.y < p.y)
    {
      if (north.vel < 1) north.vel += 1;
    }
    else
    {
      if (north.vel > 0) north.vel -= 1;
    }
  }
}

void on_ai(entt::registry &reg)
{
  on_follow_player(reg);
}
