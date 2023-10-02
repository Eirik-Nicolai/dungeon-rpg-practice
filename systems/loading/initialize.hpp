#ifndef INITIALIZE_H_
#define INITIALIZE_H_

#include <entt/entt.hpp>

#include "utils/globals.hpp"

#include "components/ai.hpp"
#include "components/logic.hpp"
#include "components/movement.hpp"
#include "components/rendering.hpp"


void on_init(entt::registry &, int, int);

#endif // INITIALIZE_H_
