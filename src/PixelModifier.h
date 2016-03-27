#if !(_PixelModifier_h)
#define _PixelModifier_h 1

#include "SDL/SDL.h"


class PixelModifier {
    public:
        void put_pixel(SDL_Surface* screen, int x, int y, const Uint32& p) const;
};

#endif /* !(_PixelModifier_h) */
