#include <gb/gb.h>

#include "sound.h"

void initSound() {
    // This enables Sound
    // these registers must be in this specific order!
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which channels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
}

void playBounceSound() {
    NR41_REG=0x2A;
    NR42_REG=0xA7;
    NR43_REG=0x57;
    NR44_REG=0xC0;
}