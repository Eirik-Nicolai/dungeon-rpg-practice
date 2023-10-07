#ifndef GLOBALS_H_
#define GLOBALS_H_


#define MAX_WINDOWS 4
#define MAINWINDOW 0
#define MENUWINDOW 1
#define OTHRWINDOW 2


extern bool ISPRESSED_NORTH;
extern bool ISPRESSED_SOUTH;
extern bool ISPRESSED_WEST;
extern bool ISPRESSED_EAST;


enum class state{WALKING, COMBAT, DIALOGUE, CUTSCENE, PAUSED, STARTMENU, TRANSITION, NONE};
extern state GAME_STATE;
extern state NEW_GAME_STATE;


#endif // GLOBALS_H_
