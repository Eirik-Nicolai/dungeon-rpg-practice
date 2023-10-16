#ifndef SYS_AI_H_
#define SYS_AI_H_

#include <entt/entt.hpp>

#include "components/ai.hpp"
#include "components/logic.hpp"
#include "components/movement.hpp"


void on_follow_player(entt::registry &, entt::entity &);

void on_ai(entt::registry &, entt::entity &);

#endif // AI_H_
