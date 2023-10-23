#ifndef RENDER_H_
#define RENDER_H_

#include <entt/entt.hpp>
#include "engine/game.hpp"

#include "utils/debug.hpp"
#include "utils/globals.hpp"

#include "components/logic.hpp"
#include "components/objects.hpp"
#include "components/movement.hpp"
#include "components/rendering.hpp"

#define MENU_ITEM_OFFS_Y 30

inline int GetStringLength(std::string s)
{
    return s.size() * 16 * 2;
}

#endif // RENDER_H_
