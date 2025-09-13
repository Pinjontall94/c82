#pragma once
#define STACK_H
#include "config.h"
#include <stdbool.h>

bool stack_out_of_bounds(struct Chip8* chip8);
short unsigned pop(struct Chip8* chip8);
bool push(struct Chip8* chip8, short unsigned value);