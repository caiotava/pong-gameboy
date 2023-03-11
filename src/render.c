#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdlib.h>
#include <string.h>
#include "render.h"
#include "vector2D.h"
#include "sprite.h"
#include "generated/ball.h"
#include "generated/font.h"
#include "generated/logo.h"
#include "generated/scores-font.h"
#include "generated/paddle.h"
#include "generated/game-over.h"
#include "generated/scores-background.h"
#include "generated/background.h"

const uint8_t PADDLE_SPRITE_TOP = 1;
const uint8_t PADDLE_SPRITE_MIDDLE = 2;
const uint8_t PADDLE_SPRITE_BOTTOM = 3;
const uint8_t BALL_SPRITE = 4;

const uint8_t PADDLE_USER_TILE_TOP = 0;
const uint8_t PADDLE_USER_TILE_MIDDLE = 1;
const uint8_t PADDLE_USER_TILE_BOTTOM = 2;

const uint8_t PADDLE_COMPUTER_TILE_TOP = 3;
const uint8_t PADDLE_COMPUTER_TILE_MIDDLE = 4;
const uint8_t PADDLE_COMPUTER_TILE_BOTTOM = 5;
const uint8_t BALL_TILE = 6;

const uint8_t TILE_WIDTH = 8;
const uint8_t TILE_HEIGHT = 8;
const uint8_t TILE_HALF_HEIGHT = 4;

const uint8_t SCREEN_HEIGHT = 160;
const uint8_t SCREEN_WIDTH = 160;

const uint8_t BOARD_TOP_BORDER = 32; // gameboy has an offset of 16 bits

extern const uint8_t SCORES_PLAYER_POS_X = 5;
extern const uint8_t SCORES_COMPUTER_POS_X = 14;

#define FONT_TILES_START 1
#define LOGO_TILES_START FONT_TILES_START+font_TILE_COUNT
#define FONT_SCORES_START 1
#define FONT_SCORES_SECOND_ROW scores_font_TILE_COUNT/2 + 1
#define SCORES_BACKGROUND_START FONT_SCORES_START+scores_font_TILE_COUNT
#define BACKGROUND_START SCORES_BACKGROUND_START+scores_background_TILE_COUNT

int initRender() {
    DISPLAY_ON;
    SPRITES_8x8;
    SHOW_SPRITES;
    SHOW_BKG;

    const palette_color_t blackAndWhite[4] = {
            RGB8(255, 255, 255),
            RGB8(RGB_BLACK, RGB_BLACK, RGB_BLACK),
            RGB8(RGB_BLACK, RGB_BLACK, RGB_BLACK),
            RGB8(RGB_BLACK, RGB_BLACK, RGB_BLACK)
    };

    set_sprite_palette(0, 1, blackAndWhite);
}

void loadScreenStart() {
    HIDE_WIN;
    move_bkg(0, 144);

    set_bkg_data(FONT_TILES_START, font_TILE_COUNT, font_tiles);
    set_bkg_data(LOGO_TILES_START, logo_TILE_COUNT, logo_tiles);

    set_bkg_based_tiles(2, 4, 18, 6, logo_map, LOGO_TILES_START);
}

void clearScreen() {
    fill_bkg_rect(0, 0, 20, 18, 0);

    // clear sprites
    for (uint8_t i = 0; i < 40; i++) {
        set_sprite_tile(i, 0);
        move_sprite(i, 0, 0);
    }
}

int loadBackground() {
    set_bkg_data(1, scores_font_TILE_COUNT, scores_font_tiles);
    set_bkg_data(SCORES_BACKGROUND_START, scores_background_TILE_COUNT, scores_background_tiles);
    set_bkg_data(BACKGROUND_START, background_TILE_COUNT, background_tiles);

    set_bkg_based_tiles(0, 0,20, 3, scores_background_map, SCORES_BACKGROUND_START);
    set_bkg_based_tiles(9, 2,2, 16, background_map, BACKGROUND_START);
}

