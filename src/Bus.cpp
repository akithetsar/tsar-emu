//
// Created by akith on 10/30/2025.
//
#include "../h/Bus.hpp"
#include "../h/Cartridge.hpp"


void Bus::mapMemory() {
    //Default
    for (auto& p : pageTable) {
        p.hotRead = p.hotWrite = nullptr;
        p.coldRead = forbbiddenRead;
        p.coldWrite = forbbiddenWrite;
    }

    mapColdpath(0x0000, 0x7FFF, cartridgeRead, cartridgeWrite);
    mapColdpath(0xFEA0, 0xFEFF, forbbiddenRead, forbbiddenWrite);
}

void Bus::mapHotpath(uint16_t startAddr, uint16_t endAddr, uint8_t *base, bool writable) {
    for (uint32_t a = startAddr & 0xFF00; a <= (static_cast<uint32_t>(endAddr) | 0x00FFu); a += 0x100) {
        uint16_t pageStart = static_cast<uint16_t>(a);
        uint16_t pageEnd   = static_cast<uint16_t>(a | 0x00FF);
        if (pageEnd < startAddr || pageStart > endAddr) continue;

        size_t page = a >> 8;

        uint16_t offset = static_cast<uint16_t>(pageStart - startAddr);

        pageTable[page].hotRead  = base ? (base + offset) : nullptr;
        pageTable[page].hotWrite  = (writable && base) ? (base + offset) : nullptr;

    }
}
void Bus::mapColdpath(uint16_t startAddr, uint16_t endAddr, ReadFn r, WriteFn w) {
    for (uint32_t a = startAddr & 0xFF00; a <= (static_cast<uint32_t>(endAddr) | 0x00FFu); a += 0x100) {
        size_t page = a >> 8;
        pageTable[page].hotRead  = nullptr;
        pageTable[page].hotWrite  = nullptr;
        pageTable[page].coldRead = r;
        pageTable[page].coldWrite = w;
    }
}


//---Handlers---

//Read forbidden/currently inaccessible memory
uint8_t Bus::forbbiddenRead(Bus &, uint16_t) {
    return 0xFF;
}

void Bus::forbbiddenWrite(Bus &, uint16_t, uint8_t) {}

uint8_t Bus::cartridgeRead(Bus & b, uint16_t addr) {
    return b.cartridge->read(addr);
}

void Bus::cartridgeWrite(Bus &, uint16_t, uint8_t) {

}
