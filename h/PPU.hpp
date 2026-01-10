//
// Created by akith on 12/16/2025.
//

#ifndef GBEMULATOR_PPU_HPP
#define GBEMULATOR_PPU_HPP

#include <array>
#include <cstdint>
#include <vector>

class Bus;
struct Sprite {
    uint8_t y;
    uint8_t x;
    uint8_t tileIndex;
    uint8_t flags;
    uint8_t oamIndex;

    // Helper methods to extract flags
    bool priority() const { return flags & 0x80; }
    bool yFlip() const { return flags & 0x40; }
    bool xFlip() const { return flags & 0x20; }
    bool palette() const { return flags & 0x10; }
};
class PPU {

public:
    PPU(Bus* bus);


    void setLcdc(uint8_t value);
    void setStat(uint8_t stat) {STAT = stat;}
    void setScx(uint8_t scx) {SCX = scx;}
    void setScy(uint8_t scy) {SCY = scy;}
    void setLy(uint8_t ly) {LY = ly;}
    void setLyc(uint8_t lyc) {LYC = lyc;}
    void setBgp(uint8_t bgp) {BGP = bgp;}
    void setObp0(uint8_t obp0) {OBP0 = obp0;}
    void setObp1(uint8_t obp1) {OBP1 = obp1;}
    void setWx(uint8_t wx) {WX = wx;}
    void setWy(uint8_t wy) {WY = wy;}

    uint8_t LCDC;
    uint8_t STAT;
    uint8_t SCX, SCY;
    uint8_t LY, LYC;
    uint8_t BGP, OBP0, OBP1;
    uint8_t WX, WY;

    enum class PPU_MODE{

        HBLANK = 0,
        VBLANK,
        OAMScan,
        Drawing,
        ILLEGAL

    };


    PPU_MODE mode;
    int dots;

    std::array<uint8_t, 160 * 144> framebuffer{};

    void run(int cycles);
    void setMode(PPU_MODE nmode);

    std::array<uint8_t, 0x2000> vram{};        // 0x8000-0x9FFF:  Video RAM
    std::array<uint8_t, 0xA0>   oam{};         // 0xFE00-0xFE9F: Object Attribute Memory


    void renderScanline();
    uint8_t getTilePixel(uint16_t tileAddr, uint8_t x, uint8_t y);
    uint8_t applyPalette(uint8_t colorId, uint8_t palette);

    void incrementLY();

    bool frame_ready;

    bool dmaActive = false;
    int dmaCycles = 0;
    uint8_t dmaSource = 0;

    void startDMA(uint8_t value);
    void tickDMA(int cycles);

    void requestVBlankInterrupt();

    void requestSTATInterrupt();

    void checkLYC();
    Bus* bus;

    uint8_t renderWindowPixel(int x);

    uint8_t renderBackgroundPixel(int x);

private:
    std::vector<Sprite> scanlineSprites;

    void evaluateSprites();
    void renderSprites();
    uint8_t getSpriteTilePixel(const Sprite& sprite, int spriteX, int spriteY);
};


#endif //GBEMULATOR_PPU_HPP
