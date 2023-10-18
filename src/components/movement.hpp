#ifndef MOVEMENT_H_
#define MOVEMENT_H_

struct movespeed{float speed;};

struct moveTick{float tick = 0;};

struct pos{
    int x;
    int y;
};

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
