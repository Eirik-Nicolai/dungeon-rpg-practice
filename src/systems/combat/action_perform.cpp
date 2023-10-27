#include "action_perform.hpp"

// FIXME clean up the arguments and streamline it a bit

void on_perform_action(entt::registry &reg, entt::entity &actor, entt::entity &target, entt::entity &action)
{
    //std::cout << "target" << std::endl;
    if(reg.all_of<damage>(action))
    {
        auto dmg = reg.get<damage>(action);
        int actual_dmg;
        switch(dmg.type)
        {
            case dmg_type::PHYSICAL:
                actual_dmg = calculate_damage_phys(reg, actor, dmg);
                calculate_resist_phys(reg, target, actual_dmg);
                break;
            case dmg_type::MAGICAL:
                actual_dmg = calculate_damage_magi(reg, actor, dmg);
                calculate_resist_magi(reg, target, actual_dmg);
                break;
            case dmg_type::PURE:
                actual_dmg = dmg.amount;
                break;
        }

        reg.patch<health>(target, [&](auto &h){
            h.curr -= actual_dmg;
        });
        on_check_target_death(reg, actor, target);
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
//TODO clean up
int calculate_damage_phys(entt::registry &reg, entt::entity &actor, damage& dmg)
{
    // get damage with actor multiplier
    auto [max, curr] = reg.get<force>(actor);
    int given_damage = dmg.amount + (dmg.amount*get_percentage(curr,10)); // effectively every 1 point of stat
                                                    // increases dmg by 10%
    given_damage *= get_raw_dmg_multiplier(reg, actor, dmg.type);

    return given_damage;
}

int calculate_damage_magi(entt::registry &reg, entt::entity &actor, damage& dmg)
{
    // get damage with actor multiplier
    auto [max, curr] = reg.get<mind>(actor);
    int given_damage = dmg.amount + (dmg.amount*get_percentage(curr, 100)); // effectively every 1 point of stat
                                                     // increases dmg by 1%
    given_damage *= get_raw_dmg_multiplier(reg, actor, dmg.type);

    return given_damage;
}

void calculate_resist_phys(entt::registry &reg, entt::entity &target, int& dmg)
{
    dmg *= get_raw_dmg_multiplier(reg, target, dmg_type::PHYSICAL);
        if(reg.all_of<force>(target))
        dmg-=std::max(0,reg.get<force>(target).curr);
    if(reg.all_of<armour>(target))
        dmg-=std::max(0,reg.get<armour>(target).curr);
}

void calculate_resist_magi(entt::registry &reg, entt::entity &target, int& dmg)
{
    dmg *= get_raw_dmg_multiplier(reg, target, dmg_type::MAGICAL);
    if(reg.all_of<mind>(target))
        dmg-=std::max(0,(reg.get<mind>(target).curr/2)); // no negative damage values
    if(reg.all_of<willpower>(target))
        dmg-=std::max(0,reg.get<willpower>(target).curr);
}

float get_raw_dmg_multiplier(entt::registry &reg, entt::entity &actor, dmg_type type)
{
    float multiplier = 1.0;
    auto eff = reg.get<affected>(actor).effects;
    for(auto e : eff)
    {
        if(reg.all_of<dmg_modifier>(e))
        {
            switch (reg.get<dmg_modifier>(e).type)
            {
                case dmg_type::PHYSICAL:
                    if(type==dmg_type::PHYSICAL)
                        multiplier *= reg.get<dmg_modifier>(e).amount;
                    break;
                case dmg_type::MAGICAL:
                    if(type==dmg_type::MAGICAL)
                        multiplier *= reg.get<dmg_modifier>(e).amount;
                    break;
                default:
                    multiplier *= reg.get<dmg_modifier>(e).amount;
            }
        }
        if(reg.all_of<_invincibility>(e)) //TODO if i have invinsible i deal 0 damage
        {
            return 0.0;
        }
    }
    return multiplier;
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

void on_check_target_death(entt::registry &reg, entt::entity &actor, entt::entity &target)
{

}


void on_perform_action_update_resource(entt::registry &reg, entt::entity &actor, entt::entity &action)
{
    if(reg.all_of<cost>(action))
    {
        auto c = reg.get<cost>(action);
        switch(c.type)
        {
            case resource_type::MANA:
            {
                if(reg.all_of<mana>(actor))
                {
                    auto &m = reg.get<mana>(actor);
                    m.curr -= c.amount;
                }
            }
            break;
            case resource_type::HEALTH:
            {
                if(reg.all_of<health>(actor))
                {
                    auto &h = reg.get<health>(actor);
                    h.curr -= c.amount;
                }
            }
            break;
            default:
                std::cout << "RESOURCE TYPE NOT IMPL" << std::endl;
        }
    }

}
