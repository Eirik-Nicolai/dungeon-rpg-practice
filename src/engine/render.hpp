#ifndef RENDER_H_
#define RENDER_H_

#include <entt/entt.hpp>
#include "game.hpp"


#include "utils/debug.hpp"

#include "components/logic.hpp"
#include "components/movement.hpp"
#include "components/rendering.hpp"

#define MENU_ITEM_OFFS_Y 30

inline int GetStringLength(std::string& s)
{
    return s.size() * 8 * 2;
}


#endif // RENDER_H_
