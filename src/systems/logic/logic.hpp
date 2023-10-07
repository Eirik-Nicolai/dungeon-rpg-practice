#ifndef SYS_LOGIC_H_
#define SYS_LOGIC_H_

#include <entt/entt.hpp>

#include "utils/debug.hpp"
#include "utils/globals.hpp"

#include "systems/AI/ai.hpp"
#include "systems/input/keypress.hpp"
#include "systems/movement/movement.hpp"
#include "systems/transition/transition.hpp"

#include "components/logic.hpp"
#include "components/movement.hpp"

void on_gamestate_change(entt::registry &);

void on_logic(entt::registry &);

#endif // LOGIC_H_