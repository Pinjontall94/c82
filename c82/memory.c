#include <stdlib.h>
#include "config.h"
#include "chip8.h"

bool address_in_bounds(short unsigned address) {
	return 0 <= address <= CHIP8_MEMORY_SIZE ? true : false;
}

char unsigned peek(struct Chip8* chip8, short unsigned address) {
	if (!address_in_bounds(address)) return NULL;
	return chip8->memory[address];
}

bool poke(struct Chip8* chip8, short unsigned address, char unsigned value) {
	if (!address_in_bounds(address)) {
		return false;
	}
	else {
		chip8->memory[address] = value;
		return true;
	}
}