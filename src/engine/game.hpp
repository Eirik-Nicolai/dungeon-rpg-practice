#ifndef GAME_H_
#define GAME_H_

#include "olcPixelGameEngine.h"
#include <entt/entt.hpp>

#include "menu.hpp"

#include "types_and_defines.hpp"

#include "systems/logic/logic.hpp"
#include "systems/loading/initialize.hpp"
#include "systems/movement/movement.hpp"
#include "systems/AI/ai.hpp"


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

        void on_render_transition_combat();

        void on_userinput_walking();
        void on_userinput_paused();
        void on_userinput_combat();

    private:
        entt::registry m_reg;
        void render_windows();

        std::vector<CombatMenu> m_combatmenus;
        std::vector<PauseMenu> m_pausemenus;
        int m_curr_menu;

        State CURR_STATE;
        State NEXT_STATE;

        float m_fElapsedTimeSinceTick;

        entt::entity m_player;

        float m_transition_progress;
        float m_transition_acc;
        float m_transition_time;
        float m_elapsed_transition_time;
};


#endif // GAME_H_
