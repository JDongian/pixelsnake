#if !(_Timer_h)
#define _Timer_h 1

// Lazyfoo
#include "SDL/SDL.h"

class LTimer
{
    public:
        //Initializes variables
        LTimer();

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        Uint32 get_ticks();

        //Checks the status of the timer
        bool is_started();
        bool is_paused();

    private:
        //The clock time when the timer started
        Uint32 mStartTicks;

        //The ticks stored when the timer was paused
        Uint32 mPausedTicks;

        //The timer status
        bool mPaused;
        bool mStarted;
};

#endif /* !(_Timer_h) */
