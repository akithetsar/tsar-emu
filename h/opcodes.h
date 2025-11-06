//
// Created by akith on 10/31/2025.
//
//
// Created by akith on 10/31/2025.
//

#ifndef GBEMULATOR_OPCODES_H
#define GBEMULATOR_OPCODES_H

#include <cstdint>
#include "CPU.h"
#include "metadata.hpp"

class opcodes {
public:
    // 0x00: NOP
    static int OP_0x00(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    // 0x01: LD BC,d16
    static int OP_0x01(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r16_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x02: LD (BC),A
    static inline int OP_0x02(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r16mem_a(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x03: INC BC
    static inline int OP_0x03(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x04: INC B
    static inline int OP_0x04(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x05: DEC B
    static inline int OP_0x05(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x06: LD B,d8
    static inline int OP_0x06(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x07: RLCA
    static inline int OP_0x07(CPU &cpu, uint8_t opcode) {
        cpu.set_flag_Z(false);
        cpu.set_flag_N(false);
        cpu.set_flag_H(false);
        cpu.set_flag_C(cpu.A().rotate_left());
        return cyclesNonCB(opcode);
    }

    // 0x08: LD (a16),SP
    static inline int OP_0x08(CPU &cpu, uint8_t opcode) {
        uint16_t imm = cpu.fetch16();
        cpu.bus->write8(imm, cpu.SP & 0xFF);
        cpu.bus->write8(imm + 1, cpu.SP >> 8);

        return cyclesNonCB(opcode);
    }

    // 0x09: ADD HL,BC
    static inline int OP_0x09(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_HL_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x0A: LD A,(BC)
    static inline int OP_0x0A(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_a_r16mem(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x0B: DEC BC
    static inline int OP_0x0B(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x0C: INC C
    static inline int OP_0x0C(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x0D: DEC C
    static inline int OP_0x0D(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x0E: LD C,d8
    static inline int OP_0x0E(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x0F: RRCA
    static inline int OP_0x0F(CPU &cpu, uint8_t opcode) {
        cpu.set_flag_Z(false);
        cpu.set_flag_N(false);
        cpu.set_flag_H(false);
        cpu.set_flag_C(cpu.A().rotate_right());
        return cyclesNonCB(opcode);
    }

    // 0x10: STOP
    static inline int OP_0x10(CPU &cpu, uint8_t opcode) {
//        cpu.fetch8();  // STOP consumes next byte
        return cyclesNonCB(opcode);
    }

    // 0x11: LD DE,d16
    static inline int OP_0x11(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r16_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x12: LD (DE),A
    static inline int OP_0x12(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r16mem_a(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x13: INC DE
    static inline int OP_0x13(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x14: INC D
    static inline int OP_0x14(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x15: DEC D
    static inline int OP_0x15(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x16: LD D,d8
    static inline int OP_0x16(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x17: RLA
    static inline int OP_0x17(CPU &cpu, uint8_t opcode) {
        bool oldC = cpu.get_flag_C();
        cpu.set_flag_Z(false);
        cpu.set_flag_N(false);
        cpu.set_flag_H(false);
        cpu.set_flag_C(cpu.A().rotate_left_through_carry(oldC));
        return cyclesNonCB(opcode);
    }

    // 0x18: JR r8
    static inline int OP_0x18(CPU &cpu, uint8_t opcode) {
        cpu.OP_jr();
        return cyclesNonCB(opcode);
    }

    // 0x19: ADD HL,DE
    static inline int OP_0x19(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_HL_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x1A: LD A,(DE)
    static inline int OP_0x1A(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_a_r16mem(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x1B: DEC DE
    static inline int OP_0x1B(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x1C: INC E
    static inline int OP_0x1C(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x1D: DEC E
    static inline int OP_0x1D(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x1E: LD E,d8
    static inline int OP_0x1E(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x1F: RRA
    static inline int OP_0x1F(CPU &cpu, uint8_t opcode) {
        bool oldC = cpu.get_flag_C();
        cpu.set_flag_Z(false);
        cpu.set_flag_N(false);
        cpu.set_flag_H(false);
        cpu.set_flag_C(cpu.A().rotate_right_through_carry(oldC));
        return cyclesNonCB(opcode);
    }

    // 0x20: JR NZ,r8
    static inline int OP_0x20(CPU &cpu, uint8_t opcode) {
        bool take;
        take = !cpu.get_flag_Z();
        if (take) {
            cpu.OP_jr();
        } else {
            cpu.fetch8(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    // 0x21: LD HL,d16
    static inline int OP_0x21(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r16_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x22: LD (HL+),A
    static inline int OP_0x22(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r16mem_a(opcode);
        ++cpu.HL;
        return cyclesNonCB(opcode);
    }

    // 0x23: INC HL
    static inline int OP_0x23(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x24: INC H
    static inline int OP_0x24(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x25: DEC H
    static inline int OP_0x25(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x26: LD H,d8
    static inline int OP_0x26(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x27: DAA
    static inline int OP_0x27(CPU & cpu, uint8_t opcode) {
        uint8_t a = cpu.A().get();

        if (!cpu.get_flag_N()) {  // After addition
            if (cpu.get_flag_C() || a > 0x99) {
                a += 0x60;
                cpu.set_flag_C(true);
            }
            if (cpu.get_flag_H() || (a & 0x0F) > 0x09) {
                a += 0x06;
            }
        } else {  // After subtraction
            if (cpu.get_flag_C()) {
                a -= 0x60;
            }
            if (cpu.get_flag_H()) {
                a -= 0x06;
            }
        }

        cpu.A().set(a);
        cpu.set_flag_Z(a == 0);
        cpu.set_flag_H(false);

        return cyclesNonCB(opcode);
    }

    // 0x28: JR Z,r8
    static inline int OP_0x28(CPU &cpu, uint8_t opcode) {
        bool take = cpu.get_flag_Z();
        if (take) {
            cpu.OP_jr();
        } else {
            cpu.fetch8(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    // 0x29: ADD HL,HL
    static inline int OP_0x29(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_HL_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x2A: LD A,(HL+)
    static inline int OP_0x2A(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_a_r16mem(opcode);
        ++cpu.HL;
        return cyclesNonCB(opcode);
    }

    // 0x2B: DEC HL
    static inline int OP_0x2B(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x2C: INC L
    static inline int OP_0x2C(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x2D: DEC L
    static inline int OP_0x2D(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x2E: LD L,d8
    static inline int OP_0x2E(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x2F: CPL
    static inline int OP_0x2F(CPU &cpu, uint8_t opcode) {
        cpu.A() = cpu.A().get() ^ 0xFF;
        cpu.set_flag_N(true);
        cpu.set_flag_H(true);
        return cyclesNonCB(opcode);
    }

    // 0x30: JR NC,r8
    static inline int OP_0x30(CPU &cpu, uint8_t opcode) {
        bool take = !cpu.get_flag_C();
        if (take) {
            cpu.OP_jr();
        } else {
            cpu.fetch8(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    // 0x31: LD SP,d16
    static inline int OP_0x31(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r16_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x32: LD (HL-),A
    static inline int OP_0x32(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r16mem_a(opcode);
        --cpu.HL;
        return cyclesNonCB(opcode);
    }

    // 0x33: INC SP
    static inline int OP_0x33(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x34: INC (HL)
    static inline int OP_0x34(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x35: DEC (HL)
    static inline int OP_0x35(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x36: LD (HL),d8
    static inline int OP_0x36(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x37: SCF
    static inline int OP_0x37(CPU &cpu, uint8_t opcode) {
        cpu.set_flag_H(false);
        cpu.set_flag_N(false);
        cpu.set_flag_C(true);
        return cyclesNonCB(opcode);
    }

    // 0x38: JR C,r8
    static inline int OP_0x38(CPU &cpu, uint8_t opcode) {
        bool take = cpu.get_flag_C();
        if (take) {
            cpu.OP_jr();
        } else {
            cpu.fetch8(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    // 0x39: ADD HL,SP
    static inline int OP_0x39(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_HL_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x3A: LD A,(HL-)
    static inline int OP_0x3A(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_a_r16mem(opcode);
        --cpu.HL;
        return cyclesNonCB(opcode);
    }

    // 0x3B: DEC SP
    static inline int OP_0x3B(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r16(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x3C: INC A
    static inline int OP_0x3C(CPU &cpu, uint8_t opcode) {
        cpu.OP_inc_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x3D: DEC A
    static inline int OP_0x3D(CPU &cpu, uint8_t opcode) {
        cpu.OP_dec_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x3E: LD A,d8
    static inline int OP_0x3E(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_imm(opcode);
        return cyclesNonCB(opcode);
    }

    // 0x3F: CCF
    static inline int OP_0x3F(CPU &cpu, uint8_t opcode) {
        cpu.set_flag_N(false);
        cpu.set_flag_H(false);
        cpu.set_flag_C(!cpu.get_flag_C());
        return cyclesNonCB(opcode);
    }

    // 0x40..0x7F
    // LD r, r' (0x40–0x7F) — except 0x76 (HALT)
    static inline int OP_0x40(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x41(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x42(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x43(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x44(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x45(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x46(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x47(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x48(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x49(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x4A(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x4B(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x4C(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x4D(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x4E(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x4F(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x50(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x51(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x52(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x53(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x54(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x55(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x56(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x57(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x58(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x59(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x5A(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x5B(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x5C(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x5D(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x5E(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x5F(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x60(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x61(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x62(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x63(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x64(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x65(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x66(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x67(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x68(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x69(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x6A(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x6B(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x6C(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x6D(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x6E(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x6F(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x70(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x71(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x72(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x73(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x74(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x75(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    // HALT (0x76)
    static inline int OP_0x76(CPU &, uint8_t opcode) { return cyclesNonCB(opcode);  }

    static inline int OP_0x77(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x78(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x79(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x7A(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x7B(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x7C(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x7D(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x7E(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0x7F(CPU &cpu, uint8_t opcode) {
        cpu.OP_ld_r8_r8(opcode);
        return cyclesNonCB(opcode);
    }


// 0x80..0x8F: ADD/ADC A, r8
    static inline int OP_0x80(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADD A,B
    static inline int OP_0x81(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADD A,C
    static inline int OP_0x82(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADD A,D
    static inline int OP_0x83(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADD A,E
    static inline int OP_0x84(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADD A,H
    static inline int OP_0x85(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADD A,L
    static inline int OP_0x86(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADD A,(HL)
    static inline int OP_0x87(CPU &cpu, uint8_t opcode) {
        cpu.OP_add_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADD A,A

    static inline int OP_0x88(CPU &cpu, uint8_t opcode) {
        cpu.OP_adc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADC A,B
    static inline int OP_0x89(CPU &cpu, uint8_t opcode) {
        cpu.OP_adc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADC A,C
    static inline int OP_0x8A(CPU &cpu, uint8_t opcode) {
        cpu.OP_adc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADC A,D
    static inline int OP_0x8B(CPU &cpu, uint8_t opcode) {
        cpu.OP_adc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADC A,E
    static inline int OP_0x8C(CPU &cpu, uint8_t opcode) {
        cpu.OP_adc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADC A,H
    static inline int OP_0x8D(CPU &cpu, uint8_t opcode) {
        cpu.OP_adc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADC A,L
    static inline int OP_0x8E(CPU &cpu, uint8_t opcode) {
        cpu.OP_adc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADC A,(HL)
    static inline int OP_0x8F(CPU &cpu, uint8_t opcode) {
        cpu.OP_adc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // ADC A,A

// 0x90..0x9F: SUB/SBC A, r8
    static inline int OP_0x90(CPU &cpu, uint8_t opcode) {
        cpu.OP_sub_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SUB B
    static inline int OP_0x91(CPU &cpu, uint8_t opcode) {
        cpu.OP_sub_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SUB C
    static inline int OP_0x92(CPU &cpu, uint8_t opcode) {
        cpu.OP_sub_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SUB D
    static inline int OP_0x93(CPU &cpu, uint8_t opcode) {
        cpu.OP_sub_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SUB E
    static inline int OP_0x94(CPU &cpu, uint8_t opcode) {
        cpu.OP_sub_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SUB H
    static inline int OP_0x95(CPU &cpu, uint8_t opcode) {
        cpu.OP_sub_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SUB L
    static inline int OP_0x96(CPU &cpu, uint8_t opcode) {
        cpu.OP_sub_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SUB (HL)
    static inline int OP_0x97(CPU &cpu, uint8_t opcode) {
        cpu.OP_sub_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SUB A

    static inline int OP_0x98(CPU &cpu, uint8_t opcode) {
        cpu.OP_sbc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SBC B
    static inline int OP_0x99(CPU &cpu, uint8_t opcode) {
        cpu.OP_sbc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SBC C
    static inline int OP_0x9A(CPU &cpu, uint8_t opcode) {
        cpu.OP_sbc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SBC D
    static inline int OP_0x9B(CPU &cpu, uint8_t opcode) {
        cpu.OP_sbc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SBC E
    static inline int OP_0x9C(CPU &cpu, uint8_t opcode) {
        cpu.OP_sbc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SBC H
    static inline int OP_0x9D(CPU &cpu, uint8_t opcode) {
        cpu.OP_sbc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SBC L
    static inline int OP_0x9E(CPU &cpu, uint8_t opcode) {
        cpu.OP_sbc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SBC (HL)
    static inline int OP_0x9F(CPU &cpu, uint8_t opcode) {
        cpu.OP_sbc_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // SBC A

// 0xA0..0xAF: AND/XOR A, r8
    static inline int OP_0xA0(CPU &cpu, uint8_t opcode) {
        cpu.OP_and_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // AND B
    static inline int OP_0xA1(CPU &cpu, uint8_t opcode) {
        cpu.OP_and_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // AND C
    static inline int OP_0xA2(CPU &cpu, uint8_t opcode) {
        cpu.OP_and_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // AND D
    static inline int OP_0xA3(CPU &cpu, uint8_t opcode) {
        cpu.OP_and_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // AND E
    static inline int OP_0xA4(CPU &cpu, uint8_t opcode) {
        cpu.OP_and_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // AND H
    static inline int OP_0xA5(CPU &cpu, uint8_t opcode) {
        cpu.OP_and_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // AND L
    static inline int OP_0xA6(CPU &cpu, uint8_t opcode) {
        cpu.OP_and_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // AND (HL)
    static inline int OP_0xA7(CPU &cpu, uint8_t opcode) {
        cpu.OP_and_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // AND A

    static inline int OP_0xA8(CPU &cpu, uint8_t opcode) {
        cpu.OP_xor_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // XOR B
    static inline int OP_0xA9(CPU &cpu, uint8_t opcode) {
        cpu.OP_xor_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // XOR C
    static inline int OP_0xAA(CPU &cpu, uint8_t opcode) {
        cpu.OP_xor_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // XOR D
    static inline int OP_0xAB(CPU &cpu, uint8_t opcode) {
        cpu.OP_xor_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // XOR E
    static inline int OP_0xAC(CPU &cpu, uint8_t opcode) {
        cpu.OP_xor_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // XOR H
    static inline int OP_0xAD(CPU &cpu, uint8_t opcode) {
        cpu.OP_xor_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // XOR L
    static inline int OP_0xAE(CPU &cpu, uint8_t opcode) {
        cpu.OP_xor_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // XOR (HL)
    static inline int OP_0xAF(CPU &cpu, uint8_t opcode) {
        cpu.OP_xor_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // XOR A

// 0xB0..0xBF: OR/CP A, r8
    static inline int OP_0xB0(CPU &cpu, uint8_t opcode) {
        cpu.OP_or_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // OR B
    static inline int OP_0xB1(CPU &cpu, uint8_t opcode) {
        cpu.OP_or_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // OR C
    static inline int OP_0xB2(CPU &cpu, uint8_t opcode) {
        cpu.OP_or_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // OR D
    static inline int OP_0xB3(CPU &cpu, uint8_t opcode) {
        cpu.OP_or_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // OR E
    static inline int OP_0xB4(CPU &cpu, uint8_t opcode) {
        cpu.OP_or_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // OR H
    static inline int OP_0xB5(CPU &cpu, uint8_t opcode) {
        cpu.OP_or_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // OR L
    static inline int OP_0xB6(CPU &cpu, uint8_t opcode) {
        cpu.OP_or_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // OR (HL)
    static inline int OP_0xB7(CPU &cpu, uint8_t opcode) {
        cpu.OP_or_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // OR A

    static inline int OP_0xB8(CPU &cpu, uint8_t opcode) {
        cpu.OP_cp_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // CP B
    static inline int OP_0xB9(CPU &cpu, uint8_t opcode) {
        cpu.OP_cp_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // CP C
    static inline int OP_0xBA(CPU &cpu, uint8_t opcode) {
        cpu.OP_cp_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // CP D
    static inline int OP_0xBB(CPU &cpu, uint8_t opcode) {
        cpu.OP_cp_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // CP E
    static inline int OP_0xBC(CPU &cpu, uint8_t opcode) {
        cpu.OP_cp_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // CP H
    static inline int OP_0xBD(CPU &cpu, uint8_t opcode) {
        cpu.OP_cp_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // CP L
    static inline int OP_0xBE(CPU &cpu, uint8_t opcode) {
        cpu.OP_cp_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // CP (HL)
    static inline int OP_0xBF(CPU &cpu, uint8_t opcode) {
        cpu.OP_cp_a_r8(opcode);
        return cyclesNonCB(opcode);
    } // CP A

    // 0xC0..0xCF
    //RET NZ
    static inline int OP_0xC0(CPU &cpu, uint8_t opcode) {
        bool take = !cpu.get_flag_Z();
        if (take) {
            cpu.OP_ret();
        }

        return cyclesNonCB(opcode, take);
    }

    //POP BC
    static inline int OP_0xC1(CPU &cpu, uint8_t opcode) {
        cpu.OP_pop(opcode);
        return cyclesNonCB(opcode);
    }

    //JP NZ, a16
    static inline int OP_0xC2(CPU &cpu, uint8_t opcode) {
        bool take = !cpu.get_flag_Z();
        if (take) {
            cpu.OP_jp();
        } else {
            cpu.fetch16(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    //JP a16
    static inline int OP_0xC3(CPU &cpu, uint8_t opcode) {
        cpu.OP_jp();
        return cyclesNonCB(opcode);
    }

    //CALL NZ, a16
    static inline int OP_0xC4(CPU &cpu, uint8_t opcode) {
        bool take = !cpu.get_flag_Z();
        if (take) {
            cpu.OP_call();
        } else {
            cpu.fetch16(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    //PUSH BC
    static inline int OP_0xC5(CPU &cpu, uint8_t opcode) {
        cpu.OP_push(opcode);
        return cyclesNonCB(opcode);
    }

    //ADD A, n8
    static inline int OP_0xC6(CPU &cpu, uint8_t opcode) {
        const uint8_t a = cpu.A().get();
        const uint8_t b = cpu.fetch8();
        const uint16_t s = uint16_t(a) + uint16_t(b);
        const uint8_t r = static_cast<uint8_t>(s);

        cpu.set_flag_Z(r == 0);
        cpu.set_flag_N(false);
        cpu.set_flag_H(((a & 0x0F) + (b & 0x0F)) > 0x0F);
        cpu.set_flag_C(s > 0xFF);

        cpu.A().set(r);
        return cyclesNonCB(opcode);
    }

    //RST 00h
    static inline int OP_0xC7(CPU &cpu, uint8_t opcode) {
        cpu.OP_rst(opcode);
        return cyclesNonCB(opcode);
    }

    //RET Z
    static inline int OP_0xC8(CPU &cpu, uint8_t opcode) {
        bool take = cpu.get_flag_Z();
        if (take) {
            cpu.OP_ret();
        }
        return cyclesNonCB(opcode, take);
    }

    //RET
    static inline int OP_0xC9(CPU &cpu, uint8_t opcode) {
        cpu.OP_ret();
        return cyclesNonCB(opcode);
    }

    //JP Z, a16
    static inline int OP_0xCA(CPU &cpu, uint8_t opcode) {
        bool take = cpu.get_flag_Z();
        if (take) {
            cpu.OP_jp();
        } else {
            cpu.fetch16(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    //PREFIX
    static inline int OP_0xCB(CPU &, uint8_t) { return 0; }

    //CALL Z
    static inline int OP_0xCC(CPU &cpu, uint8_t opcode) {
        bool take = cpu.get_flag_Z();
        if (take) {
            cpu.OP_call();
        } else {
            cpu.fetch16(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    //CALL a16
    static inline int OP_0xCD(CPU &cpu, uint8_t opcode) {
        cpu.OP_call();
        return cyclesNonCB(opcode);
    }

    //ADC A, n8
    static inline int OP_0xCE(CPU &cpu, uint8_t opcode) {
        const uint8_t a = cpu.A().get();
        const uint8_t b = cpu.fetch8();
        const uint8_t cin = cpu.get_flag_C() ? 1u : 0u;

        const uint16_t s = uint16_t(a) + uint16_t(b) + uint16_t(cin);
        const uint8_t r = static_cast<uint8_t>(s);

        cpu.set_flag_Z(r == 0);
        cpu.set_flag_N(false);
        cpu.set_flag_H(((a & 0x0F) + (b & 0x0F) + cin) > 0x0F);
        cpu.set_flag_C(s > 0xFF);

        cpu.A().set(r);
        return cyclesNonCB(opcode);
    }

    //RST 08h
    static inline int OP_0xCF(CPU &cpu, uint8_t opcode) {
        cpu.OP_rst(opcode);
        return cyclesNonCB(opcode);
    }

    // 0xD0..0xDF
    //RET NC
    static inline int OP_0xD0(CPU &cpu, uint8_t opcode) {
        bool take = !cpu.get_flag_C();
        if (take) {
            cpu.OP_ret();
        }
        return cyclesNonCB(opcode, take);
    }

    //POP DE
    static inline int OP_0xD1(CPU &cpu, uint8_t opcode) {
        cpu.OP_pop(opcode);
        return cyclesNonCB(opcode);
    }

    //JP NC, a16
    static inline int OP_0xD2(CPU &cpu, uint8_t opcode) {
        bool take = !cpu.get_flag_C();
        if (take) {
            cpu.OP_jp();
        } else {
            cpu.fetch16(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    //UNUSED
    static inline int OP_0xD3(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //CALL NC
    static inline int OP_0xD4(CPU &cpu, uint8_t opcode) {
        bool take = !cpu.get_flag_C();
        if (take) {
            cpu.OP_call();
        } else {
            cpu.fetch16(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    //PUSH DE
    static inline int OP_0xD5(CPU &cpu, uint8_t opcode) {
        cpu.OP_push(opcode);
        return cyclesNonCB(opcode);
    }

    // SUB A, n8
    static inline int OP_0xD6(CPU &cpu, uint8_t opcode) {
        const uint8_t a = cpu.A().get();
        const uint8_t b = cpu.fetch8();

        const uint16_t d = uint16_t(a) - uint16_t(b);
        const uint8_t r = static_cast<uint8_t>(d);

        cpu.set_flag_Z(r == 0);
        cpu.set_flag_N(true);
        cpu.set_flag_H((a & 0x0F) < (b & 0x0F));
        cpu.set_flag_C(a < b);

        cpu.A().set(r);
        return cyclesNonCB(opcode);
    }

    //RST 10h
    static inline int OP_0xD7(CPU &cpu, uint8_t opcode) {
        cpu.OP_rst(opcode);
        return cyclesNonCB(opcode);
    }

    //RET C
    static inline int OP_0xD8(CPU &cpu, uint8_t opcode) {
        bool take = cpu.get_flag_C();
        if (take) {
            cpu.OP_ret();
        }
        return cyclesNonCB(opcode, take);
    }

    //RETI
    static inline int OP_0xD9(CPU &cpu, uint8_t opcode) {
        //todo: enable interrupt
        cpu.OP_ret();
        return cyclesNonCB(opcode);
    }

    //JP C, a16
    static inline int OP_0xDA(CPU &cpu, uint8_t opcode) {
        bool take = cpu.get_flag_C();
        if (take) {
            cpu.OP_jp();
        } else {
            cpu.fetch16(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    //UNUSED
    static inline int OP_0xDB(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //CALL C
    static inline int OP_0xDC(CPU &cpu, uint8_t opcode) {
        bool take = cpu.get_flag_C();
        if (take) {
            cpu.OP_call();
        } else {
            cpu.fetch16(); // consume offset;
        }
        return cyclesNonCB(opcode, take);
    }

    //UNUSED
    static inline int OP_0xDD(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //SBC A, n8
    static inline int OP_0xDE(CPU &cpu, uint8_t opcode) {
        const uint8_t a = cpu.A().get();
        const uint8_t b = cpu.fetch8();
        const uint8_t cin = cpu.get_flag_C() ? 1u : 0u;

        const uint16_t d = uint16_t(a) - uint16_t(b) - uint16_t(cin);
        const uint8_t r = static_cast<uint8_t>(d);

        cpu.set_flag_Z(r == 0);
        cpu.set_flag_N(true);
        cpu.set_flag_H((a & 0x0F) < ((b & 0x0F) + cin));
        cpu.set_flag_C(a < (uint16_t(b) + cin));

        cpu.A().set(r);
        return cyclesNonCB(opcode);

    }

    //RST 18h
    static inline int OP_0xDF(CPU &cpu, uint8_t opcode) {
        cpu.OP_rst(opcode);
        return cyclesNonCB(opcode);
    }

    // 0xE0..0xEF
    //LDH [a8], A
    static inline int OP_0xE0(CPU &cpu, uint8_t opcode) {
        uint8_t offset = cpu.fetch8();
        cpu.bus->write8(0xFF00u + offset, cpu.A());
        return cyclesNonCB(opcode);
    }

    //POP HL
    static inline int OP_0xE1(CPU &cpu, uint8_t opcode) {
        cpu.OP_pop(opcode);
        return cyclesNonCB(opcode);
    }

    //LDH [C], A
    static inline int OP_0xE2(CPU &cpu, uint8_t opcode) {
        cpu.bus->write8(0xFF00u + static_cast<uint16_t>(cpu.C()), cpu.A());
        return cyclesNonCB(opcode);
    }

    //UNUSED
    static inline int OP_0xE3(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //UNUSED
    static inline int OP_0xE4(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //PUSH HL
    static inline int OP_0xE5(CPU &cpu, uint8_t opcode) {
        cpu.OP_push(opcode);
        return cyclesNonCB(opcode);
    }

    //AND A, n8
    static inline int OP_0xE6(CPU &cpu, uint8_t opcode) {
        const uint8_t a = cpu.A().get();
        const uint8_t b = cpu.fetch8();
        const uint8_t r = static_cast<uint8_t>(a & b);

        cpu.A().set(r);
        cpu.set_flag_Z(r == 0);
        cpu.set_flag_N(false);
        cpu.set_flag_H(true);
        cpu.set_flag_C(false);
        return cyclesNonCB(opcode);
    }

    //RST 20h
    static inline int OP_0xE7(CPU &cpu, uint8_t opcode) {
        cpu.OP_rst(opcode);
        return cyclesNonCB(opcode);
    }

    //ADD SP, e8
    static inline int OP_0xE8(CPU &cpu, uint8_t opcode) {
        int8_t imm8 = static_cast<int8_t>(cpu.fetch8());
        uint16_t sp = cpu.SP;

        uint16_t result = static_cast<uint16_t>(sp + imm8);

        cpu.set_flag_Z(false);
        cpu.set_flag_N(false);
        cpu.set_flag_H(((sp ^ imm8 ^ result) & 0x10) != 0);
        cpu.set_flag_C(((sp ^ imm8 ^ result) & 0x100) != 0);

        cpu.SP = result;

        return cyclesNonCB(opcode);
    }

    //JP HL
    static inline int OP_0xE9(CPU &cpu, uint8_t opcode) {
        cpu.PC.set(cpu.HL);
        return cyclesNonCB(opcode);
    }

    //LD [a16], A
    static inline int OP_0xEA(CPU &cpu, uint8_t opcode) {
        uint16_t addr = cpu.fetch16();
        cpu.bus->write8(addr, cpu.A());
        return cyclesNonCB(opcode);
    }

    //UNUSED
    static inline int OP_0xEB(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //UNUSED
    static inline int OP_0xEC(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //UNUSED
    static inline int OP_0xED(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //XOR A, n8
    static inline int OP_0xEE(CPU &cpu, uint8_t opcode) {
        const uint8_t a = cpu.A().get();
        const uint8_t b = cpu.fetch8();
        const uint8_t r = static_cast<uint8_t>(a ^ b);

        cpu.A().set(r);
        cpu.set_flag_Z(r == 0);
        cpu.set_flag_N(false);
        cpu.set_flag_H(false);
        cpu.set_flag_C(false);
        return cyclesNonCB(opcode);
    }

    //RST 28h
    static inline int OP_0xEF(CPU &cpu, uint8_t opcode) {
        cpu.OP_rst(opcode);
        return cyclesNonCB(opcode);
    }

    // 0xF0..0xFF
    //LDH A, [a8]
    static inline int OP_0xF0(CPU &cpu, uint8_t opcode) {
        uint8_t offset = cpu.fetch8();
        cpu.A() = cpu.bus->read8(0xFF00u + offset);
        return cyclesNonCB(opcode);
    }

    //POP AF
    static inline int OP_0xF1(CPU &cpu, uint8_t opcode) {
        cpu.OP_pop(opcode);
        return cyclesNonCB(opcode);
    }

    //LDH A, [C]
    static inline int OP_0xF2(CPU &cpu, uint8_t opcode) {
        cpu.A() = cpu.bus->read8(0xFF00u + static_cast<uint16_t>(cpu.C()));
        return cyclesNonCB(opcode);
    }

    static inline int OP_0xF3(CPU &, uint8_t opcode) {
        //todo: disable interrupts ime
        return cyclesNonCB(opcode);
    }

    //UNUSED
    static inline int OP_0xF4(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //PUSH AF
    static inline int OP_0xF5(CPU &cpu, uint8_t opcode) {
        cpu.OP_push(opcode);
        return cyclesNonCB(opcode);
    }

    //OR A, n8
    static inline int OP_0xF6(CPU &cpu, uint8_t opcode) {
        const uint8_t a = cpu.A().get();
        const uint8_t b = cpu.fetch8();
        const uint8_t r = static_cast<uint8_t>(a | b);

        cpu.A().set(r);
        cpu.set_flag_Z(r == 0);
        cpu.set_flag_N(false);
        cpu.set_flag_H(false);
        cpu.set_flag_C(false);
        return cyclesNonCB(opcode);
    }

    //RST 30h
    static inline int OP_0xF7(CPU &cpu, uint8_t opcode) {
        cpu.OP_rst(opcode);
        return cyclesNonCB(opcode);
    }

    //LD HL, SP+e8
    static inline int OP_0xF8(CPU &cpu, uint8_t opcode) {
        int8_t imm8 = static_cast<int8_t>(cpu.fetch8());
        uint16_t sp = cpu.SP;
        uint16_t result = static_cast<uint16_t>(sp + imm8);

        cpu.HL.set(result);

        cpu.set_flag_Z(false);
        cpu.set_flag_N(false);
        cpu.set_flag_H(((sp ^ imm8 ^ result) & 0x10) != 0);
        cpu.set_flag_C(((sp ^ imm8 ^ result) & 0x100) != 0);

        return cyclesNonCB(opcode);
    }

    //LD SP, HL
    static inline int OP_0xF9(CPU &cpu, uint8_t opcode) {
        cpu.SP = cpu.HL.get();
        return cyclesNonCB(opcode);
    }

    //LD A, [a16]
    static inline int OP_0xFA(CPU &cpu, uint8_t opcode) {
        uint16_t addr = cpu.fetch16();
        cpu.A() = cpu.bus->read8(addr);
        return cyclesNonCB(opcode);
    }

    static inline int OP_0xFB(CPU &, uint8_t opcode) {
        //todo: enable interrupts ime
        return cyclesNonCB(opcode);
    }

    //UNUSED
    static inline int OP_0xFC(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //UNUSED
    static inline int OP_0xFD(CPU &, uint8_t opcode) { return cyclesNonCB(opcode); }

    //CP A, n8
    static inline int OP_0xFE(CPU &cpu, uint8_t opcode) {
        const uint8_t a = cpu.A().get();
        const uint8_t b = cpu.fetch8();
        const uint8_t r = static_cast<uint8_t>(a - b);

        cpu.set_flag_Z(r == 0);
        cpu.set_flag_N(true);
        cpu.set_flag_H((a & 0x0F) < (b & 0x0F));
        cpu.set_flag_C(a < b);
        return cyclesNonCB(opcode);
    }

    //RST 38h
    static inline int OP_0xFF(CPU &cpu, uint8_t opcode) {
        cpu.OP_rst(opcode);
        return cyclesNonCB(opcode);
    }

// CB-prefixed opcodes (0xCB 0x00 - 0xCB 0xFF)
// Add these to your opcodes class

// 0xCB 0x00..0x0F - RLC (0x00-0x07), RRC (0x08-0x0F)
    static inline int CB_0x00(CPU &cpu, uint8_t opcode) {
        cpu.OP_rlc(opcode);
        return cyclesCB(opcode);
    } // RLC B
    static inline int CB_0x01(CPU &cpu, uint8_t opcode) {
        cpu.OP_rlc(opcode);
        return cyclesCB(opcode);
    } // RLC C
    static inline int CB_0x02(CPU &cpu, uint8_t opcode) {
        cpu.OP_rlc(opcode);
        return cyclesCB(opcode);
    } // RLC D
    static inline int CB_0x03(CPU &cpu, uint8_t opcode) {
        cpu.OP_rlc(opcode);
        return cyclesCB(opcode);
    } // RLC E
    static inline int CB_0x04(CPU &cpu, uint8_t opcode) {
        cpu.OP_rlc(opcode);
        return cyclesCB(opcode);
    } // RLC H
    static inline int CB_0x05(CPU &cpu, uint8_t opcode) {
        cpu.OP_rlc(opcode);
        return cyclesCB(opcode);
    } // RLC L
    static inline int CB_0x06(CPU &cpu, uint8_t opcode) {
        cpu.OP_rlc(opcode);
        return cyclesCB(opcode);
    } // RLC (HL)
    static inline int CB_0x07(CPU &cpu, uint8_t opcode) {
        cpu.OP_rlc(opcode);
        return cyclesCB(opcode);
    } // RLC A
    static inline int CB_0x08(CPU &cpu, uint8_t opcode) {
        cpu.OP_rrc(opcode);
        return cyclesCB(opcode);
    } // RRC B
    static inline int CB_0x09(CPU &cpu, uint8_t opcode) {
        cpu.OP_rrc(opcode);
        return cyclesCB(opcode);
    } // RRC C
    static inline int CB_0x0A(CPU &cpu, uint8_t opcode) {
        cpu.OP_rrc(opcode);
        return cyclesCB(opcode);
    } // RRC D
    static inline int CB_0x0B(CPU &cpu, uint8_t opcode) {
        cpu.OP_rrc(opcode);
        return cyclesCB(opcode);
    } // RRC E
    static inline int CB_0x0C(CPU &cpu, uint8_t opcode) {
        cpu.OP_rrc(opcode);
        return cyclesCB(opcode);
    } // RRC H
    static inline int CB_0x0D(CPU &cpu, uint8_t opcode) {
        cpu.OP_rrc(opcode);
        return cyclesCB(opcode);
    } // RRC L
    static inline int CB_0x0E(CPU &cpu, uint8_t opcode) {
        cpu.OP_rrc(opcode);
        return cyclesCB(opcode);
    } // RRC (HL)
    static inline int CB_0x0F(CPU &cpu, uint8_t opcode) {
        cpu.OP_rrc(opcode);
        return cyclesCB(opcode);
    } // RRC A

// 0xCB 0x10..0x1F - RL (0x10-0x17), RR (0x18-0x1F)
    static inline int CB_0x10(CPU &cpu, uint8_t opcode) {
        cpu.OP_rl(opcode);
        return cyclesCB(opcode);
    } // RL B
    static inline int CB_0x11(CPU &cpu, uint8_t opcode) {
        cpu.OP_rl(opcode);
        return cyclesCB(opcode);
    } // RL C
    static inline int CB_0x12(CPU &cpu, uint8_t opcode) {
        cpu.OP_rl(opcode);
        return cyclesCB(opcode);
    } // RL D
    static inline int CB_0x13(CPU &cpu, uint8_t opcode) {
        cpu.OP_rl(opcode);
        return cyclesCB(opcode);
    } // RL E
    static inline int CB_0x14(CPU &cpu, uint8_t opcode) {
        cpu.OP_rl(opcode);
        return cyclesCB(opcode);
    } // RL H
    static inline int CB_0x15(CPU &cpu, uint8_t opcode) {
        cpu.OP_rl(opcode);
        return cyclesCB(opcode);
    } // RL L
    static inline int CB_0x16(CPU &cpu, uint8_t opcode) {
        cpu.OP_rl(opcode);
        return cyclesCB(opcode);
    } // RL (HL)
    static inline int CB_0x17(CPU &cpu, uint8_t opcode) {
        cpu.OP_rl(opcode);
        return cyclesCB(opcode);
    } // RL A
    static inline int CB_0x18(CPU &cpu, uint8_t opcode) {
        cpu.OP_rr(opcode);
        return cyclesCB(opcode);
    } // RR B
    static inline int CB_0x19(CPU &cpu, uint8_t opcode) {
        cpu.OP_rr(opcode);
        return cyclesCB(opcode);
    } // RR C
    static inline int CB_0x1A(CPU &cpu, uint8_t opcode) {
        cpu.OP_rr(opcode);
        return cyclesCB(opcode);
    } // RR D
    static inline int CB_0x1B(CPU &cpu, uint8_t opcode) {
        cpu.OP_rr(opcode);
        return cyclesCB(opcode);
    } // RR E
    static inline int CB_0x1C(CPU &cpu, uint8_t opcode) {
        cpu.OP_rr(opcode);
        return cyclesCB(opcode);
    } // RR H
    static inline int CB_0x1D(CPU &cpu, uint8_t opcode) {
        cpu.OP_rr(opcode);
        return cyclesCB(opcode);
    } // RR L
    static inline int CB_0x1E(CPU &cpu, uint8_t opcode) {
        cpu.OP_rr(opcode);
        return cyclesCB(opcode);
    } // RR (HL)
    static inline int CB_0x1F(CPU &cpu, uint8_t opcode) {
        cpu.OP_rr(opcode);
        return cyclesCB(opcode);
    } // RR A

// 0xCB 0x20..0x2F - SLA (0x20-0x27), SRA (0x28-0x2F)
    static inline int CB_0x20(CPU &cpu, uint8_t opcode) {
        cpu.OP_sla(opcode);
        return cyclesCB(opcode);
    } // SLA B
    static inline int CB_0x21(CPU &cpu, uint8_t opcode) {
        cpu.OP_sla(opcode);
        return cyclesCB(opcode);
    } // SLA C
    static inline int CB_0x22(CPU &cpu, uint8_t opcode) {
        cpu.OP_sla(opcode);
        return cyclesCB(opcode);
    } // SLA D
    static inline int CB_0x23(CPU &cpu, uint8_t opcode) {
        cpu.OP_sla(opcode);
        return cyclesCB(opcode);
    } // SLA E
    static inline int CB_0x24(CPU &cpu, uint8_t opcode) {
        cpu.OP_sla(opcode);
        return cyclesCB(opcode);
    } // SLA H
    static inline int CB_0x25(CPU &cpu, uint8_t opcode) {
        cpu.OP_sla(opcode);
        return cyclesCB(opcode);
    } // SLA L
    static inline int CB_0x26(CPU &cpu, uint8_t opcode) {
        cpu.OP_sla(opcode);
        return cyclesCB(opcode);
    } // SLA (HL)
    static inline int CB_0x27(CPU &cpu, uint8_t opcode) {
        cpu.OP_sla(opcode);
        return cyclesCB(opcode);
    } // SLA A
    static inline int CB_0x28(CPU &cpu, uint8_t opcode) {
        cpu.OP_sra(opcode);
        return cyclesCB(opcode);
    } // SRA B
    static inline int CB_0x29(CPU &cpu, uint8_t opcode) {
        cpu.OP_sra(opcode);
        return cyclesCB(opcode);
    } // SRA C
    static inline int CB_0x2A(CPU &cpu, uint8_t opcode) {
        cpu.OP_sra(opcode);
        return cyclesCB(opcode);
    } // SRA D
    static inline int CB_0x2B(CPU &cpu, uint8_t opcode) {
        cpu.OP_sra(opcode);
        return cyclesCB(opcode);
    } // SRA E
    static inline int CB_0x2C(CPU &cpu, uint8_t opcode) {
        cpu.OP_sra(opcode);
        return cyclesCB(opcode);
    } // SRA H
    static inline int CB_0x2D(CPU &cpu, uint8_t opcode) {
        cpu.OP_sra(opcode);
        return cyclesCB(opcode);
    } // SRA L
    static inline int CB_0x2E(CPU &cpu, uint8_t opcode) {
        cpu.OP_sra(opcode);
        return cyclesCB(opcode);
    } // SRA (HL)
    static inline int CB_0x2F(CPU &cpu, uint8_t opcode) {
        cpu.OP_sra(opcode);
        return cyclesCB(opcode);
    } // SRA A

// 0xCB 0x30..0x3F - SWAP (0x30-0x37), SRL (0x38-0x3F)
    static inline int CB_0x30(CPU &cpu, uint8_t opcode) {
        cpu.OP_swap(opcode);
        return cyclesCB(opcode);
    } // SWAP B
    static inline int CB_0x31(CPU &cpu, uint8_t opcode) {
        cpu.OP_swap(opcode);
        return cyclesCB(opcode);
    } // SWAP C
    static inline int CB_0x32(CPU &cpu, uint8_t opcode) {
        cpu.OP_swap(opcode);
        return cyclesCB(opcode);
    } // SWAP D
    static inline int CB_0x33(CPU &cpu, uint8_t opcode) {
        cpu.OP_swap(opcode);
        return cyclesCB(opcode);
    } // SWAP E
    static inline int CB_0x34(CPU &cpu, uint8_t opcode) {
        cpu.OP_swap(opcode);
        return cyclesCB(opcode);
    } // SWAP H
    static inline int CB_0x35(CPU &cpu, uint8_t opcode) {
        cpu.OP_swap(opcode);
        return cyclesCB(opcode);
    } // SWAP L
    static inline int CB_0x36(CPU &cpu, uint8_t opcode) {
        cpu.OP_swap(opcode);
        return cyclesCB(opcode);
    } // SWAP (HL)
    static inline int CB_0x37(CPU &cpu, uint8_t opcode) {
        cpu.OP_swap(opcode);
        return cyclesCB(opcode);
    } // SWAP A
    static inline int CB_0x38(CPU &cpu, uint8_t opcode) {
        cpu.OP_srl(opcode);
        return cyclesCB(opcode);
    } // SRL B
    static inline int CB_0x39(CPU &cpu, uint8_t opcode) {
        cpu.OP_srl(opcode);
        return cyclesCB(opcode);
    } // SRL C
    static inline int CB_0x3A(CPU &cpu, uint8_t opcode) {
        cpu.OP_srl(opcode);
        return cyclesCB(opcode);
    } // SRL D
    static inline int CB_0x3B(CPU &cpu, uint8_t opcode) {
        cpu.OP_srl(opcode);
        return cyclesCB(opcode);
    } // SRL E
    static inline int CB_0x3C(CPU &cpu, uint8_t opcode) {
        cpu.OP_srl(opcode);
        return cyclesCB(opcode);
    } // SRL H
    static inline int CB_0x3D(CPU &cpu, uint8_t opcode) {
        cpu.OP_srl(opcode);
        return cyclesCB(opcode);
    } // SRL L
    static inline int CB_0x3E(CPU &cpu, uint8_t opcode) {
        cpu.OP_srl(opcode);
        return cyclesCB(opcode);
    } // SRL (HL)
    static inline int CB_0x3F(CPU &cpu, uint8_t opcode) {
        cpu.OP_srl(opcode);
        return cyclesCB(opcode);
    } // SRL A

// 0xCB 0x40..0x7F - BIT b, r
    static inline int CB_0x40(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 0, B
    static inline int CB_0x41(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 0, C
    static inline int CB_0x42(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 0, D
    static inline int CB_0x43(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 0, E
    static inline int CB_0x44(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 0, H
    static inline int CB_0x45(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 0, L
    static inline int CB_0x46(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 0, (HL)
    static inline int CB_0x47(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 0, A
    static inline int CB_0x48(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 1, B
    static inline int CB_0x49(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 1, C
    static inline int CB_0x4A(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 1, D
    static inline int CB_0x4B(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 1, E
    static inline int CB_0x4C(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 1, H
    static inline int CB_0x4D(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 1, L
    static inline int CB_0x4E(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 1, (HL)
    static inline int CB_0x4F(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 1, A

    static inline int CB_0x50(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 2, B
    static inline int CB_0x51(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 2, C
    static inline int CB_0x52(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 2, D
    static inline int CB_0x53(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 2, E
    static inline int CB_0x54(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 2, H
    static inline int CB_0x55(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 2, L
    static inline int CB_0x56(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 2, (HL)
    static inline int CB_0x57(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 2, A
    static inline int CB_0x58(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 3, B
    static inline int CB_0x59(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 3, C
    static inline int CB_0x5A(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 3, D
    static inline int CB_0x5B(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 3, E
    static inline int CB_0x5C(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 3, H
    static inline int CB_0x5D(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 3, L
    static inline int CB_0x5E(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 3, (HL)
    static inline int CB_0x5F(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 3, A

    static inline int CB_0x60(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 4, B
    static inline int CB_0x61(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 4, C
    static inline int CB_0x62(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 4, D
    static inline int CB_0x63(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 4, E
    static inline int CB_0x64(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 4, H
    static inline int CB_0x65(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 4, L
    static inline int CB_0x66(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 4, (HL)
    static inline int CB_0x67(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 4, A
    static inline int CB_0x68(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 5, B
    static inline int CB_0x69(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 5, C
    static inline int CB_0x6A(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 5, D
    static inline int CB_0x6B(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 5, E
    static inline int CB_0x6C(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 5, H
    static inline int CB_0x6D(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 5, L
    static inline int CB_0x6E(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 5, (HL)
    static inline int CB_0x6F(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 5, A

    static inline int CB_0x70(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 6, B
    static inline int CB_0x71(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 6, C
    static inline int CB_0x72(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 6, D
    static inline int CB_0x73(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 6, E
    static inline int CB_0x74(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 6, H
    static inline int CB_0x75(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 6, L
    static inline int CB_0x76(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 6, (HL)
    static inline int CB_0x77(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 6, A
    static inline int CB_0x78(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 7, B
    static inline int CB_0x79(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 7, C
    static inline int CB_0x7A(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 7, D
    static inline int CB_0x7B(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 7, E
    static inline int CB_0x7C(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 7, H
    static inline int CB_0x7D(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 7, L
    static inline int CB_0x7E(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 7, (HL)
    static inline int CB_0x7F(CPU &cpu, uint8_t opcode) {
        cpu.OP_bit(opcode);
        return cyclesCB(opcode);
    } // BIT 7, A

// 0xCB 0x80..0xBF - RES b, r
    static inline int CB_0x80(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 0, B
    static inline int CB_0x81(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 0, C
    static inline int CB_0x82(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 0, D
    static inline int CB_0x83(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 0, E
    static inline int CB_0x84(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 0, H
    static inline int CB_0x85(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 0, L
    static inline int CB_0x86(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 0, (HL)
    static inline int CB_0x87(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 0, A
    static inline int CB_0x88(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 1, B
    static inline int CB_0x89(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 1, C
    static inline int CB_0x8A(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 1, D
    static inline int CB_0x8B(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 1, E
    static inline int CB_0x8C(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 1, H
    static inline int CB_0x8D(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 1, L
    static inline int CB_0x8E(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 1, (HL)
    static inline int CB_0x8F(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 1, A

    static inline int CB_0x90(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 2, B
    static inline int CB_0x91(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 2, C
    static inline int CB_0x92(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 2, D
    static inline int CB_0x93(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 2, E
    static inline int CB_0x94(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 2, H
    static inline int CB_0x95(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 2, L
    static inline int CB_0x96(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 2, (HL)
    static inline int CB_0x97(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 2, A
    static inline int CB_0x98(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 3, B
    static inline int CB_0x99(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 3, C
    static inline int CB_0x9A(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 3, D
    static inline int CB_0x9B(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 3, E
    static inline int CB_0x9C(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 3, H
    static inline int CB_0x9D(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 3, L
    static inline int CB_0x9E(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 3, (HL)
    static inline int CB_0x9F(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 3, A

    static inline int CB_0xA0(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 4, B
    static inline int CB_0xA1(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 4, C
    static inline int CB_0xA2(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 4, D
    static inline int CB_0xA3(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 4, E
    static inline int CB_0xA4(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 4, H
    static inline int CB_0xA5(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 4, L
    static inline int CB_0xA6(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 4, (HL)
    static inline int CB_0xA7(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 4, A
    static inline int CB_0xA8(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 5, B
    static inline int CB_0xA9(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 5, C
    static inline int CB_0xAA(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 5, D
    static inline int CB_0xAB(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 5, E
    static inline int CB_0xAC(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 5, H
    static inline int CB_0xAD(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 5, L
    static inline int CB_0xAE(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 5, (HL)
    static inline int CB_0xAF(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 5, A

    static inline int CB_0xB0(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 6, B
    static inline int CB_0xB1(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 6, C
    static inline int CB_0xB2(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 6, D
    static inline int CB_0xB3(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 6, E
    static inline int CB_0xB4(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 6, H
    static inline int CB_0xB5(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 6, L
    static inline int CB_0xB6(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 6, (HL)
    static inline int CB_0xB7(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 6, A
    static inline int CB_0xB8(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 7, B
    static inline int CB_0xB9(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 7, C
    static inline int CB_0xBA(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 7, D
    static inline int CB_0xBB(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 7, E
    static inline int CB_0xBC(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 7, H
    static inline int CB_0xBD(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 7, L
    static inline int CB_0xBE(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 7, (HL)
    static inline int CB_0xBF(CPU &cpu, uint8_t opcode) {
        cpu.OP_res(opcode);
        return cyclesCB(opcode);
    } // RES 7, A

// 0xCB 0xC0..0xFF - SET b, r
    static inline int CB_0xC0(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 0, B
    static inline int CB_0xC1(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 0, C
    static inline int CB_0xC2(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 0, D
    static inline int CB_0xC3(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 0, E
    static inline int CB_0xC4(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 0, H
    static inline int CB_0xC5(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 0, L
    static inline int CB_0xC6(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 0, (HL)
    static inline int CB_0xC7(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 0, A
    static inline int CB_0xC8(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 1, B
    static inline int CB_0xC9(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 1, C
    static inline int CB_0xCA(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 1, D
    static inline int CB_0xCB(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 1, E
    static inline int CB_0xCC(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 1, H
    static inline int CB_0xCD(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 1, L
    static inline int CB_0xCE(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 1, (HL)
    static inline int CB_0xCF(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 1, A

    static inline int CB_0xD0(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 2, B
    static inline int CB_0xD1(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 2, C
    static inline int CB_0xD2(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 2, D
    static inline int CB_0xD3(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 2, E
    static inline int CB_0xD4(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 2, H
    static inline int CB_0xD5(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 2, L
    static inline int CB_0xD6(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 2, (HL)
    static inline int CB_0xD7(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 2, A
    static inline int CB_0xD8(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 3, B
    static inline int CB_0xD9(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 3, C
    static inline int CB_0xDA(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 3, D
    static inline int CB_0xDB(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 3, E
    static inline int CB_0xDC(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 3, H
    static inline int CB_0xDD(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 3, L
    static inline int CB_0xDE(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 3, (HL)
    static inline int CB_0xDF(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 3, A

    static inline int CB_0xE0(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 4, B
    static inline int CB_0xE1(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 4, C
    static inline int CB_0xE2(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 4, D
    static inline int CB_0xE3(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 4, E
    static inline int CB_0xE4(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 4, H
    static inline int CB_0xE5(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 4, L
    static inline int CB_0xE6(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 4, (HL)
    static inline int CB_0xE7(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 4, A
    static inline int CB_0xE8(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 5, B
    static inline int CB_0xE9(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 5, C
    static inline int CB_0xEA(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 5, D
    static inline int CB_0xEB(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 5, E
    static inline int CB_0xEC(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 5, H
    static inline int CB_0xED(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 5, L
    static inline int CB_0xEE(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 5, (HL)
    static inline int CB_0xEF(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 5, A

    static inline int CB_0xF0(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 6, B
    static inline int CB_0xF1(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 6, C
    static inline int CB_0xF2(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 6, D
    static inline int CB_0xF3(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 6, E
    static inline int CB_0xF4(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 6, H
    static inline int CB_0xF5(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 6, L
    static inline int CB_0xF6(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 6, (HL)
    static inline int CB_0xF7(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 6, A
    static inline int CB_0xF8(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 7, B
    static inline int CB_0xF9(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 7, C
    static inline int CB_0xFA(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 7, D
    static inline int CB_0xFB(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 7, E
    static inline int CB_0xFC(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 7, H
    static inline int CB_0xFD(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 7, L
    static inline int CB_0xFE(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 7, (HL)
    static inline int CB_0xFF(CPU &cpu, uint8_t opcode) {
        cpu.OP_set(opcode);
        return cyclesCB(opcode);
    } // SET 7, A
};
#endif //GBEMULATOR_OPCODES_H