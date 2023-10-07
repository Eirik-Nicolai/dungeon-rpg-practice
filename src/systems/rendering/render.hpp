#ifndef RENDER_H_
#define RENDER_H_

#include <ncurses.h>
#include <entt/entt.hpp>

#include "utils/debug.hpp"
#include "utils/globals.hpp"

#include "components/logic.hpp"
#include "components/movement.hpp"
#include "components/rendering.hpp"


void on_render_menu(entt::registry &, WINDOW *);
void on_render_walking(entt::registry &, WINDOW *);
void on_render(entt::registry &, std::array<WINDOW*, 4>);
void on_render_transition(entt::registry &, std::array<WINDOW*, 4>);

#endif // RENDER_H_
