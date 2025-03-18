#pragma once

#include <iostream>
#include <fstream>

namespace perf
{

class MemTracker
{
public:
    //MemTracker();
    MemTracker(const MemTracker&) = delete;
    MemTracker& operator=(const MemTracker&) = delete;
    ~MemTracker();

    static MemTracker& get()
    {
        static MemTracker mTracker;
        return mTracker;
    }

    void addAlloc(std::size_t size);
    void addFree(std::size_t size);
    void addMessage(const std::string&);
private:
    MemTracker();

    long long int allocatedMemory{0};

    long long int freedMemory{0};

    long long int maxAllocatedMemory{0};
};
};