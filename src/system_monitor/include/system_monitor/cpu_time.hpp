#pragma once
#include <cstdint>

struct CpuTimes {               // Time executing:
    std::uint64_t user;         // User code
    std::uint64_t nice;         // A process with modified priority
    std::uint64_t system;       // Kernel code
    std::uint64_t idle;         // Nothing
    std::uint64_t iowait;       // Waiting for input/output operations
    std::uint64_t irq;          // Time spent handling hardware interrupts
    std::uint64_t softirq;      // Time spent handling software interrupts
    std::uint64_t steal;        // Time yielded to the hypervisor
    std::uint64_t guest;        // Virtual machines
    std::uint64_t guest_nice;   // Virtual machines with modified priority
};
