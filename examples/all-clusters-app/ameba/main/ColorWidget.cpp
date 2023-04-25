#include <cstdio>
#include <math.h>
#include "PWMWidget.h"
#include "ColorWidget.h"

#define LEVEL_MAX 254
#define PULSE_MAX 255

void Colorwidget::hsvToRgb(HsvColor_t hsv, RgbColor_t *rgbColor)
{
    uint16_t i       = (uint16_t)hsv.fHue / 60;
    uint16_t rgb_max = hsv.byValue;
    uint16_t rgb_min = (uint16_t)(rgb_max * (100 - hsv.fSaturation)) / 100;
    uint16_t diff    = (uint16_t)hsv.fHue % 60;
    uint16_t rgb_adj = (uint16_t)((rgb_max - rgb_min) * diff) / 60;

    switch (i)
    {
        case 0:
        {
            rgbColor->byDestinationRed = PULSE_MAX - (uint8_t) rgb_max;
            rgbColor->byDestinationGreen = PULSE_MAX - (uint8_t)(rgb_min + rgb_adj);
            rgbColor->byDestinationBlue = PULSE_MAX - (uint8_t) rgb_min;
        }break;
        case 1:
        {
            rgbColor->byDestinationRed = PULSE_MAX - (uint8_t)(rgb_max - rgb_adj);
            rgbColor->byDestinationGreen = PULSE_MAX - (uint8_t) rgb_max;
            rgbColor->byDestinationBlue = PULSE_MAX - (uint8_t) rgb_min;
        }break;
        case 2:
        {
            rgbColor->byDestinationRed = PULSE_MAX - (uint8_t) rgb_min;
            rgbColor->byDestinationGreen = PULSE_MAX - (uint8_t) rgb_max;
            rgbColor->byDestinationBlue = PULSE_MAX - (uint8_t)(rgb_min + rgb_adj);
        }break;
        case 3:
        {
            rgbColor->byDestinationRed = PULSE_MAX - (uint8_t) rgb_min;
            rgbColor->byDestinationGreen = PULSE_MAX - (uint8_t)(rgb_max - rgb_adj);
            rgbColor->byDestinationBlue = PULSE_MAX - (uint8_t) rgb_max;
        }break;
        case 4:
        {
            rgbColor->byDestinationRed = PULSE_MAX - (uint8_t)(rgb_min + rgb_adj);
            rgbColor->byDestinationGreen = PULSE_MAX - (uint8_t) rgb_min;
            rgbColor->byDestinationBlue = PULSE_MAX - (uint8_t) rgb_max;
        }break;
        case 5:
        {
            rgbColor->byDestinationRed = PULSE_MAX - (uint8_t) rgb_max;
            rgbColor->byDestinationGreen = PULSE_MAX - (uint8_t) rgb_min;
            rgbColor->byDestinationBlue = PULSE_MAX - (uint8_t)(rgb_max - rgb_adj);
        }break;
        default:
        {
            rgbColor->byDestinationRed = PULSE_MAX;
            rgbColor->byDestinationGreen = PULSE_MAX;
            rgbColor->byDestinationBlue = PULSE_MAX;
        }break;
    }
}

void Colorwidget::controlCCT(CtColor_t ct, WyColor_t *wyColor)
{
    uint8_t byTemperature = ct.wCtMireds;

    switch (byTemperature)
    {
        case yellowMax:
        {
            wyColor->byDestinationYellow = PWM_PERIOD - ((((ct.wCtMireds + 256) * PWM_PERIOD) / (yellowMax + 256)) * (ct.fBrighness / LEVEL_MAX));
            wyColor->byDestinationWhite = PULSE_MAX;
        }break;
        case yellowMedium:
        {
            wyColor->byDestinationYellow = PWM_PERIOD - ((((ct.wCtMireds + 256) * PWM_PERIOD) / (yellowMax + 256)) * (ct.fBrighness / LEVEL_MAX));
            wyColor->byDestinationWhite = PWM_PERIOD - (wyColor->byDestinationYellow * (ct.fBrighness / LEVEL_MAX));
        }break;
        case yellowMin:
        {
            wyColor->byDestinationYellow = PWM_PERIOD - ((((ct.wCtMireds + 256) * PWM_PERIOD) / (yellowMax + 256)) * (ct.fBrighness / LEVEL_MAX));
            wyColor->byDestinationWhite = PWM_PERIOD - (wyColor->byDestinationYellow * (ct.fBrighness / LEVEL_MAX));
        }break;
        case yellowNeuter:
        {
            wyColor->byDestinationYellow = PWM_PERIOD - (((ct.wCtMireds  * PWM_PERIOD) / (yellowMax + 256)) * (ct.fBrighness / LEVEL_MAX));
            wyColor->byDestinationWhite = PWM_PERIOD - (wyColor->byDestinationYellow * (ct.fBrighness / LEVEL_MAX));
        }break;
        case whiteMax:
        {
            wyColor->byDestinationWhite = PWM_PERIOD - (((ct.wCtMireds * PWM_PERIOD) / whiteMax) * (ct.fBrighness / LEVEL_MAX));
            wyColor->byDestinationYellow = PULSE_MAX;
        }break;
        case whiteMedium:
        {
            wyColor->byDestinationWhite = PWM_PERIOD - (((ct.wCtMireds * PWM_PERIOD) / whiteMax) * (ct.fBrighness / LEVEL_MAX));
            wyColor->byDestinationYellow = PWM_PERIOD - (wyColor->byDestinationWhite * (ct.fBrighness / LEVEL_MAX));
        }break;
        case whiteMin:
        {
            wyColor->byDestinationWhite = PWM_PERIOD - (((ct.wCtMireds * PWM_PERIOD) / whiteMax) * (ct.fBrighness / LEVEL_MAX));
            wyColor->byDestinationYellow = PWM_PERIOD - (wyColor->byDestinationWhite * (ct.fBrighness / LEVEL_MAX));
        }break;
        case whiteNeuter:
        {
            wyColor->byDestinationWhite = PWM_PERIOD - (((ct.wCtMireds * PWM_PERIOD) / whiteMax) * (ct.fBrighness / LEVEL_MAX));
            wyColor->byDestinationYellow = PWM_PERIOD - (wyColor->byDestinationWhite * (ct.fBrighness / LEVEL_MAX));
        }break;
        default:
        {
            wyColor->byDestinationWhite = PULSE_MAX;
            wyColor->byDestinationYellow = PULSE_MAX;
        }break;
    }
}