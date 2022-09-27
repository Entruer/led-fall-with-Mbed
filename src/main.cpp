#include <mbed.h>

#include "ws2812b.hpp"

#define BLOCK 8 //LEDブロックの長さ
#define BRIGHT 60 //明るさ
#define GRAVITY 20 //重力加速度

//最下点での跳ね返り係数＝R1/R2
#define R1 3 //跳ね返り係数1
#define R2 5 //跳ね返り係数2
#define REFMINV -80 //跳ね返り最小速度

int main() {
    WS2812B ws2812b(PA_15, 59, 120, 800, 1150, 450, 60);
    DigitalOut led(LED1);
    ws2812b.setRGB(0,255,255,255);
    ws2812b.setRGB(1,1,1,100);
//    ws2812b.setRGB(20,100,0,0);
    while (true) {
        led = !led;
        ws2812b.update();
        ThisThread::sleep_for(100ms);
    }
}
