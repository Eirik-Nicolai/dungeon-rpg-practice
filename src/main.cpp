#include <iostream>
#include <string>
#include <chrono>

#include "engine/game.hpp"

auto main(int argc, char *argv[]) -> int
{
    DungeonThing demo;
    if (demo.Construct(1600, 900, 1, 1))
        demo.Start();
    return 0;
}
