#ifndef __RENDER_HEADER__

#include "vector2d.h"

#define __RENDER_HEADER__

extern const short int TILE_HEIGHT;
extern const short int TILE_WIDTH;

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

extern const int BOARD_HEIGHT;
extern const int BOARD_WIDTH;

int initRender();
int loadBackground();
int loadSprites();
int clearBackground();
int disableDisplay();
int enableDisplay();

void drawPaddle(Vector2D position);
void drawBall(Vector2D position);
#endif
