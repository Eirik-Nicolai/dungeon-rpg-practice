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
        constexpr float EQUIPMENT_X_POS = 0.5;
        constexpr float EQUIPMENT_LEFTLEAN_X_POS = 0.2;
        constexpr float EQUIPMENT_RIGHTLEAN_X_POS = 0.80;
        constexpr float EQUIPMENT_Y_TOP_POS = 0.1;
        constexpr float EQUIPMENT_Y_MID_POS = 0.40;
        constexpr float EQUIPMENT_Y_BOT_POS = 0.70;

        constexpr float EQUIPMENT_SIZE_X = 0.65;
        constexpr float EQUIPMENT_SIZE_Y = 0.66;

        constexpr int EQUIPMENT_MAX_STR_LEN = 10*16;

        void draw_equipment(DungeonThing*, entt::entity&, int x, int y);
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
