#include "memTracker.hpp"

#define FILENAME "memTracker.txt"

perf::MemTracker::MemTracker()
{
    //wyczyszczenie pliku
    std::ofstream stream(FILENAME, std::ios::out | std::ios::trunc);
		stream.close();
}

perf::MemTracker::~MemTracker()
{
    std::ofstream stream(FILENAME, std::ios::out | std::ios::app);
    if (stream.good()) 
    {
        stream << "!----------------podsumowanie-----------------!" << '\n';
        stream << "Maksymalna pamiec: " + std::to_string(maxAllocatedMemory) << '\n';
        stream << "Cala zaalokowana pamiec: " + std::to_string(allocatedMemory) << '\n';
        stream << "Cala zwolniona pamiec: " + std::to_string(freedMemory) << '\n';
    }
    else 
    {
        std::cerr << "Couldn't open log.txt\n";
    }
    stream.close();
}

void perf::MemTracker::addAlloc(std::size_t size)
{
    allocatedMemory += size;
    if (allocatedMemory > maxAllocatedMemory)
        maxAllocatedMemory = allocatedMemory;
    addMessage("New allocation: " + std::to_string(size));
    addMessage("Currently allocated: " + std::to_string(allocatedMemory));
    addMessage("Currently freed: " + std::to_string(freedMemory));
}

void perf::MemTracker::addFree(std::size_t size)
{
    freedMemory += size;
    addMessage("Freed allocation: " + std::to_string(size));
    addMessage("Currently allocated: " + std::to_string(allocatedMemory - freedMemory));
    addMessage("Currently freed: " + std::to_string(freedMemory));
}

void perf::MemTracker::addMessage(const std::string &message)
{
    std::ofstream stream(FILENAME, std::ios::out | std::ios::app);

    if (stream.good()) 
    {
        stream << message << '\n';
    }
    else 
    {
        std::cerr << "Couldn't open log.txt\n";
    }

    stream.close();
}
