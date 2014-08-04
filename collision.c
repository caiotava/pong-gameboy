#include<gb\gb.h>
#include<stdio.h>
#include<gb\console.h>
#include "collision.h"
#include "rect.h"
#include "render.h"
#include "engine.h"

short int hasCollisionWall(Rect *rect)
{
	extern Ball ball;
	short int typeWallCollision = no_wall_collision;
	int isCollisionTopWall = rect->position.y <= 17;
	int isCollisionBottomWall = rect->position.y + rect->height >= BOARD_HEIGHT;
	int isCollisionLeftWall = rect->position.x < 0;
	int isCollisionRightWall = rect->position.x + rect->width > BOARD_WIDTH;

	if (isCollisionTopWall) {
		typeWallCollision = top_wall_collision;
	}
	else if (isCollisionBottomWall) {
		typeWallCollision = bottom_wall_collision;
	}
	else if (isCollisionLeftWall) {
		typeWallCollision = left_wall_collision;
		gotoxy(14, 14);
		printf("Colissao X");
	}
	else if (isCollisionRightWall) {
		typeWallCollision = right_wall_collision;
		if ( rect == &ball ) {
			gotoxy(14, 14);
			printf("Colisao Y - %d", rect->position.x + rect->width );
		}
	}

	return typeWallCollision;
}

short int hasCollisionBallPaddle(Ball *ball, Rect *paddle)
{
	int widthBall = ball->rect.position.x + ball->rect.width;
	int heightBall = ball->rect.position.y + ball->rect.height;
	int widthPaddle = paddle->position.x + paddle->width;
	int heightPaddle = paddle->position.y + paddle->height;

	int centerPaddle = paddle->position.y + paddle->height / 2;
	int centerBall = ball->rect.position.y + ball->rect.height / 2;

	short int hasCollisionY = ((ball->rect.position.y >= paddle->position.y && ball->rect.position.y <= heightPaddle) 
		       			|| (heightBall >= paddle->position.y) && heightBall <= heightPaddle);

	short int hasCollisionX = ((ball->rect.position.x >= paddle->position.x && ball->rect.position.x <= widthPaddle)
		       			|| widthBall >= paddle->position.x && widthBall <= widthPaddle);

	if ( ! ( hasCollisionY && hasCollisionX ) ) {
		return no_paddle_collision;
	}

	if (ball->rect.position.y < centerPaddle) {
		return top_paddle_collision;
	}
	else if (ball->rect.position.y >= centerPaddle) {
		return bottom_paddle_collision;
	}
	else if (centerBall == centerPaddle) {
		return middle_paddle_collision;
	}
}
