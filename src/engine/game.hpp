#ifndef GAME_H_
#define GAME_H_

#include "olcPixelGameEngine.h"
#include <entt/entt.hpp>

#include "systems/loading/initialize.hpp"
#include "systems/movement/movement.hpp"
#include "systems/AI/ai.hpp"

#define BORDER_OFFS 10

enum class state{WALKING, COMBAT, DIALOGUE, CUTSCENE, PAUSED, STARTMENU, TRANSITION, NONE};

class DungeonThing : public olc::PixelGameEngine
{
    public:
        DungeonThing();

    public:
        bool OnUserCreate() override;
        bool OnUserUpdate(float) override;

    private: //states
        void on_render_walking();
        void on_render_paused();
        void on_render_combat();

        void on_userinput_walking();
        void on_userinput_menu();
        void on_userinput_combat();

    private:
        void render_windows();
        entt::registry m_reg;

        state CURR_STATE;
        state NEXT_STATE;

        float m_fElapsedTimeSinceTick;

        entt::entity m_player;
};


#endif // GAME_H_
