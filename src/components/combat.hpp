#ifndef COMBAT_H_
#define COMBAT_H_

#include <vector>
#include <string>
#include <list>

#include <entt/entt.hpp>


namespace combat
{
    struct pos
    {
        int x;
        int y;
    };
};

struct _enemy{};
struct _ally{};

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

struct armour {
    int curr;
    int max;
};

struct stats{
    int atk;
    int mind;
};

struct _action
{};

struct _debuff{};
struct _buff{};

struct tick{
    int rounds;
};

struct weakness{
    int amount;
};

struct fatigue{
    int amount;
};

struct affects{
    std::vector<entt::entity> targets; //FIXME should be list or smth
};

struct has_action{
    entt::entity action;
};

struct heal{
    int amount;
};

struct damage{
    int amount;
};

struct cost{
    int mana;
    int health;
    int other;
};

struct visual{
    std::string name;
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


#endif // COMBAT_H_
