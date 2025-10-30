//
// Created by akith on 10/27/2025.
//

#ifndef GBEMULATOR_EMULATOR_HPP
#define GBEMULATOR_EMULATOR_HPP

#include "Cartridge.hpp"
#include "Bus.hpp"
#include <memory>
class Emulator {

public:


    explicit Emulator(const std::string& cartridge_file): cartridge{std::make_unique<Cartridge>(cartridge_file)}, bus{std::make_unique<Bus>(cartridge.get())} {
        bus->mapMemory();
    }
    void bootEmu();





    std::unique_ptr<Cartridge> cartridge;
    std::unique_ptr<Bus> bus;

};

#endif //GBEMULATOR_EMULATOR_HPP
