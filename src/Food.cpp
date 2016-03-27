#include "Food.h"


Food::Food() {
    positions.insert(std::pair<int, int>(0, 0));

    speed = 100;
    color = (Uint32)0xee2222ff;

    run_timer.start();
    remainder = 0;
}

int random(int mod) {
    return rand() % mod; //non-uniform!
}

void Food::add_food() {
    std::pair<int, int> new_food =
        std::pair<int, int>(random(SCREEN_WIDTH), random(SCREEN_HEIGHT));
    positions.insert(new_food);
}

bool Food::remove_food(std::pair<int, int> position) {
    if (positions.find(position) != positions.end()) {
        positions.erase(position);
        return true;
    }
    return false;
}

void Food::update() {
    int time_delta = run_timer.get_ticks();
    double updates = time_delta * speed / 1000;
    for (updates += remainder; updates >= 1; --updates) {
        add_food();
    }
    remainder = updates;
    run_timer.start();
}

void Food::handle_events() {
}

void Food::show(SDL_Surface* screen) const {
    SDL_LockSurface(screen);
    for (auto food: positions) {
        put_pixel(screen, food.first, food.second, color);
    }
    SDL_UnlockSurface(screen);
}
