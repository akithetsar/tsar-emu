//
// Created by akith on [date]
//

#ifndef GBEMULATOR_TIMER_HPP
#define GBEMULATOR_TIMER_HPP

#include <cstdint>

class Bus;

class Timer {
public:
    explicit Timer(Bus* bus) : bus(bus) {
        reset();
    }

    void reset();
    void tick(int cycles);

    uint8_t getDIV() const { return div; }
    uint8_t getTIMA() const { return tima; }
    uint8_t getTMA() const { return tma; }
    uint8_t getTAC() const { return tac; }

    void setDIV(uint8_t val);
    void setTIMA(uint8_t val) { tima = val; }
    void setTMA(uint8_t val) { tma = val; }
    void setTAC(uint8_t val);

private:
    Bus* bus;

    // Timer registers
    uint8_t div;   // 0xFF04 - Divider Register (increments at 16384 Hz)
    uint8_t tima;  // 0xFF05 - Timer Counter (increments at frequency specified by TAC)
    uint8_t tma;   // 0xFF06 - Timer Modulo (value loaded into TIMA on overflow)
    uint8_t tac;   // 0xFF07 - Timer Control

    // Internal counters
    uint16_t div_counter;   // Internal counter for DIV (increments every M-cycle)
    uint16_t tima_counter;  // Internal counter for TIMA

    // Helper functions
    uint16_t getTimerFrequency() const;
    bool isTimerEnabled() const { return (tac & 0x04) != 0; }
    void requestTimerInterrupt();
};

#endif //GBEMULATOR_TIMER_HPP