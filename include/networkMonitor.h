#ifndef NETWORK_MONITOR_H
#define NETWORK_MONITOR_H

class NetworkMonitor
{
public:
    NetworkMonitor();
    ~NetworkMonitor();
    void start();
    double getNetworkUsage(); // Example function, implement more as needed

private:
    // Add private members for network data
};

#endif // NETWORK_MONITOR_H