int loadSprites() {
    set_sprite_data(1, paddle_TILE_COUNT, paddle_tiles);
    set_sprite_data(paddle_TILE_COUNT + 1, ball_TILE_COUNT, ball_tiles);

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

int loadGameOver() {
    set_bkg_data(1, game_over_TILE_COUNT, game_over_tiles);

    set_bkg_based_tiles(4, 4, 12, 9, game_over_map, 1);
}

void renderPaddleSprite(Sprite *paddle) {
    int positionX = paddle->position.x;
    int topPositionY = paddle->position.y;
    int middlePositionY = topPositionY + TILE_HEIGHT;
    int bottomPositionY = middlePositionY + TILE_HEIGHT;

    move_sprite(paddle->id, positionX, topPositionY);
    move_sprite(paddle->id + 1, positionX, middlePositionY);
    move_sprite(paddle->id + 2, positionX, bottomPositionY);
}

void drawBall(Ball *ball) {
    move_sprite(BALL_TILE, ball->sprite.position.x, ball->sprite.position.y);
}

void renderWaitVerticalRender() {
    wait_vbl_done();
}

void drawText(uint8_t x, uint8_t y, unsigned char *text) {
    uint8_t i = 0;

    // The VRAM address of the first character
    // After setting a tile, we'll increase the VRAM address each iteration to move to the next tile
    uint8_t * vramAddr = get_bkg_xy_addr(x, y);

    while (text[i] != '\0') {
        // Map our alphabet characters to only use uppercase letters
        // From the font.png
        if (text[i] >= 'A' && text[i] <= 'Z') {
            set_vram_byte(vramAddr++, FONT_TILES_START + (text[i] - 'A'));
        }
        else if (text[i] >= 'a' && text[i] <= 'z') {
            set_vram_byte(vramAddr++, FONT_TILES_START + (text[i] - 'a'));
        }
        else if (text[i] >= '0' && text[i] <= '9') {
            set_vram_byte(vramAddr++, FONT_TILES_START + 26 + (text[i] - '0'));
        }
        else {
            // Map our special characters manually
            // From the font.png
            switch (text[i]) {
                case '.':
                    set_vram_byte(vramAddr++, FONT_TILES_START + 36);
                    break;
                case '-':
                    set_vram_byte(vramAddr++, FONT_TILES_START + 37);
                    break;
                case '=':
                    set_vram_byte(vramAddr++, FONT_TILES_START + 38);
                    break;
                case '*':
                    set_vram_byte(vramAddr++, FONT_TILES_START + 39);
                    break;
                case '?':
                    set_vram_byte(vramAddr++, FONT_TILES_START + 40);
                    break;
                case '!':
                    set_vram_byte(vramAddr++, FONT_TILES_START + 41);
                    break;
                case ' ':
                    set_vram_byte(vramAddr++, 0);
                    break;
            }
        }

        i++;
    }
}

void drawNumber(uint8_t x, uint8_t y, uint16_t number, uint8_t digits) {
    unsigned char buffer[8] = "00000000";

    // Convert the number to a decimal string (stored in the buffer char array)
    uitoa(number, buffer, 10);

    // The background address of the first digit
    uint8_t * vramAddr = get_bkg_xy_addr(x, y);

    // Get the length of the number so we can add leading zeroes
    uint8_t len = strlen(buffer);

    // Add some leading zeroes
    // uitoa will not do this for us
    // Increase the VRAM address each iteration to move to the next tile
    for (uint8_t i = 0; i < digits - len; i++) {
        set_vram_byte(vramAddr++, FONT_TILES_START + 26);
    }

    // Draw our number
    // Increase the VRAM address each iteration to move to the next tile
    for (uint8_t i = 0; i < len; i++) {
        set_vram_byte(vramAddr++, (buffer[i] - '0') + FONT_TILES_START + 26);
    }
}

void drawScores(uint8_t x, uint8_t y, uint16_t number) {
    unsigned char buffer[8] = "00000000";

    // Convert the number to a decimal string (stored in the buffer char array)
    uitoa(number, buffer, 10);

    // The window address of the first digit
    uint8_t * vramAddr = get_bkg_xy_addr(x, y);
    uint8_t * vramAddrSecondRow = get_bkg_xy_addr(x, y+1);

    // Get the length of the number, so we can add leading zeroes
    uint8_t len = strlen(buffer);

    // Draw our number
    // Increase the VRAM address each iteration to move to the next tile
    for (uint8_t i = 0; i < len; i++) {
        set_vram_byte(vramAddr++, (buffer[i] - '0') + FONT_SCORES_START);
        set_vram_byte(vramAddrSecondRow++, (buffer[i] - '0') + FONT_SCORES_SECOND_ROW);
    }
}

void scrollBackground(int8_t x, int8_t y) {
    scroll_bkg(x, y);
}

Vector2D_16 backgroundPosition() {
    Vector2D_16 result = {
        .x = SCX_REG,
        .y = SCY_REG
    };

    return result;
}