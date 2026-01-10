#include "../h/Bus.hpp"
#include "../h/Cartridge.hpp"
#include "../h/WRAM.h"

uint8_t Bus::read8(uint16_t addr) {
    // ROM (0x0000-0x7FFF)
    if (addr < 0x8000) {
        return cartridge->read(addr);
    }


    // VRAM (0x8000-0x9FFF)
    if (addr < 0xA000) {
        // Check if VRAM is accessible (blocked during mode 3)
        if (!canAccessVRAM()) {
            return 0xFF;  // Return 0xFF when blocked
        }
        return ppu->vram[addr - 0x8000];
    }

    // External RAM (0xA000-0xBFFF) - Cartridge
    if (addr < 0xC000) {
        return cartridge->read(addr);
    }

    // WRAM (0xC000-0xDFFF)
    if (addr < 0xE000) {
        return wram->bank()[addr - 0xC000];
    }

    // Echo RAM (0xE000-0xFDFF) - mirrors 0xC000-0xDDFF
    if (addr < 0xFE00) {
        return wram->bank()[addr - 0xE000];
    }

    // OAM (0xFE00-0xFE9F)
    if (addr < 0xFEA0) {
        // Check if OAM is accessible (blocked during modes 2 and 3)
        if (!canAccessOAM()) {
            return 0xFF;  // Return 0xFF when blocked
        }
        return ppu->oam[addr - 0xFE00];
    }


    // Forbidden (0xFEA0-0xFEFF)
    if (addr < 0xFF00) {
        return 0xFF;
    }

    // I/O Registers (0xFF00-0xFF7F)
    if (addr < 0xFF80) {
        // Joypad register
        if (addr == 0xFF00) {
            uint8_t joypad = io_registers[0x00];  // Get button selection bits

            // Check which button group is selected
            bool selectButtons = !(joypad & 0x20);  // Bit 5: 0 = select buttons
            bool selectDpad = !(joypad & 0x10);     // Bit 4: 0 = select d-pad

            uint8_t result = joypad | 0x0F;

            if (selectButtons) {
                result &= (joypad_state >> 4) | 0xF0;
            }

            if (selectDpad) {
                result &= (joypad_state & 0x0F) | 0xF0;
            }

            return result;
        }

        // PPU registers
        switch (addr) {
            case 0xFF40: return ppu->LCDC;
            case 0xFF41: return ppu->STAT;
            case 0xFF42: return ppu->SCY;
            case 0xFF43: return ppu->SCX;
            case 0xFF44: return ppu->LY;
            case 0xFF45: return ppu->LYC;
            case 0xFF47: return ppu->BGP;
            case 0xFF48: return ppu->OBP0;
            case 0xFF49: return ppu->OBP1;
            case 0xFF4A: return ppu->WY;
            case 0xFF4B: return ppu->WX;
        }
        if (addr == 0xFF46) {
            return ppu->dmaSource;
        }

        // Timer registers
        switch (addr) {
            case 0xFF04: return timer->getDIV();
            case 0xFF05: return timer->getTIMA();
            case 0xFF06: return timer->getTMA();
            case 0xFF07: return timer->getTAC();
        }

        return io_registers[addr - 0xFF00];
    }

    // HRAM (0xFF80-0xFFFE)
    if (addr < 0xFFFF) {
        return hram[addr - 0xFF80];
    }

    // IE Register (0xFFFF)
    return ie_register;
}

void Bus::write8(uint16_t addr, uint8_t val) {
    // ROM (0x0000-0x7FFF) - May trigger bank switching
    if (addr < 0x8000) {
        cartridge->write(addr, val);
        return;
    }

    // VRAM (0x8000-0x9FFF)
    if (addr < 0xA000) {
        if (!canAccessVRAM()) {
            return;
        }
        ppu->vram[addr - 0x8000] = val;
        return;
    }

    // External RAM (0xA000-0xBFFF) - Cartridge
    if (addr < 0xC000) {
        cartridge->write(addr, val);
        return;
    }

    // WRAM (0xC000-0xDFFF)
    if (addr < 0xE000) {
        wram->bank()[addr - 0xC000] = val;
        return;
    }

    // Echo RAM (0xE000-0xFDFF) - mirrors 0xC000-0xDDFF
    if (addr < 0xFE00) {
        wram->bank()[addr - 0xE000] = val;
        return;
    }

    // OAM (0xFE00-0xFE9F)
    if (addr < 0xFEA0) {
        if (!canAccessOAM()) {
            return;
        }
        ppu->oam[addr - 0xFE00] = val;
        return;
    }

    // Forbidden (0xFEA0-0xFEFF)
    if (addr < 0xFF00) {
        return;
    }

    // I/O Registers (0xFF00-0xFF7F)
    if (addr < 0xFF80) {
        // Joypad register
        if (addr == 0xFF00) {
            io_registers[0x00] = val & 0x30;
            return;
        }
        // PPU registers
        switch (addr) {
            case 0xFF40: ppu->setLcdc(val); return;
            case 0xFF41: ppu->setStat(val); return;
            case 0xFF42: ppu->setScy(val); return;
            case 0xFF43: ppu->setScx(val); return;
            case 0xFF44: /* LY is read-only */ return;
            case 0xFF45: ppu->setLyc(val); return;
            case 0xFF47: ppu->setBgp(val); return;
            case 0xFF48: ppu->setObp0(val); return;
            case 0xFF49: ppu->setObp1(val); return;
            case 0xFF4A: ppu->setWy(val); return;
            case 0xFF4B: ppu->setWx(val); return;
        }
        if (addr == 0xFF46) {
            ppu->startDMA(val);
            return;
        }
        // Timer registers
        switch (addr) {
            case 0xFF04: timer->setDIV(val); return;
            case 0xFF05: timer->setTIMA(val); return;
            case 0xFF06: timer->setTMA(val); return;
            case 0xFF07: timer->setTAC(val); return;
        }

        io_registers[addr - 0xFF00] = val;
        return;
    }

    // HRAM (0xFF80-0xFFFE)
    if (addr < 0xFFFF) {
        hram[addr - 0xFF80] = val;
        return;
    }

    // IE Register (0xFFFF)
    ie_register = val;
}

void Bus::setPPU(PPU *nppu) {
    ppu = nppu;
}

bool Bus::canAccessVRAM() const {
    if (! ppu) return true;
    if (!(ppu->LCDC & 0x80)) return true;
    return ppu->mode != PPU:: PPU_MODE::Drawing;
}

bool Bus::canAccessOAM() const {
    if (!ppu) return true;
    if (!(ppu->LCDC & 0x80)) return true;
    return ppu->mode != PPU::PPU_MODE::OAMScan &&
           ppu->mode != PPU::PPU_MODE::Drawing;
}