//
// Created by akith on 12/16/2025.
//
#include <iostream>
#include "h/PPU.hpp"
#include "h/Bus.hpp"


PPU::PPU(Bus* bus) : dots(0), mode(PPU_MODE:: OAMScan), bus(bus), frame_ready(false) {
    oam.fill(0);
    vram.fill(0);
    LY = 0;
    LYC = 0;
    LCDC = 0x91;
    STAT = 0x00;
    SCX = 0;
    SCY = 0;
    WX = 167;
    WY = 0;
    BGP = 0xFC;
    OBP0 = 0xFF;
    OBP1 = 0xFF;
}


void PPU::run(int cycles) {
    tickDMA(cycles);
    if (!(LCDC & 0x80)) {
        return;
    }
    dots += cycles;

//    std::cout << "Dots: " << dots << std::endl;
    switch (mode) {

        case PPU_MODE::OAMScan:
//            std::cout << "Entering OAM Scan" << std::endl;

            if (dots >= 80) setMode(PPU_MODE::Drawing);
            break;
        case PPU_MODE::Drawing:
//            std::cout << "Entering DRAWING" << std::endl;

            if (dots >= 252) {
                renderScanline();
                setMode(PPU_MODE::HBLANK);
            }
            break;
        case PPU_MODE::HBLANK:
//            std::cout << "Entering HBLANK" << std::endl;

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
//            std::cout << "Entering VBLANK" << std::endl;

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

uint8_t PPU::getTilePixel(uint16_t tileAddr, uint8_t x, uint8_t y) {
    uint16_t rowAddr = tileAddr + (y * 2);

    uint8_t lowByte = vram[rowAddr];
    uint8_t highByte = vram[rowAddr + 1];

    uint8_t bitPos = 7 - x;
    uint8_t lowBit = (lowByte >> bitPos) & 0x01;
    uint8_t highBit = (highByte >> bitPos) & 0x01;

    return (highBit << 1) | lowBit;
}

uint8_t PPU:: applyPalette(uint8_t colorId, uint8_t palette) {
    return (palette >> (colorId * 2)) & 0x03;
}

void PPU::incrementLY() {
    LY++;
    checkLYC();
}

void PPU::checkLYC() {
    bool wasCoincidence = (STAT & 0x04);
    bool nowCoincidence = (LYC == LY);

    if (nowCoincidence) {
        STAT |= 0x04;

        if (! wasCoincidence && (STAT & 0x40)) {
            requestSTATInterrupt();
        }
    } else {
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
    PPU_MODE oldMode = mode;

    STAT = (STAT & 0xFC) | static_cast<uint8_t>(nmode);
    this->mode = nmode;

    if (oldMode == nmode) return;

    bool request_stat_int = false;
    switch (mode) {
        case PPU_MODE::HBLANK:
            if (STAT & 0x08) request_stat_int = true;
            break;
        case PPU_MODE:: VBLANK:
            if (STAT & 0x10) request_stat_int = true;
            break;
        case PPU_MODE::OAMScan:
            if (STAT & 0x20) request_stat_int = true;
            break;
        case PPU_MODE::Drawing:
            break;
        case PPU_MODE::ILLEGAL:
            break;
    }

    if (request_stat_int) {
        requestSTATInterrupt();
    }
}

void PPU::renderScanline() {
    if (!(LCDC & 0x80)) {
        return;
    }

    if (!(LCDC & 0x01)) {
        for (int x = 0; x < 160; x++) {
            framebuffer[LY * 160 + x] = 0;
        }
        return;
    }

    bool windowEnabled = (LCDC & 0x20) && (WY <= LY);

    for (int x = 0; x < 160; x++) {
        if (windowEnabled && (WX <= 166) && ((x + 7) >= WX)) {
            uint8_t color = renderWindowPixel(x);
            framebuffer[LY * 160 + x] = color;
        } else {
            uint8_t color = renderBackgroundPixel(x);
            framebuffer[LY * 160 + x] = color;
        }
    }

    if (LCDC & 0x02) {
        evaluateSprites();
        renderSprites();
    }
}
uint8_t PPU::renderBackgroundPixel(int x) {
    uint16_t tileMapBase = (LCDC & 0x08) ? 0x1C00 : 0x1800;

    bool unsignedTileData = (LCDC & 0x10);
    uint16_t tileDataBase = unsignedTileData ? 0x0000 : 0x0800;

    uint8_t y = (LY + SCY) & 0xFF;
    uint8_t pixelX = (x + SCX) & 0xFF;

    uint8_t tileRow = y / 8;
    uint8_t tileY = y % 8;
    uint8_t tileCol = pixelX / 8;
    uint8_t tileX = pixelX % 8;

    uint16_t tileMapAddr = tileMapBase + ((tileRow & 0x1F) * 32) + (tileCol & 0x1F);
    uint8_t tileIndex = vram[tileMapAddr];

    uint16_t tileAddr;
    if (unsignedTileData) {
        tileAddr = tileDataBase + (tileIndex * 16);
    } else {
        int8_t signedIndex = static_cast<int8_t>(tileIndex);
        tileAddr = tileDataBase + 0x0800 + (signedIndex * 16);
    }

    uint8_t colorId = getTilePixel(tileAddr, tileX, tileY);

    return applyPalette(colorId, BGP);
}

uint8_t PPU::renderWindowPixel(int x) {
    uint16_t tileMapBase = (LCDC & 0x40) ? 0x1C00 : 0x1800;

    bool unsignedTileData = (LCDC & 0x10);
    uint16_t tileDataBase = unsignedTileData ? 0x0000 : 0x0800;

    int windowX = x - (WX - 7);
    int windowY = LY - WY;

    if (windowX < 0 || windowY < 0) {
        return applyPalette(0, BGP);
    }

    uint8_t tileRow = windowY / 8;
    uint8_t tileY = windowY % 8;
    uint8_t tileCol = windowX / 8;
    uint8_t tileX = windowX % 8;

    if (tileRow >= 32 || tileCol >= 32) {
        return applyPalette(0, BGP);
    }

    uint16_t tileMapAddr = tileMapBase + (tileRow * 32) + tileCol;
    uint8_t tileIndex = vram[tileMapAddr];

    uint16_t tileAddr;
    if (unsignedTileData) {
        tileAddr = tileDataBase + (tileIndex * 16);
    } else {
        int8_t signedIndex = static_cast<int8_t>(tileIndex);
        tileAddr = tileDataBase + 0x0800 + (signedIndex * 16);
    }

    uint8_t colorId = getTilePixel(tileAddr, tileX, tileY);

    return applyPalette(colorId, BGP);
}
void PPU::evaluateSprites() {
    scanlineSprites.clear();

    int spriteHeight = (LCDC & 0x04) ? 16 : 8;

    for (int i = 0; i < 40; i++) {
        uint8_t y = oam[i * 4 + 0];
        uint8_t x = oam[i * 4 + 1];
        uint8_t tileIndex = oam[i * 4 + 2];
        uint8_t flags = oam[i * 4 + 3];

        int spriteY = y - 16;

        if (LY >= spriteY && LY < spriteY + spriteHeight) {
            Sprite sprite;
            sprite.y = y;
            sprite.x = x;
            sprite.tileIndex = tileIndex;
            sprite.flags = flags;
            sprite.oamIndex = i;

            scanlineSprites.push_back(sprite);

            if (scanlineSprites. size() >= 10) {
                break;
            }
        }
    }
}

void PPU::renderSprites() {
    int spriteHeight = (LCDC & 0x04) ? 16 : 8;

    for (int s = scanlineSprites.size() - 1; s >= 0; s--) {
        const Sprite& sprite = scanlineSprites[s];

        int spriteX = sprite.x - 8;
        int spriteY = sprite.y - 16;

        if (spriteX <= -8 || spriteX >= 160) continue;

        int spriteLineY = LY - spriteY;

        if (sprite.yFlip()) {
            spriteLineY = spriteHeight - 1 - spriteLineY;
        }

        uint8_t tileIndex = sprite.tileIndex;
        if (spriteHeight == 16) {
            if (spriteLineY < 8) {
                tileIndex = sprite.tileIndex & 0xFE;
            } else {
                tileIndex = sprite.tileIndex | 0x01;
                spriteLineY -= 8;
            }
        }

        for (int x = 0; x < 8; x++) {
            int screenX = spriteX + x;

            if (screenX < 0 || screenX >= 160) continue;

            int spritePixelX = sprite.xFlip() ? (7 - x) : x;

            uint16_t tileAddr = tileIndex * 16;
            uint8_t colorId = getTilePixel(tileAddr, spritePixelX, spriteLineY);

            if (colorId == 0) continue;

            uint8_t bgColor = framebuffer[LY * 160 + screenX];

            if (sprite. priority() && bgColor != 0) {
                continue;
            }

            uint8_t palette = sprite.palette() ? OBP1 : OBP0;
            uint8_t color = applyPalette(colorId, palette);

            framebuffer[LY * 160 + screenX] = color;
        }
    }
}
void PPU::startDMA(uint8_t value) {
    dmaSource = value;
    dmaActive = true;
    dmaCycles = 160;

    uint16_t sourceAddr = dmaSource * 0x100;
    for (int i = 0; i < 0xA0; i++) {
        oam[i] = bus->read8(sourceAddr + i);
    }
}

void PPU::tickDMA(int cycles) {
    if (!dmaActive) return;

    dmaCycles -= cycles;
    if (dmaCycles <= 0) {
        dmaActive = false;
        dmaCycles = 0;
    }
}

void PPU::setLcdc(uint8_t value) {
    bool wasEnabled = (LCDC & 0x80);
    bool nowEnabled = (value & 0x80);

    LCDC = value;

    if (wasEnabled && !nowEnabled) {
        LY = 0;
        dots = 0;
        mode = PPU_MODE::HBLANK;
        STAT = (STAT & 0xFC) | 0x00;

        framebuffer.fill(0);
    }

    if (!wasEnabled && nowEnabled) {
        LY = 0;
        dots = 0;
        mode = PPU_MODE::OAMScan;
        STAT = (STAT & 0xFC) | 0x02;
    }

    }
