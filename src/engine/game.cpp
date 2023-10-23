#define OLC_PGE_APPLICATION
#include "game.hpp"

DungeonThing::DungeonThing()
{
    sAppName = "";
    m_curr_menu = 0;
    m_transition_time = 2;
    m_transition_progress = 0;
    m_transition_acc = 5;
    m_elapsed_transition_time = 1;

    TextItem resume{
        "RESUME",
        [this]{
            NEXT_STATE = {state::WALKING, type::FROM_PAUSED_TRANSITION};
        }
    };
    TextItem options{
        "OPTIONS",
        []{
            std::cout << "OPTIONS NOT IMPL" << std::endl;
        }
    };
    TextItem exit{
        "EXIT",
        []{
            std::cout << "EXIT NOT IMPL" << std::endl;
        }
    };
    m_pausemenus.emplace_back(PauseMenu(resume, options, exit));

    TextItem fire{
    "FIRE",
    [this]{
        std::cout << "FIRE NOT IMPL" << std::endl;
    }
};
    TextItem ice{
        "ICE",
        []{
            std::cout << "ICE NOT IMPL" << std::endl;
        }
    };
    TextItem wind{
        "WIND",
        []{
            std::cout << "WIND NOT IMPL" << std::endl;
        }};
    //m_combatmenus.emplace_back(CombatMenu(fire,ice, wind));
}

bool DungeonThing::OnUserCreate()
{
    on_load_init();

    CURR_STATE = {GameState::state::WALKING, GameStateType::type::FREEROAM};
    NEXT_STATE = CURR_STATE;

    m_fElapsedTimeSinceTick = 0;

    return true;
}

bool DungeonThing::OnUserUpdate(float dt)
{
    Clear(olc::BLACK);
    Debugger::instance().Clear();

    switch(CURR_STATE.state)
    {
        case state::COMBAT:
        {
            STATE_COMBAT(dt);
        }
        break;

        case state::PAUSED:
        {
            on_userinput_paused();
            on_render_paused();
        }
        break;

        case state::WALKING:
        {
            STATE_WALKING(dt);
        }
        break;

        default:
        {
            std::cout << "not impl" << std::endl;
        }
    }

    Debugger::instance().Print(this);
    CURR_STATE = NEXT_STATE;

    return true;
}




bool DungeonThing::delay_for(float delay, float dt)
{
    if(m_elapsed_transition_time >= delay)
    {
        m_elapsed_transition_time = 0;
        return true;
    }
    m_elapsed_transition_time+= dt;
    return false;
}
