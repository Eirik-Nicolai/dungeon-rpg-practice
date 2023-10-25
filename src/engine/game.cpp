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
            //NEXT_STATE.type = type::INVENTORY;
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
    if(auto vis = m_reg.try_get<visual>(ent);m_reg.try_get<visual>(ent) != nullptr)
    {
        return vis->name;
    }
    return ret;
}

void DungeonThing::set_equipment(const entt::entity &e)
{
    auto &equipment = m_reg.ctx().get<EquipmentState>();
    std::cout << get_name(e) << std::endl;
    switch (get_equipment_indx(e))
    {
        case INV_INDEX_HEAD:
            equipment.head = e;
            break;
        case INV_INDEX_TORSO:
            equipment.torso = e;
            break;
        case INV_INDEX_LEGS:
            equipment.legs = e;
            break;
        case INV_INDEX_MAINHAND:
            equipment.main_hand = e;
            break;
        case INV_INDEX_OFFHAND:
            equipment.off_hand = e;
            break;
        case INV_INDEX_NECKLACE:
            equipment.jewellery_necklace = e;
            break;
        case INV_INDEX_FINGERLEFT:
            equipment.jewellery_finger_left = e;
            break;
        case INV_INDEX_FINGERRIGHT:
            equipment.jewellery_finger_right = e;
            break;
        case INV_INDEX_EARS:
            equipment.jewellery_ears = e;
            break;
        default:
            throw std::runtime_error("equipment indx not recognised");
    }
}

int DungeonThing::get_equipment_indx(const entt::entity &e)
{
    if(m_reg.all_of<_helmet>(e))
        return INV_INDEX_HEAD;
    if(m_reg.all_of<_legs>(e))
        return INV_INDEX_LEGS;
    if(m_reg.all_of<_torso>(e))
        return INV_INDEX_HEAD;
    if(m_reg.all_of<_main_hand>(e))
        return INV_INDEX_HEAD;
    if(m_reg.all_of<_off_hand>(e))
        return INV_INDEX_HEAD;
    if(m_reg.all_of<_accessory_head>(e))
        return INV_INDEX_HEAD;
    if(m_reg.all_of<_accessory_hand>(e))
        return INV_INDEX_HEAD;
    return -1;
}

int DungeonThing::get_percentage(int part, int whole)
{
    return 100*((float)part/(float)whole);
}
