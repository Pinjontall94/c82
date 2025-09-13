#include "config.h"
#include "chip8.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* 
* Fundamentally, the confusing thing about these stack operations w/r/t bounds-
* checking is that the SP doesn't point to capacity, nor the last pushed value, 
* but rather it points to the NEXT FREE INDEX in the stack. ergo:
* 
*   SP == 0:
*     push OKAY (push then SP++)
*     pop  NO
* 
*   SP == 0x0f:
*     push NO
*     pop  OKAY (SP-- then pop)
*/

bool stack_out_of_bounds(struct Chip8* chip8) {
	/* unsigned, so no need to check for negatives */
	/* just need to make sure no greater than 0xf or 15 */
	return chip8->registers.SP >= CHIP8_TOTAL_STACK_DEPTH ? true : false;
}

bool push(struct Chip8* chip8, short unsigned value) {
	/* Check the stack pointer bounds before operation to
	 * see if it's 0x10 <-> 0xff (invalid). Then, push to
	 * the current SP, and increment to point to new FREE stack slot 
	 */
	if (stack_out_of_bounds(chip8->registers.SP)) {
		fprintf(stderr, "stack overflow!");
		return false;
	}
	chip8->stack[chip8->registers.SP] = value;
	chip8->registers.SP++;
	return true;
}

short unsigned pop(struct Chip8* chip8) {
	char unsigned value = NULL;
	/* Decrement SP before pulling value, 
	 * bc it's the index of the next FREE stack slot, NOT the amount stored
	 * 
	 *     i.e. SP-- on SP == 1 is fine
	 *          SP-- on SP == 0 is NOT
	 */
	chip8->registers.SP--;
	if (stack_out_of_bounds(chip8)) {
		fprintf(stderr, "stack underflow!");
		return NULL;
	}
	value = chip8->stack[chip8->registers.SP];
	return value;
}