#include "game.hpp"
#include "utils/globals.hpp"

#include <vector>

#include "components/combat.hpp"
#include "components/rendering.hpp"

void DungeonThing::STATE_COMBAT(float dt)
{
    switch(CURR_STATE.type)
    {
        case type::INIT:
        {
            DrawString(600,420, "INIT");
            std::cout << "INIT" << std::endl;
            // TODO save curr state ?

            auto goblin_big = m_reg.create();
            m_reg.emplace<combat_appearence>(goblin_big, "V");
            m_reg.emplace<health>(goblin_big, 100, 100);
            m_reg.emplace<armour>(goblin_big, 5);
            m_reg.emplace<stats>(goblin_big, 10, 0);
            m_reg.emplace<ability_list>(goblin_big, std::vector<ability>());
            m_reg.emplace<_enemy>(goblin_big);

            // find positions for multi-group enemies/allies
            auto enemy_group = m_reg.view<_enemy>();
            auto [winx, winy] = GetWindowSize();
            auto winx_size = winx * 0.66;

            // switch (enemy_group.size()) {
            //     case 3:
            //         enemy_group.end()
            //     case 2:
            //     case 1:
            //         break;

            // }

            //auto goblin_mage = m_reg.create();
            //auto goblin_reg = m_reg.create();

            // clear moves if any
            while(m_movequeue.size() > 0)
                m_movequeue.pop();

            m_reg.ctx().emplace<CombatState>(-1);

            m_transition_progress = 0.0;
            m_elapsed_transition_time = 1.0;
            // TODO init entities used for combat

            NEXT_STATE.type = type::PLAYING_TRANSITION;
        }
        break;
        case type::PLAYING_TRANSITION:
        {
            DrawString(600,420, "PLAYING_TRANSITION");
            // FIXME calcuate based on time to transition
            // m_transition_progress += dt * (40*m_transition_acc);
            // if(m_transition_acc > 1.0)m_transition_acc = m_transition_acc-(5.5*dt);
            if(m_transition_progress >= 100)
            {
                m_transition_progress = 1.0;
                NEXT_STATE.type = type::PLAYER_SELECTING;
            }
            on_render_transition_combat(dt);
        }
        break;
        case type::PLAYER_SELECTING:
        {
            DrawString(600,420, "SELECTING");
            //std::cout << "SELECTING" << std::endl;
            on_userinput_combat();
            //selection_check();
            on_render_combat();
        }
        break;
        case type::INIT_PLAYER_SELECTION:
        {

        }
        break;
        case type::PERFORMING_COMBAT_ACTIONS_PLAYER:
        {

        }
        break;
        case type::PERFORMING_COMBAT_ACTIONS_ENEMY:
        {

        }
        break;
        default:
            std::cout << "TYPE NOT IMPL" << std::endl;
    }
}
