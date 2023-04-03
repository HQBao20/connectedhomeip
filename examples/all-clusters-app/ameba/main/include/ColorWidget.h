#pragma once
#include <stdint.h>

typedef struct
{
    uint8_t byRed;
    uint8_t byGreen;
    uint8_t byBlue;
}RgbColor_t;

typedef struct
{
    uint8_t byHue;
    uint8_t bySaturation;
    uint8_t byValue;
}HsvColor_t;

typedef struct
{
    uint16_t dwCtMireds;
}CtColor_t;

class Colorwidget
{
    public:
        RgbColor_t hsvToRgb(HsvColor_t hsv);
        RgbColor_t cttToRgb(CtColor_t ct);
};