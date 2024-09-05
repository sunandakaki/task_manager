#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

class MemoryMonitor
{
public:
    MemoryMonitor();
    ~MemoryMonitor();
    void start();
    double getMemoryUsage(); // Example function, implement more as needed

private:
    // Add private members for memory data
};

#endif // MEMORY_MONITOR_H
