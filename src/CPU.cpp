//
// Created by akith on 10/31/2025.
//
#include <iostream>
#include <iomanip>
#include "../h/CPU.h"
#include "../h/opcodes.h"
int CPU::cycle() {

    logState();
    uint8_t opcode = fetch8();

    if (opcode == 0xCB)
    {
        opcode = fetch8();
        return cbOpTable[opcode](*this, opcode);
        return 0;
    }

    int t = opTable[opcode](*this, opcode);

//    std::cout << '\n';
//    std::cout << "-----------------" << '\n';
//    std::cout << std::uppercase << std::setfill('0'); // optional: uppercase A-F
//
//    std::cout << "PC: 0x" << std::setw(4) << std::hex << static_cast<uint16_t>(PC) << '\n';
//    std::cout << "SP: 0x" << std::setw(4) << std::hex << static_cast<uint16_t>(SP) << '\n';
//    std::cout << "AF: 0x" << std::setw(4) << std::hex << static_cast<uint16_t>(AF) << '\n';
//    std::cout << "BC: 0x" << std::setw(4) << std::hex << static_cast<uint16_t>(BC) << '\n';
//    std::cout << "DE: 0x" << std::setw(4) << std::hex << static_cast<uint16_t>(DE) << '\n';
//    std::cout << "HL: 0x" << std::setw(4) << std::hex << static_cast<uint16_t>(HL) << '\n';
//
//    std::cout << std::dec; // switch back to decimal for flags
//    std::cout << "Z: " << get_flag_Z() << '\n';
//    std::cout << "N: " << get_flag_N() << '\n';
//    std::cout << "H: " << get_flag_H() << '\n';
//    std::cout << "C: " << get_flag_C() << '\n';
//    std::cout << "-----------------" << '\n';



    return t;



}

