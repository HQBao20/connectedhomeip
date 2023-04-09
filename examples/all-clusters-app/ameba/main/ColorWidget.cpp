#include <cstdio>
#include <math.h>
#include "PWMWidget.h"
#include "ColorWidget.h"

#define LEVEL_MAX 254

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

WyColor_t Colorwidget::controlCCT(CtColor_t ct)
{
    WyColor_t wy;
    uint8_t byTemperature = ct.wCtMireds;

    switch (byTemperature)
    {
        case yellowMax:
        {
            wy.byYellow = PWM_PERIOD - ((((ct.wCtMireds + 256) * PWM_PERIOD) / (yellowMax + 256)) * (ct.fBrighness / LEVEL_MAX));
            wy.byWhite = 255;
        }break;
        case yellowMedium:
        {
            wy.byYellow = PWM_PERIOD - ((((ct.wCtMireds + 256) * PWM_PERIOD) / (yellowMax + 256)) * (ct.fBrighness / LEVEL_MAX));
            wy.byWhite = PWM_PERIOD - (wy.byYellow * (ct.fBrighness / LEVEL_MAX));
        }break;
        case yellowMin:
        {
            wy.byYellow = PWM_PERIOD - ((((ct.wCtMireds + 256) * PWM_PERIOD) / (yellowMax + 256)) * (ct.fBrighness / LEVEL_MAX));
            wy.byWhite = PWM_PERIOD - (wy.byYellow * (ct.fBrighness / LEVEL_MAX));
        }break;
        case whiteMax:
        {
            wy.byWhite = PWM_PERIOD - (((ct.wCtMireds * PWM_PERIOD) / whiteMax) * (ct.fBrighness / LEVEL_MAX));
            wy.byYellow = 255;
        }break;
        case whiteMedium:
        {
            wy.byWhite = PWM_PERIOD - (((ct.wCtMireds * PWM_PERIOD) / whiteMax) * (ct.fBrighness / LEVEL_MAX));
            wy.byYellow = PWM_PERIOD - (wy.byWhite * (ct.fBrighness / LEVEL_MAX));
        }break;
        case whiteMin:
        {
            wy.byWhite = PWM_PERIOD - (((ct.wCtMireds * PWM_PERIOD) / whiteMax) * (ct.fBrighness / LEVEL_MAX));
            wy.byYellow = PWM_PERIOD - (wy.byWhite * (ct.fBrighness / LEVEL_MAX));
        }break;
        default:
            break;
    }

    printf("=================\n");
    printf("Brighness: %.3f\n", (ct.fBrighness / LEVEL_MAX));
    printf("Yellow: %d\n", wy.byYellow);
    printf("White: %d\n", wy.byWhite);

    return wy;
}