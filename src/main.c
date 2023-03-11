#include "render.h"
#include "input.h"
#include "sound.h"
#include "states/states.h"

void main() {
    initRender();
    initSound();

    State *currentState = &states[STATE_INITIALIZATION];
    enum StatesType nextState = currentState->type;

    while (1) {
        updateInput();

        nextState = currentState->updateFunc(0);

        if (nextState != currentState->type) {
            clearScreen();
            currentState = &states[nextState];
            currentState->initFunc();
        }
    }
}

