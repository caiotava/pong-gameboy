#include "input.h"

uint8_t buttonA;
uint8_t buttonB;
uint8_t buttonUp;
uint8_t buttonRight;
uint8_t buttonDown;
uint8_t buttonLeft;
uint8_t buttonStart;
uint8_t buttonSelect;

void updateInput()
{
    uint8_t v = joypad();

    buttonA = v & J_A;
    buttonB = v & J_B;
    buttonUp = v & J_UP;
    buttonRight = v & J_RIGHT;
    buttonDown = v & J_DOWN;
    buttonLeft = v & J_LEFT;
    buttonStart = v & J_START;
    buttonSelect = v & J_SELECT;
}