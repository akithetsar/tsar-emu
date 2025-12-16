//#include <iostream>
//#include <fstream>
//#include "h/Emulator.hpp"
//#include "h/log.h"
//#include "h/CPU.h"
//
//


#include <iostream>
#include <fstream>
#include "h/Emulator.hpp"

int main() {
    Emulator emulator("C:\\Users\\akith\\CLionProjects\\GBEmulator\\ROMS\\customTesting\\ppuTesting\\02-vblank-test.gb");
    emulator.bootEmu();

    // Optional: redirect to file for debugging
    // std::ofstream logFile("emulator_log.txt");
    // std::streambuf* coutBuf = std::cout. rdbuf();
    // std::cout.rdbuf(logFile. rdbuf());

    bool running = true;

    while (running) {
        // Run one frame (59.7 Hz = ~70224 cycles per frame)
        const int CYCLES_PER_FRAME = 70224;
        int frame_cycles = 0;

        while (frame_cycles < CYCLES_PER_FRAME) {
            // CPU executes one instruction and returns cycles used
            int cycles = emulator.cpu->cycle();
            // Advance all other components by the same cycles
            emulator.ppu->run(cycles);
            // emulator.timer->run(cycles);  // Add when you implement timer

            frame_cycles += cycles;

            // Optional: check for exit conditions
            // if (some_exit_condition) {
            //     running = false;
            //     break;
            // }
//            char t;
//            std::cin >> t;
        }

        // After each frame, check if PPU has a frame ready
        if (emulator.ppu->frame_ready) {
            emulator.ppu->frame_ready = false;

            // Here you would:
            // 1. Render the frame to screen
            // 2. Handle input
            // 3. Add frame limiting/timing if needed

            std::cout << "Frame rendered at scanline " << (int)emulator.ppu->LY << std::endl;
        }
    }

    // Restore cout if redirected
    // std::cout. rdbuf(coutBuf);
    // logFile.close();

    return 0;
}

////---- Gameboy Doctor Blargg CPU instruction testing.
//int main() {
//    // Use a basic test ROM first (e.g., cpu_instrs/individual/01-special.gb)
//    Emulator emulator = Emulator("C:\\Users\\akith\\CLionProjects\\GBEmulator\\ROMS\\02-interrupts.gb");
//    emulator.bootEmu();
//
//    // Redirect cout to file
//    std::ofstream logFile("emulator_log.txt");
//    std::streambuf* coutBuf = std::cout.rdbuf();
//    std::cout.rdbuf(logFile. rdbuf());
//
//    // Run for a limited number of instructions
//    const int MAX_INSTRUCTIONS = 10000000;
//
//    for (int i = 0; i < MAX_INSTRUCTIONS; i++) {
//        emulator.cpu->cycle();
//
//        // Optional: Stop if halted or infinite loop detected
//        // if (emulator.cpu->isHalted()) break;
//    }
//
//    // Restore cout
//    std::cout.rdbuf(coutBuf);
//    logFile.close();
//
//    std::cout << "Log written to emulator_log.txt" << std::endl;
//    return 0;
//}