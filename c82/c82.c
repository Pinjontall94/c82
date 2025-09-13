// c82.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>
#include "config.h"
#include "chip8.h"
#include "virt_hardware_screen.h"
//#include "virt_hardware_speaker.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static struct Chip8* c8 = NULL;

const char keyboard_map[] = {
    SDLK_X, SDLK_1, SDLK_2, SDLK_3,
    SDLK_Q, SDLK_W, SDLK_E, SDLK_A,
    SDLK_S, SDLK_D, SDLK_Z, SDLK_C,
    SDLK_4, SDLK_R, SDLK_F, SDLK_V,
};


/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    if (!SDL_CreateWindowAndRenderer(
        "chip8",
        SCREEN_WIDTH * WINDOW_MULTIPLIER,
        SCREEN_HEIGHT * WINDOW_MULTIPLIER,
        SDL_WINDOW_RESIZABLE, &window, &renderer
    )) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!init_chip8(&c8)) {
        SDL_Log("failed to init chip8: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    /* Draw the message */
    SDL_SetRenderDrawColor(renderer, 0x64, 0x95, 0xed, 0xff);
    SDL_RenderClear(renderer);

    draw_pixel(renderer, 10, 10);

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    free(c8);
}