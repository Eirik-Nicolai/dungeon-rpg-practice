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
            // m_equipment_menu = EquipmentMenu([&]{
            //     NEXT_STATE.type = type::ITEM_SELECTED;
            // });
            // m_equipment_menu.AddItemLeft(TextItemOnScroll{
            //     get_name(equipment.jewellery_necklace, "No necklace"),
            //     [&](){
            //         m_equip_head_left = true;
            //         return equiptype::ACCESS_HEAD;

            //     }});
            // m_equipment_menu.AddItemLeft(TextItemOnScroll{
            //     get_name(equipment.main_hand, "No main hand"),
            //     [&](){
            //         return equiptype::MAINHAND;
            //     }});
            // m_equipment_menu.AddItemLeft(TextItemOnScroll{
            //     get_name(equipment.jewellery_finger_left, "No left finger"),
            //     [&](){
            //         m_equip_finger_left = true;
            //         return equiptype::ACCESS_FINGER;
            //     }});
            // m_equipment_menu.AddItemMiddle(TextItemOnScroll{
            //     get_name(equipment.head, "No headpiece"),
            //     [&](){
            //         return equiptype::HEAD;
            //     }});
            // m_equipment_menu.AddItemMiddle(TextItemOnScroll{
            //     get_name(equipment.torso, "No torso"),
            //     [&](){
            //         return  equiptype::TORSO;
            //     }});
            // m_equipment_menu.AddItemMiddle(TextItemOnScroll{
            //     get_name(equipment.legs, "No trousers"),
            //     [&](){
            //         return  equiptype::LEGS;
            //     }});
            // m_equipment_menu.AddItemRight(TextItemOnScroll{
            //     get_name(equipment.jewellery_ears, "No ear piece"),
            //     [&](){
            //         m_equip_head_left = false;
            //         return  equiptype::ACCESS_HEAD;
            //     }});
            // m_equipment_menu.AddItemRight(TextItemOnScroll{
            //     get_name(equipment.off_hand, "No offhand"),
            //     [&](){
            //         return  equiptype::OFFHAND;
            //     }});
            // m_equipment_menu.AddItemLeft(TextItemOnScroll{
            //     get_name(equipment.jewellery_finger_right, "No right finger"),
            //     [&](){
            //         m_equip_finger_left = false;
            //         return equiptype::ACCESS_FINGER;
            //     }});

            m_transition_progress = 0.0;
            m_elapsed_transition_time = 0.0f;
            NEXT_STATE.type = type::OVERVIEW;
        }
        break;
        case type::OVERVIEW:
        {
            Debugger::instance()+="STATE: OVERVIEW";
            on_userinput_paused();
            on_render_paused();
        }
        break;
        case type::INIT_INVENTORY:
        {
            Debugger::instance()+="STATE: INIT_INVENTORY";
            auto inventory = m_reg.ctx().get<InventoryState>();
            //m_inventory_list.insert(m_inventory_list.end(),inv.equipables[i].begin(), inv.equipables[i].end());
            std::vector<MenuItem<entt::entity, entt::entity>> inventory_items;
            for(int i = 0; i < NUM_EQUIPTYPES; ++i)
            {
                for(auto item : inventory.equipables[i])
                {
                    inventory_items.emplace_back(
                        MenuItem<entt::entity, entt::entity>{
                        .content = item,
                        .info = get<visual>(item).name,
                        .select_cmd = [&](){
                            // TODO do something with item or w/e
                            return item;
                        },
                    });
                }
            }
            m_inventory_menu = ScrollableMenu(inventory_items, 5);
            MenuItem<std::string, void> use{
            "USE",
            "",
            [&]{
                // TODO menu list of equipment types
                // and then list of currently held items
                //m_curr_menu = 2;

                NEXT_STATE.type = type::EQUIPMENT;
            }};
            MenuItem<std::string, void> othershit{
            "SOME OTHER SHIT",
            "",
            []{
                std::cout << "SOME SHIT NOT IMPL" << std::endl;
            }};
            //m_pause_menu = ScrollableMenu();

            NEXT_STATE.type = type::INVENTORY;
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
            Debugger::instance()+="STATE: ITEM_SELECTED";
            auto inv = m_reg.ctx().get<InventoryState>();
            m_inventory_list = inv.equipables[m_current_selected_equipment_type];
            // m_inventory_menu = InventoryMenu();
            // for(auto e : m_inventory_list)
            // {
            //     m_inventory_menu.AddItem(TextItemOnSelect{
            //         get_name(e),
            //         [=](){
            //             set_equipment(e);

            //             NEXT_STATE.type = type::INIT_PAUSED;
            //         }});
            // }
            NEXT_STATE.type = type::INVENTORY;
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
