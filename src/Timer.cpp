//
// Created by akith on [date]
//

#include "../h/Timer.hpp"
#include "../h/Bus.hpp"

void Timer::reset() {
    div = 0;
    tima = 0;
    tma = 0;
    tac = 0;
    div_counter = 0;
    tima_counter = 0;
}

uint16_t Timer::getTimerFrequency() const {
    switch (tac & 0x03) {
        case 0: return 1024;  // 4096 Hz   (CPU clock / 1024)
        case 1: return 16;    // 262144 Hz (CPU clock / 16)
        case 2: return 64;    // 65536 Hz  (CPU clock / 64)
        case 3: return 256;   // 16384 Hz  (CPU clock / 256)
        default: return 1024;
    }
}

void Timer:: tick(int cycles) {

    div_counter += cycles;
    while (div_counter >= 256) {
        div_counter -= 256;
        div++;
    }


    if (isTimerEnabled()) {
        tima_counter += cycles;

        uint16_t freq = getTimerFrequency();

        while (tima_counter >= freq) {
            tima_counter -= freq;

            if (tima == 0xFF) {
                tima = tma;
                requestTimerInterrupt();
            } else {
                tima++;
            }
        }
    }
}

void Timer::setDIV(uint8_t val) {
    (void)val;
    div = 0;
    div_counter = 0;
}

void Timer::setTAC(uint8_t val) {
    bool was_enabled = isTimerEnabled();
    tac = val & 0x07;


    if (! was_enabled && isTimerEnabled()) {
        tima_counter = 0;
    }
}

void Timer::requestTimerInterrupt() {
    uint8_t if_reg = bus->read8(0xFF0F);
    if_reg |= 0x04;
    bus->write8(0xFF0F, if_reg);
}