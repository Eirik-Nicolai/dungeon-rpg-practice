#ifndef RENDERING_H_
#define RENDERING_H_
#include <string>

struct _renderable{};

struct simple_appearence{
    std::string c;
};

struct combat_appearence{
    std::string c;
};

struct boss_appearence{
    std::string c;
};

struct visual{
    std::string name;
    std::string desc;
    std::string char_repr;
    short colour;
};

#endif // RENDERING_H_
