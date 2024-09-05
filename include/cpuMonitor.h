#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

class CpuMonitor
{
public:
    CpuMonitor();
    ~CpuMonitor();
    void start();
    double getCpuUsage(); // Example function, implement more as needed

private:
    // Add private members for CPU data
};

#endif // CPU_MONITOR_H
