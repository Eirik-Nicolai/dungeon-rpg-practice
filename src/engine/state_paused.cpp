#include "game.hpp"
#include "utils/globals.hpp"


void DungeonThing::STATE_PAUSE(float dt)
{
    switch(CURR_STATE.type)
    {
        case type::INIT_PAUSED:
        {
            Debugger::instance()+="STATE: INIT_PAUSED";
            // TODO save curr state ?

            // TODO init entities used for combat
            m_transition_progress = 0.0;
            m_elapsed_transition_time = 0.0f;
            NEXT_STATE.type = type::OVERVIEW;;
        }
        break;
        case type::OVERVIEW:
        {
            Debugger::instance()+="STATE: OVERVIEW";
            on_userinput_paused();
            on_render_paused();
        }
        break;
        case type::INVENTORY:
        {
            Debugger::instance()+="STATE: INVENTORY";
            on_userinput_paused();
            on_render_paused();

        }
        break;
        case type::EQUIPMENT:
        {
            Debugger::instance()+="STATE: EQUIPMENT";
            on_userinput_paused();
            on_render_paused();
        }
        break;
        case type::ITEM_SELECTED:
        {
            Debugger::instance()+="STATE: ITEM_SELECTED";

        }
        break;
        default:
            std::cout << "TYPE NOT IMPL" << std::endl;
    }
}
