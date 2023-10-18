#ifndef SYS_AI_H_
#define SYS_AI_H_

#include <entt/entt.hpp>

#include "components/ai.hpp"
#include "components/logic.hpp"
#include "components/movement.hpp"


void on_follow(entt::registry &);

void on_ai(entt::registry &);

#endif // AI_H_
