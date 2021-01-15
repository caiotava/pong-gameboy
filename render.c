#include <gb/gb.h>
#include "render.h"
#include "vector2d.h"
#include "sprites.h"

const short int PADDLE_SPRITE_TOP = 0;
const short int PADDLE_SPRITE_MIDDLE = 1;
const short int PADDLE_SPRITE_BOTTOM = 2;
const short int BALL_SPRITE = 3;

const short int PADDLE_USER_TILE_TOP = 0;
const short int PADDLE_USER_TILE_MIDDLE = 1;
const short int PADDLE_USER_TILE_BOTTOM = 2;

const short int PADDLE_COMPUTER_TILE_TOP = 3;
const short int PADDLE_COMPUTER_TILE_MIDDLE = 4;
const short int PADDLE_COMPUTER_TILE_BOTTOM = 5;
const short int BALL_TILE = 6;

const short int TILE_HEIGHT = 8;
const short int TILE_WIDTH = 8;

const int SCREEN_HEIGHT = 160;
const int SCREEN_WIDTH = 160;
const int BOARD_HEIGHT = 135;
const int BOARD_WIDTH = 160;

const short int MAX_NUMBER_SPRITES = 4;

int initRender()
{
	disableDisplay() ;
	SPRITES_8x8;

	loadBackground();
	loadSprites();

	SHOW_SPRITES;

	enableDisplay();
}

int disableDisplay()
{
	disable_interrupts();
	DISPLAY_OFF;

	return 1;
}

int enableDisplay()
{
	DISPLAY_ON;
	enable_interrupts();

	return 1;
}

int loadBackground()
{
	return 1;
}

int loadSprites()
{
	set_sprite_data(0, MAX_NUMBER_SPRITES, sprites);

	// Paddle user
	set_sprite_tile(PADDLE_USER_TILE_TOP, PADDLE_SPRITE_TOP);
	set_sprite_tile(PADDLE_USER_TILE_MIDDLE, PADDLE_SPRITE_MIDDLE);
	set_sprite_tile(PADDLE_USER_TILE_BOTTOM, PADDLE_SPRITE_BOTTOM);

	// Paddler computer
	set_sprite_tile(PADDLE_COMPUTER_TILE_TOP, PADDLE_SPRITE_TOP);
	set_sprite_tile(PADDLE_COMPUTER_TILE_MIDDLE, PADDLE_SPRITE_MIDDLE);
	set_sprite_tile(PADDLE_COMPUTER_TILE_BOTTOM, PADDLE_SPRITE_BOTTOM);

	// Ball
	set_sprite_tile(BALL_TILE, BALL_SPRITE);

	return 1;
}

void drawPaddle(Vector2D position)
{
	int middleY = position.y + TILE_HEIGHT;
	int bottomY = middleY + TILE_HEIGHT;

	move_sprite(PADDLE_USER_TILE_TOP, position.x, position.y);
	move_sprite(PADDLE_USER_TILE_MIDDLE, positionX, middleY);
	move_sprite(PADDLE_USER_TILE_BOTTOM, positionX, bottomY);
}

void drawBall(Vector2D position)
{
	move_sprite(BALL_TILE, position.x, position.y);
}
