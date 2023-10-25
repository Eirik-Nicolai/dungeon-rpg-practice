#ifndef EQUIPMENT_H_
#define EQUIPMENT_H_

#include <entt/entt.hpp>

enum equiptype{HEAD=0,TORSO,LEGS,MAINHAND,OFFHAND,ACCESS_FINGER,ACCESS_HEAD};
constexpr uint8_t NUM_EQUIPTYPES = 7;

//TODO change these to just store the index
struct equipment_type{
  equiptype type;
};

struct _consumable{};

struct effect{
  entt::entity effect;
};


#endif // EQUIPMENT_H_
