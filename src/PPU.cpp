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
    LCDC = 0x80;  // LCD disabled at startup
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
    // Each tile is 8x8 pixels, 2 bits per pixel (2bpp)
    // Each row is 2 bytes:  low byte and high byte
    uint16_t rowAddr = tileAddr + (y * 2);

    uint8_t lowByte = vram[rowAddr];
    uint8_t highByte = vram[rowAddr + 1];

    // Get the bit for this pixel (MSB = leftmost pixel)
    uint8_t bitPos = 7 - x;
    uint8_t lowBit = (lowByte >> bitPos) & 0x01;
    uint8_t highBit = (highByte >> bitPos) & 0x01;

    // Combine to get color ID (0-3)
    return (highBit << 1) | lowBit;
}

uint8_t PPU:: applyPalette(uint8_t colorId, uint8_t palette) {
    // Palette maps color IDs 0-3 to shades 0-3
    // Each color takes 2 bits in the palette byte
    return (palette >> (colorId * 2)) & 0x03;
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

void PPU::renderScanline() {
    // Check if LCD is enabled
    if (!(LCDC & 0x80)) {
        return;
    }

    // Check if BG is enabled
    if (!(LCDC & 0x01)) {
        // BG disabled - fill scanline with white (color 0)
        for (int x = 0; x < 160; x++) {
            framebuffer[LY * 160 + x] = 0;
        }
        return;
    }

    // Window enabled check (bit 5 of LCDC)
    bool windowEnabled = (LCDC & 0x20) && (WY <= LY);

    // Render 160 pixels (background/window)
    for (int x = 0; x < 160; x++) {
        if (windowEnabled && (WX <= 166) && ((x + 7) >= WX)) {
            uint8_t color = renderWindowPixel(x);
            framebuffer[LY * 160 + x] = color;
        } else {
            uint8_t color = renderBackgroundPixel(x);
            framebuffer[LY * 160 + x] = color;
        }
    }

    // Render sprites if enabled (bit 1 of LCDC)
    if (LCDC & 0x02) {
        evaluateSprites();
        renderSprites();
    }
}
uint8_t PPU::renderBackgroundPixel(int x) {
    // Determine which tile map to use (bit 3 of LCDC)
    uint16_t tileMapBase = (LCDC & 0x08) ? 0x1C00 : 0x1800;

    // Determine which tile data region to use (bit 4 of LCDC)
    bool unsignedTileData = (LCDC & 0x10);
    uint16_t tileDataBase = unsignedTileData ? 0x0000 : 0x0800;

    // Apply scrolling with wrapping (256x256 pixels)
    uint8_t y = (LY + SCY) & 0xFF;
    uint8_t pixelX = (x + SCX) & 0xFF;

    uint8_t tileRow = y / 8;
    uint8_t tileY = y % 8;
    uint8_t tileCol = pixelX / 8;
    uint8_t tileX = pixelX % 8;

    // Get tile index from tile map (wrap at 32 tiles)
    uint16_t tileMapAddr = tileMapBase + ((tileRow & 0x1F) * 32) + (tileCol & 0x1F);
    uint8_t tileIndex = vram[tileMapAddr];

    // Calculate tile data address
    uint16_t tileAddr;
    if (unsignedTileData) {
        tileAddr = tileDataBase + (tileIndex * 16);
    } else {
        int8_t signedIndex = static_cast<int8_t>(tileIndex);
        tileAddr = tileDataBase + 0x0800 + (signedIndex * 16);
    }

    // Get pixel color (0-3) from tile
    uint8_t colorId = getTilePixel(tileAddr, tileX, tileY);

    // Apply palette
    return applyPalette(colorId, BGP);
}

uint8_t PPU::renderWindowPixel(int x) {
    // Window uses bit 6 of LCDC for tile map selection
    uint16_t tileMapBase = (LCDC & 0x40) ? 0x1C00 : 0x1800;

    // Tile data uses same setting as background (bit 4)
    bool unsignedTileData = (LCDC & 0x10);
    uint16_t tileDataBase = unsignedTileData ? 0x0000 : 0x0800;

    // Calculate window-relative coordinates
    // WX-7 is the left edge of the window on screen
    int windowX = x - (WX - 7);
    int windowY = LY - WY;

    // Bounds check (shouldn't happen if caller checks correctly, but be safe)
    if (windowX < 0 || windowY < 0) {
        return applyPalette(0, BGP);
    }

    uint8_t tileRow = windowY / 8;
    uint8_t tileY = windowY % 8;
    uint8_t tileCol = windowX / 8;
    uint8_t tileX = windowX % 8;

    // Bounds check for tile map
    if (tileRow >= 32 || tileCol >= 32) {
        return applyPalette(0, BGP);
    }

    // Get tile index from window tile map
    uint16_t tileMapAddr = tileMapBase + (tileRow * 32) + tileCol;
    uint8_t tileIndex = vram[tileMapAddr];

    // Calculate tile data address
    uint16_t tileAddr;
    if (unsignedTileData) {
        tileAddr = tileDataBase + (tileIndex * 16);
    } else {
        int8_t signedIndex = static_cast<int8_t>(tileIndex);
        tileAddr = tileDataBase + 0x0800 + (signedIndex * 16);
    }

    // Get pixel color (0-3) from tile
    uint8_t colorId = getTilePixel(tileAddr, tileX, tileY);

    // Apply palette
    return applyPalette(colorId, BGP);
}
void PPU::evaluateSprites() {
    scanlineSprites.clear();

    // Determine sprite height (8x8 or 8x16)
    int spriteHeight = (LCDC & 0x04) ? 16 : 8;

    // Check all 40 sprites in OAM
    for (int i = 0; i < 40; i++) {
        uint8_t y = oam[i * 4 + 0];
        uint8_t x = oam[i * 4 + 1];
        uint8_t tileIndex = oam[i * 4 + 2];
        uint8_t flags = oam[i * 4 + 3];

        // Check if sprite is on this scanline
        // Sprite Y coordinate is offset by 16
        int spriteY = y - 16;

        // Check if scanline intersects this sprite
        if (LY >= spriteY && LY < spriteY + spriteHeight) {
            Sprite sprite;
            sprite.y = y;
            sprite.x = x;
            sprite.tileIndex = tileIndex;
            sprite.flags = flags;
            sprite.oamIndex = i;

            scanlineSprites.push_back(sprite);

            // Game Boy can only render 10 sprites per scanline
            if (scanlineSprites. size() >= 10) {
                break;
            }
        }
    }
}

void PPU::renderSprites() {
    // Determine sprite height
    int spriteHeight = (LCDC & 0x04) ? 16 : 8;

    // Render sprites in reverse order (lower X = higher priority)
    // Actually, we should sort by X position first, but for simplicity,
    // we'll iterate backwards through the sprite list
    for (int s = scanlineSprites.size() - 1; s >= 0; s--) {
        const Sprite& sprite = scanlineSprites[s];

        // Calculate screen position
        int spriteX = sprite.x - 8;
        int spriteY = sprite.y - 16;

        // Skip if completely off-screen
        if (spriteX <= -8 || spriteX >= 160) continue;

        // Calculate Y position within sprite
        int spriteLineY = LY - spriteY;

        // Apply Y flip
        if (sprite.yFlip()) {
            spriteLineY = spriteHeight - 1 - spriteLineY;
        }

        // For 8x16 sprites, select top or bottom tile
        uint8_t tileIndex = sprite.tileIndex;
        if (spriteHeight == 16) {
            if (spriteLineY < 8) {
                tileIndex = sprite.tileIndex & 0xFE;  // Top tile (even)
            } else {
                tileIndex = sprite.tileIndex | 0x01;  // Bottom tile (odd)
                spriteLineY -= 8;
            }
        }

        // Render 8 pixels of this sprite
        for (int x = 0; x < 8; x++) {
            int screenX = spriteX + x;

            // Skip if pixel is off-screen
            if (screenX < 0 || screenX >= 160) continue;

            // Apply X flip
            int spritePixelX = sprite.xFlip() ? (7 - x) : x;

            // Get sprite tile pixel
            uint16_t tileAddr = tileIndex * 16;
            uint8_t colorId = getTilePixel(tileAddr, spritePixelX, spriteLineY);

            // Color 0 is transparent for sprites
            if (colorId == 0) continue;

            // Check priority
            uint8_t bgColor = framebuffer[LY * 160 + screenX];

            // If sprite has priority flag set (behind BG), only draw over BG color 0
            if (sprite. priority() && bgColor != 0) {
                continue;
            }

            // Apply sprite palette
            uint8_t palette = sprite.palette() ? OBP1 : OBP0;
            uint8_t color = applyPalette(colorId, palette);

            // Draw sprite pixel
            framebuffer[LY * 160 + screenX] = color;
        }
    }
}
