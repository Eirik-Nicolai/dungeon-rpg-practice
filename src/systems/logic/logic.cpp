#include "logic.hpp"

void on_logic(entt::registry &reg)
{
    if(NEW_GAME_STATE != state::NONE)
    {
        on_gamestate_change(reg);
    }

    switch (GAME_STATE)
    {
        case state::WALKING:
        {
            on_input_walking(reg);


            on_ai(reg);


            on_move(reg);
            break;
        }

        case state::PAUSED:
        {
            //Debug::Log("Game paused!", 0, 10);
            //on_input_menu(reg);

            break;
        }

        case state::TRANSITION:
        {
            bool done_factoring = true;
            // auto renderview = reg.view<window, transitioning>();
            // for(auto [ent, w, t]: renderview.each())
            // {
            //     w.h = w.h * t.factor;
            //     w.y = w.y + w.h;
            //     t.factor += 0.1;
            //     if (t.factor >= 1)
            //     {
            //         done_factoring = true;
            //     }

            // }
            if(done_factoring)
            {
                GAME_STATE = NEW_GAME_STATE;
                NEW_GAME_STATE = state::NONE;
            }
            break;
        }

        default:
            std::cout << "UNDEFINED STATE" << std::endl;
        break;
    }
}


void on_gamestate_change(entt::registry &reg)
{
    switch (NEW_GAME_STATE)
    {
        case state::WALKING:
        {
            Debug::Log("WALKING", 0, 1);
            break;
        }

        case state::PAUSED:
        {
            Debug::Log("PAUSE", 0, 2);

            // on_pause_transition_start(reg);
            GAME_STATE = state::TRANSITION;

            auto view = reg.view<window>();
            for (auto [ent, w]: view.each())
            {
                if(w.id == MENUWINDOW)
                {
                    reg.emplace_or_replace<_isactive>(ent);
                }
            }

            break;
        }

        case state::TRANSITION:
        {
            Debug::Log("TRANSITION", 0, 3);
        }

        default:
            std::cout << "UNDEFINED STATE" << std::endl;
        break;
    }
}
