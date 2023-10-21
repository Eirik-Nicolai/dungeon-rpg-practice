#ifndef TYPES_AND_DEFINES_H_
#define TYPES_AND_DEFINES_H_



#define BORDER_OFFS 10

struct GameState
{
    enum class state
    {
    UNKNOWNTYPE = 0,
    WALKING = 1,
    COMBAT = 2,
    DIALOGUE = 3,
    CUTSCENE = 4,
    PAUSED = 5,
    STARTMENU = 6,
    NONE
};
};

struct GameStateType
{
    enum class type {
    UNKNOWNSUBTYPE = 0,
    INIT = 1,
    PLAYING_TRANSITION = 2,

    // -------- TRANSITIONS --------
    FROM_COMBAT_TRANSITION = 1001,
    FROM_PAUSED_TRANSITION,
    // -------- -------- -------- --

    // ROAMING----------------------
    FREEROAM = 1101,
    // -----------------------------

    // -----------------------------
    PLAYER_SELECTING = 2102,
    INIT_PLAYER_SELECTION,
    PERFORMING_COMBAT_ACTIONS_PLAYER,
    PERFORMING_COMBAT_ACTIONS_ENEMY,
    // -----------------------------

    // -----------------------------
    PAUSED = 5001,
    // -----------------------------
};
};


using state = GameState::state;
using type = GameStateType::type;

struct State
{
   GameState::state state;
   GameStateType::type type;
};

//enum class state{WALKING, COMBAT, DIALOGUE, CUTSCENE, PAUSED, STARTMENU, TRANSITION, NONE};


#endif // TYPES_AND_DEFINES_H_
