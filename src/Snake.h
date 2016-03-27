#include <list>

#include "SDL/SDL.h"
#include "Timer.h"
#include "PixelModifier.h"
#include "Food.h"


class Snake : public PixelModifier {
    private:
        enum direction_t {
            UP = 0,
            DOWN = 1,
            LEFT = 2,
            RIGHT = 3
        };

        std::list<std::pair<int, int>> position;
        double speed;
        Uint32 color;
        LTimer run_timer;
        double remainder;

        direction_t dir;

        void update_position();
        std::pair<int, int> new_head_position();

        Food* food;
    public:
        Snake(int x, int y, double speed, Food* food);
        void update();
        void handle_events();
        void show(SDL_Surface* screen) const;
};
