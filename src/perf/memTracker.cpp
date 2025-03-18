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
    //stream.close();
}

void perf::MemTracker::addAlloc(std::size_t size)
{
    allocatedMemory += size;
    addMessage("New allocation: " + std::to_string(size));
    addMessage("Currently allocated: " + std::to_string(allocatedMemory));
    addMessage("Currently freed: " + std::to_string(freedMemory));
}

void perf::MemTracker::addFree(std::size_t size)
{
    allocatedMemory -= size;
    addMessage("Freed allocation: " + std::to_string(size));
    addMessage("Currently allocated: " + std::to_string(allocatedMemory));
    addMessage("Currently freed: " + std::to_string(freedMemory));
}

void perf::MemTracker::addMessage(const std::string &message)
{
    std::ofstream stream(FILENAME, std::ios::out | std::ios::app);

    if (stream.good()) {
        stream << message << '\n';
    }
    else {
        std::cerr << "Couldn't open log.txt\n";
    }

    stream.close();
}
