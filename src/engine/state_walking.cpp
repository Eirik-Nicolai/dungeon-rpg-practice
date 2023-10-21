#include "game.hpp"
#include "utils/globals.hpp"

void DungeonThing::STATE_WALKING(float dt)
{
    switch(CURR_STATE.type)
    {
        case type::INIT:
        {
            DrawString(600,420, "INIT");
            std::cout << "INIT" << std::endl;
            // TODO save curr state ?

            // TODO init entities used for combat
            m_transition_progress = 0.0;
            m_elapsed_transition_time = 0.0f;
            NEXT_STATE.type = type::FROM_COMBAT_TRANSITION;;
        }
        break;
        case type::FROM_COMBAT_TRANSITION:
        {
            DrawString(600,420, "FROM_COMBAT");
            if(m_transition_progress <= 0)
            {
                m_transition_progress = 0;
                NEXT_STATE.type = type::FREEROAM;
            }
            //on_render_transition_to_walking_from_combat(dt);
        }
        break;
        case type::FROM_PAUSED_TRANSITION:
        {
            DrawString(600,420, "FROM_PAUSED");
            NEXT_STATE.type = type::FREEROAM;

        }
        break;
        case type::FREEROAM:
        {
            DrawString(600,420, "FREEROAM");
            //std::cout << "SELECTING" << std::endl;
            on_userinput_walking();

            if(m_fElapsedTimeSinceTick >= 0.1)
            {
                on_ai(m_reg);
                on_move_tick(m_reg);
                on_collision(m_reg);
                on_move(m_reg);

                m_fElapsedTimeSinceTick = 0.0;
            }
            else
            {
                m_fElapsedTimeSinceTick += dt;
                //on_move(m_reg);
            }

            on_render_walking();
        }
        break;
        default:
            std::cout << "TYPE NOT IMPL" << std::endl;
    }
}
