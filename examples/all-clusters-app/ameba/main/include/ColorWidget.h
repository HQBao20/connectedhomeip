#pragma once
#include <stdint.h>

typedef struct
{
    uint8_t byCurrentRed;
    uint8_t byCurrentGreen;
    uint8_t byCurrentBlue;
    uint8_t byDestinationRed;
    uint8_t byDestinationGreen;
    uint8_t byDestinationBlue;
}RgbColor_t;

typedef struct
{
    uint8_t byCurrentWhite;
    uint8_t byCurrentYellow;
    uint8_t byDestinationWhite;
    uint8_t byDestinationYellow;
}WyColor_t;

typedef struct
{
    float fHue;
    float fSaturation;
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
    yellowNeuter = 182,
    whiteMax = 250,
    whiteMedium = 200,
    whiteMin = 167,
    whiteNeuter = 154
};

class Colorwidget
{
    public:
        void hsvToRgb(HsvColor_t hsv, RgbColor_t *rgbColor);
        void controlCCT(CtColor_t ct, WyColor_t *wyColor);
};