void CPU::mapOPCodes() {
    opTable[0x00] = opcodes::OP_0x00;
    opTable[0x01] = opcodes::OP_0x01;
    opTable[0x02] = opcodes::OP_0x02;
    opTable[0x03] = opcodes::OP_0x03;
    opTable[0x04] = opcodes::OP_0x04;
    opTable[0x05] = opcodes::OP_0x05;
    opTable[0x06] = opcodes::OP_0x06;
    opTable[0x07] = opcodes::OP_0x07;
    opTable[0x08] = opcodes::OP_0x08;
    opTable[0x09] = opcodes::OP_0x09;
    opTable[0x0A] = opcodes::OP_0x0A;
    opTable[0x0B] = opcodes::OP_0x0B;
    opTable[0x0C] = opcodes::OP_0x0C;
    opTable[0x0D] = opcodes::OP_0x0D;
    opTable[0x0E] = opcodes::OP_0x0E;
    opTable[0x0F] = opcodes::OP_0x0F;

    opTable[0x10] = opcodes::OP_0x10;
    opTable[0x11] = opcodes::OP_0x11;
    opTable[0x12] = opcodes::OP_0x12;
    opTable[0x13] = opcodes::OP_0x13;
    opTable[0x14] = opcodes::OP_0x14;
    opTable[0x15] = opcodes::OP_0x15;
    opTable[0x16] = opcodes::OP_0x16;
    opTable[0x17] = opcodes::OP_0x17;
    opTable[0x18] = opcodes::OP_0x18;
    opTable[0x19] = opcodes::OP_0x19;
    opTable[0x1A] = opcodes::OP_0x1A;
    opTable[0x1B] = opcodes::OP_0x1B;
    opTable[0x1C] = opcodes::OP_0x1C;
    opTable[0x1D] = opcodes::OP_0x1D;
    opTable[0x1E] = opcodes::OP_0x1E;
    opTable[0x1F] = opcodes::OP_0x1F;

    opTable[0x20] = opcodes::OP_0x20;
    opTable[0x21] = opcodes::OP_0x21;
    opTable[0x22] = opcodes::OP_0x22;
    opTable[0x23] = opcodes::OP_0x23;
    opTable[0x24] = opcodes::OP_0x24;
    opTable[0x25] = opcodes::OP_0x25;
    opTable[0x26] = opcodes::OP_0x26;
    opTable[0x27] = opcodes::OP_0x27;
    opTable[0x28] = opcodes::OP_0x28;
    opTable[0x29] = opcodes::OP_0x29;
    opTable[0x2A] = opcodes::OP_0x2A;
    opTable[0x2B] = opcodes::OP_0x2B;
    opTable[0x2C] = opcodes::OP_0x2C;
    opTable[0x2D] = opcodes::OP_0x2D;
    opTable[0x2E] = opcodes::OP_0x2E;
    opTable[0x2F] = opcodes::OP_0x2F;

    opTable[0x30] = opcodes::OP_0x30;
    opTable[0x31] = opcodes::OP_0x31;
    opTable[0x32] = opcodes::OP_0x32;
    opTable[0x33] = opcodes::OP_0x33;
    opTable[0x34] = opcodes::OP_0x34;
    opTable[0x35] = opcodes::OP_0x35;
    opTable[0x36] = opcodes::OP_0x36;
    opTable[0x37] = opcodes::OP_0x37;
    opTable[0x38] = opcodes::OP_0x38;
    opTable[0x39] = opcodes::OP_0x39;
    opTable[0x3A] = opcodes::OP_0x3A;
    opTable[0x3B] = opcodes::OP_0x3B;
    opTable[0x3C] = opcodes::OP_0x3C;
    opTable[0x3D] = opcodes::OP_0x3D;
    opTable[0x3E] = opcodes::OP_0x3E;
    opTable[0x3F] = opcodes::OP_0x3F;

    opTable[0x40] = opcodes::OP_0x40;
    opTable[0x41] = opcodes::OP_0x41;
    opTable[0x42] = opcodes::OP_0x42;
    opTable[0x43] = opcodes::OP_0x43;
    opTable[0x44] = opcodes::OP_0x44;
    opTable[0x45] = opcodes::OP_0x45;
    opTable[0x46] = opcodes::OP_0x46;
    opTable[0x47] = opcodes::OP_0x47;
    opTable[0x48] = opcodes::OP_0x48;
    opTable[0x49] = opcodes::OP_0x49;
    opTable[0x4A] = opcodes::OP_0x4A;
    opTable[0x4B] = opcodes::OP_0x4B;
    opTable[0x4C] = opcodes::OP_0x4C;
    opTable[0x4D] = opcodes::OP_0x4D;
    opTable[0x4E] = opcodes::OP_0x4E;
    opTable[0x4F] = opcodes::OP_0x4F;

    opTable[0x50] = opcodes::OP_0x50;
    opTable[0x51] = opcodes::OP_0x51;
    opTable[0x52] = opcodes::OP_0x52;
    opTable[0x53] = opcodes::OP_0x53;
    opTable[0x54] = opcodes::OP_0x54;
    opTable[0x55] = opcodes::OP_0x55;
    opTable[0x56] = opcodes::OP_0x56;
    opTable[0x57] = opcodes::OP_0x57;
    opTable[0x58] = opcodes::OP_0x58;
    opTable[0x59] = opcodes::OP_0x59;
    opTable[0x5A] = opcodes::OP_0x5A;
    opTable[0x5B] = opcodes::OP_0x5B;
    opTable[0x5C] = opcodes::OP_0x5C;
    opTable[0x5D] = opcodes::OP_0x5D;
    opTable[0x5E] = opcodes::OP_0x5E;
    opTable[0x5F] = opcodes::OP_0x5F;

    opTable[0x60] = opcodes::OP_0x60;
    opTable[0x61] = opcodes::OP_0x61;
    opTable[0x62] = opcodes::OP_0x62;
    opTable[0x63] = opcodes::OP_0x63;
    opTable[0x64] = opcodes::OP_0x64;
    opTable[0x65] = opcodes::OP_0x65;
    opTable[0x66] = opcodes::OP_0x66;
    opTable[0x67] = opcodes::OP_0x67;
    opTable[0x68] = opcodes::OP_0x68;
    opTable[0x69] = opcodes::OP_0x69;
    opTable[0x6A] = opcodes::OP_0x6A;
    opTable[0x6B] = opcodes::OP_0x6B;
    opTable[0x6C] = opcodes::OP_0x6C;
    opTable[0x6D] = opcodes::OP_0x6D;
    opTable[0x6E] = opcodes::OP_0x6E;
    opTable[0x6F] = opcodes::OP_0x6F;

    opTable[0x70] = opcodes::OP_0x70;
    opTable[0x71] = opcodes::OP_0x71;
    opTable[0x72] = opcodes::OP_0x72;
    opTable[0x73] = opcodes::OP_0x73;
    opTable[0x74] = opcodes::OP_0x74;
    opTable[0x75] = opcodes::OP_0x75;
    opTable[0x76] = opcodes::OP_0x76;
    opTable[0x77] = opcodes::OP_0x77;
    opTable[0x78] = opcodes::OP_0x78;
    opTable[0x79] = opcodes::OP_0x79;
    opTable[0x7A] = opcodes::OP_0x7A;
    opTable[0x7B] = opcodes::OP_0x7B;
    opTable[0x7C] = opcodes::OP_0x7C;
    opTable[0x7D] = opcodes::OP_0x7D;
    opTable[0x7E] = opcodes::OP_0x7E;
    opTable[0x7F] = opcodes::OP_0x7F;

    opTable[0x80] = opcodes::OP_0x80;
    opTable[0x81] = opcodes::OP_0x81;
    opTable[0x82] = opcodes::OP_0x82;
    opTable[0x83] = opcodes::OP_0x83;
    opTable[0x84] = opcodes::OP_0x84;
    opTable[0x85] = opcodes::OP_0x85;
    opTable[0x86] = opcodes::OP_0x86;
    opTable[0x87] = opcodes::OP_0x87;
    opTable[0x88] = opcodes::OP_0x88;
    opTable[0x89] = opcodes::OP_0x89;
    opTable[0x8A] = opcodes::OP_0x8A;
    opTable[0x8B] = opcodes::OP_0x8B;
    opTable[0x8C] = opcodes::OP_0x8C;
    opTable[0x8D] = opcodes::OP_0x8D;
    opTable[0x8E] = opcodes::OP_0x8E;
    opTable[0x8F] = opcodes::OP_0x8F;

    opTable[0x90] = opcodes::OP_0x90;
    opTable[0x91] = opcodes::OP_0x91;
    opTable[0x92] = opcodes::OP_0x92;
    opTable[0x93] = opcodes::OP_0x93;
    opTable[0x94] = opcodes::OP_0x94;
    opTable[0x95] = opcodes::OP_0x95;
    opTable[0x96] = opcodes::OP_0x96;
    opTable[0x97] = opcodes::OP_0x97;
    opTable[0x98] = opcodes::OP_0x98;
    opTable[0x99] = opcodes::OP_0x99;
    opTable[0x9A] = opcodes::OP_0x9A;
    opTable[0x9B] = opcodes::OP_0x9B;
    opTable[0x9C] = opcodes::OP_0x9C;
    opTable[0x9D] = opcodes::OP_0x9D;
    opTable[0x9E] = opcodes::OP_0x9E;
    opTable[0x9F] = opcodes::OP_0x9F;

    opTable[0xA0] = opcodes::OP_0xA0;
    opTable[0xA1] = opcodes::OP_0xA1;
    opTable[0xA2] = opcodes::OP_0xA2;
    opTable[0xA3] = opcodes::OP_0xA3;
    opTable[0xA4] = opcodes::OP_0xA4;
    opTable[0xA5] = opcodes::OP_0xA5;
    opTable[0xA6] = opcodes::OP_0xA6;
    opTable[0xA7] = opcodes::OP_0xA7;
    opTable[0xA8] = opcodes::OP_0xA8;
    opTable[0xA9] = opcodes::OP_0xA9;
    opTable[0xAA] = opcodes::OP_0xAA;
    opTable[0xAB] = opcodes::OP_0xAB;
    opTable[0xAC] = opcodes::OP_0xAC;
    opTable[0xAD] = opcodes::OP_0xAD;
    opTable[0xAE] = opcodes::OP_0xAE;
    opTable[0xAF] = opcodes::OP_0xAF;

    opTable[0xB0] = opcodes::OP_0xB0;
    opTable[0xB1] = opcodes::OP_0xB1;
    opTable[0xB2] = opcodes::OP_0xB2;
    opTable[0xB3] = opcodes::OP_0xB3;
    opTable[0xB4] = opcodes::OP_0xB4;
    opTable[0xB5] = opcodes::OP_0xB5;
    opTable[0xB6] = opcodes::OP_0xB6;
    opTable[0xB7] = opcodes::OP_0xB7;
    opTable[0xB8] = opcodes::OP_0xB8;
    opTable[0xB9] = opcodes::OP_0xB9;
    opTable[0xBA] = opcodes::OP_0xBA;
    opTable[0xBB] = opcodes::OP_0xBB;
    opTable[0xBC] = opcodes::OP_0xBC;
    opTable[0xBD] = opcodes::OP_0xBD;
    opTable[0xBE] = opcodes::OP_0xBE;
    opTable[0xBF] = opcodes::OP_0xBF;

    opTable[0xC0] = opcodes::OP_0xC0;
    opTable[0xC1] = opcodes::OP_0xC1;
    opTable[0xC2] = opcodes::OP_0xC2;
    opTable[0xC3] = opcodes::OP_0xC3;
    opTable[0xC4] = opcodes::OP_0xC4;
    opTable[0xC5] = opcodes::OP_0xC5;
    opTable[0xC6] = opcodes::OP_0xC6;
    opTable[0xC7] = opcodes::OP_0xC7;
    opTable[0xC8] = opcodes::OP_0xC8;
    opTable[0xC9] = opcodes::OP_0xC9;
    opTable[0xCA] = opcodes::OP_0xCA;
    opTable[0xCB] = opcodes::OP_0xCB;
    opTable[0xCC] = opcodes::OP_0xCC;
    opTable[0xCD] = opcodes::OP_0xCD;
    opTable[0xCE] = opcodes::OP_0xCE;
    opTable[0xCF] = opcodes::OP_0xCF;

    opTable[0xD0] = opcodes::OP_0xD0;
    opTable[0xD1] = opcodes::OP_0xD1;
    opTable[0xD2] = opcodes::OP_0xD2;
    opTable[0xD3] = opcodes::OP_0xD3;
    opTable[0xD4] = opcodes::OP_0xD4;
    opTable[0xD5] = opcodes::OP_0xD5;
    opTable[0xD6] = opcodes::OP_0xD6;
    opTable[0xD7] = opcodes::OP_0xD7;
    opTable[0xD8] = opcodes::OP_0xD8;
    opTable[0xD9] = opcodes::OP_0xD9;
    opTable[0xDA] = opcodes::OP_0xDA;
    opTable[0xDB] = opcodes::OP_0xDB;
    opTable[0xDC] = opcodes::OP_0xDC;
    opTable[0xDD] = opcodes::OP_0xDD;
    opTable[0xDE] = opcodes::OP_0xDE;
    opTable[0xDF] = opcodes::OP_0xDF;

    opTable[0xE0] = opcodes::OP_0xE0;
    opTable[0xE1] = opcodes::OP_0xE1;
    opTable[0xE2] = opcodes::OP_0xE2;
    opTable[0xE3] = opcodes::OP_0xE3;
    opTable[0xE4] = opcodes::OP_0xE4;
    opTable[0xE5] = opcodes::OP_0xE5;
    opTable[0xE6] = opcodes::OP_0xE6;
    opTable[0xE7] = opcodes::OP_0xE7;
    opTable[0xE8] = opcodes::OP_0xE8;
    opTable[0xE9] = opcodes::OP_0xE9;
    opTable[0xEA] = opcodes::OP_0xEA;
    opTable[0xEB] = opcodes::OP_0xEB;
    opTable[0xEC] = opcodes::OP_0xEC;
    opTable[0xED] = opcodes::OP_0xED;
    opTable[0xEE] = opcodes::OP_0xEE;
    opTable[0xEF] = opcodes::OP_0xEF;

    opTable[0xF0] = opcodes::OP_0xF0;
    opTable[0xF1] = opcodes::OP_0xF1;
    opTable[0xF2] = opcodes::OP_0xF2;
    opTable[0xF3] = opcodes::OP_0xF3;
    opTable[0xF4] = opcodes::OP_0xF4;
    opTable[0xF5] = opcodes::OP_0xF5;
    opTable[0xF6] = opcodes::OP_0xF6;
    opTable[0xF7] = opcodes::OP_0xF7;
    opTable[0xF8] = opcodes::OP_0xF8;
    opTable[0xF9] = opcodes::OP_0xF9;
    opTable[0xFA] = opcodes::OP_0xFA;
    opTable[0xFB] = opcodes::OP_0xFB;
    opTable[0xFC] = opcodes::OP_0xFC;
    opTable[0xFD] = opcodes::OP_0xFD;
    opTable[0xFE] = opcodes::OP_0xFE;
    opTable[0xFF] = opcodes::OP_0xFF;
}
void CPU::mapCBOPCodes() {
    cbOpTable[0x00] = opcodes::CB_0x00;
    cbOpTable[0x01] = opcodes::CB_0x01;
    cbOpTable[0x02] = opcodes::CB_0x02;
    cbOpTable[0x03] = opcodes::CB_0x03;
    cbOpTable[0x04] = opcodes::CB_0x04;
    cbOpTable[0x05] = opcodes::CB_0x05;
    cbOpTable[0x06] = opcodes::CB_0x06;
    cbOpTable[0x07] = opcodes::CB_0x07;
    cbOpTable[0x08] = opcodes::CB_0x08;
    cbOpTable[0x09] = opcodes::CB_0x09;
    cbOpTable[0x0A] = opcodes::CB_0x0A;
    cbOpTable[0x0B] = opcodes::CB_0x0B;
    cbOpTable[0x0C] = opcodes::CB_0x0C;
    cbOpTable[0x0D] = opcodes::CB_0x0D;
    cbOpTable[0x0E] = opcodes::CB_0x0E;
    cbOpTable[0x0F] = opcodes::CB_0x0F;

    cbOpTable[0x10] = opcodes::CB_0x10;
    cbOpTable[0x11] = opcodes::CB_0x11;
    cbOpTable[0x12] = opcodes::CB_0x12;
    cbOpTable[0x13] = opcodes::CB_0x13;
    cbOpTable[0x14] = opcodes::CB_0x14;
    cbOpTable[0x15] = opcodes::CB_0x15;
    cbOpTable[0x16] = opcodes::CB_0x16;
    cbOpTable[0x17] = opcodes::CB_0x17;
    cbOpTable[0x18] = opcodes::CB_0x18;
    cbOpTable[0x19] = opcodes::CB_0x19;
    cbOpTable[0x1A] = opcodes::CB_0x1A;
    cbOpTable[0x1B] = opcodes::CB_0x1B;
    cbOpTable[0x1C] = opcodes::CB_0x1C;
    cbOpTable[0x1D] = opcodes::CB_0x1D;
    cbOpTable[0x1E] = opcodes::CB_0x1E;
    cbOpTable[0x1F] = opcodes::CB_0x1F;

    cbOpTable[0x20] = opcodes::CB_0x20;
    cbOpTable[0x21] = opcodes::CB_0x21;
    cbOpTable[0x22] = opcodes::CB_0x22;
    cbOpTable[0x23] = opcodes::CB_0x23;
    cbOpTable[0x24] = opcodes::CB_0x24;
    cbOpTable[0x25] = opcodes::CB_0x25;
    cbOpTable[0x26] = opcodes::CB_0x26;
    cbOpTable[0x27] = opcodes::CB_0x27;
    cbOpTable[0x28] = opcodes::CB_0x28;
    cbOpTable[0x29] = opcodes::CB_0x29;
    cbOpTable[0x2A] = opcodes::CB_0x2A;
    cbOpTable[0x2B] = opcodes::CB_0x2B;
    cbOpTable[0x2C] = opcodes::CB_0x2C;
    cbOpTable[0x2D] = opcodes::CB_0x2D;
    cbOpTable[0x2E] = opcodes::CB_0x2E;
    cbOpTable[0x2F] = opcodes::CB_0x2F;

    cbOpTable[0x30] = opcodes::CB_0x30;
    cbOpTable[0x31] = opcodes::CB_0x31;
    cbOpTable[0x32] = opcodes::CB_0x32;
    cbOpTable[0x33] = opcodes::CB_0x33;
    cbOpTable[0x34] = opcodes::CB_0x34;
    cbOpTable[0x35] = opcodes::CB_0x35;
    cbOpTable[0x36] = opcodes::CB_0x36;
    cbOpTable[0x37] = opcodes::CB_0x37;
    cbOpTable[0x38] = opcodes::CB_0x38;
    cbOpTable[0x39] = opcodes::CB_0x39;
    cbOpTable[0x3A] = opcodes::CB_0x3A;
    cbOpTable[0x3B] = opcodes::CB_0x3B;
    cbOpTable[0x3C] = opcodes::CB_0x3C;
    cbOpTable[0x3D] = opcodes::CB_0x3D;
    cbOpTable[0x3E] = opcodes::CB_0x3E;
    cbOpTable[0x3F] = opcodes::CB_0x3F;

    cbOpTable[0x40] = opcodes::CB_0x40;
    cbOpTable[0x41] = opcodes::CB_0x41;
    cbOpTable[0x42] = opcodes::CB_0x42;
    cbOpTable[0x43] = opcodes::CB_0x43;
    cbOpTable[0x44] = opcodes::CB_0x44;
    cbOpTable[0x45] = opcodes::CB_0x45;
    cbOpTable[0x46] = opcodes::CB_0x46;
    cbOpTable[0x47] = opcodes::CB_0x47;
    cbOpTable[0x48] = opcodes::CB_0x48;
    cbOpTable[0x49] = opcodes::CB_0x49;
    cbOpTable[0x4A] = opcodes::CB_0x4A;
    cbOpTable[0x4B] = opcodes::CB_0x4B;
    cbOpTable[0x4C] = opcodes::CB_0x4C;
    cbOpTable[0x4D] = opcodes::CB_0x4D;
    cbOpTable[0x4E] = opcodes::CB_0x4E;
    cbOpTable[0x4F] = opcodes::CB_0x4F;

    cbOpTable[0x50] = opcodes::CB_0x50;
    cbOpTable[0x51] = opcodes::CB_0x51;
    cbOpTable[0x52] = opcodes::CB_0x52;
    cbOpTable[0x53] = opcodes::CB_0x53;
    cbOpTable[0x54] = opcodes::CB_0x54;
    cbOpTable[0x55] = opcodes::CB_0x55;
    cbOpTable[0x56] = opcodes::CB_0x56;
    cbOpTable[0x57] = opcodes::CB_0x57;
    cbOpTable[0x58] = opcodes::CB_0x58;
    cbOpTable[0x59] = opcodes::CB_0x59;
    cbOpTable[0x5A] = opcodes::CB_0x5A;
    cbOpTable[0x5B] = opcodes::CB_0x5B;
    cbOpTable[0x5C] = opcodes::CB_0x5C;
    cbOpTable[0x5D] = opcodes::CB_0x5D;
    cbOpTable[0x5E] = opcodes::CB_0x5E;
    cbOpTable[0x5F] = opcodes::CB_0x5F;

    cbOpTable[0x60] = opcodes::CB_0x60;
    cbOpTable[0x61] = opcodes::CB_0x61;
    cbOpTable[0x62] = opcodes::CB_0x62;
    cbOpTable[0x63] = opcodes::CB_0x63;
    cbOpTable[0x64] = opcodes::CB_0x64;
    cbOpTable[0x65] = opcodes::CB_0x65;
    cbOpTable[0x66] = opcodes::CB_0x66;
    cbOpTable[0x67] = opcodes::CB_0x67;
    cbOpTable[0x68] = opcodes::CB_0x68;
    cbOpTable[0x69] = opcodes::CB_0x69;
    cbOpTable[0x6A] = opcodes::CB_0x6A;
    cbOpTable[0x6B] = opcodes::CB_0x6B;
    cbOpTable[0x6C] = opcodes::CB_0x6C;
    cbOpTable[0x6D] = opcodes::CB_0x6D;
    cbOpTable[0x6E] = opcodes::CB_0x6E;
    cbOpTable[0x6F] = opcodes::CB_0x6F;

    cbOpTable[0x70] = opcodes::CB_0x70;
    cbOpTable[0x71] = opcodes::CB_0x71;
    cbOpTable[0x72] = opcodes::CB_0x72;
    cbOpTable[0x73] = opcodes::CB_0x73;
    cbOpTable[0x74] = opcodes::CB_0x74;
    cbOpTable[0x75] = opcodes::CB_0x75;
    cbOpTable[0x76] = opcodes::CB_0x76;
    cbOpTable[0x77] = opcodes::CB_0x77;
    cbOpTable[0x78] = opcodes::CB_0x78;
    cbOpTable[0x79] = opcodes::CB_0x79;
    cbOpTable[0x7A] = opcodes::CB_0x7A;
    cbOpTable[0x7B] = opcodes::CB_0x7B;
    cbOpTable[0x7C] = opcodes::CB_0x7C;
    cbOpTable[0x7D] = opcodes::CB_0x7D;
    cbOpTable[0x7E] = opcodes::CB_0x7E;
    cbOpTable[0x7F] = opcodes::CB_0x7F;

    cbOpTable[0x80] = opcodes::CB_0x80;
    cbOpTable[0x81] = opcodes::CB_0x81;
    cbOpTable[0x82] = opcodes::CB_0x82;
    cbOpTable[0x83] = opcodes::CB_0x83;
    cbOpTable[0x84] = opcodes::CB_0x84;
    cbOpTable[0x85] = opcodes::CB_0x85;
    cbOpTable[0x86] = opcodes::CB_0x86;
    cbOpTable[0x87] = opcodes::CB_0x87;
    cbOpTable[0x88] = opcodes::CB_0x88;
    cbOpTable[0x89] = opcodes::CB_0x89;
    cbOpTable[0x8A] = opcodes::CB_0x8A;
    cbOpTable[0x8B] = opcodes::CB_0x8B;
    cbOpTable[0x8C] = opcodes::CB_0x8C;
    cbOpTable[0x8D] = opcodes::CB_0x8D;
    cbOpTable[0x8E] = opcodes::CB_0x8E;
    cbOpTable[0x8F] = opcodes::CB_0x8F;

    cbOpTable[0x90] = opcodes::CB_0x90;
    cbOpTable[0x91] = opcodes::CB_0x91;
    cbOpTable[0x92] = opcodes::CB_0x92;
    cbOpTable[0x93] = opcodes::CB_0x93;
    cbOpTable[0x94] = opcodes::CB_0x94;
    cbOpTable[0x95] = opcodes::CB_0x95;
    cbOpTable[0x96] = opcodes::CB_0x96;
    cbOpTable[0x97] = opcodes::CB_0x97;
    cbOpTable[0x98] = opcodes::CB_0x98;
    cbOpTable[0x99] = opcodes::CB_0x99;
    cbOpTable[0x9A] = opcodes::CB_0x9A;
    cbOpTable[0x9B] = opcodes::CB_0x9B;
    cbOpTable[0x9C] = opcodes::CB_0x9C;
    cbOpTable[0x9D] = opcodes::CB_0x9D;
    cbOpTable[0x9E] = opcodes::CB_0x9E;
    cbOpTable[0x9F] = opcodes::CB_0x9F;

    cbOpTable[0xA0] = opcodes::CB_0xA0;
    cbOpTable[0xA1] = opcodes::CB_0xA1;
    cbOpTable[0xA2] = opcodes::CB_0xA2;
    cbOpTable[0xA3] = opcodes::CB_0xA3;
    cbOpTable[0xA4] = opcodes::CB_0xA4;
    cbOpTable[0xA5] = opcodes::CB_0xA5;
    cbOpTable[0xA6] = opcodes::CB_0xA6;
    cbOpTable[0xA7] = opcodes::CB_0xA7;
    cbOpTable[0xA8] = opcodes::CB_0xA8;
    cbOpTable[0xA9] = opcodes::CB_0xA9;
    cbOpTable[0xAA] = opcodes::CB_0xAA;
    cbOpTable[0xAB] = opcodes::CB_0xAB;
    cbOpTable[0xAC] = opcodes::CB_0xAC;
    cbOpTable[0xAD] = opcodes::CB_0xAD;
    cbOpTable[0xAE] = opcodes::CB_0xAE;
    cbOpTable[0xAF] = opcodes::CB_0xAF;

    cbOpTable[0xB0] = opcodes::CB_0xB0;
    cbOpTable[0xB1] = opcodes::CB_0xB1;
    cbOpTable[0xB2] = opcodes::CB_0xB2;
    cbOpTable[0xB3] = opcodes::CB_0xB3;
    cbOpTable[0xB4] = opcodes::CB_0xB4;
    cbOpTable[0xB5] = opcodes::CB_0xB5;
    cbOpTable[0xB6] = opcodes::CB_0xB6;
    cbOpTable[0xB7] = opcodes::CB_0xB7;
    cbOpTable[0xB8] = opcodes::CB_0xB8;
    cbOpTable[0xB9] = opcodes::CB_0xB9;
    cbOpTable[0xBA] = opcodes::CB_0xBA;
    cbOpTable[0xBB] = opcodes::CB_0xBB;
    cbOpTable[0xBC] = opcodes::CB_0xBC;
    cbOpTable[0xBD] = opcodes::CB_0xBD;
    cbOpTable[0xBE] = opcodes::CB_0xBE;
    cbOpTable[0xBF] = opcodes::CB_0xBF;

    cbOpTable[0xC0] = opcodes::CB_0xC0;
    cbOpTable[0xC1] = opcodes::CB_0xC1;
    cbOpTable[0xC2] = opcodes::CB_0xC2;
    cbOpTable[0xC3] = opcodes::CB_0xC3;
    cbOpTable[0xC4] = opcodes::CB_0xC4;
    cbOpTable[0xC5] = opcodes::CB_0xC5;
    cbOpTable[0xC6] = opcodes::CB_0xC6;
    cbOpTable[0xC7] = opcodes::CB_0xC7;
    cbOpTable[0xC8] = opcodes::CB_0xC8;
    cbOpTable[0xC9] = opcodes::CB_0xC9;
    cbOpTable[0xCA] = opcodes::CB_0xCA;
    cbOpTable[0xCB] = opcodes::CB_0xCB;
    cbOpTable[0xCC] = opcodes::CB_0xCC;
    cbOpTable[0xCD] = opcodes::CB_0xCD;
    cbOpTable[0xCE] = opcodes::CB_0xCE;
    cbOpTable[0xCF] = opcodes::CB_0xCF;

    cbOpTable[0xD0] = opcodes::CB_0xD0;
    cbOpTable[0xD1] = opcodes::CB_0xD1;
    cbOpTable[0xD2] = opcodes::CB_0xD2;
    cbOpTable[0xD3] = opcodes::CB_0xD3;
    cbOpTable[0xD4] = opcodes::CB_0xD4;
    cbOpTable[0xD5] = opcodes::CB_0xD5;
    cbOpTable[0xD6] = opcodes::CB_0xD6;
    cbOpTable[0xD7] = opcodes::CB_0xD7;
    cbOpTable[0xD8] = opcodes::CB_0xD8;
    cbOpTable[0xD9] = opcodes::CB_0xD9;
    cbOpTable[0xDA] = opcodes::CB_0xDA;
    cbOpTable[0xDB] = opcodes::CB_0xDB;
    cbOpTable[0xDC] = opcodes::CB_0xDC;
    cbOpTable[0xDD] = opcodes::CB_0xDD;
    cbOpTable[0xDE] = opcodes::CB_0xDE;
    cbOpTable[0xDF] = opcodes::CB_0xDF;

    cbOpTable[0xE0] = opcodes::CB_0xE0;
    cbOpTable[0xE1] = opcodes::CB_0xE1;
    cbOpTable[0xE2] = opcodes::CB_0xE2;
    cbOpTable[0xE3] = opcodes::CB_0xE3;
    cbOpTable[0xE4] = opcodes::CB_0xE4;
    cbOpTable[0xE5] = opcodes::CB_0xE5;
    cbOpTable[0xE6] = opcodes::CB_0xE6;
    cbOpTable[0xE7] = opcodes::CB_0xE7;
    cbOpTable[0xE8] = opcodes::CB_0xE8;
    cbOpTable[0xE9] = opcodes::CB_0xE9;
    cbOpTable[0xEA] = opcodes::CB_0xEA;
    cbOpTable[0xEB] = opcodes::CB_0xEB;
    cbOpTable[0xEC] = opcodes::CB_0xEC;
    cbOpTable[0xED] = opcodes::CB_0xED;
    cbOpTable[0xEE] = opcodes::CB_0xEE;
    cbOpTable[0xEF] = opcodes::CB_0xEF;

    cbOpTable[0xF0] = opcodes::CB_0xF0;
    cbOpTable[0xF1] = opcodes::CB_0xF1;
    cbOpTable[0xF2] = opcodes::CB_0xF2;
    cbOpTable[0xF3] = opcodes::CB_0xF3;
    cbOpTable[0xF4] = opcodes::CB_0xF4;
    cbOpTable[0xF5] = opcodes::CB_0xF5;
    cbOpTable[0xF6] = opcodes::CB_0xF6;
    cbOpTable[0xF7] = opcodes::CB_0xF7;
    cbOpTable[0xF8] = opcodes::CB_0xF8;
    cbOpTable[0xF9] = opcodes::CB_0xF9;
    cbOpTable[0xFA] = opcodes::CB_0xFA;
    cbOpTable[0xFB] = opcodes::CB_0xFB;
    cbOpTable[0xFC] = opcodes::CB_0xFC;
    cbOpTable[0xFD] = opcodes::CB_0xFD;
    cbOpTable[0xFE] = opcodes::CB_0xFE;
    cbOpTable[0xFF] = opcodes::CB_0xFF;
}

