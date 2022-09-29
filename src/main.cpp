#include <mbed.h>

//#include "ws2812b.hpp"
#include "led_fall.hpp"

int main() {
    WS2812B ws2812b(PA_15, 60, 400, 800, 850, 450, 60);
    led_fall *blocks[10];
    int now_block = 0;
    for (int i = 0; i < 10; ++i) {
        if (i % 3 == 0) {
            blocks[i] = new led_fall(&ws2812b, 100, 0, 0, 5, 0, 59 - 5 * i, 20, 0.6, 0.1, 8);
        } else if(i%3==1){
            blocks[i] = new led_fall(&ws2812b, 0, 100, 0, 5, 0, 59 - 5 * i, 20, 0.6, 0.1, 8);
        } else{
            blocks[i] = new led_fall(&ws2812b, 0, 0, 100, 5, 0, 59 - 5 * i, 20, 0.6, 0.1, 8);
        }
    }
//    led_fall first_guy(&ws2812b, 100, 0, 0, 5, 0, 59, 20, 0.6, 0.1, 5);
//    ws2812b.setRGB(1,0,0,0);
    DigitalOut led(LED1);

//    ws2812b.setRGB(1,1,1,100);
//    ws2812b.setRGB(20,24,24,24);
    while (true) {
        led = !led;
        blocks[now_block]->update_position();
        ws2812b.update();
        if (now_block>=10) return 0;
        if (!blocks[now_block]->is_falling()){
            now_block++;
            ThisThread::sleep_for(3s);
        }
        ThisThread::sleep_for(10ms);
    }
}
