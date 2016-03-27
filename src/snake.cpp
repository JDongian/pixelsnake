#include <string>
#include "assert.h"

#include "SDL/SDL.h"
#include "Timer.h"

#include "Params.h"
#include "Snake.h"
#include "Food.h"

SDL_Surface *screen = NULL;

SDL_Event event;

template <typename T>
T bound(T& x, const T& min, const T& max) {
    assert (min < max);
    if (x > max) { x = max; }
    if (x < min) { x = min; }
    return x;
}

int init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        return false;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
                              SCREEN_BPP, SDL_SWSURFACE);
    if(screen == NULL) {
        return false;
    }

    //Wat
    if(SDL_EnableUNICODE(1) == -1) {
        return false;
    }

    SDL_WM_SetCaption("Pixel Snake", NULL);

    return true;
}

void clean_up() {
    SDL_FreeSurface(screen);
    SDL_Quit();
}

void handle_events(bool& quit) {
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_q) {
                quit = true;
            }
        } else if (event.type == SDL_QUIT) {
            quit = true;
        }
    }
}

void show(SDL_Surface* surf) {
    SDL_FillRect(surf, &surf->clip_rect,
                     SDL_MapRGB(surf->format, 0x00, 0x00, 0x00));
}

int main(int argc, char* args[]) {
    bool quit = false;
    if (init() == false) {
        return 1;
    }

    Food* food = new Food;
    Snake snake(8, 8, 50, food);

    LTimer fps_timer; 
    LTimer cap_timer;
    long frame_count = 0;
    fps_timer.start();

    while (!quit) {
        cap_timer.start();

        float avg_fps = frame_count / (fps_timer.get_ticks() / 1000.f);
        if(avg_fps > 2000000) {
            avg_fps = 0;
        }

        handle_events(quit);
        food->handle_events();
        snake.handle_events();

        food->update();
        snake.update();

        show(screen);
        food->show(screen);
        snake.show(screen);

        if (SDL_Flip(screen) == -1) {
            return 1;
        }

        ++frame_count;
        int frame_ticks = cap_timer.get_ticks();
        if (frame_ticks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
        }

        printf("FPS: %.1f\r", 1000.f / cap_timer.get_ticks());
    }

    clean_up();
    return 0;
}
