#include "game.hpp"
#include "initialize.hpp"


namespace ai {
    void set_init_position_for_strolling(entt::registry &reg, entt::entity ent)
    {
        reg.remove<_follow>(ent);
        auto &ai = reg.get<ai::_strolling>(ent);
        ai.init_pos = reg.get<pos>(ent);
    }
}


namespace combat {
    // FIXME deal with f ex multiple force multipliers
    // or one buff one debuff on the same stat
    // etc
    // maybe like a third intermediate saved stat value is needed?
    void update_stats(entt::registry &reg, entt::entity ent)
    {
        auto &eff = reg.get<affected>(ent).effects;
        for(auto e : eff)
        {
            if(reg.all_of<force_modifier>(e))
            {
                std::cout << "UPDATING STATS" << std::endl;
                auto mod = reg.get<force_modifier>(e).amount;
                reg.patch<force>(ent, [&](auto &f){
                    f.curr = f.max*mod;
                });
            }
            else if(reg.all_of<force_modifier>(e))
            {
                auto mod = reg.get<mind_modifier>(e).amount;
                reg.patch<mind>(ent, [&](auto &m){
                    m.curr = m.max*mod;
                });
            }
            else if(reg.all_of<force_modifier>(e))
            {
                auto mod = reg.get<armour_modifier>(e).amount;
                reg.patch<armour>(ent, [&](auto &a){
                    a.curr = a.max*mod;
                });
            }
            else if(reg.all_of<force_modifier>(e))
            {
                auto mod = reg.get<willpower_modifier>(e).amount;
                reg.patch<willpower>(ent, [&](auto &w){
                    w.curr = w.max*mod;
                });
            }
            else if(reg.all_of<_invincibility>(e))
            {
                reg.patch<armour>(ent, [&](auto &a){
                    a.curr = 9999;
                });
                reg.patch<willpower>(ent, [&](auto &w){
                    w.curr = 9999;
                });
            }
        }
    }
}


