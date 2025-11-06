#include <iostream>
#include <fstream>
#include "h/Emulator.hpp"
#include "h/log.h"
#include "h/CPU.h"







//---- Gameboy Doctor Blargg CPU instruction testing.
//int main() {
//
//    Emulator emulator = Emulator(R"(C:\Users\akith\CLionProjects\GBEmulator\ROMS\02-interrupts.gb)");
//    emulator.bootEmu();
//
//    // Redirect cout to file
//    std::ofstream logFile("log.txt");
//    std::streambuf* coutBuf = std::cout.rdbuf();
//    std::cout.rdbuf(logFile.rdbuf());
//    std::cout << "Test";
//    // Run for a limited number of instructions
//    const int MAX_INSTRUCTIONS = 10000000; // Adjust as needed
//    int line = 1;
//
//    for (int i = 0; i < MAX_INSTRUCTIONS; i++) {
//        emulator.cpu->cycle();
//        line++;
//    }
//
//    // Restore cout
//    std::cout.rdbuf(coutBuf);
//    logFile.close();
//
//    std::cout << "Log written to log.txt" << std::endl;
//
//    return 0;
//}