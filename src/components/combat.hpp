#ifndef COMBAT_H_
#define COMBAT_H_

#include <vector>
#include <string>
#include <list>

#include <entt/entt.hpp>



//FIXME clean up and move to diff files for better overview

namespace combat
{
    struct pos
    {
        int x;
        int y;
    };
};

struct target{};

struct _enemy{};
struct _ally {};

struct _selected{};

struct pet{
    entt::entity owner;
};

struct health {
    int curr;
    int max;
};

struct mana {
    int curr;
    int max;
};

// physical def
struct armour {
    int curr;
    int max;
};

//magical def
struct willpower {
    int curr;
    int max;
};

struct force{
    int curr; //physical
    int max;  //magical
};

struct mind{
    int curr; //physical
    int max;  //magical
};

struct _action
{};

struct action_children{
    std::vector<entt::entity> children;
};

struct _debuff{};
struct _buff{};

struct tick{
    int rounds;
};

struct force_modifier{
    float amount;
};
struct force_adder{
    int amount;
};

struct mind_modifier{
    float amount;
};
struct mind_adder{
    int amount;
};

struct armour_modifier{
    float amount;
};
struct armour_adder{
    int amount;
};

struct willpower_modifier{
    float amount;
};
struct willpower_adder{
    int amount;
};

struct dmg_modifier{
    float amount;
};

struct _invincibility{};

struct affected{
    std::vector<entt::entity> effects; //FIXME should be list or smth
};

struct has_action{
    entt::entity action;
};

struct heal{
    int amount;
};

enum class dmg_type {MAGICAL, PHYSICAL, PURE};

struct damage{
    int amount;
    dmg_type type;
};

struct cost{
    int mana;
    int health;
    int other;
};

struct adds_debuff{
    entt::entity debuff;
};
struct adds_buff{
    entt::entity debuff;
};

struct combat_action{
    entt::entity action;
    entt::entity target;
};

struct _skill{};

// removes every debuff on target
struct _cleanse{};

// summons creature defined by other components
struct _summon{};



#endif // COMBAT_H_
