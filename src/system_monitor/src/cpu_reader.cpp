#include <iostream>
#include <string>
#include <fstream>

int main() {

    std::ifstream procStatFile("/proc/stat");

    if (!procStatFile.is_open()) {
        std::cerr << "Could not open /proc/stat\n";
        return 1;
    }

    std::string procStatLine;

    if (!std::getline(procStatFile, procStatLine)) {
        std::cerr << "Failed to read /proc/stat\n";
        return 1;
    }
    std::cout << procStatLine << "\n";

    return 0;
}
