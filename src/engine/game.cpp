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

    m_current_selected_equipment_type = 0;
    m_equip_finger_left = false;
    m_equip_head_left = false;

    TextItemOnSelect resume{
        "RESUME",
        [&]{
            NEXT_STATE.state = state::WALKING;
            NEXT_STATE.type = type::FREEROAM;
        }
    };
    TextItemOnSelect inventory{
        "INVENTORY",
        [&]{
            m_curr_menu = 1;
            NEXT_STATE.type = type::INIT_INVENTORY;
        }
    };
    TextItemOnSelect equipment{
        "EQUIPMENT",
        [&]{
            // TODO menu list of equipment types
            // and then list of currently held items
            //m_curr_menu = 2;

            NEXT_STATE.type = type::EQUIPMENT;
        }
    };
    TextItemOnSelect othershit{
        "SOME OTHER SHIT",
        []{
            std::cout << "SOME SHIT NOT IMPL" << std::endl;
        }
    };
    m_pausemenus.emplace_back(PauseMenu(resume, inventory, equipment, othershit));

    TextItemOnSelect USE{
        "USE ITEM",
        [&]{
            std::cout << "USE ITEM NOT IMPL" << std::endl;
        }
    };
    TextItemOnSelect INSPECT{
        "INSPECT",
        [&]{
            std::cout << "INSPECT NOT IMPL" << std::endl;
        }
    };
    TextItemOnSelect BACK{
        "BACK",
        [&]{
            m_curr_menu = 0;
            NEXT_STATE.type = type::OVERVIEW;
        }};

    m_pausemenus.emplace_back(PauseMenu(USE, INSPECT, BACK));
    TextItemOnSelect EQUIP{
        "EQUIP ITEM",
        [&]{
            std::cout << "EQUIP ITEM NOT IMPL" << std::endl;
        }
    };
    TextItemOnSelect INFO{
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

std::string DungeonThing::get_name(const entt::entity &ent, std::string ret)
{
    visual v;
    if(tryget_component(ent, v))
    {
        return v.name;
    }
    return ret;
}

void DungeonThing::set_equipment(const entt::entity &e)
{
    auto &equipment = m_reg.ctx().get<EquipmentState>();
    switch (get<equipment_type>(e).type)
    {
        case equiptype::HEAD:
            equipment.head = e;
            break;
        case equiptype::TORSO:
            equipment.torso = e;
            break;
        case equiptype::LEGS:
            equipment.legs = e;
            break;
        case equiptype::MAINHAND:
            equipment.main_hand = e;
            break;
        case equiptype::OFFHAND:
            equipment.off_hand = e;
            break;
        case equiptype::ACCESS_FINGER:
            if(m_equip_finger_left)
                equipment.jewellery_finger_left = e;
            else
                equipment.jewellery_finger_right = e;
            break;
        case equiptype::ACCESS_HEAD:
            if(m_equip_head_left)
                equipment.jewellery_finger_right = e;
            else
                equipment.jewellery_finger_right = e;
            break;
        default:
            throw std::runtime_error("equipment indx not recognised");
    }
}

int DungeonThing::get_percentage(int part, int whole)
{
    return 100*((float)part/(float)whole);
}
