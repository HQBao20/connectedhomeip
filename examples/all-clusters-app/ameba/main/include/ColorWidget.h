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
    uint8_t byWhite;
    uint8_t byYellow;
}WyColor_t;

typedef struct
{
    uint8_t byHue;
    uint8_t bySaturation;
    uint8_t byValue;
}HsvColor_t;

typedef struct
{
    uint16_t wCtMireds;
    float fBrighness;
}CtColor_t;

enum ColorTemperature
{
    yellowMax = 244,
    yellowMedium = 114,
    yellowMin = 77,
    whiteMax = 250,
    whiteMedium = 200,
    whiteMin = 167
};

class Colorwidget
{
    public:
        RgbColor_t hsvToRgb(HsvColor_t hsv);
        WyColor_t controlCCT(CtColor_t ct);
};