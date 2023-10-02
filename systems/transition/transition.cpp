#include "transition.hpp"


void on_pause_transition_start(entt::registry &reg)
{
  auto view = reg.view<window>();
  // TODO id as component?
  for( auto [ent, w]: view.each() )
  {
    if(w.id == MENUWINDOW)
    {
      reg.emplace<transitioning>(ent, GAME_STATE == state::WALKING ? 0 : 1);
      reg.emplace<_isactive>(ent);
    }
  }
}
