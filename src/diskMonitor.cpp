#include "diskMonitor.h"
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <chrono>

DiskMonitor::DiskMonitor() : diskUsage(0) {}

DiskMonitor::~DiskMonitor() {}

void DiskMonitor::start()
{
    while (true)
    {
        calculateDiskUsage();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void DiskMonitor::calculateDiskUsage()
{
    FILE *pipe = popen("df / --output=pcent | tail -1", "r");
    if (!pipe)
        return;

    char buffer[128];
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        sscanf(buffer, "%d%%", &diskUsage);
    }

    pclose(pipe);
}

double DiskMonitor::getDiskUsage()
{
    return diskUsage;
}