//Register table getters
reg16 &CPU::getTableReg16(uint8_t mask) {
    switch (mask) {
        case 0: return BC;
        case 1: return DE;
        case 2: return HL;
        case 3: return SP;
        default: return BC;
    }
}

CPU::R8Ref CPU::getTableReg8(uint8_t mask) {
    switch (mask) {
        case 0: return R8Ref::fromReg(*this, B());
        case 1: return R8Ref::fromReg(*this, C());
        case 2: return R8Ref::fromReg(*this, D());
        case 3: return R8Ref::fromReg(*this, E());
        case 4: return R8Ref::fromReg(*this, H());
        case 5: return R8Ref::fromReg(*this, L());
        case 6: return R8Ref::memHL(*this);          // [HL]
        default: return R8Ref::fromReg(*this, A());

    }
}

//Mnemonic
void CPU::OP_ld_r16_imm(uint8_t opcode) {
    uint8_t lo = fetch8();
    uint16_t imm16 = (fetch8() << 8) | lo;

    reg16& reg = getTableReg16((opcode >> 4) & 0x03);
    reg = imm16;
}


void CPU::OP_ld_r16mem_a(uint8_t opcode) {
    uint8_t a = A().get();

    // Special cases for (HL+) and (HL-)
    if (opcode == 0x22 || opcode == 0x32) {
        bus->write8(HL.get(), a);
        return;
    }

    // Regular cases: (BC) and (DE)
    uint16_t reg = getTableReg16((opcode >> 4) & 0x03).get();
    bus->write8(reg, a);
}

