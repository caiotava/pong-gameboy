
#include <stdbool.h>
#include <gbdk/emu_debug.h>

#include "sprite.h"
#include "render.h"
#include "input.h"
#include "sound.h"
#include "states_type.h"

Sprite paddleUser;
Sprite paddleComputer;
Ball ball;

int scoresPlayer = 0;
int scoresComputer = 0;

#define MAX_SCORE 9

bool isRunningGame = false;
bool isPausedGame = false;

void initPaddles() {
    paddleUser.position.x = 15;
    paddleUser.position.y = (int) SCREEN_HEIGHT / 2;
    paddleUser.size.y = TILE_HEIGHT * 3;
    paddleUser.size.x = TILE_WIDTH;
    paddleUser.id = 0;

    paddleComputer.position.x = SCREEN_WIDTH - 5;
    paddleComputer.position.y = (int) SCREEN_HEIGHT / 2;
    paddleComputer.size.y = TILE_HEIGHT * 3;
    paddleComputer.size.x = TILE_WIDTH;
    paddleUser.id = 3;
}

void initBall() {
    ball.sprite.position.x = (int) SCREEN_WIDTH / 2;
    ball.sprite.position.y = (int) SCREEN_HEIGHT / 2;
    ball.sprite.size.y = TILE_HEIGHT;
    ball.sprite.size.x = TILE_WIDTH;
    ball.velocity.x = -1;
    ball.velocity.y = 1;
}

short int hasCollisionWall(Sprite *sprite) {
    return sprite->position.y <= BOARD_TOP_BORDER || sprite->position.y + sprite->size.y >= SCREEN_HEIGHT;
}

void handleInputPaddle() {
    if (!buttonUp && !buttonDown) {
        return;
    }

    int oldPositionY = paddleUser.position.y;

    if (buttonUp) {
        paddleUser.position.y--;
    } else if (buttonDown) {
        paddleUser.position.y++;
    }

    if (hasCollisionWall(&paddleUser)) {
        paddleUser.position.y = oldPositionY;
    }
}

void doIAComputer() {
    int middlePaddleComputer = paddleComputer.position.y + TILE_HEIGHT;
    int oldPositionY = paddleComputer.position.y;

    if (middlePaddleComputer < ball.sprite.position.y) {
        paddleComputer.position.y++;
    } else if (middlePaddleComputer > ball.sprite.position.y) {
        paddleComputer.position.y--;
    }

    if (hasCollisionWall(&paddleComputer)) {
        paddleComputer.position.y = oldPositionY;
    }
}

void handleBallCollisionPaddle() {
    uint8_t userPaddleCollision = isColliding(&ball.sprite, &paddleUser);
    uint8_t computerPaddleCollision = isColliding(&ball.sprite, &paddleComputer);
    int8_t direction = 0;

    uint8_t collisionType = SPRITE_COLLISION_NONE;
    Sprite *collisionPaddle;

    if (userPaddleCollision) {
        collisionType = userPaddleCollision;
        collisionPaddle = &paddleUser;
        ball.velocity.x = 1;

        if (buttonUp) {
            direction = 1;
        } else if (buttonDown) {
            direction = -1;
        }

    } else if (computerPaddleCollision) {
        collisionType = computerPaddleCollision;
        collisionPaddle = &paddleComputer;
        ball.velocity.x = -1;
    }


    switch (collisionType) {
        case SPRITE_COLLISION_NONE:
            return;
        case SPRITE_COLLISION_TOP:
            ball.velocity.y = ball.sprite.position.y + TILE_HALF_HEIGHT <= collisionPaddle->position.y + TILE_HALF_HEIGHT ? -2 : -1;
            break;
        case SPRITE_COLLISION_BOTTOM:
            ball.velocity.y = ball.sprite.position.y >= collisionPaddle->position.y + collisionPaddle->size.y - TILE_HALF_HEIGHT ? 2 : 1;
            break;
        case SPRITE_COLLISION_MIDDLE:
            ball.velocity.y = 0;
    }

    if (ball.velocity.y < 0 && direction > 0 || ball.velocity.y > 0 && direction < 0) {
        ball.velocity.y *= -1;
    }

    playBounceSound();
}

void handleBallMoving() {
    ball.sprite.position.x += ball.velocity.x;
    ball.sprite.position.y += ball.velocity.y;

    // EMU_printf("x: %d; x+size: %d;", ball.sprite.position.x, ball.sprite.position.x + ball.sprite.size.x);

    if (ball.sprite.position.x < 0) {
        initBall();
        ball.velocity.x = -1;
        drawScores(SCORES_COMPUTER_POS_X, 0, ++scoresComputer);
    } else if (ball.sprite.position.x > SCREEN_WIDTH) {
        initBall();
        ball.velocity.x = 1;
        drawScores(SCORES_PLAYER_POS_X, 0, ++scoresPlayer);
    }

    if (hasCollisionWall(&ball.sprite)) {
        ball.velocity.y = ball.velocity.y * -1;
        ball.sprite.position.y += ball.velocity.y;
        playBounceSound();
    }

    handleBallCollisionPaddle();
}

void StateInitGamePlay(void) {
    isPausedGame = false;
    scoresComputer = 0;
    scoresPlayer = 0;

    initPaddles();
    initBall();

    loadBackground();
    loadSprites();

    drawScores(SCORES_PLAYER_POS_X, 0, scoresPlayer);
    drawScores(SCORES_COMPUTER_POS_X, 0, scoresComputer);
}

uint8_t StateUpdateGamePlay(uint8_t deltaTime) {
    handleBallMoving();
    handleInputPaddle();
    doIAComputer();

    renderPaddleSprite(&paddleUser);
    renderPaddleSprite(&paddleComputer);
    drawBall(&ball);

    renderWaitVerticalRender();

    if (scoresPlayer > MAX_SCORE || scoresComputer > MAX_SCORE) {
        return STATE_GAME_OVER;
    }

    return STATE_SCREEN_GAMEPLAY;
}
