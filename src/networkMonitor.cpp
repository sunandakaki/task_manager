#include "networkMonitor.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>

NetworkMonitor::NetworkMonitor() : prevReceivedBytes(0), prevTransmittedBytes(0) {}

NetworkMonitor::~NetworkMonitor() {}

void NetworkMonitor::start()
{
    while (true)
    {
        calculateNetworkUsage();
        calculateTransferRates(); // New function for transfer rates
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void NetworkMonitor::calculateTransferRates()
{
    receivedRate = (receivedBytes - prevReceivedBytes) / 1024.0;          // KB/s
    transmittedRate = (transmittedBytes - prevTransmittedBytes) / 1024.0; // KB/s
    prevReceivedBytes = receivedBytes;
    prevTransmittedBytes = transmittedBytes;
}

double NetworkMonitor::getReceivedRate()
{
    return receivedRate;
}

double NetworkMonitor::getTransmittedRate()
{
    return transmittedRate;
}
