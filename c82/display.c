#include "config.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static void pixel_in_bounds(int x, int y) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && SCREEN_HEIGHT) {
        return;
    }
    else {
        fprintf(stderr, "pixel out of bounds: %i, %i\n", x, y);
        exit(EXIT_FAILURE);
    }
}

void set_pixel(bool** screen, int x, int y) {
    pixel_in_bounds(x, y);
    screen[y][x] = true;
}

bool get_pixel(bool** screen, int x, int y) {
    pixel_in_bounds(x, y);
    return screen[y][x];
}