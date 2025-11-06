#pragma once
#include <cstdint>
#include "Bus.hpp"
#include "registers.hpp"

class opcodes;
class Bus;


class CPU {
public:
    // 16-bit register pairs
    reg16 AF;  // Accumulator & Flags
    reg16 BC;
    reg16 DE;
    reg16 HL;
    reg16 SP;  // Stack Pointer
    reg16 PC;  // Program Counter

    explicit CPU(Bus *bus) : bus{bus} {
        // Initialize registers
        AF.reset();
        BC.reset();
        DE.reset();
        HL.reset();
        SP.reset();
        PC.reset();
        mapOPCodes();
        mapCBOPCodes();  // Add this line
        A().set(0x01);
        F().set(0xB0);
        B().set(0x00);
        C().set(0x13);
        D().set(0x00);
        E().set(0xD8);
        H().set(0x01);
        L().set(0x4D);
        SP.set(0xFFFE);
        PC.set(0x0100);

    }
    void logState();
    int cycle();

    // Access to 8-bit registers through references
    reg8& A() { return AF.get_high(); }
    reg8& F() { return AF.get_low(); }
    reg8& B() { return BC.get_high(); }
    reg8& C() { return BC.get_low(); }
    reg8& D() { return DE.get_high(); }
    reg8& E() { return DE.get_low(); }
    reg8& H() { return HL.get_high(); }
    reg8& L() { return HL.get_low(); }

    const reg8& A() const { return AF.get_high(); }
    const reg8& F() const { return AF.get_low(); }
    const reg8& B() const { return BC.get_high(); }
    const reg8& C() const { return BC.get_low(); }
    const reg8& D() const { return DE.get_high(); }
    const reg8& E() const { return DE.get_low(); }
    const reg8& H() const { return HL.get_high(); }
    const reg8& L() const { return HL.get_low(); }



    const reg16& getReg16(uint8_t mask) const {
        switch (mask) {
            case 0: return BC;
            case 1: return DE;
            case 2: return HL;
            case 3: return SP;
            default: return BC;
        }
    }

    // Get 8-bit register by mask (for common instruction encoding)
    reg8& getReg8(uint8_t mask) {
        switch (mask) {
            case 0: return B();
            case 1: return C();
            case 2: return D();
            case 3: return E();
            case 4: return H();
            case 5: return L();
            case 7: return A();
            default: return A();
        }
    }

    const reg8& getReg8(uint8_t mask) const {
        switch (mask) {
            case 0: return B();
            case 1: return C();
            case 2: return D();
            case 3: return E();
            case 4: return H();
            case 5: return L();
            case 7: return A();
            default: return A();
        }
    }

    // Flag manipulation (F register)
    bool get_flag_Z() const { return F().test_bit(7); }  // Zero flag
    bool get_flag_N() const { return F().test_bit(6); }  // Subtract flag
    bool get_flag_H() const { return F().test_bit(5); }  // Half-carry flag
    bool get_flag_C() const { return F().test_bit(4); }  // Carry flag

    void set_flag_Z(bool val) { F().write_bit(7, val); }
    void set_flag_N(bool val) { F().write_bit(6, val); }
    void set_flag_H(bool val) { F().write_bit(5, val); }
    void set_flag_C(bool val) { F().write_bit(4, val); }

    void set_flags(bool z, bool n, bool h, bool c) {
        set_flag_Z(z);
        set_flag_N(n);
        set_flag_H(h);
        set_flag_C(c);
    }

private:
    Bus* bus;

    using GbFunc = int(*)(CPU&, uint8_t);
    GbFunc opTable[256]{};
    GbFunc cbOpTable[256]{};

    inline uint8_t fetch8() { return bus->read8(PC++); }

    void mapOPCodes();
    void mapCBOPCodes();

