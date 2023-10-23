#ifndef DAMAGE_H_
#define DAMAGE_H_

#include <entt/entt.hpp>

#include "utils/debug.hpp"
#include "utils/globals.hpp"


#include "systems/AI/ai.hpp"
#include "systems/movement/movement.hpp"

#include "components/logic.hpp"
#include "components/movement.hpp"
#include "components/combat.hpp"

void on_damage(entt::registry&, entt::entity&, entt::entity&, entt::entity&);


int get_actual_damage(int&, entt::registry&, entt::entity&, entt::entity&);
void apply_debuff(entt::registry&, entt::entity&, entt::entity&);
void apply_buff(entt::registry&, entt::entity&, entt::entity&);

#endif // DAMAGE_H_
