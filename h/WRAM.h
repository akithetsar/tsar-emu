#pragma once
#include <array>
#include <cstddef>
#include <cstdint>

class WRAM {
public:
    uint8_t* bank() { return mem.data() + 0x0000; }
    const uint8_t* bank() const { return mem.data() + 0x0000; }


private:
    alignas(64)
    std::array<uint8_t, 0x2000> mem{};

};