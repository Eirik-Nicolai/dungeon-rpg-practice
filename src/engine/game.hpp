#ifndef GAME_H_
#define GAME_H_

#include "olcPixelGameEngine.h"

#include <entt/entt.hpp>

class DungeonThing : public olc::PixelGameEngine
{
public:
    DungeonThing();

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float) override;


private:
    entt::registry reg;


};


#endif // GAME_H_
