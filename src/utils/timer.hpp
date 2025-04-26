#pragma once

namespace util
{

class Timer
{
public:
    Timer(int limit) {setLimit(limit);}
    void setLimit(int limit) {max = limit;}
    void update() {counter++;}
    void restart() {counter = 0;}
    bool hasTimePassed() {return counter >= max;}
private:
    int max{};
    int counter{};
};

/// @brief przelicza sekundy na ilosc klatek
inline int secondsToFrames(int seconds)
{
    return seconds * 60.f;
}

};