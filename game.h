#ifndef __GAME_HEADER__

#define __GAME_HEADER__

#include "rect.h"
#include "render.h"

extern Rect paddle_user;
extern Rect paddle_computer;
extern Ball ball;

void initGame();
void runGame();

#endif
