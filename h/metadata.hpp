//
// Created by akith on 10/30/2025.
//

#ifndef GBEMULATOR_METADATA_HPP
#define GBEMULATOR_METADATA_HPP


#include <array>
#include "Cartridge.hpp"

enum HeaderSectionIndex{
    EntryPoint = 0,
    NintendoLogo,
    Title,
    CBGFlag,
    NewLicenseeCode,
    SGBFlag,
    CartridgeType,
    ROMSize,
    RAMSize,
    DestinationCode,
    OldLicenseeCode,
    MaskROMVersion,
    HeaderChecksum,
    GlobalChecksum,
    ChecksumStart = Title,
    ChecksumEnd = MaskROMVersion

};
inline constexpr std::array<Cartridge::HeaderSection, 14> kHeaderSections = {{
                                                                   {0x0100, 0x0103, "Entry Point",
                                                                    "After displaying the Nintendo logo, the boot ROM jumps here; "
                                                                    "the program should jump to the game’s main entry point."},

                                                                   {0x0104, 0x0133, "Nintendo Logo",
                                                                    "Contains the bitmap of the Nintendo logo. If not read correctly, "
                                                                    "the boot ROM locks up."},

                                                                   {0x0134, 0x0143, "Title / Manufacturer Code",
                                                                    "Contains the game title and manufacturer code in newer cartridges."},

                                                                   {0x0143, 0x0143, "CGB Flag",
                                                                    "In older cartridges, this was part of the title; in newer, indicates CGB compatibility."},

                                                                   {0x0144, 0x0145, "New Licensee Code",
                                                                    "Two-character licensee code identifying the publisher."},

                                                                   {0x0146, 0x0146, "SGB Flag",
                                                                    "Indicates whether the game supports Super Game Boy features."},

                                                                   {0x0147, 0x0147, "Cartridge Type",
                                                                    "Indicates hardware present on the cartridge (MBC, RAM, battery, etc.)."},

                                                                   {0x0148, 0x0148, "ROM Size",
                                                                    "Specifies total ROM size according to a code formula."},

                                                                   {0x0149, 0x0149, "RAM Size",
                                                                    "Specifies total external RAM size (if present)."},

                                                                   {0x014A, 0x014A, "Destination Code",
                                                                    "Indicates whether the game was sold in Japan or elsewhere."},

                                                                   {0x014B, 0x014B, "Old Licensee Code",
                                                                    "Legacy one-byte licensee code used before the new licensee system."},

                                                                   {0x014C, 0x014C, "Mask ROM Version",
                                                                    "Game version number (used to identify revisions)."},

                                                                   {0x014D, 0x014D, "Header Checksum",
                                                                    "Checksum of header data; boot ROM verifies this to ensure integrity."},

                                                                   {0x014E, 0x014F, "Global Checksum",
                                                                    "Checksum over entire ROM except these two bytes."}
                                                           }};

inline constexpr std::array<uint8_t, 48> NINTENDO_LOGO = {{
                                                                  0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
                                                                  0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
                                                                  0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
                                                                  0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
                                                                  0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
                                                                  0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
                                                          }};

inline constexpr std::array<Cartridge::RomSizeEntry, 12> ROM_SIZE_TABLE = {{
                                                                        {0x00,  32 * 1024,     2},   // 32 KiB (no banking)
                                                                        {0x01,  64 * 1024,     4},
                                                                        {0x02, 128 * 1024,     8},
                                                                        {0x03, 256 * 1024,    16},
                                                                        {0x04, 512 * 1024,    32},
                                                                        {0x05,   1 * 1024 * 1024,    64},
                                                                        {0x06,   2 * 1024 * 1024,   128},
                                                                        {0x07,   4 * 1024 * 1024,   256},
                                                                        {0x08,   8 * 1024 * 1024,   512},
                                                                        {0x52,   1126400,      72},   // 1.1 MiB
                                                                        {0x53,   1228800,      80},   // 1.2 MiB
                                                                        {0x54,   1536000,      96}    // 1.5 MiB
                                                                }};
constexpr const Cartridge::RomSizeEntry* getRomSizeInfo(uint8_t code) noexcept {
    for (auto const& e : ROM_SIZE_TABLE)
        if (e.code == code)
            return &e;
    return nullptr;
}

#endif //GBEMULATOR_METADATA_HPP
