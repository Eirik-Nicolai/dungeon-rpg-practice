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
        [&]{
            NEXT_STATE.state = state::WALKING;
            NEXT_STATE.type = type::FREEROAM;
        }
    };
    TextItem inventory{
        "INVENTORY",
        [&]{
            m_curr_menu = 1;
            NEXT_STATE.type = type::INVENTORY;
        }
    };
    TextItem equipment{
        "EQUIPMENT",
        [&]{
            // TODO menu list of equipment types
            // and then list of currently held items
            m_curr_menu = 2;
            NEXT_STATE.type = type::EQUIPMENT;
        }
    };
    TextItem othershit{
        "SOME OTHER SHIT",
        []{
            std::cout << "SOME SHIT NOT IMPL" << std::endl;
        }
    };
    m_pausemenus.emplace_back(PauseMenu(resume, inventory, equipment, othershit));

    TextItem USE{
        "USE ITEM",
        [&]{
            std::cout << "USE ITEM NOT IMPL" << std::endl;
        }
    };
    TextItem INSPECT{
        "INSPECT",
        [&]{
            std::cout << "INSPECT NOT IMPL" << std::endl;
        }
    };
    TextItem BACK{
        "BACK",
        [&]{
            m_curr_menu = 0;
            NEXT_STATE.type = type::OVERVIEW;
        }};

    m_pausemenus.emplace_back(PauseMenu(USE, INSPECT, BACK));
    TextItem EQUIP{
        "EQUIP ITEM",
        [&]{
            std::cout << "EQUIP ITEM NOT IMPL" << std::endl;
        }
    };
    TextItem INFO{
        "INFO",
        [&]{
            std::cout << "INFO NOT IMPL" << std::endl;
        }};
    m_pausemenus.emplace_back(PauseMenu(EQUIP, INFO, BACK));

}

bool DungeonThing::OnUserCreate()
{
    on_load_init();

    CURR_STATE = {GameState::state::PAUSED, GameStateType::type::INIT_PAUSED};
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
            STATE_PAUSE(dt);
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

    Debugger::instance().Print(this, 0.80, 0.80);
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

std::string DungeonThing::get_name(entt::entity &ent)
{
    if(auto vis = m_reg.try_get<visual>(ent);m_reg.try_get<visual>(ent) != nullptr)
    {
        return vis->name;
    }
    return "UNNAMED_ENTITY";
}


int DungeonThing::get_percentage(int part, int whole)
{
    return 100*((float)part/(float)whole);
}
