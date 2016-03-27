#include "PixelModifier.h"


void PixelModifier::put_pixel(SDL_Surface* screen,
        int x, int y, const Uint32& p) const {
    Uint32* p_screen = (Uint32*)screen->pixels;
    p_screen += y*screen->w+x;
    *p_screen = SDL_MapRGBA(screen->format,
            p >> 4 * 6 & 0xff,
            p >> 4 * 4 & 0xff,
            p >> 4 * 2 & 0xff,
            p >> 4 * 0 & 0xff);
}
