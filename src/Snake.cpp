#include "Snake.h"


Snake::Snake(int x_pos, int y_pos, double new_speed, Food* new_food) {
    for (int i = 0; i < 30; ++i) {
        position.push_front(std::pair<int, int>(x_pos, y_pos + i));
    }

    speed = new_speed;

    dir = DOWN;

    color = (Uint32)0x44ee44ff;

    run_timer.start();
    remainder = 0;

    food = new_food;
}

std::pair<int, int> Snake::new_head_position() {
    std::pair<int, int> new_head = position.front();
    switch (dir) {
    case UP:
        --new_head.second;
        break;
    case DOWN:
        ++new_head.second;
        break;
    case LEFT:
        --new_head.first;
        break;
    case RIGHT:
        ++new_head.first;
        break;
    }
    return new_head;
}

void Snake::update_position() {
    static bool alive = true;

    std::pair<int, int> new_head = new_head_position();

    if (alive) {
        for (auto segment: position) {
            if (new_head == segment) {
                printf("%d, %d\n", new_head.first, new_head.second);
                alive = false;
            }
        }
    }

    if (alive) {
        position.push_front(new_head);

        if (!food->remove_food(new_head)) {
            position.pop_back();
        }
    }

    //bound(x, 0, SCREEN_WIDTH - 1);
    //bound(y, 0, SCREEN_HEIGHT - 1);
}

void Snake::update() {
    int time_delta = run_timer.get_ticks();
    double updates = time_delta * speed / 1000;
    for (updates += remainder; updates >= 1; --updates) {
        update_position();
    }
    remainder = updates;
    run_timer.start();
}

void Snake::handle_events() {
    direction_t new_dir = dir;
    Uint8 *keystates = SDL_GetKeyState(NULL);
    if (keystates[SDLK_k] || keystates[SDLK_UP]) {
        if (dir != DOWN) {
            new_dir = UP;
        }
    }
    if (keystates[SDLK_j] || keystates[SDLK_DOWN]) {
        if (dir != UP) {
            new_dir = DOWN;
        }
    }
    if (keystates[SDLK_h] || keystates[SDLK_LEFT]) {
        if (dir != RIGHT) {
            new_dir = LEFT;
        }
    }
    if (keystates[SDLK_l] || keystates[SDLK_RIGHT]) {
        if (dir != LEFT) {
            new_dir = RIGHT;
        }
    }
    // TODO:
    // solve the issue with holding LEFT, then pressing UP reversal
    // probably an event queue
    // this also solves biased inputs
    if (new_dir != dir) {
        //printf("CHANGE\n");
        dir = new_dir;
    }
}

void Snake::show(SDL_Surface* screen) const {
    SDL_LockSurface(screen);
    for (auto segment: position) {
        put_pixel(screen, segment.first, segment.second, color);
    }
    SDL_UnlockSurface(screen);
}
