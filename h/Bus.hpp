//
// Created by akith on 10/30/2025.
//

#ifndef GBEMULATOR_BUS_HPP
#define GBEMULATOR_BUS_HPP


#include <cstdint>
#include <array>
class Cartridge;

class Bus{

public:


    Bus(Cartridge* cart) : cartridge{cart} {}

    using ReadFn  = uint8_t(*)(Bus&, uint16_t);
    using WriteFn = void(*)(Bus&, uint16_t, uint8_t);

    inline uint8_t read8(uint16_t addr){
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

private:

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

};

#endif //GBEMULATOR_BUS_HPP
