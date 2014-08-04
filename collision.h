#ifndef __COLISSION_HEADER__

#define __COLISSION_HEADER__

#include "rect.h"

enum type_collision_wall {
	no_wall_collision = 0,
	top_wall_collision,
	right_wall_collision,
	bottom_wall_collision,
	left_wall_collision
} ;

enum type_collision_paddle {
	no_paddle_collision = 0,
	top_paddle_collision,
	middle_paddle_collision,
	bottom_paddle_collision
};

short int hasCollisionWall(Rect *rect);
short int hasCollisionBallPaddle(Ball *ball, Rect *paddle);

#endif
