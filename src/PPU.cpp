//
// Created by akith on 12/16/2025.
//
#include <iostream>
#include "h/PPU.hpp"
#include "h/Bus.hpp"


PPU::PPU(Bus* bus) : dots(0), mode(PPU_MODE:: OAMScan), bus(bus), frame_ready(false) {
    oam. fill(0);
    vram.fill(0);
    LY = 0;
    LYC = 0;
    LCDC = 0x91;  // LCD enabled, default settings
    STAT = 0x00;
}


void PPU::run(int cycles) {
    dots += cycles;

    std::cout << "Dots: " << dots << std::endl;
    switch (mode) {

        case PPU_MODE::OAMScan:
            std::cout << "Entering OAM Scan" << std::endl;

            if (dots >= 80) setMode(PPU_MODE::Drawing);
            break;
        case PPU_MODE::Drawing:
            std::cout << "Entering DRAWING" << std::endl;

            if (dots >= 252) {
                renderScanline();
                setMode(PPU_MODE::HBLANK);
            }
            break;
        case PPU_MODE::HBLANK:
            std::cout << "Entering HBLANK" << std::endl;

            if (dots >= 456) {

                dots -= 456;
                incrementLY();

                if (LY >= 144) {
                    // Enter VBlank
                    setMode(PPU_MODE::VBLANK);
                    frame_ready = true;
                    requestVBlankInterrupt();
                } else {
                    // Next scanline
                    setMode(PPU_MODE::OAMScan);
                }
            }
            break;
        case PPU_MODE::VBLANK:
            std::cout << "Entering VBLANK" << std::endl;

            if (dots >= 456) {
                dots -= 456;
                incrementLY();

                if (LY > 153) {
                    // Start new frame
                    LY = 0;
                    checkLYC();
                    setMode(PPU_MODE::OAMScan);
                }
            }

            break;
        case PPU_MODE::ILLEGAL:
            break;
    }
    
    
    
}

void PPU::renderScanline() {

}

void PPU::incrementLY() {
    LY++;
    checkLYC();
}

void PPU::checkLYC() {
    if (LYC == LY){
        STAT |= 0x04;
        if (STAT & 0x40){
            requestSTATInterrupt();
        }
    }
    else {
        STAT &= ~0x04;
    }
}

void PPU::requestVBlankInterrupt() {
    std::cout << "Requesting vblank interrupt" << std::endl;

    if (bus) {
        uint8_t if_reg = bus->read8(0xFF0F);
        bus->write8(0xFF0F, if_reg | 0x01);
    }
}

void PPU::requestSTATInterrupt() {
    std::cout << "Requesting stat interrupt" << std::endl;

    if (bus) {
        uint8_t if_reg = bus->read8(0xFF0F);
        bus->write8(0xFF0F, if_reg | 0x02);
    }
}

void PPU::setMode(PPU::PPU_MODE nmode) {
    STAT = (STAT & 0xFC) | static_cast<uint8_t>(nmode);
    this->mode = nmode;

    bool request_stat_int = false;
    switch (mode) {
        case PPU_MODE::HBLANK:
            if (STAT & 0x08) request_stat_int = true;
        break;
        case PPU_MODE::VBLANK:
            if (STAT & 0x10) request_stat_int = true;
        break;
        case PPU_MODE::OAMScan:
            if (STAT & 0x20) request_stat_int = true;
        break;
        case PPU_MODE::Drawing:
            break;
    }

    if (request_stat_int){
        requestSTATInterrupt();
    }

}

