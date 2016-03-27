#if !(_Food_h)
#define _Food_h 1

#include <set>
#include <stdlib.h>

#include "SDL/SDL.h"
#include "Timer.h"
#include "PixelModifier.h"
#include "Params.h"


class Food : public PixelModifier {
    private:
        std::set<std::pair<int, int>> positions;
        double speed;
        Uint32 color;

        LTimer run_timer;
        double remainder;
        void add_food(void);
    public:
        Food();
        void update(void);
        void handle_events(void);
        void show(SDL_Surface* screen) const;
        bool remove_food(std::pair<int, int> position);
};

#endif /* !(_Food_h) */
