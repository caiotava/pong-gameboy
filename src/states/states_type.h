#ifndef PONG_STATES_TYPE_H
#define PONG_STATES_TYPE_H

#include<stdint.h>

enum StatesType {
    STATE_INITIALIZATION = 0,
    STATE_SCREEN_START,
    STATE_SCREEN_GAMEPLAY,
    STATE_GAME_OVER
};

typedef void (*StateInitFunc)(void);
typedef uint8_t (*StateUpdateFunc)(uint8_t deltaTime);

typedef struct {
    enum StatesType type;
    StateInitFunc initFunc;
    StateUpdateFunc updateFunc;
} State;

void stateInitEmpty();
uint8_t stateUpdateEmpty(uint8_t deltaTime);

void stateInitInitialization();
uint8_t stateUpdateInitialization(uint8_t deltaTime);

#endif //PONG_STATES_TYPE_H
