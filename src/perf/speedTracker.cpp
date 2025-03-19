#include "speedTracker.hpp"

#define FILENAME "speedTracker.txt"

perf::SpeedTracker::SpeedTracker(int _logTime)
{
    logTime = _logTime;
    times = _logTime;
    std::ofstream stream(FILENAME, std::ios::out | std::ios::trunc);
		stream.close();
}

perf::SpeedTracker::~SpeedTracker()
{
    std::ofstream stream(FILENAME, std::ios::out | std::ios::app);
    if (stream.good())
    {
        stream << "!----------------podsumowanie-----------------!" << '\n';
        stream << "Czas na klatke(miliskendy): " << frameTime.asMilliseconds() << '\n';
        stream << "Maksymalny czas(milisekundy): " << maxTime.asMilliseconds() << '\n';
    }
    else 
    {
        std::cerr << "Couldn't open log.txt\n";
    }
    stream.close();
}

void perf::SpeedTracker::update()
{
    if (frameTime > maxTime)
        maxTime = frameTime;
    
    times++;
    if (times >= logTime)
    {
        std::ofstream stream(FILENAME, std::ios::out | std::ios::app);

        if (stream.good())
        {
            stream << "Czas na klatke(milisekundy): " << frameTime.asMilliseconds() << '\n';
            stream << "Czas na funkcje update(milisekundy): " << updateTime.asMilliseconds() << '\n';
            stream << "Czas na funkcje handleEvents(milisekundy): " << handleEventsTime.asMilliseconds() << '\n';
            stream << "Czas na funkcje display(milisekundy): " << displayTime.asMilliseconds() << '\n';
        }
        else
        {
            std::cerr << "Couldn't open log.txt\n";
        }

        stream.close();
        times = 0;
    }
    return;
}

void foo()
{
    perf::SpeedTracker::get().frameClock.restart();
    sf::Time time = perf::SpeedTracker::get().frameClock.getElapsedTime();
}
