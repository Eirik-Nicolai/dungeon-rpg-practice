#ifndef MOVEMENT_H_
#define MOVEMENT_H_

struct movespeed{float speed;};

struct moveTick{float tick = 0;};

struct pos{
    int x;
    int y;
};

struct directionNorth
{
    float tick = 0;
    float vel = 0;
};
struct directionSouth
{
    float tick = 0;
    float vel = 0;
};
struct directionEast
{
    float tick = 0;
    float  vel = 0;
};
struct directionWest
{
    float tick = 0;
    float  vel = 0;
};

#endif // MOVEMENT_H_
