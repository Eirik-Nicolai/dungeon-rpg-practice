#ifndef LOGIC_H_
#define LOGIC_H_

struct collision{
    int x, y;
    int w, h;
};

struct window{
    int id;
    int x, y;
    int w, h;
};

struct transitioning{
    float factor;
};

struct _isactive{};

struct _solid{}; //cannot be walked through



#endif // LOGIC_H_
