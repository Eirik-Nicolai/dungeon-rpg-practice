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

            auto equipment = m_reg.ctx().get<EquipmentState>();

            // TODO accessories can be equiped multiple places
            // figure out a way to implement this
            m_equipment_menu = EquipmentMenu([&]{
                NEXT_STATE.type = type::ITEM_SELECTED;
            });
            m_equipment_menu.AddItemLeft(TextItemOnScroll{
                get_name(equipment.jewellery_necklace, "No necklace"),
                [&](){
                    return INV_INDEX_NECKLACE;

                }});
            m_equipment_menu.AddItemLeft(TextItemOnScroll{
                get_name(equipment.main_hand, "No main hand"),
                [&](){
                    return INV_INDEX_MAINHAND;
                }});
            // m_equipment_menu.AddItemLeft(TextItemOnScroll{
            //     get_name(equipment.head),
            //     [&](){
            //         m_current_selected_equipment_type = equipment.head;
            //         NEXT_STATE.type = type::ITEM_SELECTED;
            //     }});
            m_equipment_menu.AddItemMiddle(TextItemOnScroll{
                get_name(equipment.head, "No headpiece"),
                [&](){
                    return INV_INDEX_HEAD;
                }});
            m_equipment_menu.AddItemMiddle(TextItemOnScroll{
                get_name(equipment.torso, "No torso"),
                [&](){
                    return  INV_INDEX_TORSO;
                }});
            m_equipment_menu.AddItemMiddle(TextItemOnScroll{
                get_name(equipment.legs, "No trousers"),
                [&](){
                    return  INV_INDEX_LEGS;
                }});
            m_equipment_menu.AddItemRight(TextItemOnScroll{
                get_name(equipment.jewellery_ears, "No ear piece"),
                [&](){
                    return  INV_INDEX_EARS;
                }});
            m_equipment_menu.AddItemRight(TextItemOnScroll{
                get_name(equipment.off_hand, "No offhand"),
                [&](){
                    return  INV_INDEX_OFFHAND;
                }});


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
            //std::cout << "invnentory" << std::endl;
            Debugger::instance()+="STATE: INVENTORY";
            on_userinput_paused();
            on_render_paused();

        }
        break;
        case type::ITEM_SELECTED:
        {
            std::cout << "Item seelcted state" << std::endl;
            Debugger::instance()+="STATE: ITEM_SELECTED";
            auto inv = m_reg.ctx().get<InventoryState>();
            m_inventory_list = inv.equipables[m_current_selected_equipment_type];
            m_inventory_menu = InventoryMenu();
            for(auto e : m_inventory_list)
            {
                m_inventory_menu.AddItem(TextItemOnSelect{
                    get_name(e),
                    [=](){
                        set_equipment(e);
                        NEXT_STATE.type = type::INIT_PAUSED;
                    }});
            }
            NEXT_STATE.type = type::INVENTORY;
        }
        break;
        // TODO change state to just be inventory
        // since that's what this really is
        case type::CHANGING_EQUIPMENT:
        {
            //std::cout << "chanign equipent" << std::endl;
            Debugger::instance()+="STATE: CHANGING EQUIPMENT";
            Debugger::instance()+="selected " + std::to_string(m_inventory_menu.curr_selected);
            on_userinput_paused();
            on_render_paused();
        }
        break;
        case type::EQUIPMENT:
        {
            //std::cout << "equipent" << std::endl;
            Debugger::instance()+="STATE: EQUIPMENT";
            Debugger::instance()+="selected: " + std::to_string(m_current_selected_equipment_type);
            on_userinput_paused();
            on_render_paused();
        }
        break;
        default:
            std::cout << "TYPE NOT IMPL" << std::endl;
    }
}
