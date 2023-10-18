#ifndef AI_H_
#define AI_H_

#include <entt/entt.hpp>

struct _ai{};

struct _follow{
  entt::entity target;
};

struct _at_rest{};

struct visionzone_cirle{
  int radius;
};

#endif // AI_H_
