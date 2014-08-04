#ifndef __RECT_HEADER__

#define __RECT_HEADER__

typedef struct {
	int x;
	int y;
} Axis;

typedef struct {
	Axis position;
	int height;
	int width;
} Rect;

typedef struct {
	Rect rect;
	int speedX;
	int speedY;
	int directionX;
	int directionY;
} Ball;

#endif