    friend opcodes;

//Getters based on first table from: https://gbdev.io/pandocs/CPU_Instruction_Set.html
    // Get 16-bit register by mask
    struct R8Ref;
    reg16& getTableReg16(uint8_t mask);
    R8Ref getTableReg8(uint8_t mask);


    //Memory access helpers
    inline uint16_t fetch16() {
        uint8_t lo = fetch8();
        uint16_t imm16 = (fetch8() << 8) | lo;
        return imm16;
    }

    //Mnemonic instructions
    void OP_ld_r16_imm(uint8_t opcode);
    void OP_ld_r16mem_a(uint8_t opcode);
    void OP_ld_a_r16mem(uint8_t opcode);
    void OP_inc_r16(uint8_t opcode);
    void OP_dec_r16(uint8_t opcode);
    void OP_add_HL_r16(uint8_t opcode);
    void OP_inc_r8(uint8_t opcode);
    void OP_dec_r8(uint8_t opcode);
    void OP_ld_r8_imm(uint8_t opcode);
    void OP_jr();
    void OP_ld_r8_r8(uint8_t opcode);
    void OP_add_a_r8(uint8_t opcode);
    void OP_adc_a_r8(uint8_t opcode);
    void OP_sub_a_r8(uint8_t opcode);
    void OP_sbc_a_r8(uint8_t opcode);
    void OP_and_a_r8(uint8_t opcode);
    void OP_xor_a_r8(uint8_t opcode);
    void OP_or_a_r8(uint8_t opcode);
    void OP_cp_a_r8(uint8_t opcode);
    void OP_ret();
    void OP_jp();
    void OP_call();
    void OP_rst(uint8_t opcode);
    void OP_pop(uint8_t opcode);
    void OP_push(uint8_t opcode);
    void OP_rlc(uint8_t opcode);
    void OP_rrc(uint8_t opcode);
    void OP_rl(uint8_t opcode);
    void OP_rr(uint8_t opcode);
    void OP_sla(uint8_t opcode);
    void OP_sra(uint8_t opcode);
    void OP_srl(uint8_t opcode);
    void OP_swap(uint8_t opcode);
    void OP_bit(uint8_t opcode);
    void OP_res(uint8_t opcode);
    void OP_set(uint8_t opcode);



    //Encapsulates registers and indirect (HL)
    struct R8Ref {
        enum class Kind : uint8_t { Reg, MemHL };

        CPU* cpu = nullptr;
        reg8* reg = nullptr;
        Kind kind = Kind::Reg;

        R8Ref() = default;
        static R8Ref fromReg(CPU& c, reg8& r) { return R8Ref{&c, &r, Kind::Reg}; }
        static R8Ref memHL(CPU& c)            { return R8Ref{&c, nullptr, Kind::MemHL}; }

        uint8_t get() const;

         void set(uint8_t v) const;

        inline operator uint8_t() const { return get(); }

        inline R8Ref& operator=(uint8_t v) { set(v); return *this; }
        inline R8Ref& operator=(const R8Ref& other) { set(other.get()); return *this; }

        inline R8Ref& operator+=(uint8_t v) { set(uint8_t(get() + v)); return *this; }
        inline R8Ref& operator-=(uint8_t v) { set(uint8_t(get() - v)); return *this; }
        inline R8Ref& operator&=(uint8_t v) { set(uint8_t(get() & v)); return *this; }
        inline R8Ref& operator|=(uint8_t v) { set(uint8_t(get() | v)); return *this; }
        inline R8Ref& operator^=(uint8_t v) { set(uint8_t(get() ^ v)); return *this; }

        inline R8Ref& operator++()       { set(uint8_t(get() + 1)); return *this; } // prefix
        inline uint8_t operator++(int)   { uint8_t old=get(); set(uint8_t(old+1)); return old; } // postfix
        inline R8Ref& operator--()       { set(uint8_t(get() - 1)); return *this; }
        inline uint8_t operator--(int)   { uint8_t old=get(); set(uint8_t(old-1)); return old; }

    };
};
