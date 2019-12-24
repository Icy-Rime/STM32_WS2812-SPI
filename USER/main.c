#include "stm32f10x_conf.h"
#include "SYS.h"
#include "WS2812.h"
int main()
{
    WS2812_Configuration();
    while(1)
    {
        rainbowCycle(8);
    }
    
}

