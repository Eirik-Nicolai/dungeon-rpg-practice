#include "initialize.hpp"

void on_init(entt::registry &reg, entt::entity &playerent)
{
    auto mainscreen = reg.create();
//    reg.emplace<window>(mainscreen, MAINWINDOW, 800-2, 600-2, 2, 2);
    //reg.emplace<_isactive>(mainscreen);

    auto menuscreen = reg.create();
    // reg.emplace<window>(menuscreen, MENUWINDOW, (winsizex/2)-2, winsizey-2,(winsizey/2)+2, 2);
  //  reg.emplace<window>(menuscreen, MENUWINDOW, 20, 40,(600/2)+2, 2);


    auto player = reg.create();
    reg.emplace<movespeed>(player, 1.0f);
    reg.emplace<_renderable>(player);
    reg.emplace<pos>(player, 20, 40);
    reg.emplace<simpleappearence>(player, "#");
    reg.emplace<dirVertical>(player);
    reg.emplace<dirHorisontal>(player);
    reg.emplace<moveTick>(player, 0.0f);
    reg.emplace<_player>(player);

    playerent = player;


    auto goblin = reg.create();
    reg.emplace<movespeed>(goblin, 0.6f);
    reg.emplace<_renderable>(goblin);
    reg.emplace<pos>(goblin, 200, 400);
    reg.emplace<simpleappearence>(goblin, "v");
    reg.emplace<dirVertical>(goblin);
    reg.emplace<dirHorisontal>(goblin);
    reg.emplace<moveTick>(goblin, 0.0f);
    reg.emplace<_ai>(goblin);
    reg.emplace<_follow_player>(goblin);
}
