#ifndef PONG_INPUT_H
#define PONG_INPUT_H

#include<gb/gb.h>

extern uint8_t buttonA;
extern uint8_t buttonB;
extern uint8_t buttonUp;
extern uint8_t buttonRight;
extern uint8_t buttonDown;
extern uint8_t buttonLeft;
extern uint8_t buttonStart;
extern uint8_t buttonSelect;

void updateInput();

#endif //PONG_INPUT_H
