#ifndef COMBAT_H_
#define COMBAT_H_

#include <vector>
#include <string>

#include <entt/entt.hpp>

struct combat_moves
{

};


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

struct ability
{
    int mana_cost;
    std::string name;
};

struct pound : ability
{};

struct poison : public ability
{
    int tick_dmg;
};

struct ability_list{
    std::vector<ability> list;
};

#endif // COMBAT_H_
