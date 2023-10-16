#include <iostream>
#include <string>
#include <chrono>

#include "engine/game.hpp"

auto main(int argc, char *argv[]) -> int
{
    DungeonThing demo;
    if (demo.Construct(800, 450, 2, 2))
        demo.Start();
    return 0;
}
