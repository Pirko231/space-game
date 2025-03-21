#include "program.hpp"

#ifdef UNITTESTS
#include "tests.hpp"
#endif

int main()
{
    Program program;

    #if UNITTESTS
    Tests::check(&program);
    #endif

    while (program.running())
    {
        #if SPEEDTRACKER
        if (perf::SpeedTracker::get().working())
            perf::SpeedTracker::get().frameClock.restart();
        sf::Time currentTime;
        #endif
        program.handleEvents();
        #if SPEEDTRACKER
        if (perf::SpeedTracker::get().working())
            perf::SpeedTracker::get().handleEventsTime = perf::SpeedTracker::get().frameClock.getElapsedTime() - currentTime;
        currentTime = perf::SpeedTracker::get().frameClock.getElapsedTime();
        #endif
        program.update();
        #if SPEEDTRACKER
        if (perf::SpeedTracker::get().working())
            perf::SpeedTracker::get().updateTime = perf::SpeedTracker::get().frameClock.getElapsedTime() - currentTime;
        currentTime = perf::SpeedTracker::get().frameClock.getElapsedTime();
        #endif
        program.display();
        #if SPEEDTRACKER
        if (perf::SpeedTracker::get().working())
            perf::SpeedTracker::get().displayTime = perf::SpeedTracker::get().frameClock.getElapsedTime() - currentTime;
        currentTime = perf::SpeedTracker::get().frameClock.getElapsedTime();
        #endif

        #if SPEEDTRACKER
        if (perf::SpeedTracker::get().working())
            perf::SpeedTracker::get().frameTime = perf::SpeedTracker::get().frameClock.getElapsedTime();
        perf::SpeedTracker::get().update();
        #endif
    }
}