void CPU::OP_ld_a_r16mem(uint8_t opcode) {
    // Special cases for (HL+) and (HL-)
    if (opcode == 0x2A || opcode == 0x3A) {
        A().set(bus->read8(HL.get()));
        return;
    }

    // Regular cases: (BC) and (DE)
    uint16_t reg = getTableReg16((opcode >> 4) & 0x03).get();
    A().set(bus->read8(reg));
}

void CPU::OP_inc_r16(uint8_t opcode) {
    reg16& reg = getTableReg16((opcode >> 4) & 0x03);
    ++reg;
}

void CPU::OP_dec_r16(uint8_t opcode) {
    reg16& reg = getTableReg16((opcode >> 4) & 0x03);
    --reg;
}

void CPU::OP_add_HL_r16(uint8_t opcode) {
    const uint16_t hl = HL.get();
    const uint16_t rr = getTableReg16((opcode >> 4) & 0x03).get();
    const uint32_t sum = uint32_t(hl) + uint32_t(rr);

    set_flag_N(false);
    set_flag_H(((hl & 0x0FFF) + (rr & 0x0FFF)) > 0x0FFF);
    set_flag_C(sum > 0xFFFF);

    HL.set(static_cast<uint16_t>(sum));
}

void CPU::OP_inc_r8(uint8_t opcode) {
    R8Ref r = getTableReg8((opcode >> 3) & 0x07);
    uint8_t v = r.get();
    uint8_t res = static_cast<uint8_t>(v + 1);

    set_flag_Z(res == 0);
    set_flag_N(false);
    set_flag_H(((v & 0x0F) + 1) > 0x0F);

    r.set(res);
}

