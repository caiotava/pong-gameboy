#ifndef PONG_STATES_H
#define PONG_STATES_H

#include "states_type.h"
#include "state_screen_start.h"
#include "state_gameplay.h"
#include "state_game-over.h"

extern State states[STATE_GAME_OVER + 1] = {
        {
                .type = STATE_INITIALIZATION,
                .initFunc = &stateInitInitialization,
                .updateFunc = &stateUpdateInitialization
        },
        {
                .type = STATE_SCREEN_START,
                .initFunc = &StateInitScreenStart,
                .updateFunc = &StateUpdateScreenStart
        },
        {
                .type = STATE_SCREEN_GAMEPLAY,
                .initFunc = &StateInitGamePlay,
                .updateFunc = &StateUpdateGamePlay
        },
        {
                .type = STATE_GAME_OVER,
                .initFunc = &StateInitGameOver,
                .updateFunc = &StateUpdateGameOver
        },
};


#endif //PONG_STATES_H
