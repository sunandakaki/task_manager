#include "systemMonitor.h"
#include <ncurses.h>
#include <chrono>
#include <thread>
#include <future>

SystemMonitor::SystemMonitor() {}

SystemMonitor::~SystemMonitor()
{
    for (auto &thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

// void SystemMonitor::startMonitoring()
// {
//     // Start each monitoring component in a separate thread
//     threads.emplace_back(&CpuMonitor::start, &cpuMonitor);
//     threads.emplace_back(&MemoryMonitor::start, &memoryMonitor);
//     threads.emplace_back(&DiskMonitor::start, &diskMonitor);
//     threads.emplace_back(&NetworkMonitor::start, &networkMonitor);

//     // Refresh loop
//     while (true)
//     {
//         refresh();
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//     }
// }

void SystemMonitor::startMonitoring()
{
    // Asynchronous tasks as before
    auto cpuFuture = std::async(std::launch::async, &CpuMonitor::start, cpuMonitor.get());
    auto memoryFuture = std::async(std::launch::async, &MemoryMonitor::start, memoryMonitor.get());
    auto diskFuture = std::async(std::launch::async, &DiskMonitor::start, diskMonitor.get());
    auto networkFuture = std::async(std::launch::async, &NetworkMonitor::start, networkMonitor.get());

    bool running = true;
    bool paused = false;

    while (running)
    {
        int ch = getch();
        switch (ch)
        {
        case 'p':
            paused = true;
            break;
        case 'r':
            paused = false;
            break;
        case 'q':
            running = false;
            break;
        case KEY_RESIZE:
            clear();
            break;
        }

        if (!paused)
        {
            refresh();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    // Clean exit
    cpuFuture.get();
    memoryFuture.get();
    diskFuture.get();
    networkFuture.get();
}

void SystemMonitor::refresh()
{
    clear(); // Clear ncurses screen
    displayStats();
    refresh(); // Refresh ncurses screen
}

// void SystemMonitor::displayStats()
// {
//     // Display CPU, Memory, Disk, and Network stats
//     mvprintw(0, 0, "CPU Usage: %.2f%%", cpuMonitor.getCpuUsage());
//     mvprintw(1, 0, "Memory Usage: %.2f%%", memoryMonitor.getMemoryUsage());
//     mvprintw(2, 0, "Disk Usage: %.2f%%", diskMonitor.getDiskUsage());
//     mvprintw(3, 0, "Network Usage: %.2f%%", networkMonitor.getNetworkUsage());
// }

void SystemMonitor::displayStats()
{
    // Initialize ncurses color pairs
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "CPU Usage: %.2f%%", cpuMonitor->getCpuUsage());
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(1, 0, "Memory Usage: %.2f%%", memoryMonitor->getMemoryUsage());
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    mvprintw(2, 0, "Disk Usage: %.2f%%", diskMonitor->getDiskUsage());
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(4));
    mvprintw(3, 0, "Network Usage: %.2f KB/s", networkMonitor->getNetworkUsage());
    attroff(COLOR_PAIR(4));
}
