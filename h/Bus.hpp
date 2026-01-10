//
// Created by akith on 10/30/2025.
//

#ifndef GBEMULATOR_BUS_HPP
#define GBEMULATOR_BUS_HPP

#include <cstdint>
#include <array>
#include "Timer.hpp"
#include "registers.hpp"
#include "../h/PPU.hpp"
class Cartridge;
class WRAM;

class Bus {
public:
    Bus(Cartridge* cart, WRAM* wram)
            : cartridge(cart), wram(wram), ppu(ppu), ie_register(0) {
        hram.fill(0);
        io_registers.fill(0xFF);
        timer = new Timer(this);

    }
    ~Bus() {
        delete timer;
    }
    uint8_t read8(uint16_t addr);
    void write8(uint16_t addr, uint8_t val);
    void tick(int cycles) { timer->tick(cycles); }
    void setPPU(PPU* nppu);


    Cartridge* cartridge = nullptr;
    WRAM* wram = nullptr;
    Timer* timer = nullptr;
    PPU* ppu = nullptr;
    reg8 IE;
    reg8 IF;
    bool canAccessVRAM() const;
    bool canAccessOAM() const;
    uint8_t joypad_state = 0xFF;
    void setJoypadState(uint8_t state) { joypad_state = state; }
private:
    // Memory regions
    std::array<uint8_t, 0x7F>   hram;        // 0xFF80-0xFFFE: High RAM
    std::array<uint8_t, 0x80>   io_registers;// 0xFF00-0xFF7F: I/O Registers

    uint8_t ie_register;                     // 0xFFFF: Interrupt Enable
};

#endif //GBEMULATOR_BUS_HPP