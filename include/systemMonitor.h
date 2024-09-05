#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include "CpuMonitor.h"
#include "MemoryMonitor.h"
#include "DiskMonitor.h"
#include "NetworkMonitor.h"
#include <vector>
#include <thread>

class SystemMonitor
{
public:
    SystemMonitor();
    ~SystemMonitor();
    void startMonitoring();

private:
    CpuMonitor cpuMonitor;
    MemoryMonitor memoryMonitor;
    DiskMonitor diskMonitor;
    NetworkMonitor networkMonitor;

    std::vector<std::thread> threads;
    void displayStats();
    void refresh();
};

#endif // SYSTEM_MONITOR_H
