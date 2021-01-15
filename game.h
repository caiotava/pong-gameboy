#ifndef __GAME_HEADER__

#define __GAME_HEADER__

#include "vector2d.h"

typedef struct {
	Vector2D size;
	Vector2D position;
	Vector2D speed;
} Ball;

typedef struct {
    Vector2D position;
    Vector2D size;
} Paddle;

Paddle paddle_user;
Paddle paddle_computer;
Ball ball;

void initGame();
void runGame();

#endif