void CPU::OP_dec_r8(uint8_t opcode) {
    R8Ref r = getTableReg8((opcode >> 3) & 0x07);
    uint8_t v = r.get();
    uint8_t res = static_cast<uint8_t>(v - 1);

    set_flag_Z(res == 0);
    set_flag_N(true);
    set_flag_H((v & 0x0F) == 0x00);
    r.set(res);
}

void CPU::OP_ld_r8_imm(uint8_t opcode) {
    R8Ref r = getTableReg8((opcode >> 3) & 0x07);
    uint8_t imm8 = fetch8();
    r.set(imm8);
}

void CPU::OP_jr() {
    int8_t offset = static_cast<int8_t>(fetch8());
    PC.set(PC.get() + offset);
}

void CPU::OP_ld_r8_r8(uint8_t opcode) {
    uint8_t src_idx = opcode & 0b111;
    uint8_t dst_idx = (opcode >> 3) & 0b111;

    uint8_t value = getTableReg8(src_idx).get();
    getTableReg8(dst_idx).set(value);
}

void CPU::OP_add_a_r8(uint8_t opcode) {
    const uint8_t a  = A().get();
    const uint8_t b  = getTableReg8(opcode & 0x07).get();
    const uint16_t s = uint16_t(a) + uint16_t(b);
    const uint8_t  r = static_cast<uint8_t>(s);

    set_flag_Z(r == 0);
    set_flag_N(false);
    set_flag_H(((a & 0x0F) + (b & 0x0F)) > 0x0F);
    set_flag_C(s > 0xFF);

    A().set(r);
}

