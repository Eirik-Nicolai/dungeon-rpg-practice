#ifndef RENDERING_H_
#define RENDERING_H_
#include <string>

struct _renderable{};

struct simple_appearence{
    std::string c;
};

struct boss_appearence{
    std::string c;
};

struct visual{
    std::string name;
    std::string char_repr;
    std::string desc;
   short colour; // TODO fix
};

#endif // RENDERING_H_
