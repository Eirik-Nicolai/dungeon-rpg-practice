#include "initialize.hpp"

void on_init(entt::registry &reg, int winsizex, int winsizey)
{
    auto mainscreen = reg.create();
    reg.emplace<window>(mainscreen, MAINWINDOW, winsizex-2, winsizey-2, 2, 2);
    reg.emplace<_isactive>(mainscreen);

    auto menuscreen = reg.create();
    // reg.emplace<window>(menuscreen, MENUWINDOW, (winsizex/2)-2, winsizey-2,(winsizey/2)+2, 2);
    reg.emplace<window>(menuscreen, MENUWINDOW, 20, 40,(winsizey/2)+2, 2);


    auto player = reg.create();
    reg.emplace<movespeed>(player, 0.9);
    reg.emplace<_renderable>(player);
    reg.emplace<pos>(player, 20, 40);
    reg.emplace<simpleappearence>(player, '#');
    reg.emplace<directionNorth>(player);
    reg.emplace<directionSouth>(player);
    reg.emplace<directionWest>(player);
    reg.emplace<directionEast>(player);
    reg.emplace<_player>(player);



    auto goblin = reg.create();
    reg.emplace<movespeed>(goblin, 0.9);
    reg.emplace<_renderable>(goblin);
    reg.emplace<pos>(goblin, 30, 30);
    reg.emplace<simpleappearence>(goblin, 'v');
    reg.emplace<directionNorth>(goblin);
    reg.emplace<directionSouth>(goblin);
    reg.emplace<directionWest>(goblin);
    reg.emplace<directionEast>(goblin);
    reg.emplace<_ai>(goblin);
    reg.emplace<_follow_player>(goblin);
}