void CPU::OP_adc_a_r8(uint8_t opcode) {
    const uint8_t a   = A().get();
    const uint8_t b   = getTableReg8(opcode & 0x07).get();
    const uint8_t cin = get_flag_C() ? 1u : 0u;

    const uint16_t s = uint16_t(a) + uint16_t(b) + uint16_t(cin);
    const uint8_t  r = static_cast<uint8_t>(s);

    set_flag_Z(r == 0);
    set_flag_N(false);
    set_flag_H(((a & 0x0F) + (b & 0x0F) + cin) > 0x0F);
    set_flag_C(s > 0xFF);

    A().set(r);
}

void CPU::OP_sub_a_r8(uint8_t opcode) {
    const uint8_t a = A().get();
    const uint8_t b = getTableReg8(opcode & 0x07).get();

    const uint16_t d = uint16_t(a) - uint16_t(b);
    const uint8_t  r = static_cast<uint8_t>(d);

    set_flag_Z(r == 0);
    set_flag_N(true);
    set_flag_H((a & 0x0F) < (b & 0x0F));
    set_flag_C(a < b);

    A().set(r);
}

void CPU::OP_sbc_a_r8(uint8_t opcode) {
    const uint8_t a   = A().get();
    const uint8_t b   = getTableReg8(opcode & 0x07).get();
    const uint8_t cin = get_flag_C() ? 1u : 0u;

    const uint16_t d = uint16_t(a) - uint16_t(b) - uint16_t(cin);
    const uint8_t  r = static_cast<uint8_t>(d);

    set_flag_Z(r == 0);
    set_flag_N(true);
    set_flag_H((a & 0x0F) < ((b & 0x0F) + cin));
    set_flag_C(a < (uint16_t(b) + cin));

    A().set(r);
}

