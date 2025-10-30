#include <iostream>
#include "h/Emulator.hpp"
#include "h/log.h"
int main() {

    Emulator emulator = Emulator(R"(C:\Users\akith\CLionProjects\GBEmulator\ROMS\02-write_timing.gb)");
    emulator.bootEmu();
    printByte(emulator.bus->read8(0x0105));

    return 0;
}
