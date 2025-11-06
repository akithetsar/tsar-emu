//
// Created by akith on 10/27/2025.
//

#ifndef GBEMULATOR_EMULATOR_HPP
#define GBEMULATOR_EMULATOR_HPP

#include "Cartridge.hpp"
#include "Bus.hpp"
#include "CPU.h"
#include "WRAM.h"
#include <memory>
class Emulator {

public:

    explicit Emulator(const std::string& cartridge_file)
        :   cartridge{std::make_unique<Cartridge>(cartridge_file)},
            wram{std::make_unique<WRAM>()},
            bus{std::make_unique<Bus>(cartridge.get(),wram.get())},
            cpu{std::make_unique<CPU>(bus.get())}
    {
        bus->mapMemory();
    }

    void bootEmu();

    std::unique_ptr<Cartridge> cartridge;
    std::unique_ptr<WRAM> wram;
    std::unique_ptr<Bus> bus;
    std::unique_ptr<CPU> cpu;

};

#endif //GBEMULATOR_EMULATOR_HPP
