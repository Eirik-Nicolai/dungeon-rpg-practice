#ifndef KEYPRESS_H_
#define KEYPRESS_H_

#include <entt/entt.hpp>

#include "utils/debug.hpp"

#include "components/logic.hpp"
#include "components/movement.hpp"


void on_input_menu(entt::registry &);
void on_input_walking(entt::registry &);
void on_keypress(entt::registry &);

#endif // KEYPRESS_H_
