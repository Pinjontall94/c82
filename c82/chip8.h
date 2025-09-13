#pragma once
#define CHIP8_H
#include <stdbool.h>
#include "config.h"
#include "stack.h"
/*
#include <display.h>
#include <keyboard.h>
#include <memory.h>
*/

struct Registers {
    char unsigned V[CHIP8_NUM_DATA_REGISTERS];
    short unsigned I;
    char unsigned DL, DS;
    char unsigned SP;
    short unsigned PC;
};

struct Chip8 {
    bool screen[SCREEN_WIDTH][SCREEN_HEIGHT];
    char unsigned memory[0x1000];
    char unsigned keyboard[0xf];
    struct Registers registers;
    short unsigned stack[CHIP8_TOTAL_STACK_DEPTH];
};

bool init_chip8(struct Chip8 *chip8);
bool destroy_chip8(struct Chip8 *chip8);