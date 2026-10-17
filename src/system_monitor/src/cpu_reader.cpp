#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <optional>
#include <limits>
#include <cstdint>
#include "system_monitor/cpu_time.hpp"

bool readCpuTimes(CpuTimes& result){

    std::ifstream procStatFile("/proc/stat");

    if (!procStatFile.is_open()) {
        std::cerr << "Could not open /proc/stat\n";
        return false;
    }

    std::string procStatLine;

    if (!std::getline(procStatFile, procStatLine)) {
        std::cerr << "Failed to read /proc/stat\n";
        return false;
    }

    std::istringstream cpuStream(procStatLine);

    std::string cpuLabel;
    if (!(cpuStream >> cpuLabel) || cpuLabel != "cpu") {
        std::cerr << "Failed to parse CPU label\n";
        return false;
    }

    if (!(cpuStream >> result.user >> result.nice
                    >> result.system >> result.idle
                    >> result.iowait >> result.irq
                    >> result.softirq >> result.steal
                    >> result.guest >> result.guest_nice)) {
        std::cerr << "Failed to parse CPU statistics\n";
        return false;
    }

    return true;
}

std::uint64_t calculateWorkTime(const CpuTimes& times){
    return times.user + times.nice +
        times.system + times.irq +
        times.softirq + times.steal;
}

bool hasCounterRegression(const CpuTimes& previous, const CpuTimes& current) {
    return current.user < previous.user ||
           current.nice < previous.nice ||
           current.system < previous.system ||
           current.idle < previous.idle ||
           current.iowait < previous.iowait ||
           current.irq < previous.irq ||
           current.softirq < previous.softirq ||
           current.steal < previous.steal ||
           current.guest < previous.guest ||
           current.guest_nice < previous.guest_nice;
}

std::optional<double> calculateUsage(const CpuTimes& previous, const CpuTimes& current) {

    if (hasCounterRegression(previous, current)) {
        return std::nullopt;
    }

    const std::uint64_t previousWorkTime = calculateWorkTime(previous);
    const std::uint64_t currentWorkTime = calculateWorkTime(current);

    const std::uint64_t previousFreeTime = previous.idle + previous.iowait;
    const std::uint64_t currentFreeTime = current.idle + current.iowait;

    const std::uint64_t deltaWork = currentWorkTime - previousWorkTime;
    const std::uint64_t deltaFree = currentFreeTime - previousFreeTime;
    const std::uint64_t deltaTotal = deltaWork + deltaFree;

    if (deltaTotal == 0) {
        return std::nullopt;
    }

    return 100.0 * static_cast<double>(deltaWork) / deltaTotal;
}

int main() {

    CpuTimes cpuTimes1{};
    if(!readCpuTimes(cpuTimes1)){
        std::cerr << "Failed to update cpuTimes1\n";
        return 1;
    };

    std::cout << "User: " << cpuTimes1.user
              << "\nSystem: " << cpuTimes1.system
              << "\nIdle: " << cpuTimes1.idle << "\n";

    return 0;
}
