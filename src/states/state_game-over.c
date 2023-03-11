#include "state_game-over.h"
#include "states_type.h"
#include "render.h"

uint8_t count = 0;

void StateInitGameOver(void) {
    count = 0;
    loadGameOver();
}

uint8_t StateUpdateGameOver(uint8_t deltaTime) {
    renderWaitVerticalRender();

    return (count++ > 250) ? STATE_SCREEN_START : STATE_GAME_OVER;
}