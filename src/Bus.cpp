//
// Created by akith on 10/30/2025.
//
#include "../h/Bus.hpp"
#include "../h/Cartridge.hpp"
#include "../h/WRAM.h"
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
void Bus::mapMemory() {
    // Default
    for (auto& p : pageTable) {
        p.hotRead = p.hotWrite = nullptr;
        p.coldRead = forbbiddenRead;
        p.coldWrite = forbbiddenWrite;
    }

    // ROM: 0000-7FFF
    mapColdpath(0x0000, 0x7FFF, cartridgeRead, cartridgeWrite);

    // WRAM: C000-DFFF
    mapHotpath(0xC000, 0xDFFF, wramBankPtr(), true);

    // Echo RAM: E000-FDFF
    mapColdpath(0xE000, 0xFDFF, echoRamRead, echoRamWrite);

    // Forbidden: FEA0-FEFF
    mapColdpath(0xFEA0, 0xFEFF, forbbiddenRead, forbbiddenWrite);

    // Everything in 0xFF page (I/O, HRAM, IE)
    mapColdpath(0xFF00, 0xFFFF, ffPageRead, ffPageWrite);
}


void Bus::ffPageWrite(Bus& b, uint16_t addr, uint8_t val) {
    if (addr >= 0xFF80 && addr <= 0xFFFE) {
        b.hram[addr - 0xFF80] = val;
    } else if (addr == 0xFFFF) {
        b.ie_register = val;
    } else {
        ioWrite(b, addr, val);
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

uint8_t* Bus::wramBankPtr() const { return wram->bank(); }
uint8_t Bus::ioRead(Bus& b, uint16_t addr) {
    //LY register
    if (addr == 0xFF44) {
        return 0x90;
    }

    // For now, return 0xFF for all other I/O
    return 0xFF;
}

void Bus::ioWrite(Bus& b, uint16_t addr, uint8_t val) {}


uint8_t Bus::echoRamRead(Bus& b, uint16_t addr) {
    // Echo RAM mirrors C000-DDFF
    return b.wram->bank()[addr - 0xE000];
}

void Bus::echoRamWrite(Bus& b, uint16_t addr, uint8_t val) {
    // Echo RAM mirrors C000-DDFF
    b.wram->bank()[addr - 0xE000] = val;
}
uint8_t Bus::ffPageRead(Bus& b, uint16_t addr) {
    if (addr >= 0xFF80 && addr <= 0xFFFE) {
        return b.hram[addr - 0xFF80];  // HRAM
    } else if (addr == 0xFFFF) {
        return b.ie_register;  // IE register
    } else {
        return ioRead(b, addr);  // I/O registers
    }
}

