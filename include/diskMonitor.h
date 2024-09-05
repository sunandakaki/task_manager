#ifndef DISK_MONITOR_H
#define DISK_MONITOR_H

class DiskMonitor
{
public:
    DiskMonitor();
    ~DiskMonitor();
    void start();
    double getDiskUsage(); // Example function, implement more as needed

private:
    // Add private members for disk data
};

#endif // DISK_MONITOR_H
