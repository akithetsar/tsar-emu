#include <iostream>
#include <fstream>
#include "h/Emulator.hpp"
#include "h/log.h"
#include "h/CPU.h"







//---- Gameboy Doctor Blargg CPU instruction testing.
int main() {
    // Use a basic test ROM first (e.g., cpu_instrs/individual/01-special.gb)
    Emulator emulator = Emulator("C:\\Users\\akith\\CLionProjects\\GBEmulator\\ROMS\\02-interrupts.gb");
    emulator.bootEmu();

    // Redirect cout to file
    std::ofstream logFile("emulator_log.txt");
    std::streambuf* coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(logFile. rdbuf());

    // Run for a limited number of instructions
    const int MAX_INSTRUCTIONS = 10000000;

    for (int i = 0; i < MAX_INSTRUCTIONS; i++) {
        emulator.cpu->cycle();

        // Optional: Stop if halted or infinite loop detected
        // if (emulator.cpu->isHalted()) break;
    }

    // Restore cout
    std::cout.rdbuf(coutBuf);
    logFile.close();

    std::cout << "Log written to emulator_log.txt" << std::endl;
    return 0;
}