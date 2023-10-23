#ifndef GAME_H_
#define GAME_H_

#include <queue>
#include <entt/entt.hpp>
#include "olcPixelGameEngine.h"

#include "menu.hpp"

#include "types_and_defines.hpp"
#include "components/combat.hpp"
#include "components/globals.hpp"

#include "systems/AI/ai.hpp"
#include "systems/logic/logic.hpp"
#include "systems/combat/damage.hpp"
#include "systems/movement/movement.hpp"
#include "systems/combat/buff_debuff.hpp"

class DungeonThing : public olc::PixelGameEngine
{
    public:
        DungeonThing();

    public:
        bool OnUserCreate() override;
        bool OnUserUpdate(float) override;

    private: //states
        void STATE_WALKING(float);
        void STATE_COMBAT(float);
        void STATE_PAUSE(float);


        void on_load_init();
        void on_load_combat();

        void on_render_walking();
        void on_render_paused();
        void on_render_combat();

        void on_render_transition_to_walking_from_combat(float dt);
        void on_render_transition_combat(float dt);

        void on_userinput_walking();
        void on_userinput_paused();
        void on_userinput_combat();


        bool delay_for(float, float);

    private:
        entt::registry m_reg;
        void render_windows();

        std::vector<CombatMenu> m_combatmenus;
        entt::entity m_intended_action;
        TargetMenu m_targetmenu;
        std::vector<PauseMenu> m_pausemenus;

        int m_curr_menu;

        State CURR_STATE;
        State NEXT_STATE;

        float m_fElapsedTimeSinceTick;

        entt::entity m_player;

        // TODO move to ctx and refactor
        float m_transition_progress;
        float m_transition_acc;
        float m_transition_time;
        float m_elapsed_transition_time;

        std::queue<combat_action> m_movequeue_player;
        std::queue<combat_action> m_movequeue_allies;
        std::queue<combat_action> m_movequeue_enemy;

    private:
        std::vector<std::string> m_debug;
};


#endif // GAME_H_
