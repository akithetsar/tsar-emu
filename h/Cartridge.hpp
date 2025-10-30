//
// Created by akith on 10/27/2025.
//

#ifndef GBEMULATOR_CARTRIDGE_HPP
#define GBEMULATOR_CARTRIDGE_HPP


#include <cstdint>
#include <vector>
#include <string>
class Cartridge {
public:
    struct HeaderSection {
        uint16_t start;
        uint16_t end;
        const char* name;
        const char* description;
    };
    struct RomSizeEntry {
        uint8_t code;        // Value stored at 0x0148
        uint32_t sizeBytes;  // Total ROM size in bytes
        uint16_t numBanks;   // Number of 16 KiB banks
    };


    explicit Cartridge(const std::string& cartridge_file);


    uint8_t read(uint16_t addr);

    void printMemory();
    bool verifyHeader();


private:

    std::vector<uint8_t> rom;
    RomSizeEntry romSize;





};


#endif //GBEMULATOR_CARTRIDGE_HPP
