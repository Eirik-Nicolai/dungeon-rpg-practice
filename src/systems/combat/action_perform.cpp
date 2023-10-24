#include "action_perform.hpp"

// FIXME clean up the arguments and streamline it a bit

void on_perform_action(entt::registry &reg, entt::entity &actor, entt::entity &target, entt::entity &action)
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

    if(reg.all_of<heal>(action))
    {
        auto healval = reg.get<heal>(action).amount;
        auto actual_heal = healval; //TODO add calculations
        reg.patch<health>(target, [&](auto &h){
            h.curr += actual_heal;
            if(h.curr > h.max)
                h.curr = h.max;
        });
    }

    if(reg.all_of<adds_debuff>(action))
    {
        apply_debuff(reg, reg.get<adds_debuff>(action).debuff, target);
    }

    if(reg.all_of<adds_buff>(action))
    {
        apply_buff(reg, reg.get<adds_debuff>(action).debuff, target);
    }

    if(reg.all_of<_skill>(action))
    {
        on_skill(reg, actor, target, action);
    }
}

int get_actual_damage(int &amount, entt::registry &reg, entt::entity &actor, entt::entity &target)
{
    // get damage with actor multiplier
    auto [max, curr] = reg.get<force>(actor);
    int given_damage = amount + (amount*(curr/100));

    given_damage *= get_raw_dmg_multiplier(reg, actor);

    // reduce damage by target armour
    auto arm = reg.get<armour>(target).curr;
    int taken_damage = std::clamp(0, given_damage, given_damage - arm); // FIXME need better formula
    return taken_damage;
}

float get_raw_dmg_multiplier(entt::registry &reg, entt::entity &actor)
{
    auto eff = reg.get<affected>(actor).effects;
    for(auto e : eff)
    {
        if(reg.all_of<dmg_modifier>(e))
        {
            return reg.get<dmg_modifier>(e).amount;
        }
    }
}


void apply_debuff(entt::registry &reg, entt::entity &debuff, entt::entity &target)
{
    reg.patch<affected>(target, [&](auto &aff){
        for(auto e : aff.effects)
        {
            if(e == debuff) // TODO check if this works as intended
            {
                reg.get<tick>(e).rounds = reg.get<tick>(debuff).rounds;
                return; //TODO test that this works as intended
            }
        }
        aff.effects.emplace_back(debuff);
    });
}

void apply_buff(entt::registry &reg, entt::entity &buff, entt::entity &target)
{
    reg.patch<affected>(target, [&](auto &aff){
        aff.effects.emplace_back(buff);
    });
}

void on_skill(entt::registry &reg, entt::entity &actor, entt::entity &target, entt::entity &action)
{
    if(reg.all_of<_cleanse>(action))
    {
        on_skill_cleanse(reg, actor, target, action);
    }
    if(reg.all_of<_summon>(action))
    {
        on_skill_summon(reg, actor, target, action);
    }
}

void on_skill_cleanse(entt::registry &reg, entt::entity &actor, entt::entity &target, entt::entity &action)
{
    reg.patch<affected>(target, [&](auto &aff){
        std::vector<entt::entity> stay;
        for(auto e : aff.effects)
        {
            if(reg.all_of<_buff>(e))
                stay.emplace_back(e);
        }
        aff.effects = stay;
    });
}

void on_skill_summon(entt::registry &reg, entt::entity &actor, entt::entity &target, entt::entity &action)
{

}
