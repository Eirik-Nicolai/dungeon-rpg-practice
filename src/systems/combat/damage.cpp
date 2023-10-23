#include "damage.hpp"


void on_damage(entt::registry &reg, entt::entity &actor, entt::entity &target, entt::entity &action)
{

    //std::cout << "target" << std::endl;
    if(reg.all_of<damage>(action))
    {
        auto dmg = reg.get<damage>(action);
        auto actual_dmg = get_actual_damage(dmg.amount, reg, actor, target);
        reg.patch<health>(target, [&](auto &h){
            h.curr -= actual_dmg;
        });
    }

    if(reg.all_of<adds_debuff>(action))
    {
        apply_debuff(reg, reg.get<adds_debuff>(action).debuff, target);
    }
}

int get_actual_damage(int &amount, entt::registry &reg, entt::entity &actor, entt::entity &target)
{
    // get damage with actor multiplier
    auto [atk, mind] = reg.get<stats>(actor);
    int given_damage = amount + (amount*(atk/100));
    // reduce damage by target armour
    auto arm = reg.get<armour>(target).curr;
    int taken_damage = given_damage - arm; // FIXME need better formula
    return taken_damage;
}

void apply_debuff(entt::registry &reg, entt::entity &debuff, entt::entity &target)
{
    auto &aff = reg.get<affects>(debuff);
    aff.targets.emplace_back(target);

}
