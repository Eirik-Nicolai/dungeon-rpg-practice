#include "buff_debuff.hpp"

void on_buff_debuff(entt::registry &reg)
{

}

void on_buff_debuff_enemy(entt::registry &reg, enemies &enemies)
{

}

//FIXME need a better way of dealing with things like stat decreases and so on
//FIXME have a think about debuffs applying before/during/after combat actions
void on_buff_debuff_ally(entt::registry &reg, allies &allies)
{
    auto debuffs = reg.view<_debuff, affects>();
    std::queue<entt::entity> to_be_removed;
    for(auto [dent, aff] : debuffs.each())
    {
        if(reg.all_of<damage>(dent))
        {
            auto dmg = reg.get<damage>(dent);
            for(auto t : aff.targets)
            {
                reg.patch<health>(t, [&](auto &h){
                    h.curr -= dmg.amount;
                });
            }
        }
        if(reg.all_of<tick>(dent))
        {
            reg.patch<tick>(dent, [&](auto &t){
                t.rounds--;
                if(t.rounds<0)
                    to_be_removed.emplace(dent);
            });
        }
    }

    while(!to_be_removed.empty())
    {
        //FIXME need to tick per thing debuffed not debuff itself
        //maybe reverse debuff/target relationship

        to_be_removed.pop();
    }
}
