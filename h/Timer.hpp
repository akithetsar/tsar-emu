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
    uint8_t div;
    uint8_t tima;
    uint8_t tma;
    uint8_t tac;

    // Internal counters
    uint16_t div_counter;
    uint16_t tima_counter;

    // Helper functions
    uint16_t getTimerFrequency() const;
    bool isTimerEnabled() const { return (tac & 0x04) != 0; }
    void requestTimerInterrupt();
};

#endif //GBEMULATOR_TIMER_HPP