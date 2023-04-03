#include <cstdio>
#include <math.h>
#include "ColorWidget.h"

#define clamp(a, min, max) ((a) < (min) ? (min) : ((a) > (max) ? (max) : (a)))

RgbColor_t Colorwidget::hsvToRgb(HsvColor_t hsv)
{
    RgbColor_t rgb;

    uint16_t i       = hsv.byHue / 60;
    uint16_t rgb_max = hsv.byValue;
    uint16_t rgb_min = (uint16_t)(rgb_max * (100 - hsv.bySaturation)) / 100;
    uint16_t diff    = hsv.byHue % 60;
    uint16_t rgb_adj = (uint16_t)((rgb_max - rgb_min) * diff) / 60;

    switch (i)
    {
    case 0:
        rgb.byRed = (uint8_t) rgb_max;
        rgb.byGreen = (uint8_t)(rgb_min + rgb_adj);
        rgb.byBlue = (uint8_t) rgb_min;
        break;
    case 1:
        rgb.byRed = (uint8_t)(rgb_max - rgb_adj);
        rgb.byGreen = (uint8_t) rgb_max;
        rgb.byBlue = (uint8_t) rgb_min;
        break;
    case 2:
        rgb.byRed = (uint8_t) rgb_min;
        rgb.byGreen = (uint8_t) rgb_max;
        rgb.byBlue = (uint8_t)(rgb_min + rgb_adj);
        break;
    case 3:
        rgb.byRed = (uint8_t) rgb_min;
        rgb.byGreen = (uint8_t)(rgb_max - rgb_adj);
        rgb.byBlue = (uint8_t) rgb_max;
        break;
    case 4:
        rgb.byRed = (uint8_t)(rgb_min + rgb_adj);
        rgb.byGreen = (uint8_t) rgb_min;
        rgb.byBlue = (uint8_t) rgb_max;
        break;
    default:
        rgb.byRed = (uint8_t) rgb_max;
        rgb.byGreen = (uint8_t) rgb_min;
        rgb.byBlue = (uint8_t)(rgb_max - rgb_adj);
        break;
    }

    return rgb;
}

RgbColor_t Colorwidget::cttToRgb(CtColor_t ct)
{
    RgbColor_t rgb;
    float fRed, fGreen, fBlue;

    // Algorithm credits to Tanner Helland: https://tannerhelland.com/2012/09/18/convert-temperature-rgb-algorithm-code.html

    // Convert Mireds to centiKelvins. k = 1,000,000/mired
    float fCtCentiKelvin = 10000 / ct.dwCtMireds;

    // Red
    if (fCtCentiKelvin <= 66)
    {
        fRed = 255;
    }
    else
    {
        fRed = 329.698727446f * pow(fCtCentiKelvin - 60, -0.1332047592f);
    }

    // Green
    if (fCtCentiKelvin <= 66)
    {
        fGreen = 99.4708025861f * log(fCtCentiKelvin) - 161.1195681661f;
    }
    else
    {
        fGreen = 288.1221695283f * pow(fCtCentiKelvin - 60, -0.0755148492f);
    }

    // Blue
    if (fCtCentiKelvin >= 66)
    {
        fBlue = 255;
    }
    else
    {
        if (fCtCentiKelvin <= 19)
        {
            fBlue = 0;
        }
        else
        {
            fBlue = 138.5177312231 * log(fCtCentiKelvin - 10) - 305.0447927307;
        }
    }
    rgb.byRed = (uint8_t) clamp(fRed, 0, 255);
    rgb.byGreen = (uint8_t) clamp(fGreen, 0, 255);
    rgb.byBlue = (uint8_t) clamp(fBlue, 0, 255);

    return rgb;
}