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





// Encoded cycles like Opcodes.json "cycles": either a single value [t],
// or a conditional pair [not_taken, taken] (e.g., JR/JP/CALL/RET conditionals).
// base = first entry (or single value), alt = second entry if present, else 0.
struct OpCycles {
    uint8_t base; // required cycles (or "not taken" for conditionals)
    uint8_t alt;  // 0 if no alternate; otherwise "taken" cycles
};

constexpr OpCycles Single(uint8_t t) { return OpCycles{t, 0}; }
constexpr OpCycles Pair(uint8_t a, uint8_t b) { return OpCycles{a, b}; }

// Build base (non-CB) opcode cycles (256 entries).
// Values match Pan Docs / gbdev Opcodes.json semantics (in T-cycles).
constexpr std::array<OpCycles, 256> makeBaseCycles() {
    std::array<OpCycles, 256> c{};
    // Default to 0 for all (invalid/unused opcodes will remain 0,0)
    for (auto& e : c) e = Single(0);

    // 0x00 .. 0x0F
    c[0x00] = Single(4);   // NOP
    c[0x01] = Single(12);  // LD BC,d16
    c[0x02] = Single(8);   // LD (BC),A
    c[0x03] = Single(8);   // INC BC
    c[0x04] = Single(4);   // INC B
    c[0x05] = Single(4);   // DEC B
    c[0x06] = Single(8);   // LD B,d8
    c[0x07] = Single(4);   // RLCA
    c[0x08] = Single(20);  // LD (a16),SP
    c[0x09] = Single(8);   // ADD HL,BC
    c[0x0A] = Single(8);   // LD A,(BC)
    c[0x0B] = Single(8);   // DEC BC
    c[0x0C] = Single(4);   // INC C
    c[0x0D] = Single(4);   // DEC C
    c[0x0E] = Single(8);   // LD C,d8
    c[0x0F] = Single(4);   // RRCA

    // 0x10 .. 0x1F
    c[0x10] = Single(4);   // STOP
    c[0x11] = Single(12);  // LD DE,d16
    c[0x12] = Single(8);   // LD (DE),A
    c[0x13] = Single(8);   // INC DE
    c[0x14] = Single(4);   // INC D
    c[0x15] = Single(4);   // DEC D
    c[0x16] = Single(8);   // LD D,d8
    c[0x17] = Single(4);   // RLA
    c[0x18] = Single(12);  // JR r8
    c[0x19] = Single(8);   // ADD HL,DE
    c[0x1A] = Single(8);   // LD A,(DE)
    c[0x1B] = Single(8);   // DEC DE
    c[0x1C] = Single(4);   // INC E
    c[0x1D] = Single(4);   // DEC E
    c[0x1E] = Single(8);   // LD E,d8
    c[0x1F] = Single(4);   // RRA

    // 0x20 .. 0x2F
    c[0x20] = Pair(8, 12); // JR NZ,r8
    c[0x21] = Single(12);  // LD HL,d16
    c[0x22] = Single(8);   // LD (HL+),A
    c[0x23] = Single(8);   // INC HL
    c[0x24] = Single(4);   // INC H
    c[0x25] = Single(4);   // DEC H
    c[0x26] = Single(8);   // LD H,d8
    c[0x27] = Single(4);   // DAA
    c[0x28] = Pair(8, 12); // JR Z,r8
    c[0x29] = Single(8);   // ADD HL,HL
    c[0x2A] = Single(8);   // LD A,(HL+)
    c[0x2B] = Single(8);   // DEC HL
    c[0x2C] = Single(4);   // INC L
    c[0x2D] = Single(4);   // DEC L
    c[0x2E] = Single(8);   // LD L,d8
    c[0x2F] = Single(4);   // CPL

    // 0x30 .. 0x3F
    c[0x30] = Pair(8, 12); // JR NC,r8
    c[0x31] = Single(12);  // LD SP,d16
    c[0x32] = Single(8);   // LD (HL-),A
    c[0x33] = Single(8);   // INC SP
    c[0x34] = Single(12);  // INC (HL)
    c[0x35] = Single(12);  // DEC (HL)
    c[0x36] = Single(12);  // LD (HL),d8
    c[0x37] = Single(4);   // SCF
    c[0x38] = Pair(8, 12); // JR C,r8
    c[0x39] = Single(8);   // ADD HL,SP
    c[0x3A] = Single(8);   // LD A,(HL-)
    c[0x3B] = Single(8);   // DEC SP
    c[0x3C] = Single(4);   // INC A
    c[0x3D] = Single(4);   // DEC A
    c[0x3E] = Single(8);   // LD A,d8
    c[0x3F] = Single(4);   // CCF

    // 0x40 .. 0x7F: LD r[y], r[z] (0x76 = HALT)
    for (int op = 0x40; op <= 0x7F; ++op) {
        if (op == 0x76) { c[op] = Single(4); continue; } // HALT
        bool dstHL = ((op >> 3) & 7) == 6;
        bool srcHL = (op & 7) == 6;
        c[op] = Single((dstHL || srcHL) ? 8 : 4);
    }

    // 0x80 .. 0xBF: ALU A, r[z] (src (HL) costs 8, else 4)
    for (int op = 0x80; op <= 0xBF; ++op) {
        bool srcHL = (op & 7) == 6;
        c[op] = Single(srcHL ? 8 : 4);
    }

    // 0xC0 .. 0xCF
    c[0xC0] = Pair(8, 20); // RET NZ
    c[0xC1] = Single(12);  // POP BC
    c[0xC2] = Pair(12,16); // JP NZ,a16
    c[0xC3] = Single(16);  // JP a16
    c[0xC4] = Pair(12,24); // CALL NZ,a16
    c[0xC5] = Single(16);  // PUSH BC
    c[0xC6] = Single(8);   // ADD A,d8
    c[0xC7] = Single(16);  // RST 00H
    c[0xC8] = Pair(8, 20); // RET Z
    c[0xC9] = Single(16);  // RET
    c[0xCA] = Pair(12,16); // JP Z,a16
    c[0xCB] = Single(0);   // PREFIX CB (cycles accounted by CB opcode)
    c[0xCC] = Pair(12,24); // CALL Z,a16
    c[0xCD] = Single(24);  // CALL a16
    c[0xCE] = Single(8);   // ADC A,d8
    c[0xCF] = Single(16);  // RST 08H

    // 0xD0 .. 0xDF
    c[0xD0] = Pair(8, 20); // RET NC
    c[0xD1] = Single(12);  // POP DE
    c[0xD2] = Pair(12,16); // JP NC,a16
    c[0xD3] = Single(0);   // INVALID/UNUSED
    c[0xD4] = Pair(12,24); // CALL NC,a16
    c[0xD5] = Single(16);  // PUSH DE
    c[0xD6] = Single(8);   // SUB d8
    c[0xD7] = Single(16);  // RST 10H
    c[0xD8] = Pair(8, 20); // RET C
    c[0xD9] = Single(16);  // RETI
    c[0xDA] = Pair(12,16); // JP C,a16
    c[0xDB] = Single(0);   // INVALID/UNUSED
    c[0xDC] = Pair(12,24); // CALL C,a16
    c[0xDD] = Single(0);   // INVALID/UNUSED
    c[0xDE] = Single(8);   // SBC A,d8
    c[0xDF] = Single(16);  // RST 18H

    // 0xE0 .. 0xEF
    c[0xE0] = Single(12);  // LDH (a8),A
    c[0xE1] = Single(12);  // POP HL
    c[0xE2] = Single(8);   // LD (C),A
    c[0xE3] = Single(0);   // INVALID/UNUSED
    c[0xE4] = Single(0);   // INVALID/UNUSED
    c[0xE5] = Single(16);  // PUSH HL
    c[0xE6] = Single(8);   // AND d8
    c[0xE7] = Single(16);  // RST 20H
    c[0xE8] = Single(16);  // ADD SP,e8
    c[0xE9] = Single(4);   // JP (HL)
    c[0xEA] = Single(16);  // LD (a16),A
    c[0xEB] = Single(0);   // INVALID/UNUSED
    c[0xEC] = Single(0);   // INVALID/UNUSED
    c[0xED] = Single(0);   // INVALID/UNUSED
    c[0xEE] = Single(8);   // XOR d8
    c[0xEF] = Single(16);  // RST 28H

    // 0xF0 .. 0xFF
    c[0xF0] = Single(12);  // LDH A,(a8)
    c[0xF1] = Single(12);  // POP AF
    c[0xF2] = Single(8);   // LD A,(C)
    c[0xF3] = Single(4);   // DI
    c[0xF4] = Single(0);   // INVALID/UNUSED
    c[0xF5] = Single(16);  // PUSH AF
    c[0xF6] = Single(8);   // OR d8
    c[0xF7] = Single(16);  // RST 30H
    c[0xF8] = Single(12);  // LD HL,SP+e8
    c[0xF9] = Single(8);   // LD SP,HL
    c[0xFA] = Single(16);  // LD A,(a16)
    c[0xFB] = Single(4);   // EI
    c[0xFC] = Single(0);   // INVALID/UNUSED
    c[0xFD] = Single(0);   // INVALID/UNUSED
    c[0xFE] = Single(8);   // CP d8
    c[0xFF] = Single(16);  // RST 38H

    return c;
}

// Build CB-prefixed opcode cycles (all 256).
// All CB ops are 8 cycles except those targeting (HL) (z==6), which are 16.
constexpr std::array<OpCycles, 256> makeCBCycles() {
    std::array<OpCycles, 256> c{};
    for (int cb = 0; cb < 256; ++cb) {
        bool isHL = (cb & 0x07) == 6;
        c[cb] = Single(isHL ? 16 : 8);
    }
    return c;
}

inline constexpr std::array<OpCycles, 256> OPCODE_CYCLES = makeBaseCycles();
inline constexpr std::array<OpCycles, 256> CB_OPCODE_CYCLES = makeCBCycles();

// Pick the appropriate cycle count for a conditional instruction where "taken" might apply.
constexpr uint8_t cyclesNonCB(uint8_t opcode, bool taken = false) {
    const auto& oc = OPCODE_CYCLES[opcode];
    return (!taken || oc.alt == 0) ? oc.base : oc.alt;
}
constexpr uint8_t cyclesCB(uint8_t cbOpcode) {
    return CB_OPCODE_CYCLES[cbOpcode].base; // CB ops have single cycle value (8 or 16)
}
#endif //GBEMULATOR_METADATA_HPP
