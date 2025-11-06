//
// Created by akith on 10/31/2025.
//

#ifndef GBEMULATOR_REGISTERS_HPP
#define GBEMULATOR_REGISTERS_HPP

#include <cstdint>
class CPU;

class reg8 {
private:
    uint8_t value;

public:
    reg8() : value(0) {}
    explicit reg8(uint8_t val) : value(val) {}

    uint8_t get() const { return value; }
    void set(uint8_t val) { value = val; }

    operator uint8_t() const { return value; }

    reg8& operator=(uint8_t val) {
        value = val;
        return *this;
    }

    reg8& operator=(const reg8& other) {
        value = other.value;
        return *this;
    }

    reg8& operator+=(uint8_t val) {
        value += val;
        return *this;
    }

    reg8& operator-=(uint8_t val) {
        value -= val;
        return *this;
    }

    reg8& operator&=(uint8_t val) {
        value &= val;
        return *this;
    }

    reg8& operator|=(uint8_t val) {
        value |= val;
        return *this;
    }

    reg8& operator^=(uint8_t val) {
        value ^= val;
        return *this;
    }

    reg8& operator++() {
        ++value;
        return *this;
    }

    uint8_t operator++(int) {
        uint8_t old = value;
        ++value;
        return old;
    }

    reg8& operator--() {
        --value;
        return *this;
    }

    uint8_t operator--(int) {
        uint8_t old = value;
        --value;
        return old;
    }

    void set_bit(int bit) {
        value |= (1 << bit);
    }

    void clear_bit(int bit) {
        value &= ~(1 << bit);
    }

    void toggle_bit(int bit) {
        value ^= (1 << bit);
    }

    bool test_bit(int bit) const {
        return (value & (1 << bit)) != 0;
    }

    void write_bit(int bit, bool set) {
        if (set)
            set_bit(bit);
        else
            clear_bit(bit);
    }

    uint8_t rotate_left() {
        uint8_t carry = (value & 0x80) >> 7;
        value = (value << 1) | carry;
        return carry;
    }

    uint8_t rotate_right() {
        uint8_t carry = value & 0x01;
        value = (value >> 1) | (carry << 7);
        return carry;
    }

    uint8_t rotate_left_through_carry(bool carry) {
        uint8_t new_carry = (value & 0x80) != 0;
        value = (value << 1) | (carry ? 1 : 0);
        return new_carry;
    }

    uint8_t rotate_right_through_carry(bool carry) {
        bool new_carry = (value & 0x01) != 0;
        value = (value >> 1) | (carry ? 0x80 : 0);
        return new_carry;
    }

    void shift_left_arithmetic() {
        value <<= 1;
    }

    void shift_right_arithmetic() {
        uint8_t msb = value & 0x80;
        value = (value >> 1) | msb;
    }

    void shift_right_logical() {
        value >>= 1;
    }

    void swap() {
        value = ((value & 0x0F) << 4) | ((value & 0xF0) >> 4);
    }

    uint8_t get_low_nibble() const {
        return value & 0x0F;
    }

    uint8_t get_high_nibble() const {
        return (value & 0xF0) >> 4;
    }

    void set_low_nibble(uint8_t nibble) {
        value = (value & 0xF0) | (nibble & 0x0F);
    }

    void set_high_nibble(uint8_t nibble) {
        value = (value & 0x0F) | ((nibble & 0x0F) << 4);
    }

    void reset() {
        value = 0;
    }
};

#ifndef REG16_H
#define REG16_H


class reg16 {
private:
    reg8 high;
    reg8 low;

public:
    reg16() : high(0), low(0) {}
    explicit reg16(uint16_t val) : high(val >> 8), low(val & 0xFF) {}
    reg16(uint8_t h, uint8_t l) : high(h), low(l) {}

    uint16_t get() const {
        return (static_cast<uint16_t>(high.get()) << 8) | low.get();
    }

    void set(uint16_t val) {
        high.set(val >> 8);
        low.set(val & 0xFF);
    }

    reg8& get_high() { return high; }
    reg8& get_low() { return low; }

    const reg8& get_high() const { return high; }
    const reg8& get_low() const { return low; }

    operator uint16_t() const { return get(); }

    reg16& operator=(uint16_t val) {
        set(val);
        return *this;
    }

    reg16& operator=(const reg16& other) {
        high = other.high;
        low = other.low;
        return *this;
    }

    reg16& operator+=(uint16_t val) {
        set(get() + val);
        return *this;
    }

    reg16& operator-=(uint16_t val) {
        set(get() - val);
        return *this;
    }

    reg16& operator&=(uint16_t val) {
        set(get() & val);
        return *this;
    }

    reg16& operator|=(uint16_t val) {
        set(get() | val);
        return *this;
    }

    reg16& operator^=(uint16_t val) {
        set(get() ^ val);
        return *this;
    }

    reg16& operator++() {
        set(get() + 1);
        return *this;
    }

    uint16_t operator++(int) {
        uint16_t old = get();
        set(old + 1);
        return old;
    }

    reg16& operator--() {
        set(get() - 1);
        return *this;
    }

    uint16_t operator--(int) {
        uint16_t old = get();
        set(old - 1);
        return old;
    }

    void reset() {
        high.reset();
        low.reset();
    }

    void set_bit(int bit) {
        if (bit < 8) {
            low.set_bit(bit);
        } else {
            high.set_bit(bit - 8);
        }
    }

    void clear_bit(int bit) {
        if (bit < 8) {
            low.clear_bit(bit);
        } else {
            high.clear_bit(bit - 8);
        }
    }

    bool test_bit(int bit) const {
        if (bit < 8) {
            return low.test_bit(bit);
        } else {
            return high.test_bit(bit - 8);
        }
    }

};

#endif // REG16_H

#endif //GBEMULATOR_REGISTERS_HPP
