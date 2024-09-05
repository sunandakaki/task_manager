#include "cpuMonitor.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>
#include <vector>

CpuMonitor::CpuMonitor() : prevIdleTime(0), prevTotalTime(0) {}

CpuMonitor::~CpuMonitor() {}

void CpuMonitor::start()
{
    while (true)
    {
        calculateCpuUsage();
        calculateCoreUsage();    // New function to monitor each core
        calculateCpuFrequency(); // New function to monitor CPU frequency
        calculateLoadAverage();  // New function to monitor load average
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void CpuMonitor::calculateCoreUsage()
{
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line); // Skip the first line (aggregated CPU stats)

    while (std::getline(file, line))
    {
        if (line.substr(0, 3) != "cpu")
            break; // Stop if no more CPU cores are listed

        // Parse core statistics similar to the aggregate CPU stats
        // Compute usage for each core and store in a vector or other data structure
    }
}

void CpuMonitor::calculateCpuFrequency()
{
    std::ifstream file("/proc/cpuinfo");
    std::string line;
    while (std::getline(file, line))
    {
        if (line.find("cpu MHz") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string key;
            double frequency;
            iss >> key >> key >> frequency; // Skip "cpu" and "MHz"
            cpuFrequency = frequency;
            break;
        }
    }
}

void CpuMonitor::calculateLoadAverage()
{
    std::ifstream file("/proc/loadavg");
    file >> loadAverage1 >> loadAverage5 >> loadAverage15;
}

double CpuMonitor::getCpuFrequency()
{
    return cpuFrequency;
}

double CpuMonitor::getLoadAverage(int period)
{
    switch (period)
    {
    case 1:
        return loadAverage1;
    case 5:
        return loadAverage5;
    case 15:
        return loadAverage15;
    default:
        return loadAverage1;
    }
}
