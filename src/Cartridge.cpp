//
// Created by akith on 10/27/2025.
//

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../h/Cartridge.hpp"
#include "../h/metadata.hpp"
#include "../h/log.h"


Cartridge::Cartridge(const std::string& cartridge_file) {
    std::ifstream file(cartridge_file, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << cartridge_file << std::endl;
        return;
    }

    std::streampos size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    file.close();

    std::cout << "File loaded successfully.\n";
    std::cout << "Size: " << size << " bytes\n";

    this->rom = buffer;
    if (getRomSizeInfo(rom[kHeaderSections[HeaderSectionIndex::ROMSize].start])){
        this->romSize = *getRomSizeInfo(rom[kHeaderSections[HeaderSectionIndex::ROMSize].start]);
    }
    else{
        std::cout << "Impossible ROM size byte";
    }

}

void Cartridge::printMemory() {
    std::string title(reinterpret_cast<char*>(&rom[0x0134]), 16);
    std::cout << "Game title: " << title << "\n";
    printf("Cartridge type: %02X\n", rom[0x0147]);
    printf("ROM size code: %02X\n", rom[0x0148]);
    printf("RAM size code: %02X\n", rom[0x0149]);
    std::cout << std::dec << "\n"; // switch back to decimal output

}



bool Cartridge::verifyHeader() {


    //Checking for Nintendo Logo
    for (int i = 0; i < NINTENDO_LOGO.size(); ++i) {
        if (rom[kHeaderSections[HeaderSectionIndex::NintendoLogo].start + i] != NINTENDO_LOGO[i]) return false;
    }

    //Verifying header checksum
    uint8_t checksum = 0;
    for (uint16_t address = kHeaderSections[HeaderSectionIndex::ChecksumStart].start; address <= kHeaderSections[HeaderSectionIndex::ChecksumEnd].start; ++address) {
        checksum = checksum - rom[address] - 1;
    }

    if (checksum != rom[kHeaderSections[HeaderSectionIndex::HeaderChecksum].start]) return false;

    //Verifying global checksum
    uint16_t computedGlobalChecksum = 0;
    for (uint32_t address = 0; address < romSize.sizeBytes; ++address) {
        if (address == 0x014E || address == 0x014F)
            continue; // skip the checksum bytes themselves
        computedGlobalChecksum += rom[address];
    }

    uint16_t expectedChecksum = (rom[0x014E] << 8) | rom[0x014F];
    if (computedGlobalChecksum != expectedChecksum) return false;




    return true;
}

uint8_t Cartridge::read(uint16_t addr) {
    return rom[addr];
}
