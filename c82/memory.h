#pragma once
#define MEMORY_H
#include <stdbool.h>
#include "config.h"
#include "chip8.h"

bool address_in_bounds(short unsigned address);
char unsigned peek(struct Chip8* chip8, short unsigned address);
bool poke(struct Chip8* chip8, short unsigned address, char unsigned value);
