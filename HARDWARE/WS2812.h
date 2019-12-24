#ifndef __WS2812_H
#define __WS2812_H

#include "stm32f10x_conf.h"

typedef struct
{
    u8 R;
    u8 G;
    u8 B;
}RGBColor_TypeDef;

#define Pixel_S1_NUM 6

#define CODE0 0X80
#define CODE1 0XF8

void WS2812_Configuration();

void RGB_RED(u16 Pixel_LEN);
void RGB_GREEN(u16 Pixel_LEN);
void RGB_BLUE(u16 Pixel_LEN);
void RGB_YELLOW(u16 Pixel_LEN);
void RGB_MAGENTA(u16 Pixel_LEN);
void RGB_BLACK(u16 Pixel_LEN);
void RGB_WHITE(u16 Pixel_LEN);
void rainbowCycle(u8 Pixel_LEN);

#endif

