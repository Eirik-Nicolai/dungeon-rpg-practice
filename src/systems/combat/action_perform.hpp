#ifndef DAMAGE_H_
#define DAMAGE_H_

#include <entt/entt.hpp>

#include "utils/debug.hpp"
#include "utils/utils.hpp"
#include "utils/globals.hpp"

#include "systems/AI/ai.hpp"
#include "systems/movement/movement.hpp"

#include "components/logic.hpp"
#include "components/movement.hpp"
#include "components/combat.hpp"

void on_perform_action(entt::registry&, entt::entity&, entt::entity&, entt::entity&);
void on_check_target_death(entt::registry&, entt::entity&, entt::entity&);

void on_skill(entt::registry&, entt::entity&, entt::entity&, entt::entity&);
void on_skill_cleanse(entt::registry&, entt::entity&, entt::entity&, entt::entity&);
void on_skill_summon(entt::registry&, entt::entity&, entt::entity&, entt::entity&);

int calculate_damage_phys(entt::registry&, entt::entity&,damage&);
int calculate_damage_magi(entt::registry&, entt::entity&,damage&);


void calculate_resist_phys(entt::registry&, entt::entity&, int&);
void calculate_resist_magi(entt::registry&, entt::entity&, int&);

void apply_debuff(entt::registry&, entt::entity&, entt::entity&);
void apply_buff(entt::registry&, entt::entity&, entt::entity&);

float get_raw_dmg_multiplier(entt::registry&, entt::entity&, dmg_type);

#endif // DAMAGE_H_
