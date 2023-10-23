#ifndef COMP_GLOBALS_H_
#define COMP_GLOBALS_H_

#include <cstdint>
#include <entt/entt.hpp>
// struct TransitionState
// {
//     float m_transition_progress;
//     float m_transition_acc;
//     float m_transition_time;
//     float m_elapsed_transition_time;
// };
struct MenuState
{
    int m_curr_menu;
};

struct PlayerState
{
    uint8_t level;
    uint8_t exp;
};

struct InventoryState{
    entt::entity consumables;
    entt::entity equipables;;
    entt::entity other;
};
struct EquipmentState{
    entt::entity head;
    entt::entity torso;
    entt::entity legs;
    entt::entity main_hand;
    entt::entity off_hand;
    entt::entity jewellery_finger;
    entt::entity jewellery_ears;
};

//FIXME maybe move movequeue to here
struct CombatState
{
    int selection;
};

#endif // COMB_GLOBALS_H_
