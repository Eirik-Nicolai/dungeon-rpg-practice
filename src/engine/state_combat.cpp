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
            m_reg.emplace<visual>(poison, "Poison");
            m_reg.emplace<damage>(poison, 5);
            m_reg.emplace<tick>(poison, 5);
            m_reg.emplace<affects>(poison);

            auto poison_attack = m_reg.create();
            m_reg.emplace<visual>(poison_attack, "POISON ATTACK");
            m_reg.emplace<adds_debuff>(poison_attack, poison);

            auto heavy_attack = m_reg.create();
            m_reg.emplace<visual>(heavy_attack, "HEAVY ATK");
            m_reg.emplace<damage>(heavy_attack, 40);

            auto goblin_big = m_reg.create();
            m_reg.emplace<combat_appearence>(goblin_big, "V");
            m_reg.emplace<health>(goblin_big, 100, 100);
            m_reg.emplace<armour>(goblin_big, 5);
            m_reg.emplace<stats>(goblin_big, 10, 0);
            m_reg.emplace<has_action>(goblin_big, heavy_attack);
            m_reg.emplace<_enemy>(goblin_big);

            auto goblin_mage = m_reg.create();
            m_reg.emplace<combat_appearence>(goblin_mage, "U");
            m_reg.emplace<health>(goblin_mage, 40, 40);
            m_reg.emplace<armour>(goblin_mage, 1);
            m_reg.emplace<stats>(goblin_mage, 0, 20);
            m_reg.emplace<has_action>(goblin_mage, poison_attack);
            m_reg.emplace<_enemy>(goblin_mage);

            // find positions for multi-group enemies/allies
            auto enemy_group = m_reg.view<_enemy>();
            auto [winx, winy] = GetWindowSize();
            auto posx_allies = winx * 0.30;
            auto posx_enemy = winx * 0.70;

            m_reg.emplace_or_replace<combat::pos>(m_player, (int)posx_allies, winy/3);

            // FIXME use the view to calc based on amount of enemies
            switch (enemy_group.size())
            {
                //case 3:
                    //auto en = *enemy_group.end();

                case 2:
                    m_reg.emplace_or_replace<combat::pos>(goblin_mage, (int)posx_enemy, winy/4);
                    m_reg.emplace_or_replace<combat::pos>(goblin_big, (int)posx_enemy, winy*2/4);
                    break;
                case 1:
                    m_reg.emplace_or_replace<combat::pos>(goblin_big, (int)posx_enemy, winy/3);
                    break;
            }

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

            m_targetmenu = TargetMenu([&]{
                m_movequeue_player.emplace(combat_action{
                    .action = m_intended_action,
                    .target = m_targetmenu.GetSelected()
                    });
                NEXT_STATE.type = type::ALLY_SELECTING_ACTION;
            }, goblin_mage, goblin_big);
            m_reg.ctx().emplace<CombatState>(-1);

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
        case type::PLAYER_SELECTING_ACTION:
        {
            Debugger::instance()+="STATE: PLAYER_SELECTING_ACTION";
            on_userinput_combat();
            on_render_combat();
        }
        break;
        case type::PLAYER_SELECTING_TARGET:
        {
            Debugger::instance()+="STATE: PLAYER_SELECTING_TARGET";
            on_userinput_combat();
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
        case type::INIT_PLAYER_SELECTING_TARGET:
        {
            Debugger::instance()+="STATE: INIT_PLAYER_SELECTING_TARGET";
            on_render_combat();
            NEXT_STATE.type = type::PLAYER_SELECTING_TARGET;
        }
        break;
        case type::PERFORMING_COMBAT_ACTIONS_PLAYER:
        {
            Debugger::instance()+="STATE: PERFORMING_COMBAT_ACTIONS_PLAYER";

            while(!m_movequeue_player.empty())
            {
                auto [action, target] = m_movequeue_player.front();
                on_damage(m_reg, m_player, target, action);
                m_movequeue_player.pop();
            }
            if(delay_for(1, dt))
            {
                NEXT_STATE.type = type::PERFORMING_COMBAT_ACTIONS_ALLIES;
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
                    on_damage(m_reg, m_player, target, action);
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
            on_buff_debuff_ally(m_reg, allies);
            NEXT_STATE.type = type::PERFORMING_BUFF_DEBUFF_ACTIONS_ENEMY;
        }
        break;
        case type::PERFORMING_BUFF_DEBUFF_ACTIONS_ENEMY:
        {
            Debugger::instance()+="STATE: PERFORMING_BUFF_DEBUFF_ACTIONS_ENEMY";

            NEXT_STATE.type = type::PLAYER_SELECTING_ACTION;
        }
        break;
        default:
            std::cout << "TYPE NOT IMPL" << std::endl;
    }
}
