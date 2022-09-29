//
// Created by li-xinjia on 22/09/29.
//

#ifndef LED_FALL_HPP
#define LED_FALL_HPP

#include "ws2812b.hpp"

class led_fall {
private:
    WS2812B *device;
    int R, G, B;
    int number;
    int start_point;
    int stop_point;
    float gravitational_constant;
    float coefficient_of_restitution;
    float delay;
    int max_impact;

    float v;
    bool falling = true;
    int direction;
    int position;
    int impact_times;
public:
    led_fall(WS2812B *device, int R, int G, int B, int number, int start_point, int stop_point, float g, float COR, float delay, int max_impact) :
            device(device),
            R(R), G(G), B(B),
            number(number),
            start_point(start_point),
            stop_point(stop_point),
            gravitational_constant(g),
            coefficient_of_restitution(COR),
            delay(delay),
            max_impact(max_impact) {

        if (stop_point - start_point == 0) {
            falling = false;
            return;
        } else if (stop_point - start_point > 0) {
            direction = 1;
        } else {
            direction = 0;
        }

        v = 0;
        position = start_point;
        impact_times = 0;
    }

    void update_position() {
        if (!falling) return;
        for (int i = start_point; i <= stop_point; i += direction) {
            device->setRGB(i, 0, 0, 0);
        }
        v += gravitational_constant * delay;
        position += v * (float) direction * delay;
        if ((stop_point - position) * direction <= 0) {
            position = stop_point;
            v = -v * coefficient_of_restitution;
            impact_times++;
            if (impact_times >= max_impact) {
                falling = false;
            }
        }
        for (int i = 0; i < number; ++i) {
            device->setRGB(position - i * direction, R, G, B);
        }
    }

    bool is_falling() {
        return falling;
    }
};

#endif //LED_FALL_HPP
