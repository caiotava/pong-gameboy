#include <gbdk/emu_debug.h>

#include "state_screen_start.h"
#include "render.h"
#include "input.h"
#include "states_type.h"

int blinkCounter = 29;

void StateInitScreenStart(void) {
    loadScreenStart();
}

uint8_t StateUpdateScreenStart(uint8_t deltaTime) {
    Vector2D_16 *backgroundPos = &backgroundPosition();

    if (backgroundPos->y > 0) {
        scrollBackground(0, 1);
    }

    if (backgroundPos->y == 0) {
        blinkCounter++;
        drawText(6, 17, "caiotava");

        if (blinkCounter == 30) {
            blinkCounter = 0;

            // If there is anything at this tile
            if (get_bkg_tile_xy(2, 13) != 0) {
                fill_bkg_rect(2, 13, 16, 1, 0);
            } else {
                drawText(2, 13, "PUSH ANY BUTTON");
            }
        }

        if (buttonA || buttonB || buttonStart || buttonSelect) {
            return STATE_SCREEN_GAMEPLAY;
        }
    }

    renderWaitVerticalRender();

    return STATE_SCREEN_START;
}