void CPU::OP_and_a_r8(uint8_t opcode) {
    const uint8_t a = A().get();
    const uint8_t b = getTableReg8(opcode & 0x07).get();
    const uint8_t r = static_cast<uint8_t>(a & b);

    A().set(r);
    set_flag_Z(r == 0);
    set_flag_N(false);
    set_flag_H(true);
    set_flag_C(false);
}

void CPU::OP_xor_a_r8(uint8_t opcode) {
    const uint8_t a = A().get();
    const uint8_t b = getTableReg8(opcode & 0x07).get();
    const uint8_t r = static_cast<uint8_t>(a ^ b);

    A().set(r);
    set_flag_Z(r == 0);
    set_flag_N(false);
    set_flag_H(false);
    set_flag_C(false);
}

void CPU::OP_or_a_r8(uint8_t opcode) {
    const uint8_t a = A().get();
    const uint8_t b = getTableReg8(opcode & 0x07).get();
    const uint8_t r = static_cast<uint8_t>(a | b);

    A().set(r);
    set_flag_Z(r == 0);
    set_flag_N(false);
    set_flag_H(false);
    set_flag_C(false);
}

void CPU::OP_cp_a_r8(uint8_t opcode) {
    const uint8_t a = A().get();
    const uint8_t b = getTableReg8(opcode & 0x07).get();
    const uint8_t r = static_cast<uint8_t>(a - b);

    set_flag_Z(r == 0);
    set_flag_N(true);
    set_flag_H((a & 0x0F) < (b & 0x0F));
    set_flag_C(a < b);
}

void CPU::OP_ret() {
    uint8_t lo = bus->read8(SP);
    SP++;
    uint8_t hi = bus->read8(SP);
    SP++;
    uint16_t newPC = (hi << 8) | lo;
    PC.set(newPC);
}

void CPU::OP_jp() {
    uint16_t imm16 = fetch16();
    PC.set(imm16);
}

void CPU::OP_call() {
    uint16_t imm16 = fetch16();
    SP--;
    bus->write8(SP, PC.get_high());
    SP--;
    bus->write8(SP, PC.get_low());
    PC.set(imm16);
}

void CPU::OP_rst(uint8_t opcode) {
    uint16_t vector = opcode & 0x38; // bits 3,4,5 encode vector (00h–38h)

    SP--;
    bus->write8(SP, PC.get_high());
    SP--;
    bus->write8(SP, PC.get_low());

    PC.set(vector);
}

void CPU::OP_pop(uint8_t opcode) {
    uint8_t lo = bus->read8(SP++);
    uint8_t hi = bus->read8(SP++);

    uint16_t val = (hi << 8) | lo;

    switch (opcode) {
        case 0xC1: // POP BC
            BC.set(val);
            break;

        case 0xD1: // POP DE
            DE.set(val);
            break;

        case 0xE1: // POP HL
            HL.set(val);
            break;

        case 0xF1: // POP AF
            AF.set(val & 0xFFF0); // lower nibble of F must be 0
            break;

        default:
            break;
    }
}

