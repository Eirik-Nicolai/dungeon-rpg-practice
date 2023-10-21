#ifndef COMP_GLOBALS_H_
#define COMP_GLOBALS_H_

#include <cstdint>
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

struct InventoryState{};
struct EquipmentState{};

//FIXME maybe move movequeue to here
struct CombatState
{
    int selection;
};

#endif // COMB_GLOBALS_H_
