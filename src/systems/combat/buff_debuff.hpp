#ifndef BUFF_DEBUFF_H_
#define BUFF_DEBUFF_H_

#include <entt/entt.hpp>
#include <queue>

#include "utils/debug.hpp"
#include "utils/globals.hpp"

#include "systems/AI/ai.hpp"
#include "systems/movement/movement.hpp"

#include "components/logic.hpp"
#include "components/movement.hpp"
#include "components/combat.hpp"

using enemies = entt::basic_view<entt::get_t<entt::storage_for_t<_enemy>>, entt::exclude_t<>>;
using allies = entt::basic_view<entt::get_t<entt::storage_for_t<_ally>>, entt::exclude_t<>>;

void on_damage(entt::registry&, entt::entity&, entt::entity&, entt::entity&);

void on_buff_debuff(entt::registry&);
void on_buff_debuff_enemy(entt::registry &, enemies &);
void on_buff_debuff_ally(entt::registry &, allies &);


#endif // BUFF_DEBUFF_H_
