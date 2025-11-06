//
// Created by akith on 10/30/2025.
//

#ifndef GBEMULATOR_BUS_HPP
#define GBEMULATOR_BUS_HPP


#include <cstdint>
#include <array>
#include <iostream>

class Cartridge;
class WRAM;

class Bus{

public:

    uint8_t ie_register;  // Interrupt Enable at 0xFFFF
    Bus(Cartridge* cart, WRAM* wram) : cartridge{cart}, wram(wram), ie_register(0) {
        hram.fill(0);
    }

    using ReadFn  = uint8_t(*)(Bus&, uint16_t);
    using WriteFn = void(*)(Bus&, uint16_t, uint8_t);

    inline uint8_t read8(uint16_t addr){
        if (addr == 0xFF44){
            return 0x90;
        }
        Page& page = pageTable[addr >> 8];
        if(__builtin_expect(page.hotRead != nullptr, 1)){
            return page.hotRead[addr & 0xFF];
        }

        return page.coldRead(*this, addr);

    }

    inline void write8(uint16_t addr, uint8_t val){

        Page& page = pageTable[addr >> 8];
        if(__builtin_expect(page.hotWrite != nullptr, 1)){
            page.hotWrite[addr & 0xFF] = val;
            return;
        }

        page.coldWrite(*this, addr, val);
    }

    void mapMemory();

    void mapHotpath(uint16_t startAddr, uint16_t endAddr, uint8_t* base, bool writable);
    void mapColdpath(uint16_t startAddr, uint16_t endAddr, ReadFn r, WriteFn w);


    Cartridge* cartridge = nullptr;
    WRAM*      wram = nullptr;

private:

    std::array<uint8_t, 127> hram;
    struct Page{
        uint8_t* hotRead = nullptr;
        uint8_t* hotWrite = nullptr;
        ReadFn coldRead = nullptr;
        WriteFn coldWrite = nullptr;
    };
    std::array<Page, 256> pageTable;


    //Handlers
    static uint8_t forbbiddenRead(Bus&, uint16_t);
    static void forbbiddenWrite(Bus&, uint16_t, uint8_t);
    static uint8_t cartridgeRead(Bus&, uint16_t);
    static void cartridgeWrite(Bus&, uint16_t, uint8_t);
    static uint8_t ioRead(Bus&, uint16_t);
    static void ioWrite(Bus&, uint16_t, uint8_t);
    uint8_t *wramBankPtr() const;
    static uint8_t echoRamRead(Bus&, uint16_t);
    static void echoRamWrite(Bus&, uint16_t, uint8_t);
    static uint8_t ffPageRead(Bus &b, uint16_t addr);

    static void ffPageWrite(Bus &b, uint16_t addr, uint8_t val);
};

#endif //GBEMULATOR_BUS_HPP
