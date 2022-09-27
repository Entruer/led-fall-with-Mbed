//
// Created by li-xinjia on 22/09/26.
//

#ifndef WS2812B_HPP
#define WS2812B_HPP

#if defined ( __GNUC__ )    /* GCC Compiler */
#define NOP __asm __volatile("nop\n")
#elif defined(__ICCARM__)     /* IAR */
#define NOP asm("NOP")
#else
#define NOP __nop()
#endif

#include <mbed.h>

#define ZERO_HIGH_NS 150
#define ONE_HIGH_NS 800
#define ZERO_LOW_NS 1100
#define ONE_LOW_NS 450
#define RESET_US 50

class WS2812B {
private:
    unsigned int zero_high_ns;
    unsigned int one_high_ns;
    unsigned int zero_low_ns;
    unsigned int one_low_ns;
    unsigned int reset_us;
    uint8_t *trans_buffer;
    unsigned short max_port;
    DigitalOut pin;
public:
    WS2812B(PinName pin_name, unsigned short size,
            unsigned int zero_high_ns,
            unsigned int one_high_ns,
            unsigned int zero_low_ns,
            unsigned int one_low_ns,
            unsigned int reset_us) :
            zero_high_ns(zero_high_ns),
            one_high_ns(one_high_ns),
            zero_low_ns(zero_low_ns),
            one_low_ns(one_low_ns),
            reset_us(reset_us),
            pin(pin_name) {
        max_port = size;
        trans_buffer = new uint8_t[size * 3]();
        pin = 0;
    }

    void setRGB(unsigned short port, uint8_t R, uint8_t G, uint8_t B) {
        if (port > max_port || port < 0) {
            return;
        }
        trans_buffer[port * 3] = G;
        trans_buffer[port * 3 + 1] = R;
        trans_buffer[port * 3 + 2] = B;
    }

    void update() {
        unsigned int j;
        reset();
        for (int i = 0; i < max_port * 3; ++i) {
            for (int k = 0; k < 8; ++k) {
                j = 0;
                if ((trans_buffer[i] >> k) & 0x01) {
                    pin = 1;
                    for (; j < one_high_ns; j++) {
                        NOP;
                    }
//                    wait_ns(one_high_ns);
                    pin = 0;
                    for (; j < one_low_ns; j++) {
                        NOP;
                    }
//                    wait_ns(one_low_ns);
                } else {
                    pin = 1;
                    for (; j < zero_high_ns; j++) {
                        NOP;
                    }
//                    wait_ns(zero_high_ns);
                    pin = 0;
                    for (; j < zero_low_ns; j++) {
                        NOP;
                    }
//                    wait_ns(zero_low_ns);
                }
            }
        }
        pin = 1;
    }

    void reset() {
        pin = 0;
        wait_us(reset_us);
    }
};

#endif //WS2812B_HPP
