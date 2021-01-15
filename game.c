#include <gb/gb.h>
#include "engine.h"
#include "vector2d.h"
#include "render.h"
#include "collision.h"

Paddle paddle_user;
Paddle paddle_computer;
Ball ball;

int isRunningGame = FALSE; 
int isPausedGame = FALSE;

void handleUserInput();
void handleBallMoving();
void checkCollision();
void checkCollisionPaddle();
void checkCollisionBall();
void fixCollisionBallPaddle( Ball *ball, short int typePaddleCollision );
void fixCollisionWall( Rect *rect, short int typeWallCollision );
void handleInputPaddle(UBYTE userInput);
void handleInputStartButton(UBYTE userInput);
void doIAComputer();

void initGame()
{
	isRunningGame = FALSE;
	isPausedGame = FALSE;

	initPaddles();
	initBall();
	initRender();
}

void initPaddles()
{
	paddle_user.position.x = 15;
	paddle_user.position.y = (int) SCREEN_HEIGHT / 2;
	paddle_user.height = TILE_HEIGHT * 3;
	paddle_user.width = 3;

	paddle_computer.position.x = SCREEN_WIDTH - 5;
	paddle_computer.position.y = (int) SCREEN_HEIGHT / 2;	
	paddle_computer.height = TILE_HEIGHT * 3;
	paddle_computer.width = 3;
}

void initBall()
{
	ball.position.x = (int) SCREEN_WIDTH / 2;
	ball.position.y = (int) SCREEN_HEIGHT / 2;
	ball.size.y = 8;
	ball.size.x = 6;
	ball.speed.x = -2;
	ball.speed.y = 1;
}

void runGame()
{
	while(1) {
		disableDisplay();

		handleUserInput();
		handleBallMoving();
		doIAComputer();
		checkCollision();

		drawPaddleUser( &paddle_user );
		drawPaddleComputer( &paddle_computer );
		drawBall( &ball );

		enableDisplay();
	}
}

void handleUserInput()
{
	UBYTE userInput;

	userInput = joypad();

	handleInputPaddle(userInput);
	handleInputStartButton(userInput);
}

void handleInputPaddle(UBYTE userInput) {
	extern Rect paddle_user;

	int isUpInput = userInput & J_UP;
	int isDownInput = userInput & J_DOWN;

	if (! isUpInput && ! isDownInput) {
		return;
	}

	if (userInput & J_UP) {
		paddle_user.position.y--;
	}
	else if (userInput & J_DOWN) {
		paddle_user.position.y++;
	}
}

void handleInputStartButton(UBYTE userInput)
{
	if (! (userInput & J_START)) {
		return ;
	}

	if (! isRunningGame) {
		isRunningGame = TRUE;
	}
	else if(isRunningGame) {
		isPausedGame = TRUE;
	}
}

void handleBallMoving()
{
	extern Ball ball;

	ball.rect.position.x += ball.speedX;
	ball.rect.position.y += ball.speedY;

	if ( hasCollisionWall( &ball.rect ) ) {
		ball.speedY = ball.speedY * -1;	
		ball.rect.position.y += ball.speedY;
	}
}

void doIAComputer()
{
	extern Rect paddle_computer;
	extern Ball ball;

	int middlePaddleComputer = paddle_computer.position.y + TILE_HEIGHT;

	if ( middlePaddleComputer < ball.rect.position.y ) {
		paddle_computer.position.y++;
	}
	else if ( middlePaddleComputer > ball.rect.position.y ) {
		paddle_computer.position.y--;
	}
}

void checkCollision()
{
	checkCollisionPaddle();
	checkCollisionBall();
}

void checkCollisionPaddle()
{
	extern Rect paddle_user;
	extern Rect paddle_computer;

	short int typeCollisionPaddleUser = hasCollisionWall(&paddle_user);
	short int typeCollisionPaddleComputer = hasCollisionWall(&paddle_computer);

	fixCollisionWall( &paddle_user, typeCollisionPaddleUser );
	fixCollisionWall( &paddle_computer, typeCollisionPaddleComputer );
}

void fixCollisionWall( Rect *rect, short int typeWallCollision )
{
	switch( typeWallCollision ) {
		case top_wall_collision:
			rect->position.y++;
			break;
		case bottom_wall_collision:
			rect->position.y--;
			break;
	}
}

void checkCollisionBall()
{
	extern Rect paddle_user;
	extern Rect paddle_computer;
	extern Ball ball;

	short int hasCollisionPaddleUser = hasCollisionBallPaddle(&ball, &paddle_user);
	short int hasCollisionPaddleComputer = hasCollisionBallPaddle(&ball, &paddle_computer);

	if ( hasCollisionPaddleUser || hasCollisionPaddleComputer) {
		fixCollisionBallPaddle(&ball, hasCollisionPaddleUser);
		fixCollisionBallPaddle(&ball, hasCollisionPaddleComputer);
	}
}

void fixCollisionBallPaddle( Ball *ball, short int typePaddleCollision )
{
	if ( ! typePaddleCollision ) {
		return;
	}

	switch(typePaddleCollision) {
		case top_paddle_collision:
			ball->speedY = -2;
			break;
		case bottom_paddle_collision:
			ball->speedY = 1;
			break;
		case middle_paddle_collision:
			ball->speedY = 0;
	}

	ball->speedX = ball->speedX * -1;
}
