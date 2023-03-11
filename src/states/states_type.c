#include "states_type.h"
#include "render.h"

void stateInitEmpty() {

}

uint8_t stateUpdateEmpty(uint8_t deltaTime) {
    return STATE_INITIALIZATION;
}

void stateInitInitialization() {

}

uint8_t stateUpdateInitialization(uint8_t deltaTime) {
    renderWaitVerticalRender();

    return STATE_SCREEN_START;
}