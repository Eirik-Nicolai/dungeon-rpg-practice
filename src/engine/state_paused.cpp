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
            using equipmentitem = MenuItem<entt::entity, void>;
            auto equipment = m_reg.ctx().get<EquipmentState>();
            std::vector<equipmentitem> equipment_l;
            std::vector<equipmentitem> equipment_m;
            std::vector<equipmentitem> equipment_r;


            equipment_l.emplace_back(equipmentitem{
                .content = equipment.necklace,
                .info = get_name(equipment.necklace, "No necklace"),
                .select_cmd = [=](){
                    //return equipment.necklace;
                },
                .scroll_cmd = [=](){
                    m_equip_head_left = true;
                    //return equipment.necklace;

                },
            });
            equipment_l.emplace_back(equipmentitem{
                .content = equipment.main_hand,
                .info = get_name(equipment.main_hand, "No main hand"),
                .select_cmd = [=](){
                    //return equipment.main_hand;
                },
                .scroll_cmd = [=](){
                    //return equipment.main_hand;
                },
            });
            equipment_l.emplace_back(equipmentitem{
                .content = equipment.finger_left,
                .info = get_name(equipment.finger_left, "No left finger"),
                .select_cmd = [=](){
                    //return equipment.finger_left;
                },
                .scroll_cmd = [=](){
                    //return equipment.finger_left;
                },
            });
            equipment_m.emplace_back(equipmentitem{
                .content = equipment.head,
                .info = get_name(equipment.head, "No headpiece"),
                .select_cmd = [=](){
                    //return equipment.head;
                },
                .scroll_cmd = [=](){
                    //return equipment.head;

                },
            });
            equipment_m.emplace_back(equipmentitem{
                .content = equipment.torso,
                .info = get_name(equipment.torso, "No torso"),
                .select_cmd = [=](){
                    //return equipment.head;
                },
                .scroll_cmd = [=](){
                    //return equipment.head;

                },
            });
            equipment_m.emplace_back(equipmentitem{
                .content = equipment.legs,
                .info = get_name(equipment.legs, "No legs"),
                .select_cmd = [=](){
                    //return equipment.jewellery_necklace;
                },
                .scroll_cmd = [=](){
                    //return equipment.jewellery_necklace;

                },
            });
            equipment_r.emplace_back(equipmentitem{
                .content = equipment.ears,
                .info = get_name(equipment.ears, "No earring"),
                .select_cmd = [=](){
                    //return equipment.jewellery_necklace;
                },
                .scroll_cmd = [=](){
                    //return equipment.jewellery_necklace;

                },
            });
            equipment_r.emplace_back(equipmentitem{
                .content = equipment.off_hand,
                .info = get_name(equipment.off_hand, "No offhand"),
                .select_cmd = [=](){
                    //return equipment.jewellery_necklace;
                },
                .scroll_cmd = [=](){
                    //return equipment.jewellery_necklace;

                },
            });
            equipment_r.emplace_back(equipmentitem{
                .content = equipment.finger_right,
                .info = get_name(equipment.finger_right, "No right finger"),
                .select_cmd = [=](){
                    //return equipment.jewellery_necklace;
                },
                .scroll_cmd = [=](){
                    //return equipment.jewellery_necklace;

                },
            });
            m_equipment_menu = EquipmentMenu(equipment_l, equipment_m, equipment_r);
            std::cout << "loading things" << std::endl;

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
                        .select_cmd = [=](){
                            // TODO do something with item or w/e
                            return item;
                        },
                        .scroll_cmd = [=](){
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
            // m_inventory_list = inv.equipables[m_current_selected_equipment_type];
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
            // Debugger::instance()+="selected: " + std::to_string(m_current_selected_equipment_type);
            on_userinput_paused();
            on_render_paused();
        }
        break;
        default:
            std::cout << "TYPE NOT IMPL" << std::endl;
    }
}
