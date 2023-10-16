#ifndef RENDER_H_
#define RENDER_H_

#include <entt/entt.hpp>

#include "utils/debug.hpp"
#include "utils/globals.hpp"

#include "components/logic.hpp"
#include "components/movement.hpp"
#include "components/rendering.hpp"


void on_render_menu(entt::registry &);
void on_render_walking(entt::registry &);
void on_render(entt::registry &);
void on_render_transition(entt::registry &);

#endif // RENDER_H_
