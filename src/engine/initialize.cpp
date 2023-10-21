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



void DungeonThing::on_load_init()
{

    m_reg.on_construct<ai::_strolling>().connect<&ai::set_init_position_for_strolling>();

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
    // COMBAT
    m_reg.emplace<health>(player, 100, 100);
    m_reg.emplace<mana>(player, 100, 100);;
    m_reg.emplace<armour>(player, 0, 0);;
    m_reg.emplace<stats>(player, 1, 1);

    m_reg.emplace<ability_list>(player, std::vector<ability>{
        poison{{50,"Poison"},
        10
    },
    });

    m_player = player;


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
