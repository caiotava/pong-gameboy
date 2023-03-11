#ifndef PONG_RENDER_H
#define PONG_RENDER_H

#include "sprite.h"

extern const uint8_t TILE_HEIGHT;
extern const uint8_t TILE_WIDTH;
extern const uint8_t TILE_HALF_HEIGHT;

extern const uint8_t SCREEN_HEIGHT;
extern const uint8_t SCREEN_WIDTH;

extern const uint8_t BOARD_TOP_BORDER;

extern const uint8_t SCORES_PLAYER_POS_X;
extern const uint8_t SCORES_COMPUTER_POS_X;

int initRender();

void loadScreenStart();

int loadBackground();

int loadSprites();

int loadGameOver();

void clearScreen();

void renderPaddleSprite(Sprite *paddle);

void drawBall(Ball *ball);

void renderWaitVerticalRender();

void drawNumber(uint8_t x, uint8_t y, uint16_t number, uint8_t digits);

void drawScores(uint8_t x, uint8_t y, uint16_t number);

void drawText(uint8_t x, uint8_t y, unsigned char *text);

void scrollBackground(int8_t x, int8_t y);

Vector2D_16 backgroundPosition();

#endif // PONG_RENDER_H
