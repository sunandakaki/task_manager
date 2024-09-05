#include "memoryMonitor.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>

MemoryMonitor::MemoryMonitor() : totalMemory(0), freeMemory(0), bufferMemory(0), cacheMemory(0) {}

MemoryMonitor::~MemoryMonitor() {}

void MemoryMonitor::start()
{
    while (true)
    {
        calculateMemoryUsage();
        calculateBufferCacheUsage(); // New function for buffer/cache
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void MemoryMonitor::calculateBufferCacheUsage()
{
    std::ifstream file("/proc/meminfo");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string key;
        long value;
        iss >> key >> value;
        if (key == "Buffers:")
        {
            bufferMemory = value;
        }
        else if (key == "Cached:")
        {
            cacheMemory = value;
        }
    }
}

long MemoryMonitor::getBufferMemory()
{
    return bufferMemory;
}

long MemoryMonitor::getCacheMemory()
{
    return cacheMemory;
}
