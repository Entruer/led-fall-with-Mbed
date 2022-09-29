#include <mbed.h>

//#include "ws2812b.hpp"
#include "led_fall.hpp"

#define BLOCK 8 //LEDブロックの長さ
#define BRIGHT 60 //明るさ
#define GRAVITY 20 //重力加速度

//最下点での跳ね返り係数＝R1/R2
#define R1 3 //跳ね返り係数1
#define R2 5 //跳ね返り係数2
#define REFMINV -80 //跳ね返り最小速度

int main() {
    WS2812B ws2812b(PA_15, 60, 400, 800, 850, 450, 60);
    led_fall first_guy(&ws2812b, 100, 0, 0, 5, 0, 59, 20, 0.6,0.1,5);
//    ws2812b.setRGB(1,0,0,0);
    DigitalOut led(LED1);

//    ws2812b.setRGB(1,1,1,100);
//    ws2812b.setRGB(20,24,24,24);
    while (true) {
        led = !led;
        first_guy.update_position();
        ws2812b.update();
        ThisThread::sleep_for(10ms);
    }
}
