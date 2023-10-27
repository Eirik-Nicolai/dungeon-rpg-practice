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

#define MENU_ITEM_OFFS_Y 50

//TODO namespaces
// -------------------------------------
namespace PAUSED
{
    namespace OVERVIEW
    {
        constexpr float EQUIPMENT_POS_X = 0.2;
        constexpr float EQUIPMENT_POS_X_OFFS = 0.3;
        constexpr float EQUIPMENT_POS_Y = 0.1;
        constexpr float EQUIPMENT_POS_Y_OFFS = 0.30;

        constexpr float EQUIPMENT_SIZE_X = 0.65;
        constexpr float EQUIPMENT_SIZE_Y = 0.66;

        constexpr int EQUIPMENT_MAX_STR_LEN = 10*16;

        void draw_equipment(DungeonThing*, entt::entity&, std::string&, int x, int y, olc::Pixel c = olc::WHITE);
        std::string get_inv_stats_drawn(DungeonThing*, entt::entity&);
    }
}


// -------------------------------------

// TODO check this
inline int GetStringLength(std::string s, int scale)
{
    return s.size() * 8 * scale;
}




#endif // RENDER_H_
