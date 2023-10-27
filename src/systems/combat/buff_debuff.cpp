#include "buff_debuff.hpp"

void on_buff_debuff(entt::registry &reg)
{

}

// FIXME see on update stats in initialize
// we just keep it simple for now
void on_debuff_gone(entt::registry &reg, entt::entity &owner, entt::entity &debuff)
{
    if(reg.all_of<force_modifier>(debuff))
    {
        auto mod = reg.get<force_modifier>(debuff).amount;
        reg.patch<force>(owner, [&](auto &f){
            f.curr = f.max;
        });
    }
    else if(reg.all_of<force_modifier>(debuff))
    {
        auto mod = reg.get<mind_modifier>(debuff).amount;
        reg.patch<mind>(owner, [&](auto &m){
            m.curr = m.max;
        });
    }
    else if(reg.all_of<force_modifier>(debuff))
    {
        auto mod = reg.get<armour_modifier>(debuff).amount;
        reg.patch<armour>(owner, [&](auto &a){
            a.curr = a.max;
        });
    }
    else if(reg.all_of<force_modifier>(debuff))
    {
        auto mod = reg.get<willpower_modifier>(debuff).amount;
        reg.patch<willpower>(owner, [&](auto &w){
            w.curr = w.max;
        });
    }
    else if(reg.all_of<_invincibility>(debuff))
    {
        reg.patch<armour>(owner, [&](auto &a){
            a.curr = a.max;
        });
        reg.patch<willpower>(owner, [&](auto &w){
            w.curr = w.max;
        });
    }
}

void on_buff_debuff_enemy(entt::registry &reg, enemies &enemies)
{
    auto affected_targets = reg.view<affected>();
    std::vector<entt::entity> stay;
    for(auto [ent, aff] : affected_targets.each())
    {
        stay.clear();
        for(auto dent : aff.effects)
        {
            stay.emplace_back(dent);
            if(reg.all_of<damage>(dent))
            {
                auto dmg = reg.get<damage>(dent);
                reg.patch<health>(ent, [&](auto &h){
                    h.curr -= dmg.amount;
                });

            }
            if(reg.all_of<tick>(dent))
            {
                reg.patch<tick>(dent, [&](auto &t){
                    t.rounds--;
                    if(t.rounds<=0)
                    {
                        stay.pop_back();
                        on_debuff_gone(reg, ent, dent);
                    }
                });
            }
        }
        aff.effects = stay;
    }

}

//FIXME need a better way of dealing with things like stat decreases and so on
//FIXME have a think about debuffs applying before/during/after combat actions
void on_buff_debuff_ally(entt::registry &reg, allies &allies)
{
    auto affected_targets = reg.view<_enemy, affected>();
    std::vector<entt::entity> stay;
    for(auto [ent, aff] : affected_targets.each())
    {
        stay.clear();
        for(auto dent : aff.effects)
        {
            stay.emplace_back(dent);
            if(reg.all_of<damage>(dent))
            {
                auto dmg = reg.get<damage>(dent);
                reg.patch<health>(ent, [&](auto &h){
                    h.curr -= dmg.amount;
                });

            }
            if(reg.all_of<tick>(dent))
            {
                reg.patch<tick>(dent, [&](auto &t){
                    t.rounds--;
                    if(t.rounds<0)
                    {
                        stay.pop_back();
                        on_debuff_gone(reg, ent, dent);
                    }
                });
            }
        }
    }
}
