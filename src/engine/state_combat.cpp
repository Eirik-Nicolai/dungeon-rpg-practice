#include "game.hpp"
#include "utils/globals.hpp"

#include <vector>

#include "components/combat.hpp"
#include "components/rendering.hpp"

void DungeonThing::STATE_COMBAT(float dt)
{
    switch(CURR_STATE.type)
    {
        case type::INIT:
        {
            Debugger::instance()+="STATE: INIT";
            // TODO save curr state ?

            //FIXME needs to actually be loaded in somehow
            auto poison = m_reg.create();
            m_reg.emplace<_debuff>(poison);
            m_reg.emplace<visual>(poison, "Poison", "bro", "P");
            m_reg.emplace<damage>(poison, 5);
            m_reg.emplace<tick>(poison, 2);

            auto heavy_attack = m_reg.create();
            m_reg.emplace<visual>(heavy_attack, visual{
                .name = "HEAVY ATK",
                });
            m_reg.emplace<damage>(heavy_attack, 40);
            m_reg.emplace<adds_debuff>(heavy_attack, poison);

            auto goblin_big = create_enemy("HUGE", "V", 1000);
            m_reg.emplace<has_action>(goblin_big, heavy_attack);

            auto goblin_mage = create_enemy("small", "U", 1000);
            m_reg.emplace<armour>(goblin_mage, 1);
            m_reg.emplace<force>(goblin_mage, 0, 0);
            m_reg.emplace<mind>(goblin_mage, 20, 20);

            // find positions for multi-group enemies/allies
            //auto enemy_group = m_reg.view<_enemy>();
            auto [winx, winy] = GetWindowSize();
            auto posx_allies = winx * 0.30;
            auto posx_enemy = winx * 0.70;

            m_reg.emplace_or_replace<combat::pos>(m_player, (int)posx_allies, winy/3);
            m_reg.emplace_or_replace<combat::pos>(goblin_mage, (int)posx_enemy, winy/4);
            m_reg.emplace_or_replace<combat::pos>(goblin_big, (int)posx_enemy, winy*2/4);

            // FIXME use the view to calc based on amount of enemies
            // switch (enemy_group.size())
            // {
            //     //case 3:
            //         //auto en = *enemy_group.end();

            //     case 2:
            //         break;
            //     case 1:
            //         //m_reg.emplace_or_replace<combat::pos>(goblin_big, (int)posx_enemy, winy/3);
            //         break;
            // }

            //auto goblin_mage = m_reg.create();
            //auto goblin_reg = m_reg.create();

            // clear prev lists if any
            while(m_movequeue_player.size() > 0)
                m_movequeue_player.pop();
            while(m_movequeue_allies.size() > 0)
                m_movequeue_allies.pop();
            while(m_movequeue_enemy.size() > 0)
                m_movequeue_enemy.pop();

            //m_targetmenu.clear();


            MenuItem<bool,void> attack{
            .content = true,
            .info =    "ATTACK",
            .select_cmd = [&]{
                NEXT_STATE.type = type::LOAD_ACTIONS;
                m_curr_menu++;
            }};

            MenuItem<bool, void> skill{
            .content = true,
            .info =    "SKILL",
            .select_cmd = [&]{
                NEXT_STATE.type = type::LOAD_ACTIONS;
                m_curr_menu++;
            }};

            MenuItem<bool,void> item{
            .content = true,
            .info =    "ITEM",
            .select_cmd = [&]{
                std::cout << "ITEMS NOT IMPL" << std::endl;
            }};
            MenuItem<bool,void> item1{
            .content = true,
            .info =    "ITEM",
            .select_cmd = [&]{
                std::cout << "ITEMS NOT IMPL" << std::endl;
            }};
            auto col1 = std::vector<MenuItem<bool,void>>{attack,skill};
            auto col2 = std::vector<MenuItem<bool,void>>{item};
            m_combat_menus.emplace_back(CombatMenu(col1, col2));
            auto atkcol1 = std::vector<MenuItem<bool,void>>{};
            m_combat_menus.emplace_back(CombatMenu(atkcol1));


            MenuItem<bool,void> sk1{
            .info =    "SKILL",
            .select_cmd = [=]{
                m_intended_action = heavy_attack;
                NEXT_STATE.type = type::INIT_PLAYER_SELECTING_TARGET;
            }};

            //FIXME clean up
            std::vector<MenuItem<entt::entity, void>> enemyvec;
            std::vector<MenuItem<entt::entity, void>> allyvec;

            // for(auto [e] : enemies.each())
            // {
            // }
            auto enemies = m_reg.view<_enemy>();

            for(auto [ent] : enemies.each())
            {   //TODO we don't have arguments for funcs yet so have to copy explicitly
                auto cent = ent;
                enemyvec.emplace_back(MenuItem<entt::entity, void>{
                    .content = cent,
                    .select_cmd = [=](){
                        on_perform_action_update_resource(m_reg, m_player, m_intended_action);
                        if (m_reg.any_of<action_children>(m_intended_action))
                        {
                            auto children = m_reg.get<action_children>(m_intended_action).children;
                            for(auto a : children)
                            {
                                targets t;
                                if(!tryget_component(a, t))
                                {
                                    m_movequeue_player.emplace(combat_action{
                                        .action = a,
                                        .target = ent
                                    });
                                }
                                else
                                {
                                    m_movequeue_player.emplace(combat_action{
                                        .action = a,
                                        .target = t.who
                                    });
                                }
                            }
                        }
                        NEXT_STATE.type = type::ALLY_SELECTING_ACTION;
                    },
                    });
            }
            // for(auto [ent] : ally_targets.each())
            // {
            //     std::cout << get_name(ent) << std::endl;
            //     allyvec.emplace_back(MenuItem<entt::entity, void>{
            //         .content = ent,
            //         .select_cmd = action,
            //         });
            // }
            m_reg.ctx().emplace<CombatState>(-1);
            m_target_menu = TargetMenu(enemyvec);

            m_transition_progress = 0.0;
            m_elapsed_transition_time = 1.0;
            // TODO init entities used for combat

            NEXT_STATE.type = type::PLAYING_TRANSITION;
        }
        break;
        case type::PLAYING_TRANSITION:
        {
            Debugger::instance()+="STATE: PLAYING TRANSITION";
            // FIXME calcuate based on time to transition
            // m_transition_progress += dt * (40*m_transition_acc);
            // if(m_transition_acc > 1.0)m_transition_acc = m_transition_acc-(5.5*dt);
            if(m_transition_progress >= 100)
            {
                m_transition_progress = 0.0;
                NEXT_STATE.type = type::PLAYER_SELECTING_ACTION;
            }
            on_render_transition_combat(dt);
        }
        break;
        case type::INIT_COMBAT_ROUND:
        {
            Debugger::instance()+="STATE: INIT_COMBAT_ROUND";
            m_curr_menu = 0;
            NEXT_STATE.type = type::PLAYER_SELECTING_ACTION;
        }
        break;
        case type::PLAYER_SELECTING_ACTION:
        {
            Debugger::instance()+="STATE: PLAYER_SELECTING_ACTION";
            on_userinput_combat();
            on_render_combat();
        }
        break;
        // TODO recursive menus, load once and just check mana cost, etc
        case type::LOAD_ACTIONS:
        {
            // TODO need to figure out AOE and targeting diff tthings in one action
            auto strong = m_reg.create();
            m_reg.emplace<_buff>(strong);
            m_reg.emplace<visual>(strong, "STRONG", "s", "s");
            m_reg.emplace<dmg_modifier>(strong, 3, dmg_type::PHYSICAL);
            m_reg.emplace<tick>(strong, 1);

            auto poison = m_reg.create();
            m_reg.emplace<_debuff>(poison);
            m_reg.emplace<visual>(poison, "Poison", "bro", "P");
            m_reg.emplace<damage>(poison, 5);
            m_reg.emplace<tick>(poison, 2);

            auto get_strong = m_reg.create();
            m_reg.emplace<visual>(get_strong, "STRONG", "s", "s");
            m_reg.emplace<targets>(get_strong, m_player);
            m_reg.emplace<adds_debuff>(get_strong, strong);

            auto hit_hard = m_reg.create();
            m_reg.emplace<visual>(hit_hard, "STRONG", "s", "s");
            m_reg.emplace<damage>(hit_hard, 100, dmg_type::PHYSICAL);

            auto superpunch = m_reg.create();
            m_reg.emplace<cost>(superpunch, 80, resource_type::MANA);
            m_reg.emplace<visual>(superpunch, "superpunch");
            m_reg.emplace<action_children>(superpunch, std::vector<entt::entity>{
                get_strong,
                hit_hard
            });
            auto b = has_enough_resources(m_player, superpunch);
            MenuItem<bool,void> at1{
            .content = b,
            .info =    "HEAVY ATTACK",
            .select_cmd = [=]{
                if(b)
                {
                    m_intended_action = superpunch;
                    NEXT_STATE.type = type::INIT_PLAYER_SELECTING_TARGET;
                }
            }};

            MenuItem<bool, void> at2{
            .content = true,
            .info =    "BITCH",
            .select_cmd = [=]{
                m_intended_action = superpunch;
                NEXT_STATE.type = type::INIT_PLAYER_SELECTING_TARGET;
            }};

            MenuItem<bool, void> at3{
            .content = true,
            .info =    "CUNT",
            .select_cmd = [=]{
                m_intended_action = superpunch;
                NEXT_STATE.type = type::INIT_PLAYER_SELECTING_TARGET;
            }};

            MenuItem<bool,void> back{
            .content = true,
            .info =    "BACK",
            .select_cmd = [&]{
                --m_curr_menu;
            }};
            auto atkcol1 = std::vector<MenuItem<bool,void>>{at1, at2};
            auto atkcol2 = std::vector<MenuItem<bool,void>>{at3, back};

            m_combat_menus[1] = CombatMenu(atkcol1, atkcol2);
            NEXT_STATE.type = type::PLAYER_SELECTING_ACTION;
        }
        break;
        case type::INIT_PLAYER_SELECTING_TARGET:
        {

            NEXT_STATE.type = type::PLAYER_SELECTING_TARGET;

        }
        break;
        case type::PLAYER_SELECTING_TARGET:
        {
            Debugger::instance()+="STATE: PLAYER_SELECTING_TARGET";
            on_userinput_combat();
            on_render_combat();
        }
        break;
        case type::ALLY_SELECTING_ACTION:
        {
            Debugger::instance()+="STATE: ALLY_SELECTING_ACTION";

            if(delay_for(1, dt))
            {
                NEXT_STATE.type = type::ENEMY_SELECTING_ACTION;
            }
            on_render_combat();
        }
        break;
        case type::ENEMY_SELECTING_ACTION:
        {
            Debugger::instance()+="STATE: ENEMY_SELECTING_ACTION";
            //FIXME some sort of ai
            auto enemy_action_view = m_reg.view<_enemy, has_action>();
            for (auto [ent, act] : enemy_action_view.each())
            {
                m_movequeue_enemy.emplace(combat_action{
                    .action = act.action,
                    .target = m_player
                });
            }
            NEXT_STATE.type = type::PERFORMING_COMBAT_ACTIONS_PLAYER;
            on_render_combat();
        }
        break;
        case type::PERFORMING_COMBAT_ACTIONS_PLAYER:
        {
            Debugger::instance()+="STATE: PERFORMING_COMBAT_ACTIONS_PLAYER";

            if(m_movequeue_player.empty())
            {
                if(delay_for(1, dt))
                {
                    NEXT_STATE.type = type::PERFORMING_COMBAT_ACTIONS_ALLIES;
                }
            }
            else
            {
                if(delay_for(1, dt))
                {
                    auto [action, target] = m_movequeue_player.front();
                    on_perform_action(m_reg, m_player, target, action);
                    m_movequeue_player.pop();
                }
            }
            on_render_combat();
        }
        break;
        case type::PERFORMING_COMBAT_ACTIONS_ALLIES:
        {
            Debugger::instance()+="STATE: PERFORMING_COMBAT_ACTIONS_ALLIES";

            if(delay_for(1, dt))
            {
                NEXT_STATE.type = type::PERFORMING_COMBAT_ACTIONS_ENEMY;
            }
            on_render_combat();
        }
        break;
        case type::PERFORMING_COMBAT_ACTIONS_ENEMY:
        {
            Debugger::instance()+="STATE: PERFORMING_COMBAT_ACTIONS_ENEMY";
            if(m_movequeue_enemy.empty())
            {
                if(delay_for(1, dt))
                {
                    NEXT_STATE.type = type::PERFORMING_BUFF_DEBUFF_ACTIONS_ALLIES;
                }
            }
            else
            {
                if(delay_for(1, dt))
                {
                    auto [action, target] = m_movequeue_enemy.front();
                    on_perform_action(m_reg, m_player, target, action);
                    m_movequeue_enemy.pop();
                }
            }
            on_render_combat();
        }
        break;
        case type::PERFORMING_BUFF_DEBUFF_ACTIONS_ALLIES:
        {
            Debugger::instance()+="STATE: PERFORMING_BUFF_DEBUFF_ACTIONS_ALLIES";
            auto allies = m_reg.view<_ally>();
            //on_buff_debuff_ally(m_reg, allies);
            NEXT_STATE.type = type::PERFORMING_BUFF_DEBUFF_ACTIONS_ENEMY;
        }
        break;
        case type::PERFORMING_BUFF_DEBUFF_ACTIONS_ENEMY:
        {
            Debugger::instance()+="STATE: PERFORMING_BUFF_DEBUFF_ACTIONS_ENEMY";
            auto enemy = m_reg.view<_enemy>();
            on_buff_debuff_enemy(m_reg, enemy);
            NEXT_STATE.type = type::INIT_COMBAT_ROUND;
        }
        break;
        default:
            std::cout << "TYPE NOT IMPL" << std::endl;
    }
}