void DungeonThing::on_load_init()
{

    m_reg.on_construct<ai::_strolling>().connect<&ai::set_init_position_for_strolling>();

    m_reg.on_update<affected>().connect<&combat::update_stats>();

    // STATE AND GLOBALS

    // m_reg.ctx().emplace<TransitionState>(0.0,5.0,2.0,0.0);
    m_reg.ctx().emplace<MenuState>(0);
    //m_reg.ctx().emplace<PlayerState>(100,100,1,0);
    m_reg.ctx().emplace<InventoryState>();
    m_reg.ctx().emplace<EquipmentState>();

    auto &winsize = GetWindowSize();

    auto edgenorth = m_reg.create();
    m_reg.emplace<_wall>(edgenorth);
    m_reg.emplace<_solid>(edgenorth);
    m_reg.emplace<pos>(edgenorth, 0, 0);
    m_reg.emplace<size>(edgenorth, winsize.x, 10);
    auto edgesouth = m_reg.create();
    m_reg.emplace<_wall>(edgesouth);
    m_reg.emplace<_solid>(edgesouth);
    m_reg.emplace<pos>(edgesouth, 0, (winsize.y/GetPixelSize().x)-10);
    m_reg.emplace<size>(edgesouth, winsize.x, 10);
    auto edgewest = m_reg.create();
    m_reg.emplace<_wall>(edgewest);
    m_reg.emplace<_solid>(edgewest);
    m_reg.emplace<pos>(edgewest, 0, 0);
    m_reg.emplace<size>(edgewest, 10, winsize.y);
    auto edgeeast = m_reg.create();
    m_reg.emplace<_solid>(edgeeast);
    m_reg.emplace<_wall>(edgeeast);
    m_reg.emplace<pos>(edgeeast, (winsize.x/GetPixelSize().x)-10, 0);
    m_reg.emplace<size>(edgeeast, 10, winsize.y);

    auto player = m_reg.create();
    // MOVE
    m_reg.emplace<movespeed>(player, 0.1f);
    m_reg.emplace<_renderable>(player);
    m_reg.emplace<pos>(player, 20, 40);
    m_reg.emplace<simple_appearence>(player, "#");
    m_reg.emplace<dirVertical>(player);
    m_reg.emplace<dirHorisontal>(player);
    m_reg.emplace<moveTick>(player, 0.0f);

    // INVENTORY
    auto helmet = m_reg.create();
    m_reg.emplace<_helmet>(helmet);
    m_reg.emplace<visual>(helmet, "HOOD");
    m_reg.emplace<armour>(helmet, 1);

    auto torso = m_reg.create();
    m_reg.emplace<_torso>(torso);
    m_reg.emplace<visual>(torso, "SWEATER");
    m_reg.emplace<armour>(torso, 1);

    auto legs = m_reg.create();
    m_reg.emplace<_legs>(legs);
    m_reg.emplace<visual>(legs, "TROUSERS");
    m_reg.emplace<armour>(legs, 1);

    auto mainhand = m_reg.create();
    m_reg.emplace<_main_hand>(mainhand);
    m_reg.emplace<visual>(mainhand, "SWORD");
    m_reg.emplace<force>(mainhand, 1, 1);

    auto offhand = m_reg.create();
    m_reg.emplace<_off_hand>(offhand);
    m_reg.emplace<visual>(offhand, "SHIELD");
    m_reg.emplace<armour>(offhand, 1);

    auto ear = m_reg.create();
    m_reg.emplace<_accessory_head>(ear);
    m_reg.emplace<visual>(ear, "EARRING");
    m_reg.emplace<willpower>(ear, 1);

    auto finger = m_reg.create();
    m_reg.emplace<_accessory_hand>(finger);
    m_reg.emplace<visual>(finger, "RING");
    m_reg.emplace<mind>(finger, 1, 1);

    auto &state = m_reg.ctx().get<EquipmentState>();
    state.head = helmet;
    state.torso = torso;
    state.legs = legs;
    state.main_hand = mainhand;
    state.off_hand = offhand;
    state.jewellery_ears = ear;
    state.jewellery_finger = finger;


    // COMBAT
    m_reg.emplace<_ally>(player);
    m_reg.emplace<combat_appearence>(player, "#");
    m_reg.emplace<health>(player, 100, 100);
    m_reg.emplace<mana>(player, 100, 100);
    m_reg.emplace<armour>(player, 0, 0);
    m_reg.emplace<willpower>(player, 0, 0);
    m_reg.emplace<force>(player, 2, 2);
    m_reg.emplace<mind>(player, 2, 2);
    m_reg.emplace<affected>(player);

    auto reg_attack = m_reg.create();
    m_reg.emplace<visual>(reg_attack, "ATK");
    m_reg.emplace<damage>(reg_attack, 30);

    auto weakness = m_reg.create();
    m_reg.emplace<_debuff>(weakness);
    m_reg.emplace<visual>(weakness, "WEAKENED");
    m_reg.emplace<tick>(weakness, 2);
    m_reg.emplace<dmg_modifier>(weakness, (float)0.0);

    auto bleed = m_reg.create();
    m_reg.emplace<_debuff>(bleed);
    m_reg.emplace<visual>(bleed, "BLEEDING");
    m_reg.emplace<damage>(bleed, 10);
    m_reg.emplace<tick>(bleed, 2);

    auto bleed_attack = m_reg.create();
    m_reg.emplace<visual>(bleed_attack, "Bleed atk");
    m_reg.emplace<adds_debuff>(bleed_attack, bleed);

    auto weakness_attack = m_reg.create();
    m_reg.emplace<visual>(weakness_attack, "Weakness atk");
    m_reg.emplace<adds_debuff>(weakness_attack, weakness);

    auto does_multiple_things_attack = m_reg.create();
    m_reg.emplace<visual>(does_multiple_things_attack, "ATK MANY");
    m_reg.emplace<action_children>(does_multiple_things_attack, std::vector<entt::entity>{reg_attack, weakness_attack});

    auto healing = m_reg.create();
    m_reg.emplace<visual>(healing, "HEAL");
    m_reg.emplace<heal>(healing, 20);

    auto cleanse_skill = m_reg.create();
    m_reg.emplace<_skill>(cleanse_skill);
    m_reg.emplace<_cleanse>(cleanse_skill);

    auto does_multiple_things_heal = m_reg.create();
    m_reg.emplace<visual>(does_multiple_things_heal, "HEAL CLEANSE");
    m_reg.emplace<action_children>(does_multiple_things_heal, std::vector<entt::entity>{healing, cleanse_skill});

    // FIXME set up skills tied to player system
    // m_reg.emplace<skill_list>(player, std::vector<skill>{
    //     poison{{50,"Poison"},
    //     10
    // },
    // });

    m_player = player;

    TextItem attack{
        "ATTACK",
        [=]{
            NEXT_STATE.type = type::INIT_PLAYER_SELECTING_TARGET;
            m_intended_action = does_multiple_things_attack;
        }
    };
    TextItem skill{
        "SKILL",
        [&]{
            m_curr_menu = 1;
        }
    };
    TextItem item{
        "ITEM",
        []{
            std::cout << "EXIT NOT IMPL" << std::endl;
        }};
    TextItem run {
        "RUN",
        [&]{
            NEXT_STATE = {state::WALKING, type::FROM_COMBAT_TRANSITION};
            std::cout << "EXIT NOT IMPL" << std::endl;
        }};
    m_combatmenus.emplace_back(CombatMenu(attack, skill, item, run));

    TextItem cleanse{
    "CLEANSE",
    [=]{
        NEXT_STATE.type = type::INIT_PLAYER_SELECTING_TARGET;
        m_intended_action = does_multiple_things_heal;
    }};
    TextItem back{
    "BACK",
    [=]{
        m_curr_menu = 0;
    }};
    m_combatmenus.emplace_back(CombatMenu(cleanse, back));

    auto goblin = m_reg.create();
    m_reg.emplace<movespeed>(goblin, 0.6f);
    m_reg.emplace<_renderable>(goblin);
    m_reg.emplace<pos>(goblin, 300, 400);
    m_reg.emplace<simple_appearence>(goblin, "v");
    m_reg.emplace<dirVertical>(goblin);
    m_reg.emplace<dirHorisontal>(goblin);
    m_reg.emplace<moveTick>(goblin, 0.0f);
    m_reg.emplace<ai::_follow>(goblin, player);
    //m_reg.emplace<ai::_at_rest>(goblin);

    auto wall = m_reg.create();
    m_reg.emplace<_wall>(wall);
    m_reg.emplace<_renderable>(wall);
    m_reg.emplace<pos>(wall, 100, 100);
    m_reg.emplace<size>(wall, 400, 30);
    m_reg.emplace<_solid>(wall);

}
