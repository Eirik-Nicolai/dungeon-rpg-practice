#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <iostream>

struct movespeed{float speed;};

struct moveTick{float tick = 0;};

struct pos{
    int x;
    int y;
};
inline std::ostream &operator<<(std::ostream &os, const pos &p) {
    os << "{" << p.x << ", " << p.y << "}";
    return os;
}

struct size{
    int width;
    int height;
};

struct dirVertical
{
    bool up;
    bool down;
};
struct dirHorisontal
{
    bool left;
    bool right;
};

#endif // MOVEMENT_H_
