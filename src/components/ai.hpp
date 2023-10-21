#ifndef AI_H_
#define AI_H_

#include <entt/entt.hpp>

#include "components/movement.hpp"

namespace ai {
  struct _follow{
    entt::entity target;
  };

  struct _strolling{
    int dirX;
    int dirY;
    int strolling_progress;
    pos init_pos;
    bool reverse;
  };

  struct _at_rest{};

  struct visionzone_cirle{
    int radius;
  };


}
struct _ai{};

#endif // AI_H_