void CPU::OP_push(uint8_t opcode) {
    uint16_t val;

    switch (opcode) {
        case 0xC5: // PUSH BC
            val = BC.get();
            break;
        case 0xD5: // PUSH DE
            val = DE.get();
            break;
        case 0xE5: // PUSH HL
            val = HL.get();
            break;
        case 0xF5: // PUSH AF
            val = AF.get() & 0xFFF0;
            break;
        default:
            return;
    }
    SP--;
    bus->write8(SP, (val >> 8) & 0xFF);
    SP--;
    bus->write8(SP, val & 0xFF);
}

void CPU::OP_rlc(uint8_t opcode) {
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    uint8_t carry = (val & 0x80) >> 7;
    uint8_t result = (val << 1) | carry;

    set_flag_Z(result == 0);
    set_flag_N(false);
    set_flag_H(false);
    set_flag_C(carry != 0);

    reg.set(result);
}

void CPU::OP_rrc(uint8_t opcode) {
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    uint8_t carry = val & 0x01;
    uint8_t result = (val >> 1) | (carry << 7);

    set_flag_Z(result == 0);
    set_flag_N(false);
    set_flag_H(false);
    set_flag_C(carry != 0);

    reg.set(result);
}

void CPU::OP_rl(uint8_t opcode) {
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    uint8_t old_carry = get_flag_C() ? 1 : 0;
    uint8_t new_carry = (val & 0x80) >> 7;
    uint8_t result = (val << 1) | old_carry;

    set_flag_Z(result == 0);
    set_flag_N(false);
    set_flag_H(false);
    set_flag_C(new_carry != 0);

    reg.set(result);
}

void CPU::OP_rr(uint8_t opcode) {
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    uint8_t old_carry = get_flag_C() ? 1 : 0;
    uint8_t new_carry = val & 0x01;
    uint8_t result = (val >> 1) | (old_carry << 7);

    set_flag_Z(result == 0);
    set_flag_N(false);
    set_flag_H(false);
    set_flag_C(new_carry != 0);

    reg.set(result);
}

void CPU::OP_sla(uint8_t opcode) {
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    uint8_t carry = (val & 0x80) >> 7;
    uint8_t result = val << 1;

    set_flag_Z(result == 0);
    set_flag_N(false);
    set_flag_H(false);
    set_flag_C(carry != 0);

    reg.set(result);
}

void CPU::OP_sra(uint8_t opcode) {
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    uint8_t carry = val & 0x01;
    uint8_t msb = val & 0x80;
    uint8_t result = (val >> 1) | msb;

    set_flag_Z(result == 0);
    set_flag_N(false);
    set_flag_H(false);
    set_flag_C(carry != 0);

    reg.set(result);
}

void CPU::OP_srl(uint8_t opcode) {
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    uint8_t carry = val & 0x01;
    uint8_t result = val >> 1;

    set_flag_Z(result == 0);
    set_flag_N(false);
    set_flag_H(false);
    set_flag_C(carry != 0);

    reg.set(result);
}

void CPU::OP_swap(uint8_t opcode) {
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    uint8_t result = ((val & 0x0F) << 4) | ((val & 0xF0) >> 4);

    set_flag_Z(result == 0);
    set_flag_N(false);
    set_flag_H(false);
    set_flag_C(false);

    reg.set(result);
}

void CPU::OP_bit(uint8_t opcode) {
    uint8_t bit = (opcode >> 3) & 0b111;
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    bool bit_set = (val & (1 << bit)) != 0;

    set_flag_Z(!bit_set);
    set_flag_N(false);
    set_flag_H(true);
}

void CPU::OP_res(uint8_t opcode) {
    uint8_t bit = (opcode >> 3) & 0b111;
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    uint8_t result = val & ~(1 << bit);
    reg.set(result);
}

void CPU::OP_set(uint8_t opcode) {
    uint8_t bit = (opcode >> 3) & 0b111;
    R8Ref reg = getTableReg8(opcode & 0b111);
    uint8_t val = reg.get();

    uint8_t result = val | (1 << bit);
    reg.set(result);
}

void CPU::logState() {
    // Format the flags register properly
    uint8_t f = F().get();

    // Read the next 4 bytes at PC for PCMEM
    uint16_t pc = PC.get();
    uint8_t pcmem[4];
    for (int i = 0; i < 4; i++) {
        pcmem[i] = bus->read8(pc + i);
    }

    // Output in gameboy-doctor format
    std::cout << std::uppercase << std::setfill('0');
    std::cout << "A:" << std::setw(2) << std::hex << static_cast<int>(A().get())
              << " F:" << std::setw(2) << std::hex << static_cast<int>(f)
              << " B:" << std::setw(2) << std::hex << static_cast<int>(B().get())
              << " C:" << std::setw(2) << std::hex << static_cast<int>(C().get())
              << " D:" << std::setw(2) << std::hex << static_cast<int>(D().get())
              << " E:" << std::setw(2) << std::hex << static_cast<int>(E().get())
              << " H:" << std::setw(2) << std::hex << static_cast<int>(H().get())
              << " L:" << std::setw(2) << std::hex << static_cast<int>(L().get())
              << " SP:" << std::setw(4) << std::hex << static_cast<int>(SP.get())
              << " PC:" << std::setw(4) << std::hex << static_cast<int>(pc)
              << " PCMEM:"
              << std::setw(2) << std::hex << static_cast<int>(pcmem[0]) << ","
              << std::setw(2) << std::hex << static_cast<int>(pcmem[1]) << ","
              << std::setw(2) << std::hex << static_cast<int>(pcmem[2]) << ","
              << std::setw(2) << std::hex << static_cast<int>(pcmem[3])
              << std::dec << '\n';
}

inline uint8_t CPU::R8Ref::get() const {
    if (kind == Kind::Reg) {
        return reg->get();
    } else {
        // [HL]
        return cpu->bus->read8(cpu->HL.get());
    }
}
inline void CPU::R8Ref::set(uint8_t v) const {
    if (kind == Kind::Reg) {
        reg->set(v);
    } else {
        // [HL]
        cpu->bus->write8(cpu->HL.get(), v);
    }
}
